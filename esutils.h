#ifndef ESUTILS_H
#define ESUTILS_H

#include <QString>
#include <QJsonValue>
#include "esindex.h"
class EsUtils
{
public:
    EsUtils();

    static QList<QMap<QString,QString>> query(QString url);
    static QString JsonValueToString(QJsonValue value);
    static EsIndex* parseIndics(QString str,int* size);
};

#endif // ESUTILS_H
