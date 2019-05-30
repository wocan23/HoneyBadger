#include "esindex.h"

EsIndex::EsIndex()
{

}


void EsIndex::setName(QString name){
    this->name = name;
}
void EsIndex::setAliasNames(QString aliasNames){
    this->aliasNames = this->aliasNames;
}
void EsIndex::setSettings(QString settings){
    this->settings = settings;
}
void EsIndex::setMappings(QString mappings){
    this->mappings = mappings;
}

QString EsIndex::getName(){
    return this->name;
}
QString EsIndex::getAliasNames(){
    return this->aliasNames;
}
QString EsIndex::getSettings(){
    return this->settings;
}
QString EsIndex::getMappings(){
    return this->mappings;
}
