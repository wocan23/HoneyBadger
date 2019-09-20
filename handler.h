#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QString>
#include <conn.h>
#include <esindex.h>
#include "esindextabwidegt.h"

class Handler : public QObject
{
    Q_OBJECT
private:
    explicit Handler(QObject *parent = nullptr);

signals:
    void addConnSignal(Conn * conn);
    void editConnSignal(Conn * conn);
    void addTabSignal(Conn*conn,EsIndex* esIndex, TabType tabType);
    void queryIndexSinal();
public:
    static Handler* getInstance();
    bool isDigitString(QString src);
    QString getUUID();




    void addConn(Conn *conn);
    void editConn(Conn *conn);

public slots:

private:
    static Handler *hand;
};


#endif // HANDLER_H
