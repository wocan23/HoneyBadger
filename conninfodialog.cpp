#include "conninfodialog.h"
#include "ui_conninfodialog.h"


#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLayoutItem>
#include <QSizePolicy>

ConnInfoDialog::ConnInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnInfoDialog)
{
    ui->setupUi(this);
}

ConnInfoDialog::ConnInfoDialog(Conn* conn){
    flushConnInfo(conn);
}

ConnInfoDialog::~ConnInfoDialog()
{
    delete ui;
}

void ConnInfoDialog::flushConnInfo(Conn *conn){
    QLabel *ip = new QLabel(conn->getIp());
    QLabel *port= new QLabel(conn->getPort());
    QLabel *user= new QLabel(conn->getUserName());
    QLabel *pwd= new QLabel(conn->getPwd());

    QLabel *ipL= new QLabel("ip:");
    QLabel *portL= new QLabel("port:");
    QLabel *userL= new QLabel("user:");
    QLabel *pwdL= new QLabel("pwd:");

    ip->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    port->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    user->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    pwd->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    ipL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    portL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    userL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    pwdL->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    ipL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    portL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    userL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    pwdL->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    ip->setAlignment(Qt::AlignVCenter);
    port->setAlignment(Qt::AlignVCenter);
    user->setAlignment(Qt::AlignVCenter);
    pwd->setAlignment(Qt::AlignVCenter);

    QVBoxLayout * vlayout = new QVBoxLayout;

    QHBoxLayout * ipLayout = new QHBoxLayout;
    QHBoxLayout * portLayout = new QHBoxLayout;
    QHBoxLayout * userNameLayout = new QHBoxLayout;
    QHBoxLayout * pwdLayout = new QHBoxLayout;



//    ipLayout->addItem(new QLayoutItem());
    ipLayout->addWidget(ipL);
    ipLayout->addWidget(ip);


    portLayout->addWidget(portL);
    portLayout->addWidget(port);

    userNameLayout->addWidget(userL);
    userNameLayout->addWidget(user);

    pwdLayout->addWidget(pwdL);
    pwdLayout->addWidget(pwd);

    ipLayout->setStretch(0,4);
    ipLayout->setStretch(1,6);

    portLayout->setStretch(0,4);
    portLayout->setStretch(1,6);

    userNameLayout->setStretch(0,4);
    userNameLayout->setStretch(1,6);

    pwdLayout->setStretch(0,4);
    pwdLayout->setStretch(1,6);

    vlayout->addLayout(ipLayout);
    vlayout->addLayout(portLayout);
    vlayout->addLayout(userNameLayout);
    vlayout->addLayout(pwdLayout);

    this->setLayout(vlayout);

}
