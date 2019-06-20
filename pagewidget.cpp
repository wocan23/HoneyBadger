#include "pagewidget.h"
#include <QToolBar>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>


#define BUTTON_WIDTH 50
#define BUTTON_2WIDTH 50

PageWidget::PageWidget(int totalNum, int pageSize, int currentPage){
    this->totalNum = totalNum;
    this->pageSize = pageSize;
     this->totalPage = (this->totalNum + this->pageSize -1)/this->pageSize;
    if(currentPage > this->totalPage){
        this->currentPage = this->totalPage;
    }else if(currentPage < 1){
        this->currentPage = 1;
    }else{
        this->currentPage = currentPage;
    }

    QPushButton * toStart = new QPushButton;
    QPushButton * toEnd = new QPushButton;
    QPushButton * next = new QPushButton;
    QPushButton * last = new QPushButton;
    QLineEdit * cpage = new QLineEdit;
    this->cpage = cpage;
    QLabel *label = new QLabel;
    this->label = label;
    QString labelStr = "总"+QString::number(this->totalNum)+"条";
    label->setText(labelStr);

    toStart->setText("<<");
    toEnd->setText(">>");
    next->setText(">");
    last->setText("<");
    cpage->setText("1");
    cpage->setFixedWidth(BUTTON_WIDTH);
    cpage->setAlignment(Qt::AlignHCenter);

    toStart->setFixedWidth(BUTTON_2WIDTH);
    toEnd->setFixedWidth(BUTTON_2WIDTH);
    next->setFixedWidth(BUTTON_WIDTH);
    last->setFixedWidth(BUTTON_WIDTH);


    this->addWidget(toStart);
    this->addWidget(last);
    this->addWidget(cpage);
    this->addWidget(next);
    this->addWidget(toEnd);
    this->addWidget(label);

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setGeometry(10,200,10,100);

    connect(toStart,SIGNAL(clicked()),this,SLOT(toStartPage()));
    connect(toEnd,SIGNAL(clicked()),this,SLOT(toEndPage()));
    connect(last,SIGNAL(clicked()),this,SLOT(lastPage()));
    connect(next,SIGNAL(clicked()),this,SLOT(nextPage()));
    connect(cpage,SIGNAL(editingFinished()),this,SLOT(toPage()));



}

void PageWidget::toStartPage(){
    this->currentPage = 1;
    this->cpage->setText(QString::number(currentPage));
    emit this->to(this->currentPage,this->pageSize);
}

void PageWidget::toEndPage(){
    this->currentPage = this->totalPage;
    this->cpage->setText(QString::number(currentPage));
    emit this->to(this->currentPage,this->pageSize);
}

void PageWidget::lastPage(){
    if(this->currentPage != 1){
        this->currentPage = this->currentPage - 1;
        this->cpage->setText(QString::number(currentPage));
        emit this->to(this->currentPage,this->pageSize);
    }

}

void PageWidget::nextPage(){
    if(this->currentPage != this->totalPage){
        this->currentPage = this->currentPage+1;
        this->cpage->setText(QString::number(currentPage));
        emit this->to(this->currentPage,this->pageSize);
    }

}

void PageWidget::toPage(){
    QString cpageStr = this->cpage->text();
    int cpageInt = cpageStr.toInt();
    if(cpageInt < 1 || cpageInt > this->totalPage){
        this->cpage->setText(QString::number(currentPage));
        return;
    }
    this->currentPage = cpageInt;
    this->cpage->setText(QString::number(currentPage));
    emit this->to(this->currentPage,this->pageSize);
}

void PageWidget::changeSize(){

}

void PageWidget::changeShow(int totalNum, int pageSize, int currentPage){
    this->totalNum = totalNum;
    this->pageSize = pageSize;
     this->totalPage = (this->totalNum + this->pageSize -1)/this->pageSize;
    if(currentPage > this->totalPage){
        this->currentPage = this->totalPage;
    }else if(currentPage < 1){
        this->currentPage = 1;
    }else{
        this->currentPage = currentPage;
    }
    this->cpage->setText(QString::number(this->currentPage));
    QString labelStr = "总"+QString::number(this->totalNum)+"条,共"+QString::number(totalPage)+"页";
    this->label->setText(labelStr);
}
