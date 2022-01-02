#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef HTMLFORM_H
#define HTMLFORM_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QStackedLayout>
#include <QFile>
namespace Ui {
class HtmlForm;
}

class HtmlForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit HtmlForm(QString filename , QWidget *parent = nullptr);
    ~HtmlForm();

private:
    Ui::HtmlForm *ui;
    QWebEngineView *m_webView;
};

#endif // HTMLFORM_H
