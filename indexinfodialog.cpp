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
    QStringList aliasNames = esIndex->getAliasNames();
    QMap<QString,QString> mappings = esIndex->getMappings();

    QVBoxLayout * layout = new QVBoxLayout;
    QVBoxLayout * vlayout = new QVBoxLayout;

    QString indexNameL = "索引名称";
    QString aliasNameL = "索引别名";
    QString settingsNameL = "settings";
    QString mappingsL = "mappings";
    QString aliasNameStr;
    if(aliasNames.size() != 0){
        aliasNameStr = aliasNames.join(",");
    }else{
        aliasNameStr = "";
    }

    QSize dialogSize = this->size();
    int width = dialogSize.width();

    QHBoxLayout * indexLayout = CommonUtils::createShowLayout(indexNameL,indexName,width/3*2);
    QHBoxLayout * aliasLayout = CommonUtils::createShowLayout(aliasNameL,aliasNameStr,width/3*2);
    QHBoxLayout * settingsLayout = CommonUtils::createShowLayout(settingsNameL,settings,width/3*2);

    vlayout->addLayout(indexLayout);
    vlayout->addLayout(aliasLayout);
    vlayout->addLayout(settingsLayout);

    QVBoxLayout * vmLayout = new QVBoxLayout;

    QStringList keys = mappings.keys();
    for (int i = 0; i < mappings.size(); i++) {
        QString key = keys.at(i);
        QString value = mappings.value(key);
        QHBoxLayout * mLayout = CommonUtils::createShowLayout(key,value,width/3*2);
        vmLayout->addLayout(mLayout);
    }
    QHBoxLayout * mappingssLayout = CommonUtils::createShowLayout(mappingsL, vmLayout);

    vlayout->addLayout(mappingssLayout);

    QScrollArea * scrollArea = new QScrollArea;
    vlayout->setContentsMargins(10,10,10,10);
    scrollArea->setLayout(vlayout);
    layout->addWidget(scrollArea);
    this->setLayout(layout);


}
IndexInfoDialog::~IndexInfoDialog()
{
    delete ui;
}
