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
    QVERIFY(!confirmsignal.at(0).value<bool>());//Mi aspetto che il valore passato come parametro dal segnale creationConfirm sia false
    QVERIFY(base->isInNameListWidget(name));//Mi aspetto che base abbia aggiunto un nuovo nome alla namelistwidget

    //Testiamo il caso di nome già presente
    base->createNote(name);
    confirmsignal=spy.takeFirst();
    QVERIFY(confirmsignal.at(0).value<bool>());//Ora mi aspetto che il parametro sia true
    QVERIFY(base->isInNameListWidget(name));//Mi aspetto che ci sia un nome nota1 nella nemelistwidget
}

void TestBaseWindow::testOpenNote() {

}

void TestBaseWindow::testDeleteNoteClicked() {

}

void TestBaseWindow::cleanupTestCase() {
    delete base;
}
