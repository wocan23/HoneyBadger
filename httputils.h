#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <QObject>

class HttpUtils : public QObject
{
    Q_OBJECT
private:
    explicit HttpUtils(QObject *parent = nullptr);
    static HttpUtils * util;
public:   
    static QString Post(QString url,QString json);
    static QString Get(QString url);
    static HttpUtils * getInstance();
signals:

public slots:
};

#endif // HTTPUTILS_H
