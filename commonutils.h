#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QHBoxLayout>
#include <QWidget>

class CommonUtils
{
public:
    CommonUtils();

    static QHBoxLayout * createShowLayout(QString& key, QString& value);
    static QHBoxLayout * createShowLayout(QString& key, QLayout* layout);
};

#endif // COMMONUTILS_H
