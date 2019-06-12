#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSplitter>
#include <QScrollArea>
#include "estoolbar.h"
#include <QDebug>
#include <QStringList>
#include "httputils.h"
#include "conn.h"
#include "esindextabwidegt.h"
#include "estreewidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->esToolBar = new EsToolBar;
    this->ui->toolBarLayout->addWidget(this->esToolBar);


    EsTreeWidget * treeWidget = new EsTreeWidget;
    QSizePolicy treePolicy = treeWidget->sizePolicy();
    treePolicy.setHorizontalStretch(2);
    treeWidget->setSizePolicy(treePolicy);
    treeWidget->setMinimumWidth(60);
    treeWidget->setMaximumWidth(600);


    treeWidget->setHeaderHidden(true);
    EsIndexTabWidegt *tab = new EsIndexTabWidegt;
    tab->setVisible(true);
    //    tab->setMaximumWidth(20);
    tab->setAutoFillBackground(true);
//    tab->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    tab->setVisible(true);
//    tab->setTabsClosable(true);


    QSplitter * splitter = new QSplitter(Qt::Horizontal);

    QScrollArea * area = new QScrollArea;
    area->setWidget(tab);
    area->setWidgetResizable(true);
    area->setAutoFillBackground(true);
    area->setMinimumWidth(300);
    area->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);
    area->setVisible(true);

//    QSizePolicy areaP = area->sizePolicy();
//    areaP.setHorizontalStretch(9);
//    area->setSizePolicy(areaP);
//    area->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

//    splitter->setStretchFactor(0,1);
//    splitter->setStretchFactor(1,7);

    splitter->addWidget(treeWidget);
    splitter->addWidget(area);
    splitter->setCollapsible(0,true);


    this->ui->verticalLayout->addWidget(splitter);



}

MainWindow::~MainWindow()
{
    delete ui;
}



