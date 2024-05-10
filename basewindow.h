//
// Created by nicco on 10/05/2024.
//

#ifndef DENOTE_BASEWINDOW_H
#define DENOTE_BASEWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class BaseWindow; }
QT_END_NAMESPACE

class BaseWindow : public QMainWindow {
Q_OBJECT

public:
    explicit BaseWindow(QWidget *parent = nullptr);

    ~BaseWindow() override;

private:
    Ui::BaseWindow *ui;
};


#endif //DENOTE_BASEWINDOW_H
