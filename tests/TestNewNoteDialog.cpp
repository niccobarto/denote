//
// Created by nicco on 06/09/2024.
//

#include "TestNewNoteDialog.h"

void TestNewNoteDialog::initTestCase() {
    father=new BaseWindow();
    dialog=new NewNoteDialog(father);
    //Simuliamo BaseWindow::newNoteClicked() poiché non vogliamo aprire la dialog
}
void TestNewNoteDialog::testInvalidNameInsert() {
    //Simuliamo BaseWindow::newNoteClicked() poiché non vogliamo aprire la dialog
    connect(dialog, &NewNoteDialog::newNoteNameInsert, father, &BaseWindow::createNote);

    //Testiamo il caso di nome non inserito
    (dialog->getNoteTitleBox())->clear();
    dialog->noteCreationButtonClicked(); //Simulo il click del pulsante notecreationbutton
    QCOMPARE(dialog->getErrorCreationLabel()->text(),"ERRORE: Devi inserire un nome");

    //Testiamo il caso di nome inserito già presente
    QString name="nota1";
    father->createNote(name); //Creo una prima nota con questo nome senza l'utilizzo di NewNoteDialog, come se fosse già stata creata
    (dialog->getNoteTitleBox())->setText(name);
    dialog->noteCreationButtonClicked(); //Simulo il click del pulsante notecreationbutton
    QCOMPARE(dialog->getErrorCreationLabel()->text(),"ERRORE: Questo nome è già in uso");
}

void TestNewNoteDialog::testValidNameInsert() {
    //Simuliamo BaseWindow::newNoteClicked() poiché non vogliamo aprire la dialog
    connect(dialog, &NewNoteDialog::newNoteNameInsert, father, &BaseWindow::createNote);

    QString name="nota2";
    (dialog->getNoteTitleBox())->setText(name);
    dialog->noteCreationButtonClicked(); //Simulo il click del pulsante notecreationbutton
    QVERIFY(!dialog->isVisible()); //Todo: non è l'approccio migliore al controllo della chiusura della finestra
}

void TestNewNoteDialog::cleanupTestCase() {
 delete father;
}
