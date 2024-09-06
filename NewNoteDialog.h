//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_NEWNOTEDIALOG_H
#define DENOTE_NEWNOTEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
QT_BEGIN_NAMESPACE
namespace Ui { class NewNoteDialog; }
QT_END_NAMESPACE

class NewNoteDialog : public QDialog {
Q_OBJECT
friend class TestNewNoteDialog;
public:
    explicit NewNoteDialog(QWidget *parent = nullptr);

    //getter per i test
    QLineEdit* getNoteTitleBox();
    QLabel* getErrorCreationLabel();
    QPushButton* getNoteCreationButton();

    ~NewNoteDialog() override;

signals:
    void newNoteNameInsert(QString name); //segnale per la conferma di creazione della nota

    private slots:
    void noteCreationButtonClicked();
    void receiveCreationConfirm(bool found);

private:
    Ui::NewNoteDialog *ui;
};


#endif //DENOTE_NEWNOTEDIALOG_H
