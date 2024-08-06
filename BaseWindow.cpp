//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BaseWindow.h" resolved

#include "BaseWindow.h"
#include "ui_files/ui_BaseWindow.h"
#include "NewNoteDialog.h"

BaseWindow::BaseWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BaseWindow) {
    ui->setupUi(this);
    ui->noteeditor->setDisabled(true);
    //collega l'evento di cliccaggio del pulsante "newnotebutton" al metodo che ho creato negli slot privati chiamato newNoteClicked
    connect(ui->newnotebutton,&QPushButton::clicked,this,&BaseWindow::newNoteClicked);
    connect(ui->notelist,&QListWidget::itemDoubleClicked,this,&BaseWindow::openNote);
    connect(ui->savebutton,&QPushButton::clicked,this,&BaseWindow::save);
}

BaseWindow::~BaseWindow() {
    delete ui;
}


//SLOTS
void BaseWindow::newNoteClicked() {
    NewNoteDialog createDialog(this); //come "parent" metto this, ovvero la mia finestra principale basewindow

    //connette il "signal" proveniente dalla finestra di creazione allo slot createNote
    connect(&createDialog, &NewNoteDialog::noteConfirmed, this, &BaseWindow::createNote);
    createDialog.exec();   //eseguo la finestra di dialogo
}

void BaseWindow::createNote( QString name) {
    manager->createNewNote(name);
    ui->notelist->addItem(name);
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


