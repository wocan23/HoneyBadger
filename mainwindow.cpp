#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "estoolbar.h"
#include <QDebug>
#include "estreewidgetitem.h"
#include <QStringList>
#include "httputils.h"
#include "conn.h"
#include "esindextabwidegt.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->esToolBar = new EsToolBar;
    this->ui->toolBarLayout->addWidget(this->esToolBar);
//    this->ui->mainLayout.a
    this->ui->treeWidget->setHeaderHidden(true);
    EsIndexTabWidegt *tabWidget = new EsIndexTabWidegt;
    this->ui->scrollArea->setWidget(tabWidget);



}

MainWindow::~MainWindow()
{
    delete ui;
}



