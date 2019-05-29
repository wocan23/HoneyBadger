#ifndef ESTREEWIDGET_H
#define ESTREEWIDGET_H

#include <QWidget>
#include<QTreeWidget>
#include <QTreeWidgetItem>
#include "conn.h"

class EsTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit EsTreeWidget(QWidget *parent = nullptr);

signals:



public slots:
   void esItemDoubleClicked(QTreeWidgetItem* item, int index);
   void addConn(Conn *conn);
};

#endif // ESTREEWIDGET_H
