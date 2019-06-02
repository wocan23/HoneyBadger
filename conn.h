#ifndef CONN_H
#define CONN_H

#include <QString>
#include "esindex.h"

class Conn
{
public:
    Conn();
    ~Conn();
    Conn(QString id,QString connName,QString userName,QString pwd,QString ip,QString port);
    QString getUserName();
    QString getPwd();
    QString getPort();
    QString getIp();
    QString getId();
    QString getConnName();
    int getIndexSize();
    void setUserName(QString userName);
    void setPwd(QString pwd);
    void setIp(QString ip);
    void setPort(QString port);
    void setId(QString id);
    void setConnName(QString connName);
    void setIndexSize(int size);


    void parseIndics(QString& str);
    EsIndex * getIndics();
private:
    QString userName;
    QString pwd;
    QString ip;
    QString port;
    QString connName;
    QString id;

    EsIndex *esIndics;
    int indexSize;

};

#endif // CONN_H
