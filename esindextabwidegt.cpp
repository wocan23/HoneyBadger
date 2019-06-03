#include "esindextabwidegt.h"
#include "estreewidgetitem.h"
#include "handler.h"
#include "pagewidget.h"
#include "httputils.h"
#include "esutils.h"
#include "esindextablewidget.h"
#include "tabcontentwidget.h"

#include <QVBoxLayout>
#include <QTextBrowser>
#include <QMap>
#include <QDebug>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStringLiteral>






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

    // 查询数据
    QString baseUrl = "http://"+conn->getIp()+":"+conn->getPort()+"/"+esIndex->getName()+"/_search";
    QString url = baseUrl +"?size=20";
    int totalSize;
    QList<QMap<QString,QString>> list = EsUtils::query(url,totalSize);


    QMap<QString,QString> mappings = esIndex->getMappings();
    QStringList fields = mappings.keys();

    TabContentWidget * content = new TabContentWidget;
    content->setQueryUrl(baseUrl);
    content->setFields(fields);
    content->flushData(list,fields,totalSize,1,20);

    this->addTab(content,icon,tabLabel);

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
