#include "tabcontentwidget.h"


#include "pagewidget.h"
#include "esindextablewidget.h"
#include "esutils.h"

#include <QMessageBox>
#include <QVBoxLayout>
#include <QHeaderView>


TabContentWidget::TabContentWidget(QWidget *parent) : QWidget(parent)
{

        PageWidget * pageWidget = new PageWidget(0);
        QVBoxLayout * vLayout = new QVBoxLayout;
        EsIndexTableWidget * tableWidget = new EsIndexTableWidget;
        vLayout->addWidget(tableWidget);
        vLayout->addWidget(pageWidget);

        this->setLayout(vLayout);

        this->pageWidget = pageWidget;
        this->tableWidget = tableWidget;

        connect(this->pageWidget,SIGNAL(to( int, int)),this,SLOT(to( int, int)));
}

void TabContentWidget::flushData(QList<QMap<QString, QString> >& data, QStringList& fields, int totalNum, int currentPage, int pageSize){
    tableWidget->setColumnCount(fields.size());
    tableWidget->setRowCount(data.size());
    tableWidget->setVisible(true);
    tableWidget->setShowGrid(true);
    tableWidget->setHorizontalHeaderLabels(fields);

    for(int i = 0 ;i < data.size(); i ++){
        QMap<QString,QString> obj = data.at(i);
        for (int j = 0; j < fields.size(); j++) {
            QString field = fields.at(j);
            QString v;
            if(obj.contains(field)){
               v = obj.find(field).value();
            }else{
               v = "";
            }
            QTableWidgetItem * item = tableWidget->item(i,j);
            if(item == NULL){
                item = new QTableWidgetItem(v);
                tableWidget->setItem(i,j,item);
            }else{
                item->setText(v);
            }

        }
    }

    pageWidget->changeShow(totalNum,pageSize,currentPage);
}

void TabContentWidget::to(int page, int pageSize){
    int totalSize;
    QString url = this->queryUrl+"?size="+QString::number(pageSize)+"&from="+QString::number(pageSize*(page-1));
    EsResult result = EsUtils::query(url,"{}",totalSize);
    if(result.code != 1){
        QMessageBox::information(this,"错误",result.msg,"确定");
        return;
    }
    QList<QMap<QString,QString>> list = result.data;
    flushData(list,this->fields,totalSize,page,pageSize);
}

void TabContentWidget::setQueryUrl(QString &url){
    this->queryUrl = url;
}

void TabContentWidget::setFields(QStringList &fields){
    this->fields = fields;
}
