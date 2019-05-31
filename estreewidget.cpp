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
        Conn* conn = esItem->getConn();
        if(!esItem->isOpen()){
            QString url = "http://"+conn->getIp()+":"+conn->getPort()+"/_cluster/state";
            HttpUtils * util = HttpUtils::getInstance();
            QString res = util->Get(url);
            EsIndex* indics= conn->getIndics();
//            if(indics == NULL){
                conn->parseIndics(res);
                indics= conn->getIndics();
//            }

            for (int i = 0; i < conn->getIndexSize(); i++) {
                EsIndex indexObj = indics[i];
                EsTreeWidgetItem *docItem = new EsTreeWidgetItem(item);
                docItem->setText(0,indexObj.getName());
                docItem->setIcon(0,QIcon(":/icon/pic/index.png"));
                docItem->setEsItemType(INDEX);
//
                QString *aliasNamesPtr = indexObj.getAliasNames();
                if(aliasNamesPtr != NULL){
                    docItem->setToolTip(0,aliasNamesPtr[0]);
                }
                item->addChild(docItem);
            }
        }else{
            esItem->setOpen(false);
        }

    }else if(esItemType == INDEX){
        // 是索引
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
