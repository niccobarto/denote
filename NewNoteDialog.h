//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NEWNOTEDIALOG_H
#define DENOTE_NEWNOTEDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class NewNoteDialog; }
QT_END_NAMESPACE

class NewNoteDialog : public QDialog {
Q_OBJECT

public:
    explicit NewNoteDialog(QWidget *parent = nullptr);

    ~NewNoteDialog() override;
signals:
    void noteConfirmed(QString name); //segnale per la conferma di creazione della nota

    private slots:
    void noteCreationButtonClicked();

private:
    Ui::NewNoteDialog *ui;
};


#endif //DENOTE_NEWNOTEDIALOG_H
