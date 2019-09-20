#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "estoolbar.h"
#include <QDebug>
#include "estreewidgetitem.h"
#include <QStringList>
#include "httputils.h"
#include "conn.h"
#include "esindextabwidegt.h"
#include <QScrollArea>
#include <QSplitter>
#include <QLabel>
#include "estreewidget.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->esToolBar = new EsToolBar;
    this->ui->toolBarLayout->addWidget(this->esToolBar);

    EsTreeWidget * treeWidget = new EsTreeWidget;
    treeWidget->setHeaderHidden(true);


    EsIndexTabWidegt *tabWidget = new EsIndexTabWidegt;

    QScrollArea * scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(tabWidget);

    QSplitter * splitter = new QSplitter;
    splitter->addWidget(treeWidget);
    splitter->addWidget(scrollArea);
    splitter->setStretchFactor(0,2);
    splitter->setStretchFactor(1,700);

    this->ui->mainLayout->addWidget(splitter);

}

MainWindow::~MainWindow()
{
    delete ui;
}



