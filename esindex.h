#ifndef ESINDEX_H
#define ESINDEX_H

#include <QString>
#include <QMap>


class EsIndex
{
private:
    QString name;
    QStringList aliasNames;
    QString settings;
    QMap<QString,QString> mappings;

//    Conn *conn;
public:
    EsIndex();

    void setName(QString name);
    void setAliasNames(QStringList aliasNames);
    void setSettings(QString settings);
    void setMappings(QMap<QString,QString> mappings);
//    void setConn(Conn * conn);

    QString getName();
    QStringList getAliasNames();
    QString getSettings();
    QMap<QString,QString> getMappings();
//    Conn* getConn();


};

#endif // ESINDEX_H
