#ifndef ESUTILS_H
#define ESUTILS_H

#include <QString>
#include <QJsonValue>
#include "esindex.h"
#include "conn.h"

class EsResult{
public:
    EsResult();
    int code;
    QString msg;
    QList<QMap<QString,QString>> data;

    static EsResult success();
    static EsResult success(QList<QMap<QString,QString>> data);
    static EsResult success(QString msg, QList<QMap<QString,QString>> data);
    static EsResult failed(int code, QString msg);
};

class EsUtils
{
public:
    EsUtils();

    static EsResult parseBoolEsResult(QString & resStr);
    static EsResult query(QString url,QString param,int& size);
    static QString JsonValueToString(QJsonValue value);
    static EsIndex* parseIndics(QString &str,int& size);
    static EsResult changeName(Conn *conn, EsIndex* esIndex,QString& newName);
    static EsResult addAlias(Conn *conn, EsIndex* esIndex,QString& aliasName);
    static EsResult changeAlias(Conn *conn, EsIndex* esIndex,QString& oldAlias,QString& newAlias);
    static EsResult removeAlias(Conn *conn, EsIndex* esIndex,QString& oldAlias);
    static void getBaseUrl(QString &url,Conn* conn);


};



#endif // ESUTILS_H
