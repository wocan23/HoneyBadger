#include "conn.h"

Conn::Conn()
{

}

Conn::Conn(QString id,QString connName,QString userName,QString pwd,QString ip,QString port){
    this->id = id;
    this->connName = connName;
    this->userName = userName;
    this->pwd = pwd;
    this->ip = ip;
    this->port = port;
}

void Conn::setIp(QString ip){
    this->ip = ip;
}

void Conn::setPwd(QString pwd){
    this->pwd = pwd;
}

void Conn::setUserName(QString userName){
    this->userName = userName;
}

void Conn::setPort(QString port){
    this->port = port;
}

void Conn::setId(QString id){
    this->id = id;
}

void Conn::setConnName(QString connName){
    this->connName = connName;
}

QString Conn::getIp(){
    return this->ip;
}

QString Conn::getPwd(){
    return this->pwd;
}

QString Conn::getPort(){
    return this->port;
}

QString Conn::getUserName(){
    return this->userName;
}

QString Conn::getConnName(){
    return this->connName;
}

QString Conn::getId(){
    return this->id;
}
