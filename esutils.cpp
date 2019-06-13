#include "esutils.h"
#include "httputils.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QMap>
#include <QList>
#include <QDebug>


EsResult::EsResult(){

}

EsResult EsResult::success(){
    EsResult result;
    result.code = 1;
    return result;
}

EsResult EsResult::success(QList<QMap<QString, QString> > data){
    EsResult result;
    result.code = 1;
    result.data =  data;
    return result;
}

EsResult EsResult::success(QString msg, QList<QMap<QString, QString> > data){
    EsResult result;
    result.code = 1;
    result.msg = msg;
    result.data =  data;
    return result;
}

EsResult EsResult::failed(int code, QString msg){
    EsResult result;
    result.code = code;
    result.msg = msg;
    return result;
}

EsUtils::EsUtils()
{

}

EsResult EsUtils::query(QString url,QString param,int& totalSize){
    QString res = HttpUtils::Post(url,param);
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(res.toUtf8(),&parseError);
    // 最外层是一个object/数组，这里是object
    QJsonObject obj = document.object();
    QJsonObject hitObj = obj.value("hits").toObject();
    totalSize = hitObj.value("total").toInt();
    QJsonArray hitArr = hitObj.value("hits").toArray();
    int size = hitArr.size();
    QList<QMap<QString,QString>> list;
    for (int i = 0 ; i < size; i ++) {
        QMap<QString,QString> map;
        QJsonObject obj = hitArr.at(i).toObject();
        QStringList  keys = obj.keys();
        for (int j = 0; j < keys.size(); j++) {
            QString key = keys.at(j);
            QJsonValue v = obj.value(key);          
            if("_source" == key){
                QJsonObject sObj = v.toObject();
                QStringList sourceKeys = sObj.keys();
                for( int k = 0; k < sourceKeys.size(); k ++){
                    QString skey = sourceKeys.at(k);
                    QJsonValue sv = sObj.value(skey);
                    map.insert(skey,JsonValueToString(sv));
                }
            }
            map.insert(key,JsonValueToString(v));
        }
        list.insert(i,map);
    }
    return EsResult::success(list);

}

EsIndex* EsUtils::parseIndics(QString &str,int& isize){
    QJsonParseError parseError;
    QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(),&parseError);
    // 最外层是一个object/数组，这里是object
    QJsonObject obj = document.object();

    QJsonObject metaObj = obj.value("metadata").toObject();
    QJsonObject indicesObj = metaObj.value("indices").toObject();

    QStringList keys = indicesObj.keys();

    EsIndex *esIndices = new EsIndex[keys.size()];
    int indexSize = keys.size();
    isize = indexSize;


    for (int i = 0; i < keys.size(); i ++) {
        QString key = keys.at(i);
        EsIndex *index = new EsIndex;
        index->setName(key);
        QJsonObject indexObj = indicesObj.value(key).toObject();

        QJsonDocument jsonDoc;
        QJsonObject obj = indexObj.value("settings").toObject();
        jsonDoc.setObject(obj);
        index->setSettings(jsonDoc.toJson(QJsonDocument::Compact));

        QJsonObject mObj = indexObj.value("mappings").toObject();
        if(mObj.keys().size() != 0){
            QString key1 = mObj.keys().at(0);
            QMap<QString,QString>  mappings;
            QJsonObject pObj = mObj.value(key1).toObject().value("properties").toObject();
            QStringList pkeys = pObj.keys();
            for (int j = 0; j < pkeys.size(); j++) {
                QString pkey = pkeys.at(j);
                QString typeValue = pObj.value(pkey).toObject().value("type").toString();
                mappings.insert(pkey,typeValue);
            }

            index->setMappings(mappings);
        }

        QJsonArray aliasJsonArr = indexObj.value("aliases").toArray();

        if(aliasJsonArr.size() >0){
            QStringList alias;
           for (int j = 0; j < aliasJsonArr.size();j++) {
               alias << aliasJsonArr.at(j).toString();
           };
           index->setAliasNames(alias);
        }


        esIndices[i] = *index;
    }
    return esIndices;
}

QString EsUtils::JsonValueToString(QJsonValue value){
    QString rsvalue;
    if(value.isString()){
        rsvalue = value.toString();

    }
    if(value.isDouble()){
        double svalue = value.toDouble();
        rsvalue = QString::number(svalue,'f',2);

    }
    if(value.toBool()){
        bool svalue = value.toBool();
        rsvalue = QString::number(svalue,'f',0);
    }
    return rsvalue;
}

EsResult EsUtils::parseBoolEsResult(QString & resStr){
    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(resStr.toUtf8(), &jsonerror);
    QJsonObject obj = doc.object();
    QJsonValue ack = obj.contains("acknowledged");
    if(ack.isNull()){
        return EsResult::failed(0,"失败");
    }
    return EsResult::success();
}
EsResult EsUtils::changeName(Conn *conn, EsIndex *esIndex, QString &newName){
    EsResult result;
    return result;
}

EsResult EsUtils::changeAlias(Conn *conn, EsIndex *esIndex, QString &oldAlias, QString &newAlias){
    QString indexName =  esIndex->getName();
    QString url ;
    getBaseUrl(url,conn);
    url = url + "_aliases";
    QString param("{ \
                  \"actions\": [ \
                    { \
                      \"remove\": { \
                        \"index\": \""+indexName+"\", \
                        \"alias\": \""+oldAlias+"\" \
                      } ,\
                      \"add\": { \
                        \"index\": \""+indexName+"\", \
                        \"alias\": \""+newAlias+"\" \
                      } \
                    } \
                  ] \
                }");
    QString res = HttpUtils::Post(url,param);
    return parseBoolEsResult(res);
}

EsResult EsUtils::removeAlias(Conn *conn, EsIndex *esIndex, QString &aliasName){
    QString indexName =  esIndex->getName();
    QString url ;
    getBaseUrl(url,conn);
    url = url + "_aliases";
    QString param("{ \
                  \"actions\": [ \
                    { \
                      \"remove\": { \
                        \"index\": \""+indexName+"\", \
                        \"alias\": \""+aliasName+"\" \
                      } \
                    } \
                  ] \
                }");
    QString res = HttpUtils::Post(url,param);
    return parseBoolEsResult(res);
}

EsResult EsUtils::addAlias(Conn *conn, EsIndex *esIndex, QString &aliasName){
    QString indexName =  esIndex->getName();
    QString url ;
    getBaseUrl(url,conn);
    url = url + "_aliases";
    QString param("{ \
                  \"actions\": [ \
                    { \
                      \"add\": { \
                        \"index\": \""+indexName+"\", \
                        \"alias\": \""+aliasName+"\" \
                      } \
                    } \
                  ] \
                }");
    QString res = HttpUtils::Post(url,param);
    return parseBoolEsResult(res);
}

void EsUtils::getBaseUrl(QString &url, Conn *conn){
    if(conn->getUserName() == NULL || conn->getPwd() == NULL || conn->getUserName() == "" || conn->getPwd() == ""){
        url = "http://"+conn->getIp()+":"+conn->getPort()+"/";
    }else{
        url = "http://"+conn->getUserName()+":"+conn->getPwd()+"@"+conn->getIp()+":"+conn->getPort()+"/";
    }
}


