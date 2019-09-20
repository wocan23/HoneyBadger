#include "estoolbar.h"
#include "createconndialog.h"
#include "handler.h"

EsToolBar::EsToolBar(QWidget *parent) : QToolBar(parent)
{
    QAction *act[6];

      act[0] = new QAction(QIcon(":/icon/pic/conn.png"), "conn", this);
      act[1] = new QAction(QIcon(":/icon/pic/index.png"), "index", this);
      act[2] = new QAction(QIcon(":/icon/pic/doc.png"), "doc", this);
      act[3] = new QAction(QIcon(":/icon/pic/editDoc.png"), "edit", this);
      act[4] = new QAction(QIcon(":/icon/pic/search.png"), "search", this);
      act[5] = new QAction(QIcon(":/icon/pic/help.png"), "help", this);

      act[0]->setShortcut(Qt::Key_Control | Qt::Key_E);
      act[0]->setToolTip("This is a ToolTip");

      this->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

      for(int i = 0 ; i < 6 ; i++)
      {
          this->addAction(act[i]);
      }
      connect(act[0],SIGNAL(triggered()),this,SLOT(createConnDialog()));
      connect(act[4],SIGNAL(triggered()),this,SLOT(createSearchDialog()));

}
void EsToolBar::createConnDialog(){
   CreateConnDialog* dialog = new CreateConnDialog;
   dialog->exec();
}

void EsToolBar::createIndexDialog(){

}

void EsToolBar::createDocDialog(){

}

void EsToolBar::createEditDocDialog(){

}

void EsToolBar::createSearchDialog(){
    Handler * hanler = Handler::getInstance();
    emit hanler->queryIndexSinal();
}
