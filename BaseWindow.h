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
    friend class TestBaseWindow;

    public:
        explicit BaseWindow(QWidget *parent = nullptr);
        ~BaseWindow() override;
     signals:
        void creationConfirm(bool found);

    private slots:

        void newNoteClicked(); //SLOT connesso all'evento newnotebutton::clicked

        void openNote(QListWidgetItem* n);
        void save();
        void deleteNoteClicked();
        void deleteNote();
        void createNote(const QString& name);
        void isTextSelected();
        void changeSelectedTextSize();
    private:
        Ui::BaseWindow *ui;
        NoteManager* manager=new NoteManager();
        Note* current=nullptr;
        //metodi per TestBaseWindow
        list<QString> getListWidgetNames();
        bool isInNameListWidget(const QString& name);
        list<Note*> getNotes(){
            return manager->getNoteList();
        }
        void setTextForTest(const QString& name,const QString& text);
        QString getTextNoteSelected();
        QString getCurrentNoteLabelText();
    };



    #endif //DENOTE_BASEWINDOW_H
