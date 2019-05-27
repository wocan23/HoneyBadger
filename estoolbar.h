#ifndef ESTOOLBAR_H
#define ESTOOLBAR_H

#include <QWidget>
#include <QToolBar>

class EsToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit EsToolBar(QWidget *parent = nullptr);

signals:

private slots:
    void createConnDialog();
    void createDocDialog();
    void createIndexDialog();
    void createSearchDialog();
    void createEditDocDialog();
};

#endif // ESTOOLBAR_H
