#ifndef ESINDEXTABWIDEGT_H
#define ESINDEXTABWIDEGT_H

#include <QWidget>
#include <QTabWidget>
#include "esindex.h"
#include "conn.h"

enum TabType{
    ADD,QUERY
};

class EsIndexTabWidegt : public QTabWidget
{
    Q_OBJECT
public:
    explicit EsIndexTabWidegt(QWidget *parent = nullptr);

    void addIndexTab(Conn *conn, EsIndex* esIndex);
    void addIndexQueryTab(Conn *conn, EsIndex* esIndex);

signals:

public slots:
    void addTabPage(Conn *conn, EsIndex* esIndex, TabType tabType);
    void deleteTabPage(int index);
};

#endif // ESINDEXTABWIDEGT_H
