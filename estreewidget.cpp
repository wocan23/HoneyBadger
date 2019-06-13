#include "estreewidget.h"
#include "estreewidgetitem.h"
#include "handler.h"
#include "esutils.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QTreeWidgetItem>
#include <QDebug>
#include <QLineEdit>
#include "esquerywidget.h"
#include "createconndialog.h"

EsTreeWidget::EsTreeWidget(QWidget *parent) : QTreeWidget(parent)
{
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addConnSignal(Conn*)),this,SLOT(addConn(Conn*)));
    connect(hand,SIGNAL(editConnSignal(Conn*)),this,SLOT(editConnFinish(Conn*)));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),this,SLOT(esItemDoubleClicked(QTreeWidgetItem*, int)));

    // 索引菜单
    QMenu * indexMenu = new QMenu;

    QAction * queryIndex = new QAction(this);
    queryIndex->setText("查询");
    indexMenu ->addAction(queryIndex);

    indexMenu->addSeparator();

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
    this->removeAliasActon= removeAlias;

//    QAction * editAlias = new QAction(this);
//    editAlias->setText("修改别名");
//    indexMenu ->addAction(editAlias);

    this->indexMenu = indexMenu;


    // 连接菜单
    QMenu * connMenu = new QMenu;
    QAction * connInfo = new QAction(this);
    connInfo->setText("连接信息");
    connMenu->addAction(connInfo);

    QAction * editConn = new QAction(this);
    editConn->setText("编辑连接名称");
    connMenu ->addAction(editConn);

    connMenu->addSeparator();

    QAction * updateConn = new QAction(this);
    updateConn->setText("修改连接信息");
    connMenu ->addAction(updateConn);

    connMenu->addSeparator();

    QAction * closeConn = new QAction(this);
    closeConn->setText("关闭连接");
    connMenu ->addAction(closeConn);

    connMenu->addSeparator();

    QAction * removeConn = new QAction(this);
    removeConn->setText("删除连接");
    connMenu ->addAction(removeConn);

    this->connMenu = connMenu;


    connect(connInfo, SIGNAL(triggered(bool)), this, SLOT(showConnInfo())); //右键动作槽
    connect(editConn, SIGNAL(triggered(bool)), this, SLOT(editConn())); //右键动作槽
    connect(closeConn, SIGNAL(triggered(bool)), this, SLOT(closeConn())); //右键动作槽
    connect(removeConn, SIGNAL(triggered(bool)), this, SLOT(removeConn())); //右键动作槽
    connect(updateConn, SIGNAL(triggered(bool)), this, SLOT(updateConn())); //右键动作槽

    connect(indexInfo, SIGNAL(triggered(bool)), this, SLOT(showIndexInfo())); //右键动作槽
    connect(queryIndex, SIGNAL(triggered(bool)), this, SLOT(queryIndex())); //右键动作槽
    connect(editIndex, SIGNAL(triggered(bool)), this, SLOT(editIndex())); //右键动作槽
    connect(addAlias, SIGNAL(triggered(bool)), this, SLOT(addAlias())); //右键动作槽
    connect(removeAlias, SIGNAL(triggered(bool)), this, SLOT(removeAlias())); //右键动作槽
    connect(this,SIGNAL(itemChanged(QTreeWidgetItem *, int )),this,SLOT(editFinish(QTreeWidgetItem *, int)));

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
    EsTreeWidgetItem *connItem = new EsTreeWidgetItem(this);
    connItem->setText(0,conn->getConnName());
    connItem->setIcon(0,QIcon(":/icon/pic/conn.png"));
    connItem->setConn(conn);
    connItem->setEsItemType(CONN);
    connItem->setOpen(false);
}

