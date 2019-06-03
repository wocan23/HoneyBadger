#ifndef TABCONTENTWIDGET_H
#define TABCONTENTWIDGET_H

#include <QWidget>
#include <pagewidget.h>
#include <esindextablewidget.h>
#include <QList>
#include <QMap>
#include <QStringList>
class TabContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TabContentWidget(QWidget *parent = nullptr);
    void flushData(QList<QMap<QString,QString>>& data,QStringList& fields,int totalNum,int currentPage = 1,int pageSize = 10);
    void setQueryUrl(QString &url);
    void setFields(QStringList &fields);
signals:

public slots:
   void to(int page, int pageSize);

private:
    PageWidget * pageWidget;
    EsIndexTableWidget * tableWidget;
    QString queryUrl;
    QStringList fields;

};

#endif // TABCONTENTWIDGET_H
