//
// Created by nicco on 10/05/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_NewNoteDialog.h" resolved

#include "NewNoteDialog.h"
#include "ui_files/ui_NewNoteDialog.h"


NewNoteDialog::NewNoteDialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::NewNoteDialog) {
    ui->setupUi(this);
    ui->errorcreationlabel->setVisible(false); //ToDo setto l'invisibilità qui perché non sono riuscito a farlo direttamente da qtCreator. Da cambiare pià avanti
    //metodo che connette il pulsante di conferma di creazione con il suo metodo associato
    connect(ui->notecreationbutton,&QPushButton::clicked,this,&NewNoteDialog::noteCreationButtonClicked);
}

NewNoteDialog::~NewNoteDialog() {
    delete ui;
}

void NewNoteDialog::noteCreationButtonClicked() {
    if(ui->notetitlebox->text()=="")
        ui->errorcreationlabel->setVisible(true);
    else{

        this->close(); //chiude la finestra di dialogo della creazione della nota
    }
}