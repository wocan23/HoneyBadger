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

    // 获取行数
    QString newValue = CommonUtils::toJsonFormat(value);
    qDebug()<<newValue;

    QLabel *valueL = new QLabel(newValue);
//    valueL->adjustSize();
//    valueL->setGeometry(QRect(328, 240, 329, 27*8)); //四倍行距

//    valueL->setReadOnly(true);

    valueL->setWordWrap(true);
    valueL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);


    keyL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    valueL->setAlignment(Qt::AlignVCenter);

    hLayout->addWidget(keyL);
    hLayout->addWidget(valueL);

    hLayout->setStretch(0,4);
    hLayout->setStretch(1,6);
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
    QString str;
    int tab = 0;
    bool isTab = false;
    int quotNum = 0;
    for (int i=0; i < jsonStr.length(); i++) {
        QChar ch = jsonStr.at(i);
        if(ch == '"'){
            quotNum++;
        }
        // 前面加回车加tab
        if(ch == '}' && quotNum%2 == 0){
            tab--;
            str.append("\n");
            for (int j = 0 ; j < tab; j++) {
                str.append("\t");
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
                    str.append("\t");
                }
            }
        }
    }
    return str;
}
