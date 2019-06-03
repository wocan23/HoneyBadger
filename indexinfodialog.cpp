#include "indexinfodialog.h"
#include "ui_indexinfodialog.h"

#include <QList>
#include <QMap>

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



}
IndexInfoDialog::~IndexInfoDialog()
{
    delete ui;
}
