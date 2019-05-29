#include "httputils.h"
#include <QUrl>
#include "curl/curl.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QEventLoop>

HttpUtils::HttpUtils(QObject *parent) : QObject(parent)
{

}

HttpUtils * HttpUtils::util = new HttpUtils;
HttpUtils * HttpUtils::getInstance(){
    return util;
}

QString HttpUtils::Post(QString url,QString json){
    QNetworkAccessManager * _manager = new QNetworkAccessManager;
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    QNetworkReply *reply = _manager->post(request, json.toUtf8());
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop,SLOT(quit()));
    eventLoop.exec();       //block until finish
    responseData = reply->readAll();
    QString result;
    result.prepend(responseData);
    return result;
}

QString HttpUtils::Get(QString url){
    QNetworkAccessManager * _manager = new QNetworkAccessManager;
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    QNetworkReply *reply = _manager->get(request);
    QByteArray responseData;
    QEventLoop eventLoop;
    connect(_manager, SIGNAL(finished(QNetworkReply*)), &eventLoop,SLOT(quit()));
    eventLoop.exec();       //block until finish
    responseData = reply->readAll();
    QString result;
    result.prepend(responseData);
    return result;
}

