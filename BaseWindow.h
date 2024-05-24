    //
    // Created by nicco on 10/05/2024.
    //

    #ifndef DENOTE_BASEWINDOW_H
    #define DENOTE_BASEWINDOW_H

    #include <QMainWindow>
    #include "NoteManager.h"

    QT_BEGIN_NAMESPACE
    namespace Ui { class BaseWindow; }
    QT_END_NAMESPACE

    class BaseWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit BaseWindow(QWidget *parent = nullptr);

        ~BaseWindow() override;
    signals:

    private slots:
        //medoto connesso all'evento newnotebutton::clicked
        void createNote( QString name);
        void newNoteClicked();
    private:
        Ui::BaseWindow *ui;
        NoteManager* manager=new NoteManager();

    };



    #endif //DENOTE_BASEWINDOW_H
