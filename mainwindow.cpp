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

    this->ui->mainLayout->addWidget(treeWidget);
    this->ui->mainLayout->addWidget(scrollArea);

    this->ui->mainLayout->setStretch(0,2);
    this->ui->mainLayout->setStretch(1,8);

}

MainWindow::~MainWindow()
{
    delete ui;
}



