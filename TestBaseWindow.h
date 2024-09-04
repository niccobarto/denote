//
// Created by nicco on 03/09/2024.
//

#ifndef DENOTE_TESTBASEWINDOW_H
#define DENOTE_TESTBASEWINDOW_H
#include <QtTest/QTest>
#include "BaseWindow.h"
class TestBaseWindow:public QObject {
    Q_OBJECT
private slots:
    void initTestCase();
    void testCreateNote();
    void testOpenNote();
    void testDeleteNoteClicked();
    void cleanupTestCase();
private:
    BaseWindow* base;
    QListWidgetItem* nameselected;

};


#endif //DENOTE_TESTBASEWINDOW_H
