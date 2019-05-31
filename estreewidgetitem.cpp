#include "estreewidgetitem.h"
#include <QDebug>


EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidget *parent) : QTreeWidgetItem(parent)
{
    conn = NULL;
}
EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidgetItem *parent) : QTreeWidgetItem(parent)
{
    conn = NULL;
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

EsTreeWidgetItem::~EsTreeWidgetItem(){
    if (conn != NULL){
        delete conn;
    }
}
