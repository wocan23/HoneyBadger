#include "esquerywidget.h"


#include <QSplitter>
#include <QPushButton>
#include "esutils.h"
#include "commonutils.h"
#include <simpleeditor.h>






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
    QAction * existAction = new QAction("exists");

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
    QHBoxLayout * hboxLayout = new QHBoxLayout;
    QLineEdit * urlBar = new QLineEdit;

    QPushButton * clearBtn = new QPushButton("清空");
    QPushButton * queryBtn = new QPushButton("查询");
    hboxLayout->addWidget(urlBar);
    hboxLayout->addWidget(clearBtn);
    hboxLayout->addWidget(queryBtn);


    // 文本域:参数
    QPlainTextEdit *paramBar = new MyGCodeTextEdit;
    // 结果列表
    QTableWidget * resultContent = new QTableWidget;

    QSplitter *querySplitter = new QSplitter(Qt::Vertical);
    querySplitter->addWidget(paramBar);
    querySplitter->addWidget(resultContent);
    querySplitter->setStretchFactor(0,2);
    querySplitter->setStretchFactor(1,7);
    // 结果条数信息
    QLabel * resNum = new QLabel;

    this->urlBar = urlBar;
    this->paramBar = paramBar;
    this->resNum = resNum;
    this->resultContent = resultContent;

    boxLayout->addWidget(toolBar);
    boxLayout->addLayout(hboxLayout);
//    boxLayout->addWidget(paramBar);
    boxLayout->addWidget(querySplitter);
    boxLayout->addWidget(resNum);

//    boxLayout->setStretchFactor(paramBar,3);
//    boxLayout->setStretchFactor(resultContent,6);
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

    connect(queryBtn,SIGNAL(clicked()),this,SLOT(query()));
    connect(clearBtn,SIGNAL(clicked()),this,SLOT(clearParam()));

}

void EsQueryWidget::setUrlBar(){
    EsIndex * index = this->currIndex;
    Conn * conn = this->conn;
    QString baseUrl1;
    EsUtils::getBaseUrl(baseUrl1,conn);
    this->urlBar->setText(baseUrl1+index->getName()+"/"+"_search");
    this->urlBar->setEnabled(false);
}

void EsQueryWidget::setConn(Conn *conn){
    this->conn = conn;
}

void EsQueryWidget::setParamBar(QString &paramStr){
    QString jsonFormatParam = CommonUtils::toJsonFormat(paramStr);
    this->paramBar->setPlainText(jsonFormatParam);
    // 字体
    QFont qf;
    qf.setBold(true);
    qf.setPointSize(16);
    qf.setFamily("华文仿宋");
    qf.setLetterSpacing(QFont::AbsoluteSpacing,0.9);

    this->paramBar->setFont(qf);

    // 颜色
    QPalette p = this->paramBar->palette();
    QColor color(75,75,75);
    p.setColor(QPalette::Active, QPalette::Text, color);
    this->paramBar->setPalette(p);



    bool finded = this->paramBar->find("FIELD",QTextDocument::FindCaseSensitively);
    QTextDocument* document = this->paramBar->document();
    QTextCursor cursor;
    if(!finded){
        this->paramBar->find("VALUE",QTextDocument::FindCaseSensitively);
        cursor = document->find("VALUE",QTextDocument::FindCaseSensitively);
    }else {
        cursor = document->find("FIELD",QTextDocument::FindCaseSensitively);
    }


    this->paramBar->setFocus();

    int pos = cursor.position();
//    this->paramBar->show();
    QTextCursor cs =this->paramBar->textCursor();
    cs.movePosition(QTextCursor::Start);
    cs.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,pos);
    this->paramBar->setTextCursor(cs);

}

void EsQueryWidget::query(){
    int totalSize = 0;
    QList<QMap<QString,QString>> resList = EsUtils::query(this->urlBar->text(),this->paramBar->toPlainText(),totalSize).data;
    QStringList fields = this->currIndex->getMappings().keys();
    CommonUtils::fullEsTableData(this->resultContent,resList,fields);
    this->resNum->setText("总"+QString::number(totalSize)+"条，默认显示10条");
}

