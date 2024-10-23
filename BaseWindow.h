    //
    // Created by nicco on 10/05/2024.
    //

    #ifndef DENOTE_BASEWINDOW_H
    #define DENOTE_BASEWINDOW_H

    #include <QMainWindow>
    #include "NoteManager.h"
    #include "NewNoteDialog.h"
    #include "Note.h"
    #include "RenameNoteDialog.h"
    #include "DeleteNoteDialog.h"
    #include <QListWidget>
    #include <QFileDialog>
    #include <QFile>
    #include <QTextStream>
    #include <QMessageBox>
    #include <QPushButton>
    #include <QIcon>

    QT_BEGIN_NAMESPACE
    namespace Ui { class BaseWindow; }
    QT_END_NAMESPACE

    class BaseWindow : public QMainWindow {
    Q_OBJECT
    friend class TestBaseWindow;
    friend class TestNewNoteDialog;
    public:
        explicit BaseWindow(QWidget *parent = nullptr);
        ~BaseWindow() override;
     signals:
        void creationConfirm(bool result);
        void renameConfirm(bool result);

    private slots:

        void newNoteClicked(); //SLOT connesso all'evento newnotebutton::clicked
        void createNote(const QString& name);
        void deleteNoteClicked();
        void deleteNote();
        void openNote(QListWidgetItem* n);
        void renameNoteClicked();
        void renameNote(QString& oldname,const QString &newname);
        void loadNoteClicked();
        void favouriteClicked();
        void blockedClicked();
        void saveChanges();
        void inTextSelectedCase();
        void changeSelectedTextSize();
        void changedSearchBar();
        void favouriteFilterChanged();
        void blockedFilterChanged();
    private:
        void initializeGui();
        void connectSignalsToSlots();
        Ui::BaseWindow *ui;
        NoteManager* manager;
        Note* current=nullptr;
        NewNoteDialog* createdialog;
        DeleteNoteDialog* deletedialog;
        RenameNoteDialog* renamedialog;

        void setDefault();
        void addToNameListWidget(const QString& name);
        void updateNameListWidget();
        QStringList getFilteredNameList();
        void setNameListWidget(QStringList& names);
        //metodi per TestBaseWindow
        list<QString> getListWidgetNames();
        bool isInNameListWidget(const QString& name);
        void setTextForTest(const QString& name,const QString& text);
        QString getTextNoteSelected();
        QString getCurrentNoteLabelText();

        //metodi per TestNewNoteDialog
        NewNoteDialog* getCreateDialog(){
            return createdialog;
        }
    };



    #endif //DENOTE_BASEWINDOW_H
