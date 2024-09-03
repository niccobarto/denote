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
    //collega l'evento di cliccaggio del pulsante "newnotebutton" al metodo che ho creato negli slot privati chiamato newNoteClicked
    connect(ui->newnotebutton,&QPushButton::clicked,this,&BaseWindow::newNoteClicked);
    connect(ui->namelistwidget, &QListWidget::itemDoubleClicked, this, &BaseWindow::openNote);
    connect(ui->savebutton,&QPushButton::clicked,this,&BaseWindow::save);
    connect(ui->deletenotebutton,&QPushButton::clicked,this, &BaseWindow::deleteNoteClicked);
}

BaseWindow::~BaseWindow() {
    delete ui;
}


//SLOTS
void BaseWindow::newNoteClicked() {
    NewNoteDialog createdialog(this); //come "parent" metto this, ovvero la mia finestra principale basewindow

    //connette il "signal" proveniente dalla finestra di creazione allo slot createNote
    connect(&createdialog, &NewNoteDialog::newNoteNameInsert, this, &BaseWindow::createNote);
    createdialog.exec();   //eseguo la finestra di dialogo
}

void BaseWindow::createNote( QString name) {
    bool found=manager->createNewNote(name);
     if(!found) //se non esiste già una nota con lo stesso nome aggiungi il nome della nota al namelistwidget
         ui->namelistwidget->addItem(name);
    emit creationConfirm(found); //invia segnale di creationConfirm con il risultato dell'operazione

}

void BaseWindow::openNote(QListWidgetItem* n) {
    current=manager->getNote(n->text());
    ui->noteeditor->setDisabled(false);
    ui->currentnotelabel->setText(current->getName());
    ui->noteeditor->setText(current->getText());
}

void BaseWindow::save() {
     if(current!= nullptr){
         manager->saveNote(current->getName(),ui->noteeditor->toHtml());
     }
}

void BaseWindow::deleteNoteClicked() {
    if(current!= nullptr){
        DeleteNoteDialog deletedialog(this);
        connect(&deletedialog,&DeleteNoteDialog::confirmDelete,this,&BaseWindow::deleteNote);
        deletedialog.exec();
    }

}

void BaseWindow::deleteNote() {
    manager->deleteNote(current->getName());
    QListWidgetItem* notedeleted=ui->namelistwidget->findItems(current->getName(), Qt::MatchExactly).value(0);
    if(notedeleted){
        ui->namelistwidget->takeItem(ui->namelistwidget->row(notedeleted));
        delete notedeleted;
        current= nullptr;
        ui->noteeditor->clear();
        ui->noteeditor->setDisabled(true);
        ui->currentnotelabel->setText("Nessuna nota aperta");
    }
}
//getter per i test
QPushButton *BaseWindow::getNewNoteButton() {
    return ui->newnotebutton;
}

list<QString> BaseWindow::getListWidgetNames() {
    list<QString> names;
    for (int i = 0; i < ui->namelistwidget->count(); ++i)
        names.push_back(ui->namelistwidget->item(i)->text());
    return names;
}

bool BaseWindow::isInNameListWidget(QString& name) {
    list<QString> namesinlistwidget=getListWidgetNames();
    for (QString n: namesinlistwidget) {
        if(n==name)
            return true;
    }
    return false;
}


