//
// Created by nicco on 02/09/2024.
//

#ifndef DENOTE_TESTNOTEMANAGER_H
#define DENOTE_TESTNOTEMANAGER_H
#include <QtTest/QTest>
#include "../NoteManager.h"

class TestNoteManager:public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testCreateNote();
    void testDeleteNote();
    void testNotExistingNote();
    void testSaveNote();
    void testChangeFavouriteStatus();
    void testChangeBlockedStatus();
    void testRenameNote();
    void testGetNote();
    void testGetNumberOfNotes();
    void cleanupTestCase();
private:
    NoteManager* manager;
};


#endif //DENOTE_TESTNOTEMANAGER_H
