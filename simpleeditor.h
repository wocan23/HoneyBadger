#ifndef SIMPLEEDITOR_H
#define SIMPLEEDITOR_H

#include <QtWidgets>

typedef struct SyntaxHight {
    QString keyWord;
    QColor   highlightColor;
}SyntaxHight_T;

class MySyntaxHighlighterEditor : public QSyntaxHighlighter {

    Q_OBJECT

public:
    MySyntaxHighlighterEditor(QTextDocument *document = 0);
    void readSyntaxHighter(const QString &fileName);
    QMap<QString, QColor> syntaxHightMap; //保存语法高亮信息

protected:
    void highlightBlock(const QString &text);

private:
    QRegularExpression matchReExpression;

};

class MyGCodeTextEdit;
class LineNumberArea;

class MyGCodeTextEdit : public QPlainTextEdit{

    Q_OBJECT

public:
    MyGCodeTextEdit(QWidget *parent  = 0);
    //void setCompleter(QCompleter *completer);
    QString wordUnderCursor() const;
    int lineNumberAreaWidth();
    void lineNumberAreaPaintEvent(QPaintEvent *event);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e);

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);

public slots:
    void onCompleterActivated(const QString &completion);
    void onCurosPosChange(void);

private:
    MySyntaxHighlighterEditor *gCodeHighlighter;
    QCompleter *keyWordsComplter;
    QStringList keyWordsList;
    QTextCursor curTextCursor;
    QRect curTextCursorRect;
    QString completerPrefix;

    //显示行号
    QWidget *lineNumberArea;

};

class LineNumberArea : public QWidget
{

public:
    explicit LineNumberArea(MyGCodeTextEdit *editor): QWidget(editor)
    {
        gCodeTextEdit = editor;
        //setVisible(true);
    }

    QSize sizeHint() const override
    {
        return QSize(gCodeTextEdit->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        gCodeTextEdit->lineNumberAreaPaintEvent(event);
        //qDebug() << "gCodeTextEdit:" << __FUNCTION__;
    }

private:
    MyGCodeTextEdit *gCodeTextEdit;
};


class MyGCodeEditor : public QMainWindow {

    Q_OBJECT

public:
    explicit MyGCodeEditor(QMainWindow *parent = 0);

private:
    MyGCodeTextEdit *myGCodeTextEdit;

};

class SimpleEditor : public QMainWindow
{
    Q_OBJECT

public:
    SimpleEditor(QWidget *parent = 0);
    //~SimpleEditor();
};

#endif // SIMPLEEDITOR_H
