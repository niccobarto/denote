//
// Created by nicco on 06/09/2024.
//

#ifndef DENOTE_TESTNEWNOTEDIALOG_H
#define DENOTE_TESTNEWNOTEDIALOG_H
#include <QtTest/QTest>
#include "../NewNoteDialog.h"
#include "../BaseWindow.h"

class TestNewNoteDialog:public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testInvalidNameInsert();
    void testValidNameInsert();
    void cleanupTestCase();
private:
    NewNoteDialog* dialog;
    BaseWindow* father;
};

#endif //DENOTE_TESTNEWNOTEDIALOG_H
