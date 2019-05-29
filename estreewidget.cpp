#include "estreewidget.h"
#include "estreewidgetitem.h"
#include <QDebug>
#include "httputils.h"
#include "handler.h"

EsTreeWidget::EsTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addConnSignal(Conn*)),this,SLOT(addConn(Conn*)));
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*, int)),this,SLOT(esItemClicked(QTreeWidgetItem*, int)));
}

void EsTreeWidget::esItemClicked(QTreeWidgetItem* item, int index){
    EsTreeWidgetItem * esItem = (EsTreeWidgetItem*)item;
    Conn* conn = esItem->getConn();
    // 获取所有索引
    QString url = "http://"+conn->getIp()+":"+conn->getPort()+"/_cluster/state";
    HttpUtils * util = HttpUtils::getInstance();
    QString res = util->Post(url,"{}");
    qDebug()<<res;
}


void EsTreeWidget::addConn(Conn *conn){
    qDebug()<<"添加连接";
    EsTreeWidgetItem *connItem = new EsTreeWidgetItem(this);
    connItem->setText(0,conn->getConnName());
    connItem->setIcon(0,QIcon(":/icon/pic/conn.png"));
    connItem->setConn(conn);
    connItem->setEsItemType(CONN);
    connItem->setOpen(false);


}
