#ifndef ESINDEX_H
#define ESINDEX_H

#include <QString>
#include <QMap>

class EsIndex
{
private:
    QString name;
    QString *aliasNames;
    QString settings;
    QMap<QString,QString> mappings;
public:
    EsIndex();

    void setName(QString name);
    void setAliasNames(QString *aliasNames);
    void setSettings(QString settings);
    void setMappings(QMap<QString,QString> mappings);

    QString getName();
    QString* getAliasNames();
    QString getSettings();
    QMap<QString,QString> getMappings();
};

#endif // ESINDEX_H
