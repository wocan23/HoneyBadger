#include "commonutils.h"

#include <QLabel>
#include <QTextBrowser>

CommonUtils::CommonUtils()
{

}

QHBoxLayout* CommonUtils::createShowLayout(QString &key, QString& value){

    QHBoxLayout * hLayout = new QHBoxLayout;

    QLabel *keyL = new QLabel(key+":");
    keyL->setFixedWidth(100);
    QLabel *valueL = new QLabel(value);
    valueL->setText(value);
//    valueL->adjustSize();
//    valueL->setGeometry(QRect(328, 240, 329, 27*8)); //四倍行距

//    valueL->setReadOnly(true);

    valueL->setWordWrap(true);
    valueL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    valueL->setScaledContents(true);

    keyL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
//    valueL->setAlignment(Qt::AlignVCenter);

    hLayout->addWidget(keyL);
    hLayout->addWidget(valueL);

    hLayout->setStretch(0,4);
    hLayout->setStretch(1,6);

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
