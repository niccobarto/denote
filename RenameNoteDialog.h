//
// Created by nicco on 26/09/2024.
//

#ifndef DENOTE_RENAMENOTEDIALOG_H
#define DENOTE_RENAMENOTEDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class RenameNoteDialog; }
QT_END_NAMESPACE

class RenameNoteDialog : public QDialog {
Q_OBJECT
public:
     explicit RenameNoteDialog(QString& name,QWidget *parent = nullptr);
    ~RenameNoteDialog();

    signals:
    void newNameInsert(const QString oldname,const QString &newname);

private slots:
    void confirmRenameButtonClicked();
    void cancelClicked();
    void receiveRenameConfirm(bool result);
private:
    Ui::RenameNoteDialog *ui;
    QString oldname;
};


#endif //DENOTE_RENAMENOTEDIALOG_H
