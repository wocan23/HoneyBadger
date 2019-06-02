#ifndef ESUTILS_H
#define ESUTILS_H

#include <QString>
class EsUtils
{
public:
    EsUtils();

    static QList<QMap<QString,QString>> query(QString url);
};

#endif // ESUTILS_H
