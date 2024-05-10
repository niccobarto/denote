/********************************************************************************
** Form generated from reading UI file 'basewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEWINDOW_H
#define UI_BASEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseWindow
{
public:
    QWidget *centralwidget;
    QListWidget *notelist;
    QPushButton *newnotebutton;
    QFrame *line;
    QLabel *label_4;
    QGroupBox *groupBox;
    QSpinBox *sizechanger;
    QLabel *label;
    QPushButton *savebutton;
    QPushButton *fullscreenbutton;
    QTextEdit *noteeditor;
    QLabel *label_3;
    QLabel *title;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BaseWindow)
    {
        if (BaseWindow->objectName().isEmpty())
            BaseWindow->setObjectName("BaseWindow");
        BaseWindow->resize(908, 778);
        centralwidget = new QWidget(BaseWindow);
        centralwidget->setObjectName("centralwidget");
        notelist = new QListWidget(centralwidget);
        notelist->setObjectName("notelist");
        notelist->setGeometry(QRect(80, 80, 761, 161));
        newnotebutton = new QPushButton(centralwidget);
        newnotebutton->setObjectName("newnotebutton");
        newnotebutton->setGeometry(QRect(810, 50, 31, 31));
        QFont font;
        font.setPointSize(13);
        newnotebutton->setFont(font);
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(20, 250, 871, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(640, 40, 171, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(15);
        label_4->setFont(font1);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 280, 841, 431));
        sizechanger = new QSpinBox(groupBox);
        sizechanger->setObjectName("sizechanger");
        sizechanger->setGeometry(QRect(130, 30, 91, 31));
        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 30, 121, 31));
        QFont font2;
        font2.setPointSize(9);
        label->setFont(font2);
        savebutton = new QPushButton(groupBox);
        savebutton->setObjectName("savebutton");
        savebutton->setGeometry(QRect(730, 30, 91, 29));
        fullscreenbutton = new QPushButton(groupBox);
        fullscreenbutton->setObjectName("fullscreenbutton");
        fullscreenbutton->setGeometry(QRect(570, 30, 141, 29));
        noteeditor = new QTextEdit(groupBox);
        noteeditor->setObjectName("noteeditor");
        noteeditor->setGeometry(QRect(0, 70, 841, 361));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(80, 40, 111, 41));
        label_3->setFont(font1);
        title = new QLabel(centralwidget);
        title->setObjectName("title");
        title->setGeometry(QRect(310, -20, 231, 81));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Lucida Bright")});
        font3.setPointSize(37);
        title->setFont(font3);
        title->setAlignment(Qt::AlignmentFlag::AlignCenter);
        BaseWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BaseWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 908, 33));
        BaseWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(BaseWindow);
        statusbar->setObjectName("statusbar");
        BaseWindow->setStatusBar(statusbar);

        retranslateUi(BaseWindow);

        QMetaObject::connectSlotsByName(BaseWindow);
    } // setupUi

    void retranslateUi(QMainWindow *BaseWindow)
    {
        BaseWindow->setWindowTitle(QCoreApplication::translate("BaseWindow", "BaseWindow", nullptr));
        newnotebutton->setText(QCoreApplication::translate("BaseWindow", "+", nullptr));
        label_4->setText(QCoreApplication::translate("BaseWindow", "Crea nuova nota ->", nullptr));
        groupBox->setTitle(QCoreApplication::translate("BaseWindow", "GroupBox", nullptr));
        label->setText(QCoreApplication::translate("BaseWindow", "Dimensione carattere:", nullptr));
        savebutton->setText(QCoreApplication::translate("BaseWindow", "SALVA", nullptr));
        fullscreenbutton->setText(QCoreApplication::translate("BaseWindow", "SCHERMO INTERO", nullptr));
        noteeditor->setHtml(QCoreApplication::translate("BaseWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_3->setText(QCoreApplication::translate("BaseWindow", "Le tue note:", nullptr));
        title->setText(QCoreApplication::translate("BaseWindow", "DE NOTE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseWindow: public Ui_BaseWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEWINDOW_H
