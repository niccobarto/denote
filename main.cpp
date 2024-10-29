#include <QApplication>
#include <QPushButton>
#include "BaseWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto manager=new NoteManager();
    BaseWindow w(manager);
    w.show();
    return QApplication::exec();
}
