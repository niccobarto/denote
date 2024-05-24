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

    //collega l'evento di cliccaggio del pulsante "newnotebutton" al metodo che ho creato negli slot privati chiamato newNoteClicked
    connect(ui->newnotebutton,&QPushButton::clicked,this,&BaseWindow::newNoteClicked);
}

BaseWindow::~BaseWindow() {
    delete ui;
}

void BaseWindow::newNoteClicked() {
    NewNoteDialog createdialog(this); //come parent do this, ovvero la mia finestra principale basewindow

    //connette il segnale proveniente dalla finestra di creazione allo slot createNote
    connect(&createdialog,&NewNoteDialog::noteConfirmed,this,&BaseWindow::createNote);
    createdialog.exec();   //eseguo la finestra di dialogo
}

void BaseWindow::createNote( QString name) {
    manager->createNewNote(name);
}


