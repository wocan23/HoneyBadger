#include "conn.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QStringList>
#include <QDebug>

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

void Conn::parseIndics(QString str){
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(),&parseError);
    // 最外层是一个object/数组，这里是object
    QJsonObject obj = document.object();

    QJsonObject metaObj = obj.value("metadata").toObject();
    QJsonObject indicesObj = metaObj.value("indices").toObject();

    QStringList keys = indicesObj.keys();

    EsIndex *esIndices = new EsIndex[keys.size()];
    this->setIndexSize(keys.size());


    for (int i = 0; i < keys.size(); i ++) {
        QString key = keys.at(i);
        EsIndex *index = new EsIndex;
        index->setName(key);
        QJsonObject indexObj = indicesObj.value(key).toObject();
        index->setSettings(indexObj.value("settings").toString());
        index->setMappings(indexObj.value("mappings").toString());
        index->setAliasNames(indexObj.value("aliases").toString());
        esIndices[i] = *index;
    }
    this->esIndics = esIndices;
    qDebug()<<"end2";
}

EsIndex* Conn::getIndics(){
    return this->esIndics;
}

void Conn::setIndexSize(int size){
    this->indexSize = size;
}

int Conn::getIndexSize(){
    return this->indexSize;
}