void EsQueryWidget::clearParam(){
    this->paramBar->clear();
}





void EsQueryWidget::must(){
    setUrlBar();
    QString paramStr = " { \
                       \"query\":{\
                           \"bool\":{\
                               \"must\":[\
                                   {\
                                       \"term\":{\
                                           \"FIELD\":\"VALUE\"\
                                       }\
                                   }\
                               ]\
                           }\
                       }\
                   }";
    setParamBar(paramStr);

}
void EsQueryWidget::mustNot(){
    setUrlBar();
    QString paramStr = " { \
                       \"query\":{\
                           \"bool\":{\
                               \"must_not\":[\
                                   {\
                                       \"term\":{\
                                           \"FIELD\":\"VALUE\"\
                                       }\
                                   }\
                               ]\
                           }\
                       }\
                   }";
    setParamBar(paramStr);
}
void EsQueryWidget::should(){
    setUrlBar();
    QString paramStr = " { \
                       \"query\":{\
                           \"bool\":{\
                               \"should\":[\
                                   {\
                                       \"term\":{\
                                           \"FIELD\":\"VALUE\"\
                                       }\
                                   }\
                               ]\
                           }\
                       }\
                   }";
    setParamBar(paramStr);
}
void EsQueryWidget::boolF(){
    setUrlBar();
    QString paramStr = " { \
                       \"query\":{\
                           \"bool\":{\
                               \"must\":[\
                                   {\
                                       \"term\":{\
                                           \"FIELD\":\"VALUE\"\
                                       }\
                                   }\
                               ],\
                                \"must_not\":[\
                                    {\
                                        \"term\":{\
                                            \"FIELD\":\"VALUE\"\
                                        }\
                                    }\
                                ],\
                               \"should\":[\
                                   {\
                                       \"term\":{\
                                           \"FIELD\":\"VALUE\"\
                                       }\
                                   }\
                               ]\
                           }\
                       }\
                   }";
    setParamBar(paramStr);
}
void EsQueryWidget::ids(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"ids\":{\
                                    \"values\":[\"VALUE\"]\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::match(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"match\":{\
                                    \"FIELD\":\"value\"\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::multMatch(){
    setUrlBar();
    QString paramStr = "{\
                       \"query\":{\
                           \"match\":{\
                               \"FIELD\":{\
                                   \"query\":\"VALUE\",\
                                   \"minimum_should_match\":1\
                               }\
                           }\
                       }\
                   }";
    setParamBar(paramStr);
}
void EsQueryWidget::matchPhrase(){
    setUrlBar();
    QString paramStr = "{\
                       \"query\":{\
                           \"match_phrase\":{\
                               \"FIELD\":{\
                                   \"query\":\"VALUE\",\
                                   \"minimum_should_match\":1\
                               }\
                           }\
                       }\
                   }";
    setParamBar(paramStr);
}
void EsQueryWidget::term(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"term\":{\
                                    \"FIELD\":\"VALUE\"\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::terms(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"terms\":{\
                                    \"FIELD\":[\"VALUE\"]\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::range(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"range\":{\
                                    \"FIELD\":{\
                                        \"gte\":0,\
                                        \"lte\":20\
                                    }\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::fuzzy(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"fuzzy\":{\
                                    \"FIELD\":\"VALUE\"\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::regex(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"regex\":{\
                                    \"FIELD\":\"VALUE\"\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::wildcard(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"wildcard\":{\
                                    \"FIELD\":\"VALUE\"\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}
void EsQueryWidget::exist(){
    setUrlBar();
    QString paramStr = "{\
                            \"query\":{\
                                \"exists\":{\
                                    \"FIELD\":\"VALUE\"\
                                }\
                            }\
                        }";
    setParamBar(paramStr);
}

void EsQueryWidget::setIndex(EsIndex *esIndex){
    this->currIndex = esIndex;
}


