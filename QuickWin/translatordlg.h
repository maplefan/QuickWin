#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TranslatorDlg_H
#define TranslatorDlg_H

#include <QMainWindow>
#include <selectedtext.h>
#include <translator.h>
#include <form.h>
#include<QSystemTrayIcon>
#include<QMenu>
#include<QAction>
#include <MyGlobalShortcut/MyGlobalShortCut.h>
namespace Ui {
class TranslatorDlg;
}


class TranslatorDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit TranslatorDlg(QWidget *parent = 0);
    ~TranslatorDlg();
    void noticeWindow();
    void timerEvent(QTimerEvent *);
    bool getOnNotice();
    bool getTextIsWorking();
    void installHook();
    void uninstallHook();
public slots:

    // 有新的剪贴板内容
    void newselectedtext(QString str);
    // 新的单词查询完成
    void translateWordFinished(Words word);
    // 新的句子查询完成
    void translateSentencesFinished(QString);
    // 划词开关
    void activate();
    void quitExe();

private:
    void adjustWindowPos(Form* window);
private:
    Ui::TranslatorDlg *ui;
    SelectedText* m_text;
    QLabel* notice;
    int m_timer;
    bool onNotice;
    QSystemTrayIcon *trayIcon;
    QMenu *menu;
    QAction *exitExe;
};
#endif

