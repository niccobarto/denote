/********************************************************************************
** Form generated from reading UI file 'NewNoteDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWNOTEDIALOG_H
#define UI_NEWNOTEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NewNoteDialog
{
public:
    QPushButton *notecreationbutton;
    QLabel *label_2;
    QLabel *errorcreationlabel;
    QLineEdit *notetitlebox;
    QLabel *label;

    void setupUi(QDialog *NewNoteDialog)
    {
        if (NewNoteDialog->objectName().isEmpty())
            NewNoteDialog->setObjectName("NewNoteDialog");
        NewNoteDialog->resize(339, 190);
        notecreationbutton = new QPushButton(NewNoteDialog);
        notecreationbutton->setObjectName("notecreationbutton");
        notecreationbutton->setGeometry(QRect(150, 140, 75, 24));
        label_2 = new QLabel(NewNoteDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 90, 41, 16));
        QFont font;
        font.setPointSize(11);
        label_2->setFont(font);
        errorcreationlabel = new QLabel(NewNoteDialog);
        errorcreationlabel->setObjectName("errorcreationlabel");
        errorcreationlabel->setEnabled(false);
        errorcreationlabel->setGeometry(QRect(80, 120, 221, 20));
        errorcreationlabel->setFont(font);
        errorcreationlabel->setStyleSheet(QString::fromUtf8("color:red;"));
        notetitlebox = new QLineEdit(NewNoteDialog);
        notetitlebox->setObjectName("notetitlebox");
        notetitlebox->setGeometry(QRect(70, 90, 241, 21));
        label = new QLabel(NewNoteDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 30, 121, 31));
        QFont font1;
        font1.setPointSize(13);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(NewNoteDialog);

        QMetaObject::connectSlotsByName(NewNoteDialog);
    } // setupUi

    void retranslateUi(QDialog *NewNoteDialog)
    {
        NewNoteDialog->setWindowTitle(QCoreApplication::translate("NewNoteDialog", "NewNoteDialog", nullptr));
        notecreationbutton->setText(QCoreApplication::translate("NewNoteDialog", "CREA", nullptr));
        label_2->setText(QCoreApplication::translate("NewNoteDialog", "Titolo:", nullptr));
        errorcreationlabel->setText(QCoreApplication::translate("NewNoteDialog", "ERRORE. Devi inserire un titolo", nullptr));
        label->setText(QCoreApplication::translate("NewNoteDialog", "NUOVA NOTA", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewNoteDialog: public Ui_NewNoteDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWNOTEDIALOG_H
