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
        BaseWindow* father= dynamic_cast<BaseWindow*>(this->parent());
        connect(father, &BaseWindow::creationConfirm, this, &NewNoteDialog::receiveCreationConfirm); //associa il segnale creationConfrm() emesso da father allo slot receiveCreationConfirm()
        emit newNoteNameInsert(ui->notetitlebox->text()); //emetti il segnale di conferma creazione finestra newNoteNameInsert e passando come parametro il nome scritto
    }
}
void NewNoteDialog::receiveCreationConfirm(bool found) {
    if(!found){
        close(); //chiude la finestra di dialogo della creazione della nota
    } //Se !found==true Nota creata correttamente
    else
        ui->errorcreationlabel->setText("ERRORE: Nome già usato");

}
QLineEdit* NewNoteDialog::getNoteTitleBox() {
    return ui->notetitlebox;
}

QLabel* NewNoteDialog::getErrorCreationLabel() {
    return ui->errorcreationlabel;
}

QPushButton* NewNoteDialog::getNoteCreationButton() {
    return ui->notecreationbutton;
}



