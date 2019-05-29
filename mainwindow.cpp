#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "estoolbar.h"
#include <QDebug>
#include "estreewidgetitem.h"
#include <QStringList>
#include "httputils.h"
#include "conn.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->esToolBar = new EsToolBar;
    this->ui->toolBarLayout->addWidget(this->esToolBar);
//    this->ui->mainLayout.a
    this->ui->treeWidget->setHeaderHidden(true);
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addConnSignal(Conn*)),this,SLOT(addConn(Conn*)));

    connect(this->ui->treeWidget,SIGNAL(itemClicked(QTreeWidgetItem*, int)),this,SLOT(itemClicked(QTreeWidgetItem*, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addConn(Conn *conn){
    qDebug()<<"添加连接";
//    QTreeWidgetItem * tiem = new QTreeWidgetItem;
    EsTreeWidgetItem *connItem = new EsTreeWidgetItem(ui->treeWidget);
    connItem->setText(0,conn->getConnName());
    connItem->setIcon(0,QIcon(":/icon/pic/conn.png"));
    connItem->setConn(conn);

    QString url = "http://"+conn->getIp()+":"+conn->getPort()+"/_search";
    HttpUtils * util = HttpUtils::getInstance();
    QString res = util->Post(url,"{}");
//    qDebug()<< res;
}

void MainWindow::itemClicked(QTreeWidgetItem* item, int index){
    EsTreeWidgetItem * esItem = (EsTreeWidgetItem*)item;
    qDebug()<< QString(index);
    qDebug()<< esItem->text(0);
    Conn* conn = esItem->getConn();
    qDebug()<< conn->getPort();

}
