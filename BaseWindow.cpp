//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BaseWindow.h" resolved

#include "BaseWindow.h"
#include "ui_files/ui_BaseWindow.h"
#include "NewNoteDialog.h"
#include "DeleteNoteDialog.h"

BaseWindow::BaseWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BaseWindow) {
    ui->setupUi(this);
    ui->noteeditor->setDisabled(true);
    ui->sizechanger->setDisabled(true);
    //collega l'evento di cliccaggio del pulsante "newnotebutton" al metodo che ho creato negli slot privati chiamato newNoteClicked
    ui->sizechanger->setValue(ui->noteeditor->currentFont().pointSize());//Il valore iniziale in sizechanger è il font-size di noteeditor
    connect(ui->newnotebutton,&QPushButton::clicked,this,&BaseWindow::newNoteClicked);//associa il segnale clicked di newnotebutton allo slot newNoteClicked()
    connect(ui->namelistwidget, &QListWidget::itemDoubleClicked, this, &BaseWindow::openNote);
    connect(ui->savebutton,&QPushButton::clicked,this, &BaseWindow::saveClicked);//associa il segnale clicked di savebutton allo slot saveClicked()
    connect(ui->deletenotebutton,&QPushButton::clicked,this, &BaseWindow::deleteNoteClicked);
    connect(ui->noteeditor,&QTextEdit::selectionChanged,this,&BaseWindow::isTextSelected); //associa il segnale selectionChanged allo slot isTextSelected
    connect(ui->sizechanger,&QSpinBox::valueChanged,this,&BaseWindow::changeSelectedTextSize); //associa il segnale valueChanged allo slot changeSelectedTextSize()
    connect(ui->loadnotebutton,&QPushButton::clicked,this, &BaseWindow::loadNoteClicked); //associa il segnale clicked di uploadnotebutton allo slot loadNoteClicked()
}

BaseWindow::~BaseWindow() {
    delete ui;
    delete current;
    delete createdialog;
    delete manager;
}


//SLOTS
void BaseWindow::newNoteClicked() {
    createdialog=new NewNoteDialog(this); //come "parent" metto this, ovvero la mia finestra principale basewindow
    //connette il "signal" proveniente dalla finestra di creazione allo slot createNote()
    connect(createdialog, &NewNoteDialog::newNoteNameInsert, this, &BaseWindow::createNote);
    createdialog->exec();   //eseguo la finestra di dialogo
}

void BaseWindow::createNote(const QString& name) {
    bool found=manager->createNewNote(name);
     if(!found) //se non esiste già una nota con lo stesso nome aggiungi il nome della nota al namelistwidget
         ui->namelistwidget->addItem(name);

     emit creationConfirm(found); //invia segnale di creationConfirm con il risultato dell'operazione

}

void BaseWindow::openNote(QListWidgetItem* n) { //il segnale QListWidget passa come parametro il puntatore al QListWidgetItem selezionato
    current=manager->getNote(n->text()); //con n->text() si indica il nome (in notelistwidget ogni colonna rappresenta il nome di una nota)
    ui->noteeditor->setDisabled(false);
    ui->currentnotelabel->setText(current->getName());
    ui->noteeditor->setText(current->getText());
}

void BaseWindow::saveClicked() {
     if(current!= nullptr){
         manager->saveNote(current->getName(),ui->noteeditor->toHtml());
     }
}

void BaseWindow::deleteNoteClicked() {
    if(current!= nullptr){ //Cancella solo se è selezionata una nota
        DeleteNoteDialog deletedialog(this); //Apri la finestra di dialogo per la conferma dell'eliminazione
        connect(&deletedialog,&DeleteNoteDialog::confirmDelete,this,&BaseWindow::deleteNote);//Associa lo slot deleteNote() al segnale confirmDelete
        deletedialog.exec();
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
        ui->noteeditor->clear();
        ui->noteeditor->setDisabled(true);
        ui->currentnotelabel->setText("Nessuna nota aperta");
    }
}
/*
 * QTextCursor contiene una serie di informazioni che permettono di trattarlo come un "cursore fittizio". Lo si
 * usa quindi per manipolare un testo in molti modi (come cancellare del testo selezionato, modificarlo, inserire altro
 * testo nella posizione del cursore) o estrarre informazioni da esso (per esempio il font della carattere alla sinistra
 * del cursore).
*/
 void BaseWindow::isTextSelected() {
    ui->sizechanger->blockSignals(true);
     /*
    Dato che sia in if che in esle settiamo un vuovo valore alla QSpinBox sizechanger,
    disabilito temporaneamente i segnali della QSpinBox per evitare che venga chiamato
    lo slot changeSelectedTextSize()
   */
    if(ui->noteeditor->textCursor().selectedText()==nullptr){
        ui->sizechanger->setDisabled(true); //Se non è selezionato nemmeno un carattere allora disabilità sizechanger
        QFont font=ui->noteeditor->textCursor().charFormat().font(); //Ottendo il font riferito alla posizione della barra verticale
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
}

void BaseWindow::loadNoteClicked() {
    QString filepath=QFileDialog::getOpenFileName(this,tr("Apri un file di testo"),"",tr("File di testo (*.txt)")); //In questo modo sarà possibile solo scegliere file .txt
    if(!filepath.isEmpty() && filepath.contains("txt")){ //se ho effettivamente selezionato un file
        QFile file(filepath); //creo un QFile associandolo dando il path del file
        file.open(QIODevice::ReadOnly); //apro il file in modalità lettura
        QTextStream reader(&file); //con QTextStream posso leggere il contenuto
        QFileInfo f(file); //Con QFileInfo posso ottenere il nome del singolo file e non la path completa
        QString name=f.fileName(); //Leggo il nome del file
        QString text=reader.readAll(); //Leggo il file selezionato
        file.close(); //chiudo il file
        createNote(name); //creo la nota con il nome del file
        QListWidgetItem* loadedwidgetitem=ui->namelistwidget->findItems(name, Qt::MatchExactly).at(0); //trovo il corrispettivo QListWidgetItem
        openNote(loadedwidgetitem); //apro la nota
        ui->noteeditor->setText(text); //inserisco il testo nel noteeditor
        saveClicked(); //salvo
    }
    else{
        QMessageBox box;
        box.setText("Scelta file non valida");
        box.setWindowTitle("Errore scelta file");
        box.exec();
    }
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
    for (QString n: namesinlistwidget) {
        if(n==name)
            return true;
    }
    return false;
}

QString BaseWindow::getTextNoteSelected() {
    if(current!= nullptr)
        return current->getText();
    return nullptr;
}

QString BaseWindow::getCurrentNoteLabelText() {
    return ui->currentnotelabel->text();
}

void BaseWindow::setTextForTest(const QString& name,const QString& text) {
    manager->saveNote(name, text);
}