void EsTreeWidget::editConnFinish(Conn *conn){
    EsTreeWidgetItem *connItem = this->currentItem;
    connItem->setText(0,conn->getConnName());
    connItem->setIcon(0,QIcon(":/icon/pic/conn.png"));
    connItem->setConn(conn);
    connItem->setEsItemType(CONN);
    connItem->setOpen(false);
    this->closeConn();
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
               if(esItem->getEsIndex()->getAliasNames().size() == 0){
                   this->removeAliasActon->setEnabled(false);
               }else{
                    this->removeAliasActon->setEnabled(true);
               }
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
    this->openPersistentEditor(this->currentItem,0);
}

void EsTreeWidget::addAlias(){
    Conn * conn = this->currentItem->getConn();
    EsIndex * index = this->currentItem->getEsIndex();
    bool isOK;
    QStringList aliasNames = index->getAliasNames();
    QString oldAlias = aliasNames.join(",");

    QInputDialog * inputDialog = new QInputDialog(this);
    inputDialog->setTextValue("新别名");
    inputDialog->setLabelText("原别名:"+oldAlias);
    inputDialog->setOkButtonText("确定");
    inputDialog->setCancelButtonText("取消");
    int res = inputDialog->exec();
    if(res == 0){
        return;
    }
    QString newAlias = inputDialog->textValue();
    int ack = EsUtils::addAlias(conn,index,newAlias).code;
    if(ack == 1){
        QStringList newAliases = index->getAliasNames() << newAlias;
        index->setAliasNames(newAliases);
        QMessageBox::information(this,"提示","添加成功","确定");
        QColor color("green");
        this->currentItem->setTextColor(0,color);
    }else{
        QMessageBox::information(this,"提示","添加失败","确定");
    }
}

void EsTreeWidget::removeAlias(){
    Conn * conn = this->currentItem->getConn();
    EsIndex * index = this->currentItem->getEsIndex();
    bool isOK;
    QStringList aliasNames = index->getAliasNames();
    QString oldAlias = aliasNames.join(",");

    QInputDialog * inputDialog = new QInputDialog(this);
    inputDialog->setLabelText("选择要删除的别名");
    inputDialog->setComboBoxItems(aliasNames);
    inputDialog->setOkButtonText("确定");
    inputDialog->setCancelButtonText("取消");
    int res = inputDialog->exec();
    if(res == 0){
        return;
    }
    // 获取选择的内容
    QString selAlias = inputDialog->textValue();
    int ack = EsUtils::removeAlias(conn,index,selAlias).code;
    if(ack == 1){
        aliasNames.removeOne(selAlias);
        index->setAliasNames(aliasNames);
        QMessageBox::information(this,"提示","删除成功","确定");
        if(aliasNames.size() == 0){
            // 去除颜色
            QColor color("black");
            this->currentItem->setTextColor(0,color);
        }

    }else{
        QMessageBox::information(this,"提示","删除失败","确定");
    }
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

void EsTreeWidget::editFinish(QTreeWidgetItem *item, int column){
    EsTreeWidgetItem * esItem = (EsTreeWidgetItem*)item;
    this->closePersistentEditor(item,column);
    ESItemType type = esItem->getEsItemType();
    switch (type) {
    case CONN:
        if(esItem->getConn() != NULL){
            esItem->getConn()->setConnName(item->text(column));
        }
        break;
    case INDEX:
        if(esItem->getEsIndex() != NULL){
            QString lastName = esItem->getEsIndex()->getName();
            //QString newName = esItem->text(column);
        }
        break;
    }
}

void EsTreeWidget::queryIndex(){
    Handler* hand = Handler::getInstance();
    emit hand->addTabSignal(this->currentItem->getConn(),this->currentItem->getEsIndex(),QUERY);
}

void EsTreeWidget::removeConn(){
    this->removeItemWidget(this->currentItem,0);
    delete this->currentItem;
}

void EsTreeWidget::updateConn(){
    Conn *conn = this->currentItem->getConn();
    CreateConnDialog* dialog = new CreateConnDialog(conn);
    dialog->exec();
}
