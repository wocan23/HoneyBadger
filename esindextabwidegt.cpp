#include "esindextabwidegt.h"

#include <QMessageBox>
#include "esutils.h"
#include "handler.h"
#include "tabcontentwidget.h"
#include "esquerywidget.h"
#include "estreewidgetitem.h"
#include "pagewidget.h"
#include "httputils.h"
#include "esindextablewidget.h"

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
    this->setTabsClosable(true);
    Handler * hand = Handler::getInstance();
    connect(hand,SIGNAL(addTabSignal(Conn*,EsIndex*,TabType)),this,SLOT(addTabPage(Conn*,EsIndex*, TabType)));
    connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(deleteTabPage(int)));
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

void EsIndexTabWidegt::deleteTabPage(int index){
    QWidget * pWidget = this->widget(index);
    this->removeTab(index);
    if(pWidget != NULL){
        delete pWidget;
    }
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
    EsResult result = EsUtils::query(url,"{}",totalSize);
    if(result.code != 1){
        QMessageBox::information(this,"查询失败",result.msg,"确定");
        return;
    }
    QList<QMap<QString,QString>> list = result.data;


    QMap<QString,QString> mappings = esIndex->getMappings();
    QStringList fields = mappings.keys();

    TabContentWidget * content = new TabContentWidget;
    content->setQueryUrl(baseUrl);
    content->setFields(fields);
    content->flushData(list,fields,totalSize,1,20);

    this->addTab(content,icon,tabLabel);
    this->setCurrentWidget(content);

}

void EsIndexTabWidegt::addIndexQueryTab(Conn *conn, EsIndex* esIndex){
    QString connName = conn->getConnName();
    QString indexName = esIndex->getName();
    QString tabLabel = "查询@"+indexName +"@"+ connName;
    QIcon icon(INDEX_QUERY_ICON_PATH);
    EsQueryWidget * queryWidget = new EsQueryWidget;
    queryWidget->setIndex(esIndex);
    queryWidget->setConn(conn);
    queryWidget->setUrlBar();
    this->addTab(queryWidget,icon,tabLabel);
    this->setCurrentWidget(queryWidget);
}
