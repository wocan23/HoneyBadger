#include "estreewidgetitem.h"
#include <QDebug>


EsTreeWidgetItem::EsTreeWidgetItem(QTreeWidget *parent) : QTreeWidgetItem(parent)
{

}

void EsTreeWidgetItem::mouseDoubleClickEvent(QMouseEvent *event){
    qDebug()<<"double click";

}

void EsTreeWidgetItem::mouseReleaseEvent(QMouseEvent *event){
    qDebug()<<"mouse release event";
}

Conn* EsTreeWidgetItem::getConn(){
    return this->conn;
}

void EsTreeWidgetItem::setConn(Conn *conn){
    this->conn = conn;
}
