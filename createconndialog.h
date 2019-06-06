#ifndef CREATECONNDIALOG_H
#define CREATECONNDIALOG_H

#include <QDialog>
#include <conn.h>

namespace Ui {
class CreateConnDialog;
}

class CreateConnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateConnDialog(QWidget *parent = nullptr);
    explicit CreateConnDialog(Conn* conn, QWidget *parent= nullptr);
    ~CreateConnDialog();

private slots:
    void sumbit();
    void cancel();

private:
    Ui::CreateConnDialog *ui;
    bool isEdit;
    Conn *conn;
};

#endif // CREATECONNDIALOG_H
