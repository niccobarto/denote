//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_NewNoteDialog.h" resolved

#include "NewNoteDialog.h"
#include "ui_files/ui_NewNoteDialog.h"


NewNoteDialog::NewNoteDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::NewNoteDialog) {
    ui->setupUi(this);
}

NewNoteDialog::~NewNoteDialog() {
    delete ui;
}
