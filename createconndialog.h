#ifndef CREATECONNDIALOG_H
#define CREATECONNDIALOG_H

#include <QDialog>

namespace Ui {
class CreateConnDialog;
}

class CreateConnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateConnDialog(QWidget *parent = nullptr);
    ~CreateConnDialog();

private slots:
    void sumbit();
    void cancel();

private:
    Ui::CreateConnDialog *ui;
};

#endif // CREATECONNDIALOG_H
