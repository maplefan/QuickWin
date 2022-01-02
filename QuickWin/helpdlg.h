#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef HELPDLG_H
#define HELPDLG_H

#include <QMainWindow>
#include <QDateTime>
namespace Ui {
class HelpDlg;
}

class HelpDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit HelpDlg(QWidget *parent = nullptr);
    ~HelpDlg();

private slots:
    void on_authorBtn_clicked();

    void on_githubBtn_clicked();

    void on_BlogBtn_clicked();

    void on_donateBtn_clicked();

    void on_thanksBtn_clicked();

    void on_okBtn_clicked();

private:
    Ui::HelpDlg *ui;
};

    static const QString buildDateTime();

#endif // HELPDLG_H
