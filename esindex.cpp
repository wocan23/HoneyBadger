#include "esindex.h"

EsIndex::EsIndex()
{
}

void EsIndex::setName(QString name){
    this->name = name;
}
void EsIndex::setAliasNames(QStringList aliasNames){
    this->aliasNames = aliasNames;
}
void EsIndex::setSettings(QString settings){
    this->settings = settings;
}
void EsIndex::setMappings(QMap<QString,QString> mappings){
    this->mappings = mappings;
}

QString EsIndex::getName(){
    return this->name;
}
QStringList EsIndex::getAliasNames(){
    return this->aliasNames;
}
QString EsIndex::getSettings(){
    return this->settings;
}
QMap<QString,QString> EsIndex::getMappings(){
    return this->mappings;
}

//void EsIndex::setConn(Conn *conn){
//    this->conn = conn;
//}

//Conn* EsIndex::getConn(){
//    return this->conn;
//}
