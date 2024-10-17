//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BaseWindow.h" resolved

#include "BaseWindow.h"
#include "ui_files/ui_BaseWindow.h"

BaseWindow::BaseWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BaseWindow) {
    ui->setupUi(this);
    manager=new NoteManager();
    initializeGui();
    createdialog = nullptr;
    deletedialog = nullptr;
    renamedialog = nullptr;
}
void BaseWindow::initializeGui() {
    ui->noteeditor->setDisabled(true);
    ui->sizechanger->setDisabled(true);
    ui->showblocked->setVisible(false);
    ui->showfavourite->setVisible(false);
    ui->namelistwidget->addItems(manager->getDefaultNoteList());
    connectSignalsToSlots();
}
void BaseWindow::connectSignalsToSlots() {
    //collega l'evento di cliccaggio del pulsante "newnotebutton" al metodo che ho creato negli slot privati chiamato newNoteClicked
    ui->sizechanger->setValue(ui->noteeditor->currentFont().pointSize());//Il valore iniziale in sizechanger è il font-size di noteeditor
    connect(ui->newnotebutton,&QPushButton::clicked,this,&BaseWindow::newNoteClicked);//associa il segnale clicked di newnotebutton allo slot newNoteClicked()
    connect(ui->namelistwidget, &QListWidget::itemDoubleClicked, this, &BaseWindow::openNote);
    connect(ui->noteeditor,&QTextEdit::textChanged,this, &BaseWindow::saveChanges);//associa il segnale di modifica del testo della nota allo slot saveChanges()
    connect(ui->deletenotebutton,&QPushButton::clicked,this, &BaseWindow::deleteNoteClicked);
    connect(ui->noteeditor,&QTextEdit::selectionChanged,this,&BaseWindow::inTextSelectedCase); //associa il segnale selectionChanged allo slot inTextSelectedCase
    connect(ui->sizechanger,&QSpinBox::valueChanged,this,&BaseWindow::changeSelectedTextSize); //associa il segnale valueChanged allo slot changeSelectedTextSize()
    connect(ui->loadnotebutton,&QPushButton::clicked,this, &BaseWindow::loadNoteClicked); //associa il segnale clicked di uploadnotebutton allo slot loadNoteClicked()
    connect(ui->renamebutton,&QPushButton::clicked,this,&BaseWindow::renameNoteClicked);
    connect(ui->favouritebutton,&QPushButton::clicked,this,&BaseWindow::favouriteClicked);
    connect(ui->blockbutton,&QPushButton::clicked,this,&BaseWindow::blockedClicked);
    connect(ui->searchbar,&QLineEdit::textChanged,this, &BaseWindow::changedSearchBar);
    connect(ui->favouritefilter,&QCheckBox::clicked,this,&BaseWindow::favouriteFilterChanged);
    connect(ui->blockedfilter,&QCheckBox::clicked,this,&BaseWindow::blockedFilterChanged);
}

BaseWindow::~BaseWindow() {
    delete ui;
    delete current;
    delete createdialog;
    delete manager;
    delete deletedialog;
    delete renamedialog;
}


//SLOTS
void BaseWindow::newNoteClicked() {
    createdialog=new NewNoteDialog(this); //come "parent" metto this, ovvero la mia finestra principale basewindow
    //connette il "signal" proveniente dalla finestra di creazione allo slot createNote()
    connect(createdialog, &NewNoteDialog::newNoteNameInsert, this, &BaseWindow::createNote);
    createdialog->exec();   //eseguo la finestra di dialogo
}

void BaseWindow::createNote(const QString& name) {
    bool result=manager->createNewNote(name);
     if(result) //se non esiste già una nota con lo stesso nome aggiungi il nome della nota al namelistwidget
         ui->namelistwidget->addItem(name);
     emit creationConfirm(result); //invia segnale di creationConfirm con il risultato dell'operazione

}

void BaseWindow::deleteNoteClicked() {
    if(current!= nullptr){ //Cancella solo se è selezionata una nota
        deletedialog=new DeleteNoteDialog(this); //Apri la finestra di dialogo per la conferma dell'eliminazione
        connect(deletedialog,&DeleteNoteDialog::confirmDelete,this,&BaseWindow::deleteNote);//Associa lo slot deleteNote() al segnale confirmDelete
        deletedialog->exec();
    }
}

