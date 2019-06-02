#include "esindextabwidegt.h"
#include "estreewidgetitem.h"
#include "handler.h"
#include "pagewidget.h"
#include "httputils.h"
#include "esutils.h"
#include "esindextablewidget.h"

#include <QVBoxLayout>
#include <QTextBrowser>
#include <QMap>
#include <QDebug>
#include <QTableWidgetItem>
#include <QHeaderView>





#define INDEX_ICON_PATH ":/icon/pic/index.png"
#define INDEX_QUERY_ICON_PATH ":/icon/pic/search.png"

EsIndexTabWidegt::EsIndexTabWidegt(QWidget *parent) : QTabWidget(parent)
{
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addTabSignal(Conn*,EsIndex*,TabType)),this,SLOT(addTabPage(Conn*,EsIndex*, TabType)));
}

void EsIndexTabWidegt::addTabPage(Conn *conn, EsIndex* esIndex, TabType tabType){
    switch (tabType) {
        case ADD:
            this->addIndexTab(conn,esIndex);
            break;
        case QUERY:
            this->addIndexQueryTab(conn,esIndex);
            break;
    }
}

void EsIndexTabWidegt::deleteTabPage(Conn *conn, EsIndex* esIndex){
    QString connName = conn->getConnName();
    QString indexName = esIndex->getName();
    QString tabLabel = indexName +"@"+ connName;
    QIcon icon(INDEX_ICON_PATH);
}

void EsIndexTabWidegt::addIndexTab(Conn *conn, EsIndex* esIndex){
    QString connName = conn->getConnName();
    QString indexName = esIndex->getName();
    QString tabLabel = indexName +"@"+ connName;
    QIcon icon(INDEX_ICON_PATH);

    QVBoxLayout * vLayout = new QVBoxLayout;
    // 查询数据
    QString url = "http://"+conn->getIp()+":"+conn->getPort()+"/"+esIndex->getName()+"/_search";
    QList<QMap<QString,QString>> list = EsUtils::query(url);

    int resultSize = list.size();

    EsIndexTableWidget * tableWidget = new EsIndexTableWidget;
    QMap<QString,QString> mappings = esIndex->getMappings();
    QStringList fields = mappings.keys();

    tableWidget->setHorizontalHeaderLabels(fields);
    tableWidget->setColumnCount(fields.size());
    tableWidget->setRowCount(list.size());
    tableWidget->setVisible(true);
    tableWidget->setShowGrid(true);
    QHeaderView * header = tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);


    for(int i = 0 ;i < resultSize; i ++){
        QMap<QString,QString> obj = list.at(i);
        for (int j = 0; j < fields.size(); j++) {
            QString field = fields.at(j);
            QString v = obj.find(field).value();
            QTableWidgetItem * item = new QTableWidgetItem(v);
            tableWidget->setItem(i,j,item);
        }
    }

    PageWidget * pageWidget = new PageWidget(list.size(),10,1);
    QWidget * widget = new QWidget;

    vLayout->addWidget(tableWidget);
    vLayout->addWidget(pageWidget);

    widget->setLayout(vLayout);
    this->addTab(widget,icon,tabLabel);

}

void EsIndexTabWidegt::addIndexQueryTab(Conn *conn, EsIndex* esIndex){
    QString connName = conn->getConnName();
    QString indexName = esIndex->getName();
    QString tabLabel = "查询@"+indexName +"@"+ connName;
    QIcon icon(INDEX_QUERY_ICON_PATH);
    QTextBrowser *brower= new QTextBrowser;
    brower->setText("查询");
    this->addTab(brower,icon,tabLabel);
}
