#ifndef CONN_H
#define CONN_H

#include <QString>

class Conn
{
public:
    Conn();
    Conn(QString id,QString connName,QString userName,QString pwd,QString ip,QString port);
    QString getUserName();
    QString getPwd();
    QString getPort();
    QString getIp();
    QString getId();
    QString getConnName();
    void setUserName(QString userName);
    void setPwd(QString pwd);
    void setIp(QString ip);
    void setPort(QString port);
    void setId(QString id);
    void setConnName(QString connName);
private:
    QString userName;
    QString pwd;
    QString ip;
    QString port;
    QString connName;
    QString id;

};

#endif // CONN_H