void BaseWindow::deleteNote() {
    QListWidgetItem* notedeleted=ui->namelistwidget->findItems(current->getName(), Qt::MatchExactly).value(0); //Ottieni il QListWidgetItem per eliminarlo poi dalla QListWidget
    if(notedeleted){
        manager->deleteNote(current->getName()); //Elimina la nota utilizzando il nome del selezionato
        ui->namelistwidget->takeItem(ui->namelistwidget->row(notedeleted)); //Elimina la nota dal QListWidget
        delete notedeleted;
        //Deseleziona la nota
        current= nullptr;
        setDefault();
    }
}

void BaseWindow::openNote(QListWidgetItem* n) { //il segnale QListWidget passa come parametro il puntatore al QListWidgetItem selezionato
    current=manager->getNote(n->text()); //con n->text() si indica il nome (in notelistwidget ogni colonna rappresenta il nome di una nota)
    ui->currentnotetext->setText(current->getName());
    ui->noteeditor->setDisabled(false);
    ui->noteeditor->setHtml(current->getText()); //setHtml() e non setText() perché in questo modo il codice Html viene convertito in testo salvaguardando le modifiche grafiche del testo
    ui->showblocked->setVisible(current->isBlocked());
    ui->showfavourite->setVisible(current->isFavourite());
    ui->noteeditor->setReadOnly(current->isBlocked());
}

void BaseWindow::renameNoteClicked() {
    if(current!= nullptr){
        renamedialog=new RenameNoteDialog(current->getName(),this); //Crea una nuova finestra di ridenominazione
        connect(renamedialog, &RenameNoteDialog::newNameInsert, this, &BaseWindow::renameNote); //Associa il segnale newNameInsert allo slot renameNote
        renamedialog->exec(); //Esegue la finestra renamedialog
    }
}

void BaseWindow::renameNote(const QString &oldname,const QString &newname) {
    bool result=manager->renameNote(oldname, newname); //result=true implica nome non in uso (e la modifica del nome in NoteManager è già avvenuta)
    if(result){ //Se il nome non è in uso
        QListWidgetItem* noterenamed=ui->namelistwidget->findItems(oldname, Qt::MatchExactly).value(0); //Ottieni il QListWidgetItem per rinominarlo nella QListWidget
        noterenamed->setText(newname); //Rinomina il QListWidgetItem
        ui->currentnotetext->setText(newname);
    }
    emit renameConfirm(result);//Invia un segnale con l'esito dell'operazione per dire al RenameNoteDialog cosa fare
}

void BaseWindow::loadNoteClicked() {
    QString filepath=QFileDialog::getOpenFileName(this,tr("Apri un file di testo"),"",tr("File di testo (*.txt)")); //In questo modo sarà possibile solo scegliere file .txt
    if(!filepath.isEmpty() && filepath.contains("txt")){ //se ho effettivamente selezionato un file
        QString name=manager->loadNote(filepath);
        if(name!=""){
            ui->namelistwidget->addItem(name);
            QListWidgetItem* loadedwidgetitem=ui->namelistwidget->findItems(name, Qt::MatchExactly).at(0); //trovo il corrispettivo QListWidgetItem
            openNote(loadedwidgetitem); //apro la nota
        }
        else{
            QMessageBox box;
            box.setText("Il nome della nota è già utilizzato");
            box.setWindowTitle("Errore scelta file");
            box.exec();
        }
    }
    else{
        QMessageBox box;
        box.setText("Scelta file non valida");
        box.setWindowTitle("Errore scelta file");
        box.exec();
    }
}

void BaseWindow::favouriteClicked() {
    if(current!=nullptr){
        manager->changeFavouriteStatus(current->getName()); //Alterna nota preferita/nota non preferita
        ui->showfavourite->setVisible(current->isFavourite()); //Mostra la label se è preferita
    }
}


void BaseWindow::blockedClicked() {
    if(current!=nullptr){
        manager->changeBlockedStatus(current->getName()); //Alterna nota preferita/nota non preferita
        ui->showblocked->setVisible(current->isBlocked()); //Mostra la label se è bloccata
        ui->noteeditor->setReadOnly(current->isBlocked()); //Blocca l'editor in caso di nota bloccata
    }
}

