#include "estreewidgetitem.h"
#include <QDebug>
#include "handler.h"
#include "httputils.h"
#include "esindextabwidegt.h"

EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidget *parent) : QTreeWidgetItem(parent)
{
    conn = NULL;
}
EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    conn = NULL;
}

EsTreeWidgetItem::~EsTreeWidgetItem(){
    if (conn != NULL){
        delete conn;
    }
}

void EsTreeWidgetItem::doubleClickConn(){
    QString url = "http://"+conn->getIp()+":"+conn->getPort()+"/_cluster/state";
    HttpUtils * util = HttpUtils::getInstance();
    QString res = util->Get(url);
    EsIndex* indics= conn->getIndics();
    conn->parseIndics(res);
    indics= conn->getIndics();

    for (int i = 0; i < conn->getIndexSize(); i++) {
        EsIndex indexObj = indics[i];
        EsTreeWidgetItem *docItem = new EsTreeWidgetItem(this);
        docItem->setText(0,indexObj.getName());
        docItem->setIcon(0,QIcon(":/icon/pic/index.png"));
        docItem->setEsItemType(INDEX);
        docItem->setEsIndex(&indics[i]);
        docItem->setConn(conn);

        QString *aliasNamesPtr = indexObj.getAliasNames();
        if(aliasNamesPtr != NULL){
            docItem->setToolTip(0,aliasNamesPtr[0]);
        }
        this->addChild(docItem);
    }
}

void EsTreeWidgetItem::doubleClickIndex(){
    // tab页
    Conn* conn = this->getConn();
    EsIndex* esIndex = this->getEsIndex();
    Handler* hand = Handler::getInstance();
    emit hand->addTabSignal(conn,esIndex,ADD);
}

Conn* EsTreeWidgetItem::getConn(){
    return this->conn;
}

void EsTreeWidgetItem::setConn(Conn *conn){
    this->conn = conn;
}

bool EsTreeWidgetItem::isOpen(){
    return this->open;
}

void EsTreeWidgetItem::setOpen(bool open){
    this->open = open;
}

ESItemType EsTreeWidgetItem::getEsItemType(){
    return this->esItemType;
}

void EsTreeWidgetItem::setEsItemType(ESItemType itemType){
    this->esItemType = itemType;
}

void EsTreeWidgetItem::setEsIndex(EsIndex *esIndex){
    this->esIndex = esIndex;
}

EsIndex* EsTreeWidgetItem::getEsIndex(){
    return this->esIndex;
}

