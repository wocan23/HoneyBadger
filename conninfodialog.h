#ifndef CONNINFODIALOG_H
#define CONNINFODIALOG_H

#include "conn.h"
#include <QDialog>

namespace Ui {
class ConnInfoDialog;
}

class ConnInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnInfoDialog(QWidget *parent = nullptr);
    explicit ConnInfoDialog(Conn* conn);
    ~ConnInfoDialog();

    void flushConnInfo(Conn* conn);

private:
    Ui::ConnInfoDialog *ui;
};

#endif // CONNINFODIALOG_H
