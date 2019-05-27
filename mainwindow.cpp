#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "estoolbar.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->esToolBar = new EsToolBar;
    this->ui->toolBarLayout->addWidget(this->esToolBar);

    this->ui->treeWidget->setHeaderHidden(true);
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addConnSignal(Conn*)),this,SLOT(addConn(Conn*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addConn(Conn *conn){
    qDebug()<<"添加连接";
    QTreeWidgetItem *connItem = new QTreeWidgetItem(ui->treeWidget,QStringList(conn->getConnName()));
    connItem->setIcon(0,QIcon(":/icon/pic/conn.png"));
}
