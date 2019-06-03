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
    explicit EsTreeWidgetItem(QTreeWidgetItem *parent);
    void setConn(Conn *conn);
    Conn * getConn();
    ESItemType getEsItemType();
    void setEsItemType(ESItemType itemType);
    bool isOpen();
    void setOpen(bool open);

    void doubleClickConn();
    void doubleClickIndex();
    EsIndex *getEsIndex();
    void setEsIndex(EsIndex* esIndex);

    void showConnInfo();
    void showIndexInfo();


    ~EsTreeWidgetItem();
signals:

public slots:
private:
    Conn* conn;
    ESItemType esItemType;
    bool open;
    EsIndex* esIndex;

};

#endif // ESTREEWIDGETITEM_H
