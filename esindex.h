#ifndef ESINDEX_H
#define ESINDEX_H

#include <QString>


class EsIndex
{
private:
    QString name;
    QString *aliasNames;
    QString settings;
    QString mappings;
public:
    EsIndex();
    ~EsIndex();

    void setName(QString name);
    void setAliasNames(QString *aliasNames);
    void setSettings(QString settings);
    void setMappings(QString mappings);

    QString getName();
    QString* getAliasNames();
    QString getSettings();
    QString getMappings();
};

#endif // ESINDEX_H
