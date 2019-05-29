#ifndef ESTREEWIDGET_H
#define ESTREEWIDGET_H

#include <QWidget>
#include<QTreeWidget>

class EsTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit EsTreeWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ESTREEWIDGET_H
