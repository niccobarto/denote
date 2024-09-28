//
// Created by nicco on 26/09/2024.
//

#include "RenameNoteDialog.h"
#include "ui_files/ui_RenameNoteDialog.h"
#include "BaseWindow.h"

RenameNoteDialog::RenameNoteDialog(QString& name,QWidget *parent):
    QDialog(parent), ui(new Ui::RenameNoteDialog) {
    ui->setupUi(this);
    ui->currentnotetext->setText(name);
    oldname=ui->currentnotetext->text();
    connect(ui->confirm,&QPushButton::clicked,this,&RenameNoteDialog::confirmRenameButtonClicked);
    connect(ui->cancel,&QPushButton::clicked,this,&RenameNoteDialog::cancelClicked);
}
RenameNoteDialog::~RenameNoteDialog() {
    delete ui;
}

void RenameNoteDialog::confirmRenameButtonClicked() {
    if(ui->currentnotetext->text().isEmpty()){
        ui->errorlabel->setText("ERRORE: Devi inserire un nome");
    }
    else{
        BaseWindow* father= dynamic_cast<BaseWindow*>(this->parent());
        connect(father, &BaseWindow::renameConfirm, this, &RenameNoteDialog::receiveRenameConfirm); //associa il segnale creationConfrm() emesso da father allo slot receiveCreationConfirm()
        emit newNameInsert(oldname,ui->currentnotetext->text());
    }

void RenameNoteDialog::cancelClicked() {
    close();
    delete this;
}

void RenameNoteDialog::receiveRenameConfirm(bool result) {
    if(result){
        close();
        delete this;
    }
    else{
        ui->errorlabel->setText("ERRORE: Questo nome già in uso");
    }

}

void RenameNoteDialog::cancelClicked() {
    close();
}
