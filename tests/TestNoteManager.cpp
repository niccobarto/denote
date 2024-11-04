//
// Created by nicco on 02/09/2024.
//

#include "TestNoteManager.h"


void TestNoteManager::initTestCase() {
    manager=new NoteManager("../tests/testsnotes");
}

void TestNoteManager::testCreateNote() {
    QString name="testcreate";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
}

void TestNoteManager::testGetNumberOfNotes() {
    QString name="testnumbercount";
    manager->createNewNote(name);

    QString name1="testfavouritecount";
    manager->createNewNote(name1);
    manager->changeFavouriteStatus(name1);

    QString name2="testblockedcount";
    manager->createNewNote(name2);
    manager->changeBlockedStatus(name2);

    QString name3="testfavouriteblockedcount";
    manager->createNewNote(name3);
    manager->changeBlockedStatus(name3);


    QCOMPARE(manager->getTotalNumber(),manager->getNoteListSize()); //Mi aspetto che il numero totale di note sia pari alla dimensione della lista di note
    QCOMPARE(manager->getFavNumber(),manager->getFavouriteListSize()); //Mi aspetto che il numero di note preferite sia pari alla dimensione della lista di note preferite
    QCOMPARE(manager->getBlockNumber(),manager->getBlockedListSize()); //Mi aspetto che il numero di note bloccate sia pari alla dimensione della lista di note bloccate
}

void TestNoteManager::testDeleteNote() {
    QString name="testdelete";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
    if(manager->isNameUsed(name)){
        manager->deleteNote(name);
        QVERIFY(!manager->isNameUsed(name)); //Mi aspetto un false perché non deve essere usato
    }
}

void TestNoteManager::testNotExistingNote() {
    QString name="testexisting";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
    if(manager->isNameUsed(name)){
        QString rename="testexistingABCABC";
        manager->renameNote(name,rename);
        if(manager->isNameUsed(rename)){ //In questo modo so che non esiste nessun nota con il nome "testexisting"
            QCOMPARE(manager->getNote(name),nullptr);
        }
    }
}

void TestNoteManager::testSaveNote() {
    QString name="testsave";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
    QString text="La lista della spesa: carote,cipolle,pasta";
    if(manager->isNameUsed(name)) {
        manager->saveNote(name, text);
        QCOMPARE(manager->getNote(name)->getText(), text);
    }
}
void TestNoteManager::testChangeFavouriteStatus() {
    QString name="testfavourite";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
    if(manager->isNameUsed(name)){
        QCOMPARE(manager->getNote(name)->getName(),name);
        Note* n=manager->getNote(name);
        bool previousfavstatus=n->isFavourite();
        manager->changeFavouriteStatus(name);
        QCOMPARE(n->isFavourite(),!previousfavstatus); //cioè verifico se lo stato è cambiato
        manager->changeFavouriteStatus(name);
        QCOMPARE(n->isFavourite(),previousfavstatus); //ora verifico se lo stato è tornato al precedente
    }
}

void TestNoteManager::testChangeBlockedStatus() {
    QString name="testblocked";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
    if(manager->isNameUsed(name)) {
        Note* n=manager->getNote(name);
        bool prevblockstatus=n->isBlocked();
        manager->changeBlockedStatus(name);
        QCOMPARE(n->isBlocked(),!prevblockstatus); //cioè verifico se lo stato è cambiato
        manager->changeBlockedStatus(name);
        QCOMPARE(n->isBlocked(),prevblockstatus); //cioè verifico se lo stato è cambiato
    }
}

void TestNoteManager::testRenameNote() {
    QString oldname="testrename";
    manager->createNewNote(oldname);
    QCOMPARE(manager->getNote(oldname)->getName(),oldname);
    if(manager->isNameUsed(oldname)){
        QString rename="testrenameABCABC";
        Note* n=manager->getNote(oldname);
        manager->renameNote(oldname,rename);
        QCOMPARE(n->getName(),rename);
    }
}

void TestNoteManager::testGetNote(){
    QString name="testgetnote";
    manager->createNewNote(name);
    QCOMPARE(manager->getNote(name)->getName(),name);
}

void TestNoteManager::cleanupTestCase() {
    for(QString name:manager->getAllNotesName())
        manager->deleteNote(name);
    delete manager;
}


