    //
    // Created by nicco on 10/05/2024.
    //

    #ifndef DENOTE_BASEWINDOW_H
    #define DENOTE_BASEWINDOW_H

    #include <QMainWindow>
    #include "NoteManager.h"
    #include "Note.h"
    #include <QListWidget>
#include <QPushButton>

    QT_BEGIN_NAMESPACE
    namespace Ui { class BaseWindow; }
    QT_END_NAMESPACE

    class BaseWindow : public QMainWindow {
    Q_OBJECT
    friend class TestNewNote;
    /*
      In questo modo posso permettere al TestNewNote di simulare un inserimento
      di nome
     */
    public:
        explicit BaseWindow(QWidget *parent = nullptr);
        ~BaseWindow() override;

        //getter per i test
        QPushButton* getNewNoteButton();
        list<Note*> getNotes(){
            return manager->getNoteList();
        }
    signals:

    private slots:

        void newNoteClicked(); //SLOT connesso all'evento newnotebutton::clicked

        void openNote(QListWidgetItem* n);
        void save();
        void deleteNoteClicked();
        void deleteNote();
        void createNote(QString name);
    private:
        Ui::BaseWindow *ui;
        NoteManager* manager=new NoteManager();
        Note* current=nullptr;
    };



    #endif //DENOTE_BASEWINDOW_H
