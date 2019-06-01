#include "estreewidget.h"
#include "estreewidgetitem.h"
#include <QDebug>
#include "httputils.h"
#include "handler.h"

EsTreeWidget::EsTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addConnSignal(Conn*)),this,SLOT(addConn(Conn*)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(esItemDoubleClicked(QTreeWidgetItem*, int)));
}

void EsTreeWidget::esItemDoubleClicked(QTreeWidgetItem* item, int index){
    EsTreeWidgetItem * esItem = (EsTreeWidgetItem*)item;

    ESItemType esItemType = esItem->getEsItemType();
    // 如果是连接且未打开获取所有索引
    if(esItemType == CONN){

        if(!esItem->isOpen()){
            esItem->doubleClickConn();
            esItem->setOpen(true);
        }

    }else if(esItemType == INDEX){
        // 是索引
        esItem->doubleClickIndex();
    }

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
