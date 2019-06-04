#ifndef INDEXINFODIALOG_H
#define INDEXINFODIALOG_H

#include "esindex.h"

#include <QDialog>
#include <QHBoxLayout>

namespace Ui {
class IndexInfoDialog;
}

class IndexInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IndexInfoDialog(QWidget *parent = nullptr);
    explicit IndexInfoDialog(EsIndex* esIndex);
    ~IndexInfoDialog();

    void flushIndexInfo(EsIndex* esIndex);

private:
    Ui::IndexInfoDialog *ui;
};

#endif // INDEXINFODIALOG_H
