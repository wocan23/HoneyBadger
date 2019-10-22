#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/icon/ico/favicon.ico"));
    w.setWindowTitle("Honey Badger");
    w.show();

    return a.exec();
}
