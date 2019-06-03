#include "estreewidget.h"
#include "estreewidgetitem.h"

#include "httputils.h"
#include "handler.h"
#include <QTreeWidgetItem>
#include <QDebug>

EsTreeWidget::EsTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addConnSignal(Conn*)),this,SLOT(addConn(Conn*)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(esItemDoubleClicked(QTreeWidgetItem*, int)));


    // 右键菜单
    QMenu * indexMenu = new QMenu;
    QAction * indexInfo = new QAction(this);
    indexInfo->setText("索引信息");
    indexMenu ->addAction(indexInfo);
    this->indexMenu = indexMenu;

    QMenu * connMenu = new QMenu;
    QAction * connInfo = new QAction(this);
    connInfo->setText("连接信息");
    connMenu->addAction(connInfo);
    this->connMenu = connMenu;

    connect(indexInfo, SIGNAL(triggered(bool)), this, SLOT(showIndexInfo())); //右键动作槽
    connect(connInfo, SIGNAL(triggered(bool)), this, SLOT(showConnInfo())); //右键动作槽

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

void EsTreeWidget::contextMenuEvent(QContextMenuEvent *event){
    QPoint point = event->pos(); //得到窗口坐标
        QTreeWidgetItem *item = this->itemAt(point);
        if(item != NULL)
        {
           EsTreeWidgetItem * esItem = (EsTreeWidgetItem*)item;
           this->currentItem = esItem;
           ESItemType esItemType = esItem->getEsItemType();
           if(esItemType == INDEX){
               this->indexMenu->exec(QCursor::pos());
           }else if (esItemType == CONN) {
                this->connMenu->exec(QCursor::pos());
            }
            //菜单出现的位置为当前鼠标的位置
            event->accept();
        }
}

void EsTreeWidget::showConnInfo(){
    this->currentItem->showConnInfo();
}

void EsTreeWidget::showIndexInfo(){
   this->currentItem->showIndexInfo();
}
