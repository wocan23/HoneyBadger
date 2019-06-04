#include "indexinfodialog.h"
#include "ui_indexinfodialog.h"
#include "commonutils.h"

#include <QScrollArea>
#include <QMap>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QDebug>


IndexInfoDialog::IndexInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IndexInfoDialog)
{
    ui->setupUi(this);
}

IndexInfoDialog::IndexInfoDialog(EsIndex * esIndex){
    flushIndexInfo(esIndex);
}

void IndexInfoDialog::flushIndexInfo(EsIndex *esIndex){
    QString indexName = esIndex->getName();
    QString settings = esIndex->getSettings();
    QString *aliasNames = esIndex->getAliasNames();
    QMap<QString,QString> mappings = esIndex->getMappings();

    QVBoxLayout * layout = new QVBoxLayout;
    QVBoxLayout * vlayout = new QVBoxLayout;

    QString indexNameL = "索引名称";
    QString aliasNameL = "索引别名";
    QString settingsNameL = "settings";
    QString mappingsL = "mappings";
    QString aliasNameStr;
    if(aliasNames != NULL){

        int size = sizeof(aliasNames)/sizeof(aliasNames[0]);
        QStringList aliasNameList;
        if(size !=  0){
            for(long j = 0; j < size; j ++){
                QString aliasName = aliasNames[j];
                aliasNameList<<aliasName;
            }
            aliasNameStr = aliasNameList.join(",");
        }
    }else{
        aliasNameStr = "";
    }

    QHBoxLayout * indexLayout = CommonUtils::createShowLayout(indexNameL,indexName);
    QHBoxLayout * aliasLayout = CommonUtils::createShowLayout(aliasNameL,aliasNameStr);
    QHBoxLayout * settingsLayout = CommonUtils::createShowLayout(settingsNameL,settings);

    vlayout->addLayout(indexLayout);
    vlayout->addLayout(aliasLayout);
    vlayout->addLayout(settingsLayout);

    QVBoxLayout * vmLayout = new QVBoxLayout;

    QStringList keys = mappings.keys();
    for (int i = 0; i < mappings.size(); i++) {
        QString key = keys.at(i);
        QString value = mappings.value(key);
        QHBoxLayout * mLayout = CommonUtils::createShowLayout(key,value);
        vmLayout->addLayout(mLayout);
    }
    QHBoxLayout * mappingssLayout = CommonUtils::createShowLayout(mappingsL, vmLayout);

    vlayout->addLayout(mappingssLayout);

    QScrollArea * scrollArea = new QScrollArea;
    scrollArea->setLayout(vlayout);
    layout->addWidget(scrollArea);
    this->setLayout(layout);


}
IndexInfoDialog::~IndexInfoDialog()
{
    delete ui;
}
