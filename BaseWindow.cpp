//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BaseWindow.h" resolved

#include "BaseWindow.h"
#include "ui_files/ui_BaseWindow.h"

BaseWindow::BaseWindow(NoteManager* n,QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BaseWindow) {
    ui->setupUi(this);
    manager=n;
    manager->addObserver(this);
    colordialog=new QColorDialog(this);
    update();
    initializeGui();
    connectSignalsToSlots();
    createdialog = nullptr;
    deletedialog = nullptr;
    renamedialog = nullptr;
}
void BaseWindow::initializeGui() {
    ui->noteeditor->setDisabled(true);
    ui->sizechanger->setDisabled(true);
    ui->showblocked->setVisible(false);
    ui->showfavourite->setVisible(false);
    QStringList names=manager->getAllNotesName();
    for(QString name:names)
        addToNameListWidget(name);
    move(screen()->geometry().center() - frameGeometry().center());
    QWidget::setWindowTitle("Denote");
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
    connect(ui->searchbar,&QLineEdit::textChanged,this, &BaseWindow::updateNameListWidget);
    connect(ui->favouritefilter,&QCheckBox::clicked,this,&BaseWindow::updateNameListWidget);
    connect(ui->blockedfilter,&QCheckBox::clicked,this,&BaseWindow::updateNameListWidget);
    connect(ui->colorbutton,&QPushButton::clicked,this,&BaseWindow::changeColorClicked);
}

BaseWindow::~BaseWindow() {
    manager->removeObserver(this);
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
         updateNameListWidget();
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
    manager->deleteNote(current->getName()); //Elimina la nota utilizzando il nome del selezionato
    updateNameListWidget();
    //Deseleziona la nota
    current= nullptr;
    setDefault();
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

void BaseWindow::renameNote(QString &oldname,const QString &newname) {
    bool result=manager->renameNote(oldname, newname); //result=true implica nome non in uso (e la modifica del nome in NoteManager è già avvenuta)
    if(result){ //Se il nome non è in uso
        updateNameListWidget();
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
        updateNameListWidget();
    }
}


void BaseWindow::blockedClicked() {
    if(current!=nullptr){
        manager->changeBlockedStatus(current->getName()); //Alterna nota preferita/nota non preferita
        ui->showblocked->setVisible(current->isBlocked()); //Mostra la label se è bloccata
        ui->noteeditor->setReadOnly(current->isBlocked()); //Blocca l'editor in caso di nota bloccata
        updateNameListWidget();
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

void BaseWindow::changeColorClicked() {
    colordialog->exec();
    QColor color=colordialog->currentColor(); //Ottengo il colore selezionato
    QTextCharFormat format;
    format.setForeground(QBrush(color)); //Imposto il colore del testo
    ui->noteeditor->textCursor().mergeCharFormat(format); //Applico il colore al testo selezionato
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
    ui->currentnotetext->setText("Nessuna nota aperta");
}

void BaseWindow::addToNameListWidget(const QString &name) { //Per ogni nome da inserire nella namelistwidget crea l'appropriato QListWidgetItem
    QListWidgetItem* item=new QListWidgetItem(name);
    if(manager->getNote(name)->isBlocked())
        item->setForeground(QBrush(QColor(Qt::blue)));
    if(manager->getNote(name)->isFavourite()){
        item->setIcon(QIcon::fromTheme("emblem-favorite"));
        ui->namelistwidget->insertItem(0,item);
    }
    else
        ui->namelistwidget->addItem(item);
}

void BaseWindow::updateNameListWidget() {
    QStringList namesbyfilter=getFilteredNameList();
    ui->namelistwidget->clear();
    setNameListWidget(namesbyfilter);
}

QStringList BaseWindow::getFilteredNameList() { //restituisce la lista di nomi adeguati ai filtri scelti
    if(ui->favouritefilter->isChecked() && ui->blockedfilter->isChecked())
        return manager->getFavBlockNotes();
    else if(ui->favouritefilter->isChecked())
        return manager->getFavouriteNotes();
        else if(ui->blockedfilter->isChecked())
            return manager->getBlockedNotes();
        else
            return manager->getAllNotesName();
}

void BaseWindow::setNameListWidget(QStringList &names) { //Aggiorna la namelistwidget con i nomi che rispettano tutti i filtri, sia in base al nome che alle preferenze
     if(ui->searchbar->text().isEmpty()){
         for(QString name: names)
             addToNameListWidget(name);
     }
     else{
         for(QString name: names){
             if(name.contains(ui->searchbar->text()))
                 addToNameListWidget(name);
         }
     }
}

void BaseWindow::update() {
    ui->ntotal->setText(QString::number(manager->getTotalNumber()));
    ui->nfavourite->setText(QString::number(manager->getFavNumber()));
    ui->nblocked->setText(QString::number(manager->getBlockNumber()));
}





