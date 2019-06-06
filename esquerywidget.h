#ifndef ESQUERYWIDGET_H
#define ESQUERYWIDGET_H

#include "esindex.h"
#include "conn.h"
#include <QToolBar>
#include <QWidget>
#include <QLabel>

#include <QMap>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPlainTextEdit>



class EsQueryWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EsQueryWidget(QWidget *parent = nullptr);

    void setIndex(EsIndex * esIndex);
    void setConn(Conn * conn);
    void setUrlBar();
    void setParamBar(QString &paramStr);

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

    void query();
    void clearParam();

private:
    EsIndex * currIndex;
    QToolBar * toolBar;
    QLabel * resNum;
    QPlainTextEdit * paramBar;
    QLineEdit * urlBar;
    QTableWidget * resultContent;
    Conn * conn;
};

#endif // ESQUERYWIDGET_H
