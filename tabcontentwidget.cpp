#include "tabcontentwidget.h"

#include "pagewidget.h"
#include "esindextablewidget.h"

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
}

void TabContentWidget::flushData(QList<QMap<QString, QString> >& data, QStringList& fields, int totalNum, int currentPage, int pageSize){
    tableWidget->setColumnCount(fields.size());
    tableWidget->setRowCount(data.size());
    tableWidget->setVisible(true);
    tableWidget->setShowGrid(true);
    QHeaderView * header = tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableWidget->setHorizontalHeaderLabels(fields);

    for(int i = 0 ;i < pageSize; i ++){
        QMap<QString,QString> obj = data.at(i);
        for (int j = 0; j < fields.size(); j++) {
            QString field = fields.at(j);
            QString v;
            if(obj.contains(field)){
               v = obj.find(field).value();
            }else{
               v = "";
            }
            QTableWidgetItem * item = new QTableWidgetItem(v);
            tableWidget->setItem(i,j,item);
        }
    }

    pageWidget->changeShow(totalNum,pageSize,currentPage);
}
