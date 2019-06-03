#ifndef ESINDEXTABLEWIDGET_H
#define ESINDEXTABLEWIDGET_H

#include <QTableWidget>
#include <QStringList>

class EsIndexTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit EsIndexTableWidget(QWidget *parent = nullptr);

signals:

public slots:


private:
    QStringList titles;
};

#endif // ESINDEXTABLEWIDGET_H
