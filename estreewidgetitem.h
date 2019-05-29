#ifndef ESTREEWIDGETITEM_H
#define ESTREEWIDGETITEM_H

#include <QWidget>
#include <QTreeWidgetItem>
#include "conn.h"


class EsTreeWidgetItem : public QObject,public QTreeWidgetItem
{
    Q_OBJECT
public:
    explicit EsTreeWidgetItem(QTreeWidget *parent);
    void setConn(Conn *conn);
    Conn * getConn();
    bool isIndex();
    void mouseDoubleClickEvent(QMouseEvent *event) ;
    void mouseReleaseEvent(QMouseEvent *event);
signals:

public slots:
private:
    Conn* conn;
    bool isIdx;
};

#endif // ESTREEWIDGETITEM_H
