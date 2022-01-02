#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTranslator>
#include <QMainWindow>
#include <QPoint>
#include <QProcess>
#include <QFont>
#include <QDebug>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMenu>
#include <QDir>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QScreen>
#include <QLibrary>
#include <QSignalMapper>
#include <QBitmap>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QToolTip>
#include <queue>
#define WIN32_LEAN_AND_MEAN
#include <comutil.h>
#include <Windows.h>
#include "hotkeymanage.h"
#include <dwmapi.h>
#include <TlHelp32.h>
#include <QAbstractNativeEventFilter>
#include "getnetinfothread.h"
#include "pcinfowindow.h"
#include "config.h"
#include "colorwidget.h"
#include "taskmgr.h"
#include "systeminfo.h"
#include "taskbar.h"
#include "quicklook.h"
#include "adapterinfo.h"
#include "networkinfo.h"
#include "helpdlg.h"
#include "snappit.h"
#include "PCSearch.h"
#include "translatordlg.h"
#include "screenShot/screen.h"
#include "quickstock.h"
#include "stickynote.h"
#include "maintool.h"
#include "timereminder.h"
#include "setting.h"

#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Dwmapi.lib")

enum FocusedWindowType
{
    INVALID0,
    DESKTOP,
    EXPLORER,
};

typedef  BSTR (*_GetSelectedFromDesktop)();
typedef  BSTR (*_GetSelectedFromExplorer)();
typedef  int(*_GetFocusedWindowType)();

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow ,public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    //键盘钩子回调函数
    static LRESULT  CALLBACK  KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
    //键盘钩子，QuickLook中用到
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void changeEvent(QEvent *e);
    bool event(QEvent *e);
    bool nativeEventFilter(const QByteArray & eventType, void * message, long * result);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void moveEvent(QMoveEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *e);
    void closeEvent(QCloseEvent *event);
    bool isDirExist(QString fullPath);
    void createFile(QString filePath,QString fileName);
    bool isForegroundFullscreen ();
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    Setting *st;
    PCSearch *pcs;
    TranslatorDlg *tld;
    MemoryInfo mi;
    TaskMgr *tm;
    ColorWidget *cw;
    PCInfoWindow *piw;
    QWidget *snWidget;
    TaskBar *tb;
    MainTool *mt;
    TimeReminder *trd;
    HotkeyManage *hm;
    snappit *snap;
    Screen *sc;
    QuickStock *qs;
    bool bPressFlag;
    QPoint beginDrag;
    QRect desktopRect;
    int windowWidth;
    int windowHeight;
    int m_eEdgeStatus;
    QSystemTrayIcon *m_trayIcon;
    Ui::MainWindow *ui;
    double netUpload;
    double netDownload;
    unsigned int cpuPercent;
    unsigned int memoryPercent;
    GetNetInfoThread *gnit;
    QMenu *menu;
    QMenu *menuOpacity;
    QMenu *menuAdapter;
    QAction *acSetNetCard;
    QAction *acTrafficStat;
    QAction *acShowMainWindow;
    QAction *acAlwaysTop;
    QAction *acKeepSide;
    QAction *acLockWindow;
    QAction *acShowOnTaskBar;
    QAction *acSetOpacity;
    QAction *acOtherSetting;
    QAction *acCatchScreen;
    QAction *acStickyNote;
    QAction *acCatchColor;
    QAction *acSniffer;
    QAction *acHotkeyManage;
    QAction *acShowHardWare;
    QAction *acShowStock;
    QAction *acTaskMgr;
    QAction *acMainTool;
    QAction *acTimeReminder;
    QAction *acHelp;
    QAction *acExit;
    QAction *acSet100Opacity;
    QAction *acSet80Opacity;
    QAction *acSet60Opacity;
    QAction *acSet40Opacity;
    QAction *acSelectAll;
    QAction *acSelectAuto;
    std::vector<QAction*> acConnection;
    unsigned __int64 m_last_in_bytes ;
    unsigned __int64 m_last_out_bytes ;
    unsigned __int64 m_in_bytes; //当前已接收的字节数
    unsigned __int64 m_out_bytes; //当前已发送的字节数
    DWORD dwSize;
    int ac_connection_selected;
    bool configShowMainWindow;
    bool configAlwaysTop;
    bool configKeepSide;
    bool configLockWindow;
    bool configShowOnTaskBar;
    int configPacity;
    QString configSelectedConnection;
    QFont *fontTitle;
    QFont *fontLabel;
    QFont *fontInfo;
    int m_nTimerIDHook;
    int m_nTimerIDInfo;
    MIB_IFTABLE* m_pIfTable;
    std::vector<NetWorkConection> adapters;
    QString selectedAdapter;
    SYSTEMTIME startTime;
    int windowX;
    int windowY;

    //Ui::snappit ui;
    std::vector<ImageView *> _arr_imgView;
    QString _file_path;
    QAction *m_prefer;
    QAction *m_quit;
    QTranslator *m_translator;

    enum{
        EG_NORMAL,
        EG_TOP,
        EG_RIGHT,
        EG_LEFT,
    };

private slots:
    void quitExe();
    void setNetCard();
    void showTrafficStat();
    void showMainWindow();
    void setAlwaysTop();
    void setKeepSide();
    void setLockWindow();
    void showOnTaskBar();
    void setOpacity();
    void showOtherSetting();
    void showCatchScreen();
    void showStickyNote();
    void showCatchColor();
    void showSniffer();
    void showTaskMgr();
    void showMainTool();
    void showTimeReminder();
    void showHotkeyManage();
    void showHardWare();
    void showStock();
    void showHelp();
    void set100Opacity();
    void set80Opacity();
    void set60Opacity();
    void set40Opacity();
    void setSelectAdapter(QString);
    void setSelectAll();
    void setSelectAuto();
    void onActivated(QSystemTrayIcon::ActivationReason reason);
    void activatedSearch();
    void activatedTranslator();
    void showBrowser();
    void showCustom();
};
#endif // MAINWINDOW_H

QMainWindow* getMainWindow();
