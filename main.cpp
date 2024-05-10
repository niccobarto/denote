#include <QApplication>
#include <QPushButton>
#include "basewindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    BaseWindow w;
    w.show();
    return QApplication::exec();
}
