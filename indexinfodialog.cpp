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
#include <QBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>



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


    QJsonObject jsonObj;
    QStringList keys = mappings.keys();
    for (int i = 0; i < mappings.size(); i++) {
        QString key = keys.at(i);
        QString value = mappings.value(key);
        jsonObj.insert(key,value);
    }
    QJsonDocument document;
    document.setObject(jsonObj);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString jsonStr(byteArray);
    QString mappingsStr = CommonUtils::toJsonFormat(jsonStr);

    QString info;
    info.append(indexNameL+":"+indexName+"\n");
    info.append(aliasNameL+":"+aliasNameStr+"\n");
    info.append(settingsNameL+":"+CommonUtils::toJsonFormat(settings)+"\n");
    info.append(mappingsL+":"+ mappingsStr+"\n");

    QLabel *label = new QLabel(info);
    QFont ft;
    ft.setPointSize(13);
    ft.setWeight(3);
    label->setFont(ft);
    QScrollArea * scrollArea = new QScrollArea;
    scrollArea->setWidget(label);

    QBoxLayout * layout = new QBoxLayout(QBoxLayout::TopToBottom);
    layout->addWidget(scrollArea);
    this->setLayout(layout);


}
IndexInfoDialog::~IndexInfoDialog()
{
    delete ui;
}
