#ifndef ESUTILS_H
#define ESUTILS_H

#include <QString>
#include <QJsonValue>
class EsUtils
{
public:
    EsUtils();

    static QList<QMap<QString,QString>> query(QString url);
    static QString JsonValueToString(QJsonValue value);
};

#endif // ESUTILS_H
