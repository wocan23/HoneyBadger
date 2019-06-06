#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include <QHBoxLayout>
#include <QWidget>
#include <QInputDialog>
#include <QTableWidget>

class CommonUtils
{
public:
    CommonUtils();

    static QHBoxLayout * createShowLayout(QString& key, QString& value,int width);
    static QHBoxLayout * createShowLayout(QString& key, QLayout* layout);
    static QString toJsonFormat(QString &jsonStr);
    static void fullEsTableData(QTableWidget* tableWidget,QList<QMap<QString,QString>>& data,QStringList& fields);
};

#endif // COMMONUTILS_H