void BaseWindow::saveChanges() {
    if(current!= nullptr){
        manager->saveNote(current->getName(),ui->noteeditor->toHtml());
    }
}
/*
 * QTextCursor contiene una serie di informazioni che permettono di trattarlo come un "cursore fittizio". Lo si
 * usa quindi per manipolare un testo in molti modi (come cancellare del testo selezionato, modificarlo, inserire altro
 * testo nella posizione del cursore) o estrarre informazioni da esso (per esempio il font della carattere alla sinistra
 * del cursore).
*/
 void BaseWindow::inTextSelectedCase() {
    ui->sizechanger->blockSignals(true);
     /*
    Dato che sia in if che in esle settiamo un vuovo valore alla QSpinBox sizechanger,
    disabilito temporaneamente i segnali della QSpinBox per evitare che venga chiamato
    lo slot changeSelectedTextSize()
   */
    if(ui->noteeditor->textCursor().selectedText()==nullptr){
        ui->sizechanger->setDisabled(true); //Se non è selezionato nemmeno un carattere allora disabilità sizechanger
        QFont font=ui->noteeditor->textCursor().charFormat().font(); //Ottengo il font riferito alla posizione della barra verticale
        ui->sizechanger->setValue(font.pointSize()); //Modifica comunque il valore in sizechanger in base al formato presente dove si posiziona la barra verticale
    }
    else{
        ui->sizechanger->setDisabled(false); //Se è selezionato almeno un carattere abilita sizechanger
        QFont font=ui->noteeditor->textCursor().charFormat().font();//Ottengo il font del testo selezionato
        //Se si seleziona del testo con DIFFERENTI pointSize(), si considera sempre la grandezza selezionata per ultima
        ui->sizechanger->setValue(font.pointSize());
    }
    ui->sizechanger->blockSignals(false);
}
void BaseWindow::changeSelectedTextSize() {
    QTextCharFormat format; //creo un nuovo formato
    format.setFontPointSize(ui->sizechanger->value()); //imposto il pointsize del nuovo formato
    ui->noteeditor->textCursor().mergeCharFormat(format); //Applico il nuovo formato al testo selezionato
    saveChanges();
}

//metodi per TestBaseWindow
list<QString> BaseWindow::getListWidgetNames() {
    list<QString> names;
    for (int i = 0; i < ui->namelistwidget->count(); ++i)
        names.push_back(ui->namelistwidget->item(i)->text());
    return names;
}
bool BaseWindow::isInNameListWidget(const QString& name) {
    list<QString> namesinlistwidget=getListWidgetNames();
    for(QString n: namesinlistwidget) {
        if(n==name)
            return true;
    }
    return false;
}

QString BaseWindow::getTextNoteSelected() {
    if(current!= nullptr){
        QTextDocument doc;
        doc.setHtml(current->getText()); //In questo modo doc può tradurre il codice html che rappresenta il testo
        QString d=doc.toPlainText();
        return d;
    }
    return nullptr;
}

QString BaseWindow::getCurrentNoteLabelText() {
    return ui->currentnotetext->text();
}

void BaseWindow::setTextForTest(const QString& name,const QString& text) {
    manager->saveNote(name, text);
}

void BaseWindow::setDefault() { //Resetta il noteeditor
    ui->noteeditor->clear();
    ui->noteeditor->setDisabled(true);
    ui->currentnotetext->setText("Nessuna nota aperta");}

void BaseWindow::changedSearchBar() {
    QString searchtext=ui->searchbar->text();
    ui->namelistwidget->clear();
    if(searchtext==""){
        QStringList notenames=manager->getDefaultNoteList();
        ui->namelistwidget->addItems(notenames);
    }
    else{
        QStringList similarnotesname=manager->getSimilarNotes(searchtext);
        ui->namelistwidget->addItems(similarnotesname);
    }
}

void BaseWindow::favouriteFilterChanged() {
    //Todo modificare la QListWidget con le note preferite
}

void BaseWindow::blockedFilterChanged() {
//Todo modificare la QListWidget con le note bloccate
}



