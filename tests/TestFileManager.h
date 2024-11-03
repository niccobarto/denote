//
// Created by nicco on 29/10/2024.
//

#ifndef DENOTE_TESTFILEMANAGER_H
#define DENOTE_TESTFILEMANAGER_H
#include <QtTest/QTest>
#include "../FileManager.h"

class TestFileManager : public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testGetFileContent();
    void testCreateNoteFile();
    void testSaveFile();
    void testReadFileLoaded();
    void cleanupTestCase();
private:
    FileManager* manager;
};


#endif //DENOTE_TESTFILEMANAGER_H
