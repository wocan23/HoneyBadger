#include "handler.h"
#include <QUuid>

Handler::Handler(QObject *parent) : QObject(parent)
{

}

Handler* Handler::hand = new Handler;

Handler* Handler::getInstance(){
    return hand;
}


bool Handler::isDigitString(QString src){
    const char *s = src.toUtf8().data();
    while(*s && *s>='0' && *s<='9'){
        s++;
    }
    return !bool(*s);
}

void Handler::addConn(Conn *conn){
    emit addConnSignal(conn);
}

void Handler::editConn(Conn *conn){
    emit editConnSignal(conn);
}

QString Handler::getUUID(){
    QUuid id = QUuid::createUuid();
    QString strId = id.toString();
    return strId;
}

