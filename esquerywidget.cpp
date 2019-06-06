#include "esquerywidget.h"

#include "esutils.h"
#include <QDebug>


EsQueryWidget::EsQueryWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * boxLayout = new QVBoxLayout;
    // 查询条
    QToolBar * toolBar = new QToolBar;

    QAction * mustActon = new QAction("must");
    QAction * mustNotActon = new QAction("mustNot");
    QAction * shouldActon = new QAction("should");
    QAction * boolActon = new QAction("bool");
    QAction * idsActon = new QAction("ids");

    QAction * matchActon = new QAction("match");
    QAction * multMatchActon = new QAction("multMatch");
    QAction * matchPhraseActon = new QAction("matchPhrase");

    QAction * termActon = new QAction("term");
    QAction * termsActon = new QAction("terms");

    QAction * rangeActon = new QAction("range");
    QAction * fuzzyActon = new QAction("fuzzy");
    QAction * regexAction = new QAction("regex");
    QAction * wildcardAction = new QAction("wildcard");
    QAction * existAction = new QAction("exist");

    toolBar->addAction(mustActon);
    toolBar->addAction(mustNotActon);
    toolBar->addAction(shouldActon);
    toolBar->addAction(boolActon);
    toolBar->addAction(idsActon);
    toolBar->addAction(matchActon);
    toolBar->addAction(multMatchActon);
    toolBar->addAction(matchPhraseActon);

    toolBar->addAction(termActon);
    toolBar->addAction(termsActon);
    toolBar->addAction(rangeActon);
    toolBar->addAction(fuzzyActon);
    toolBar->addAction(regexAction);

    toolBar->addAction(wildcardAction);
    toolBar->addAction(existAction);


    // 查询路径
    QLineEdit * urlBar = new QLineEdit;
    // 文本域:参数
    QTextBrowser *paramBar = new QTextBrowser;
    // 结果列表
    QTableWidget * resultContent = new QTableWidget;
    // 结果条数信息
    QLabel * resNum = new QLabel;

    this->urlBar = urlBar;
    this->paramBar = paramBar;
    this->resNum = resNum;
    this->resultContent = resultContent;

    boxLayout->addWidget(toolBar);
    boxLayout->addWidget(urlBar);
    boxLayout->addWidget(paramBar);
    boxLayout->addWidget(resultContent);

    this->setLayout(boxLayout);


    // 槽事件
    connect(mustActon,SIGNAL(triggered()),this,SLOT(must()));
    connect(mustNotActon,SIGNAL(triggered()),this,SLOT(mustNot()));
    connect(shouldActon,SIGNAL(triggered()),this,SLOT(should()));
    connect(boolActon,SIGNAL(triggered()),this,SLOT(boolF()));
    connect(idsActon,SIGNAL(triggered()),this,SLOT(ids()));
    connect(matchActon,SIGNAL(triggered()),this,SLOT(match()));
    connect(multMatchActon,SIGNAL(triggered()),this,SLOT(multMatch()));
    connect(matchPhraseActon,SIGNAL(triggered()),this,SLOT(matchPhrase()));
    connect(termActon,SIGNAL(triggered()),this,SLOT(term()));
    connect(termsActon,SIGNAL(triggered()),this,SLOT(terms()));
    connect(rangeActon,SIGNAL(triggered()),this,SLOT(range()));
    connect(fuzzyActon,SIGNAL(triggered()),this,SLOT(fuzzy()));
    connect(regexAction,SIGNAL(triggered()),this,SLOT(regex()));
    connect(wildcardAction,SIGNAL(triggered()),this,SLOT(wildcard()));
    connect(existAction,SIGNAL(triggered()),this,SLOT(exist()));

}


void EsQueryWidget::must(){
    setUrlBar();
    this->paramBar->setText("{\
                            \"query\":{\
                                \"term\":{\
                                    \"field\":\"value\"\
                                }\
                            }\
                        }");
}
void EsQueryWidget::mustNot(){

}
void EsQueryWidget::should(){}
void EsQueryWidget::boolF(){}
void EsQueryWidget::ids(){}
void EsQueryWidget::match(){}
void EsQueryWidget::multMatch(){}
void EsQueryWidget::matchPhrase(){}
void EsQueryWidget::term(){}
void EsQueryWidget::terms(){}
void EsQueryWidget::range(){}
void EsQueryWidget::fuzzy(){}
void EsQueryWidget::regex(){}
void EsQueryWidget::wildcard(){}
void EsQueryWidget::exist(){}

void EsQueryWidget::setIndex(EsIndex *esIndex){
    this->currIndex = esIndex;
}

void EsQueryWidget::setUrlBar(){
    EsIndex * index = this->currIndex;
    Conn * conn = this->conn;
    QString baseUrl;
    EsUtils::getBaseUrl(baseUrl,conn);
    this->urlBar->setText(baseUrl+"_search");
    this->urlBar->setEnabled(false);
}

void EsQueryWidget::setConn(Conn *conn){
    this->conn = conn;
}
