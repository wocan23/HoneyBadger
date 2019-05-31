#include "esindextabwidegt.h"
#include "estreewidgetitem.h"
#include <QTextBrowser>
#include "handler.h"

#define INDEX_ICON_PATH ":/icon/pic/index.png"
#define INDEX_QUERY_ICON_PATH ":/icon/pic/search.png"

EsIndexTabWidegt::EsIndexTabWidegt(QWidget *parent) : QTabWidget(parent)
{
    Handler* hand = Handler::getInstance();
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
    QTextBrowser *brower= new QTextBrowser;
    brower->setText("表格");
    this->addTab(brower,icon,tabLabel);

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
