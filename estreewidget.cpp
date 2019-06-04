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


    // 索引菜单
    QMenu * indexMenu = new QMenu;

    QAction * indexInfo = new QAction(this);
    indexInfo->setText("索引信息");
    indexMenu ->addAction(indexInfo);

    QAction * editIndex = new QAction(this);
    editIndex->setText("编辑");
    indexMenu ->addAction(editIndex);

    indexMenu->addSeparator();

    QAction * addAlias = new QAction(this);
    addAlias->setText("添加别名");
    indexMenu ->addAction(addAlias);

    QAction * removeAlias = new QAction(this);
    removeAlias->setText("删除别名");
    indexMenu ->addAction(removeAlias);

    QAction * editAlias = new QAction(this);
    editAlias->setText("修改别名");
    indexMenu ->addAction(editAlias);

    this->indexMenu = indexMenu;


    // 连接菜单
    QMenu * connMenu = new QMenu;
    QAction * connInfo = new QAction(this);
    connInfo->setText("连接信息");
    connMenu->addAction(connInfo);

    QAction * editConn = new QAction(this);
    editConn->setText("修改连接名称");
    connMenu ->addAction(editConn);

    QAction * closeConn = new QAction(this);
    closeConn->setText("关闭连接");
    connMenu ->addAction(closeConn);

    this->connMenu = connMenu;

    connect(indexInfo, SIGNAL(triggered(bool)), this, SLOT(showIndexInfo())); //右键动作槽
    connect(connInfo, SIGNAL(triggered(bool)), this, SLOT(showConnInfo())); //右键动作槽
    connect(editConn, SIGNAL(triggered(bool)), this, SLOT(editConn())); //右键动作槽
    connect(closeConn, SIGNAL(triggered(bool)), this, SLOT(closeConn())); //右键动作槽
    connect(this,SIGNAL(itemChanged(QTreeWidgetItem *, int )),this,SLOT(editFinishConn(QTreeWidgetItem *, int)));

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

void EsTreeWidget::editIndex(){

}

void EsTreeWidget::addAlias(){

}

void EsTreeWidget::removeAlias(){

}

void EsTreeWidget::editAlias(){

}

void EsTreeWidget::closeConn(){
    int count = this->currentItem->childCount();
    for(int i = count-1; i >= 0; i--){
        this->currentItem->removeChild(this->currentItem->child(i));
    }
    this->currentItem->setOpen(false);
}

void EsTreeWidget::editConn(){
    this->openPersistentEditor(this->currentItem,0);
}

void EsTreeWidget::editFinishConn(QTreeWidgetItem *item, int column){
    this->closePersistentEditor(item,column);
    EsTreeWidgetItem * esItem = (EsTreeWidgetItem*)item;
    if(esItem->getConn() != NULL){
        esItem->getConn()->setConnName(item->text(column));
    }
}
