#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/icon/ico/favicon.ico"));
    w.setWindowTitle("mh");
    w.show();

    return a.exec();
}
