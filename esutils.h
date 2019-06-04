#ifndef ESUTILS_H
#define ESUTILS_H

#include <QString>
#include <QJsonValue>
#include "esindex.h"
#include "conn.h"
class EsUtils
{
public:
    EsUtils();

    static QList<QMap<QString,QString>> query(QString url,int& size);
    static QString JsonValueToString(QJsonValue value);
    static EsIndex* parseIndics(QString &str,int& size);
    static bool changeName(Conn *conn, EsIndex* esIndex,QString& newName);
    static bool addAlias(Conn *conn, EsIndex* esIndex,QString& aliasName);
    static bool changeAlias(Conn *conn, EsIndex* esIndex,QString& oldAlias,QString& newAlias);
    static bool removeAlias(Conn *conn, EsIndex* esIndex,QString& oldAlias);
};

#endif // ESUTILS_H
