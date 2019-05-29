#ifndef ESTREEWIDGETITEM_H
#define ESTREEWIDGETITEM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "conn.h"

enum ESItemType{
    CONN,INDEX
};

class EsTreeWidgetItem : public QObject,public QTreeWidgetItem
{
    Q_OBJECT
public:
    explicit EsTreeWidgetItem(QTreeWidget *parent);
    void setConn(Conn *conn);
    Conn * getConn();
    ESItemType getEsItemType();
    void setEsItemType(ESItemType itemType);
    bool isOpen();
    void setOpen(bool open);
signals:

public slots:
private:
    Conn* conn;
    ESItemType esItemType;
    bool open;

};

#endif // ESTREEWIDGETITEM_H
