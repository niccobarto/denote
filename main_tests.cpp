//
// Created by nicco on 01/09/2024.
//
#include <QApplication>
#include <QPushButton>
#include "BaseWindow.h"
#include "TestNoteManager.h"
#include "TestBaseWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TestNoteManager tnotemanager;
    TestBaseWindow tbasewindow;
    QTest::qExec(&tnotemanager,argc,argv);
    QTest::qExec(&tbasewindow,argc,argv);
}