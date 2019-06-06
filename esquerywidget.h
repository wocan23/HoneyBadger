#ifndef ESQUERYWIDGET_H
#define ESQUERYWIDGET_H

#include "esindex.h"
#include "conn.h"
#include <QToolBar>
#include <QWidget>
#include <QLabel>

#include <QMap>
#include <QLineEdit>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QTableWidget>



class EsQueryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EsQueryWidget(QWidget *parent = nullptr);

    void setIndex(EsIndex * esIndex);
    void setConn(Conn * conn);
    void setUrlBar();

signals:

public slots:
    void must();
    void mustNot();
    void should();
    void boolF();
    void ids();
    void match();
    void multMatch();
    void matchPhrase();
    void term();
    void terms();
    void range();
    void fuzzy();
    void regex();
    void wildcard();
    void exist();

private:
    EsIndex * currIndex;
    QToolBar * toolBar;
    QLabel * resNum;
    QTextBrowser * paramBar;
    QLineEdit * urlBar;
    QTableWidget * resultContent;
    Conn * conn;
};

#endif // ESQUERYWIDGET_H
