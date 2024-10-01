//
// Created by nicco on 03/09/2024.
//

#include "TestBaseWindow.h"
#include <QSignalSpy>
void TestBaseWindow::initTestCase() {
base=new BaseWindow();
}

void TestBaseWindow::testCreateNote() {
    //Testiamo il caso di nome NON già presente
    QString name="nota1";
    QSignalSpy spy(base, &BaseWindow::creationConfirm); //raccogli il segnale creationConfirm emesso da createNote()
    base->createNote(name);
    QList<QVariant> confirmsignal=spy.takeFirst(); //preleva il primo (e l'unico) segnale emesso da createNote
    QVERIFY(confirmsignal.at(0).value<bool>());//Mi aspetto che il valore passato come parametro dal segnale creationConfirm sia true
    QVERIFY(base->isInNameListWidget(name));//Mi aspetto che base abbia aggiunto un nuovo nome alla namelistwidget

    //Testiamo il caso di nome già presente
    base->createNote(name);
    confirmsignal=spy.takeFirst();
    QVERIFY(!confirmsignal.at(0).value<bool>());//Ora mi aspetto che il parametro sia false
    QVERIFY(base->isInNameListWidget(name));//Mi aspetto che ci sia un nome nota1 nella nemelistwidget
}

void TestBaseWindow::testOpenNote() {
    /*
     Per testare OpenNote devo salvare del testo senza utilizzare OpenNote per salvarlo.
     Infatti BaseWindow::saveNote() si basa sul puntatore current che viene modificato
     in BaseWindow::openNote(). Per testare openNote quindi devo cambiare current (per
     cambiare il testo) in maniera diretta
    */
    QString faketext="Lista della spesa: carote,pasta,pane...";
    QString name="nota1";
    base->setTextForTest(name,faketext);
    nameselected=new QListWidgetItem();
    nameselected->setText(name); //so che è presente in namelistwidget
    base->openNote(nameselected);
    QCOMPARE(base->getTextNoteSelected(),faketext);//mi aspetto che nel noteeditor sia presente il testo della che ho selezionato
    QCOMPARE(base->getCurrentNoteLabelText(),nameselected->text());//mi aspetto che la label che mostra quale nota è aperta mostri quella corretta
}

void TestBaseWindow::testDeleteNoteClicked() {
    nameselected=new QListWidgetItem();
    QString name="nota1";
    nameselected->setText(name);
    base->openNote(nameselected);
    base->deleteNote();
    QVERIFY(!base->isInNameListWidget(name));//Mi aspetto che questo nome non ci sia nel namelistwidget
    QCOMPARE(base->getCurrentNoteLabelText(),"Nessuna nota aperta");

}

void TestBaseWindow::cleanupTestCase() {
    delete base;
    delete nameselected;
}
