//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BaseWindow.h" resolved

#include "basewindow.h"
#include "ui_files/ui_BaseWindow.h"


BaseWindow::BaseWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BaseWindow) {
    ui->setupUi(this);

    //collega l'evento di cliccaggio del pulsante "newnotebutton" al metodo che ho creato negli slot privati chiamato newNoteClicked
    connect(ui->newnotebutton,&QPushButton::clicked,this,&BaseWindow::newNoteClicked);
}

BaseWindow::~BaseWindow() {
    delete ui;
}


