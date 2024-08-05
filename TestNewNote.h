//
// Created by nicco on 31/07/2024.
//

#ifndef DENOTE_TESTNEWNOTE_H
#define DENOTE_TESTNEWNOTE_H
#include "NewNoteDialog.h"
#include <QLineEdit>
#include <QtTest/QTest>
class TestNewNote:public QObject {
    Q_OBJECT
private slots:

    void testEmptyName(); //test in caso di nota senza nome
    void testNoteCreation();
private:
    NewNoteDialog* dialog;

};


#endif //DENOTE_TESTNEWNOTE_H
