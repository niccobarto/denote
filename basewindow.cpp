//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BaseWindow.h" resolved

#include "basewindow.h"
#include "cmake-build-debug/denote_autogen/include/ui_files/ui_BaseWindow.h"


BaseWindow::BaseWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::BaseWindow) {
    ui->setupUi(this);
}

BaseWindow::~BaseWindow() {
    delete ui;
}
