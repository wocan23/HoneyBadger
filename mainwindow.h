#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "estoolbar.h"
#include "handler.h"
#include "conn.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void addConn(Conn *conn);
private:
    Ui::MainWindow *ui;
    EsToolBar *esToolBar;


};

#endif // MAINWINDOW_H
