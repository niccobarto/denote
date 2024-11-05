//
// Created by nicco on 07/08/2024.
//

#ifndef DENOTE_DELETENOTEDIALOG_H
#define DENOTE_DELETENOTEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class DeleteNoteDialog; }
QT_END_NAMESPACE

class DeleteNoteDialog : public QDialog {
Q_OBJECT

public:
    explicit DeleteNoteDialog(const QString& notenameselected,QWidget *parent = nullptr);

    ~DeleteNoteDialog() override;
    signals:
    void confirmDelete();
private slots:
    void confirmClicked();
    void cancelClicked();
private:
    Ui::DeleteNoteDialog *ui;
};


#endif //DENOTE_DELETENOTEDIALOG_H
