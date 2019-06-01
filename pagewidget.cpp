#include "pagewidget.h"
#include <QToolBar>
#include <QPushButton>
#include <QLineEdit>


#define BUTTON_WIDTH 50
#define BUTTON_2WIDTH 50

PageWidget::PageWidget(QWidget *parent) : QToolBar(parent)
{
    QPushButton * toStart = new QPushButton;
    QPushButton * toEnd = new QPushButton;
    QPushButton * next = new QPushButton;
    QPushButton * last = new QPushButton;
    QLineEdit * cpage = new QLineEdit;


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

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setGeometry(10,200,10,100);

}

void PageWidget::toStartPage(){

}

void PageWidget::toEndPage(){

}

void PageWidget::lastPage(){

}

void PageWidget::nextPage(){

}

void PageWidget::toPage(int page){

}
