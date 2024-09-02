//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_NewNoteDialog.h" resolved

#include "NewNoteDialog.h"
#include "ui_files/ui_NewNoteDialog.h"
#include "BaseWindow.h"

NewNoteDialog::NewNoteDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::NewNoteDialog) {
    ui->setupUi(this);
    //metodo che connette il pulsante di conferma di creazione con il suo metodo associato
    connect(ui->notecreationbutton,&QPushButton::clicked,this,&NewNoteDialog::noteCreationButtonClicked);
}

NewNoteDialog::~NewNoteDialog() {
    delete ui;
}

void NewNoteDialog::noteCreationButtonClicked() {
    if(ui->notetitlebox->text().isEmpty())
        ui->errorcreationlabel->setText("ERRORE: Devi inserire un nome");
    else{
        BaseWindow* b= dynamic_cast<BaseWindow*>(this->parent());
        connect(b, &BaseWindow::creationConfirm, this, &NewNoteDialog::receiveCreationConfirm);
        emit newNoteNameInsert(ui->notetitlebox->text()); //emetti il segnale di conferma creazione finestra
    }
}
void NewNoteDialog::receiveCreationConfirm(bool found) {
    if(!found) //Se !found==true Nota creata correttamente
        close(); //chiude la finestra di dialogo della creazione della nota
    else
        ui->errorcreationlabel->setText("ERRORE: Nome già usato");

}
QLineEdit* NewNoteDialog::getNoteTitleBox() {
    return ui->notetitlebox;
}

QLabel *NewNoteDialog::getErrorCreationLabel() {
    return ui->errorcreationlabel;
}

QPushButton *NewNoteDialog::getNoteCreationButton() {
    return ui->notecreationbutton;
}



