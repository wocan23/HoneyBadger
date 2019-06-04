#ifndef ESTREEWIDGET_H
#define ESTREEWIDGET_H

#include <estreewidgetitem.h>
#include "conn.h"
#include <QWidget>
#include<QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>


class EsTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit EsTreeWidget(QWidget *parent = nullptr);

signals:



public slots:
   void esItemDoubleClicked(QTreeWidgetItem* item, int index);
   void contextMenuEvent(QContextMenuEvent *event); //右键默认槽
   void addConn(Conn *conn);
   void showConnInfo();
   void showIndexInfo();

   void editIndex();
   void addAlias();
   void removeAlias();
   void editAlias();

   void closeConn();
   void editConn();
   void editFinishConn(QTreeWidgetItem *item, int column);

private:
   QMenu * indexMenu;
   QMenu * connMenu;

   EsTreeWidgetItem * currentItem;

};

#endif // ESTREEWIDGET_H
