#include "commonutils.h"

#include <QLabel>
#include <QTextBrowser>
#include <QDebug>

CommonUtils::CommonUtils()
{

}

QHBoxLayout* CommonUtils::createShowLayout(QString &key, QString& value, int width){

    QHBoxLayout * hLayout = new QHBoxLayout;

    QLabel *keyL = new QLabel(key+":");
    keyL->setFixedWidth(100);

    QString newValue = CommonUtils::toJsonFormat(value);

    QLabel *valueL = new QLabel(newValue);

    valueL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    keyL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    valueL->setAlignment(Qt::AlignVCenter);

    hLayout->addWidget(keyL);
    hLayout->addWidget(valueL);

    hLayout->setEnabled(true);

    return hLayout;
}


QHBoxLayout* CommonUtils::createShowLayout(QString &key, QLayout* layout){

    QHBoxLayout * hLayout = new QHBoxLayout;

    QLabel *keyL = new QLabel(key+":");
    keyL->setFixedWidth(100);



    keyL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    hLayout->addWidget(keyL);
    hLayout->addLayout(layout);

    hLayout->setStretch(0,4);
    hLayout->setStretch(1,6);

    return hLayout;
}

QString CommonUtils::toJsonFormat(QString &jsonStr){
    QString oldStr = jsonStr;
    oldStr.replace("\t","");
    oldStr.replace(" ","");
    QString str;
    int tab = 0;
    bool isTab = false;
    int quotNum = 0;
    for (int i=0; i < oldStr.length(); i++) {
        QChar ch = oldStr.at(i);
        if(ch == '"'){
            quotNum++;
        }
        // 前面加回车加tab
        if(ch == '}' && quotNum%2 == 0){
            tab--;
            str.append("\n");
            for (int j = 0 ; j < tab; j++) {
                str.append("    ");
            }
        }

        str.append(ch);
        // 后处理
        if( quotNum%2 == 0){
            if(ch == '{'){
                tab++;
                str.append("\n");
                isTab = true;
            }else if(ch == ','){
                str.append("\n");
                isTab = true;
            }else{
                isTab = false;
            }
            if(isTab){
                for (int j = 0 ; j < tab; j++) {
                    str.append("    ");
                }
            }
        }
    }
    return str;
}

void CommonUtils::fullEsTableData(QTableWidget* tableWidget,QList<QMap<QString, QString> > &data, QStringList &fields){
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

}
