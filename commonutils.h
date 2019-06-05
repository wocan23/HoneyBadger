#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QHBoxLayout>
#include <QWidget>
#include <QInputDialog>

class CommonUtils
{
public:
    CommonUtils();

    static QHBoxLayout * createShowLayout(QString& key, QString& value,int width);
    static QHBoxLayout * createShowLayout(QString& key, QLayout* layout);
    static QString toJsonFormat(QString &jsonStr);
};

#endif // COMMONUTILS_H
