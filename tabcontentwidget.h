#ifndef TABCONTENTWIDGET_H
#define TABCONTENTWIDGET_H

#include <QWidget>
#include <pagewidget.h>
#include <esindextablewidget.h>
#include <QList>
#include <QMap>

class TabContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TabContentWidget(QWidget *parent = nullptr);
    void flushData(QList<QMap<QString,QString>>& data,QStringList& fields,int totalNum,int currentPage = 1,int pageSize = 10);

signals:

public slots:

private:
    PageWidget * pageWidget;
    EsIndexTableWidget * tableWidget;

};

#endif // TABCONTENTWIDGET_H
