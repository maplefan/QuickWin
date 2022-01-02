#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TASKBAR_H
#define TASKBAR_H

#include <QMouseEvent>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QScreen>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <getnetinfothread.h>
#include "config.h"

QColor GetWindowsThemeColor();
QColor DesktopXYColor(int x,int y);

enum DoubleClickAction
{
    BROWSER = 0,
    SCREENSHOT,
    STICKYNOTE,
    COLORPICKER,
    TASKMANAGER,
    MAINTOOL,
    REMINDER,
    HOTKEYMANAGER,
    STOCK,
    HARDWARE,
    TRANSLATOR,
    SEARCH,
    CUSTOM,
};

namespace Ui {
class TaskBar;
}

class TaskBar : public QMainWindow
{
    Q_OBJECT

public:
    explicit TaskBar(QWidget *parent = 0);
    ~TaskBar();
    bool event(QEvent *event);
    bool IsTaskBarOnTopOrButtom();
    void timerEvent(QTimerEvent *event);
    void closeEvent(QCloseEvent *event);
    void adaptColor();
    void adaptRcMin();
    void changeLabel(int cpuPercent , int memoryPercent , double netUploadex , double netDownloadex);//修改任务栏数据
    void changeLabel(QString , QString , QString , QString );
    void changeLabel();
    void mouseDoubleClickEvent(QMouseEvent *event);
    bool isForegroundFullscreen ();

private:
    Ui::TaskBar *ui;
    HWND m_hTaskbar;//寻找类名是Shell_TrayWnd的窗口句柄
    HWND m_hBar; 	//寻找二级容器的句柄
    HWND m_hMin; 	//寻找最小化窗口的句柄
    HWND m_hTrayNotify; //右侧任务通知栏的句柄
    RECT m_rcMin; //最小化窗口区域
    RECT m_rcBar; //获得二级容器的区域
    RECT m_rcTaskBar; //任务栏区域
    RECT m_rcMinInit; //初始的任务栏最小化区域
    RECT m_rcTrayNotify; //右侧任务通知栏的区域
    int taskBarWidth;
    int taskBarHeight;
    int showInfoNum;
    int m_left_space;//水平方向最小化窗口和二级窗口的间距
    int m_top_space;//垂直方向最小化窗口和二级窗口的间距
    int rcMinWidth;//最小化窗口宽度
    int rcMinInitWidth;//最小化窗口原始宽度
    int rcMinHeight;//最小化窗口高度
    int rcMinInitHeight;//最小化窗口原始高度
    int rcMinX;//最小化窗口原始X
    int rcMinY;//最小化窗口原始Y
    int rcTrayNotifyX;
    int rcTrayNotifyY;

signals:
    void showBrowserEvent();
    void showCatchScreenEvent();
    void showStickyNoteEvent();
    void showCatchColorEvent();
    void showTaskMgrEvent();
    void showMainToolEvent();
    void showTimeReminderEvent();
    void showHotkeyManageEvent();
    void showStockEvent();
    void showHardWareEvent();
    void activatedTranslatorEvent();
    void activatedSearchEvent();
    void showCustomEvent();

};

#endif // TASKBAR_H
