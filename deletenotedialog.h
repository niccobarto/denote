//
// Created by nicco on 07/08/2024.
//

#ifndef DENOTE_DELETENOTEDIALOG_H
#define DENOTE_DELETENOTEDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class DeleteNoteDialog; }
QT_END_NAMESPACE

class DeleteNoteDialog : public QDialog {
Q_OBJECT

public:
    explicit DeleteNoteDialog(QWidget *parent = nullptr);

    ~DeleteNoteDialog() override;

private:
    Ui::DeleteNoteDialog *ui;
};


#endif //DENOTE_DELETENOTEDIALOG_H
