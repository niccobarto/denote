//
// Created by nicco on 07/08/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_DeleteNoteDialog.h" resolved

#include "deletenotedialog.h"
#include "ui_files/ui_DeleteNoteDialog.h"


DeleteNoteDialog::DeleteNoteDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::DeleteNoteDialog) {
    ui->setupUi(this);
}

DeleteNoteDialog::~DeleteNoteDialog() {
    delete ui;
}
