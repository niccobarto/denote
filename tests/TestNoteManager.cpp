//
// Created by nicco on 02/09/2024.
//

#include "TestNoteManager.h"


void TestNoteManager::initTestCase() {
    manager=new NoteManager();
}

void TestNoteManager::testCreateNote() {
    QString n="nota1";
    manager->createNewNote(n);
    QCOMPARE(manager->getNote(n)->getName(),n);
}

void TestNoteManager::testDeleteNote() {
    QString noteselected="nota1";
    manager->deleteNote(noteselected);

}

void TestNoteManager::testSaveNote() {
    QString n="nota2";
    manager->createNewNote(n);
    QString text="La lista della spesa: carote,cipolle,pasta";
    manager->saveNote(n,text);
    QCOMPARE(manager->getNote(n)->getText(),text);
}

void TestNoteManager::cleanupTestCase() {
    delete manager;
}


