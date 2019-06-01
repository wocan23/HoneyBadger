#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QToolBar>

class PageWidget : public QToolBar
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr);

signals:
    void to(int page);

public slots:
    void toPage(int page);
    void nextPage();
    void lastPage();
    void toEndPage();
    void toStartPage();

private:
    int totalPage;
    int currentPage;
    int pageSize;
};

#endif // PAGEWIDGET_H
