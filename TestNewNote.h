//
// Created by nicco on 31/07/2024.
//

#ifndef DENOTE_TESTNEWNOTE_H
#define DENOTE_TESTNEWNOTE_H
#include "NewNoteDialog.h"
#include "BaseWindow.h"
#include <QLineEdit>
#include <QtTest/QTest>
class TestNewNote:public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testNoteCreation(); //test di creazione della nota
    void testEmptyName(); //test in caso di nota senza nome


private:
    NewNoteDialog* dialog;
    BaseWindow* base;
};


#endif //DENOTE_TESTNEWNOTE_H
