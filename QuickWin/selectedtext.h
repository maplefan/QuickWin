﻿#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef SELECTEDTEXT_H
#define SELECTEDTEXT_H

#include <QObject>
#include <qt_windows.h>
#include <QClipboard>
#include <QApplication>
#include <Winuser.h>
#include <QMimeData>
#include <MyGlobalShortcut/MyGlobalShortCut.h>
#pragma comment  (lib, "User32.lib")
    // 全局键盘钩子

class SelectedText : public QObject
{
    Q_OBJECT
public:

    ~SelectedText();

    static int CALLBACK mouseProc(int ncode, WPARAM wParam, LPARAM lParam); // 回调函数
    SelectedText(QObject *parent = 0);
    SelectedText(const SelectedText&);
    SelectedText& operator=(const SelectedText &);
    void installHook();         // 安装钩子
    void uninstallHook();       // 卸载钩子
    void checkSelectedText();   // 检查是否有文本被选中

    bool  m_move;               // 鼠标是否拖动
    POINT m_down_pos;           // 上次左键按下位置
    POINT m_up_pos;             // 此时左键弹起位置

    QClipboard* m_board;
    QString m_lastString;       // 上次剪贴板中的内容
    QMimeData* m_old_data;      // 原剪贴板内容
    static SelectedText* pthis;
    bool working;

    HWND m_hwnd;                // 要复制的窗口的句柄
    HHOOK MyHook;

signals:
    void newtextselected(QString str);
public slots:

private slots:
    void textCopyFinished();
private:
    QMimeData * copyMimeData(const QMimeData * mimeReference);  // 复制剪贴板内容

};
#endif // SELECTEDTEXT_H
