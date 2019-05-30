#include "estreewidgetitem.h"
#include <QDebug>


EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidget *parent) : QTreeWidgetItem(parent)
{

}
EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{

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
