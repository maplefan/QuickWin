#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef TASKMGR_H
#define TASKMGR_H

#ifdef _WIN32
#ifndef _WIN_CPU_H_
#define _WIN_CPU_H_
#pragma comment(lib,"Iphlpapi.lib")
#endif
#endif
#define WIN32_LEAN_AND_MEAN
#include <QTimer>
#include <QDebug>
#include <vector>
#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>
#include <QToolTip>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QDir>
#include <QtWin>
#include <QAction>
#include <QMessageBox>
#include <QTemporaryFile>
#include <QHeaderView>
#include <Windows.h>
#include <shellapi.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include "tableview.h"
#include <string>
#include <vector>
#include <new>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include "moduledlg.h"
#include "threaddlg.h"
using namespace std;
/*
typedef struct tagpare_net
{
    DWORD dwsend;
    DWORD dwrecv;
}NET_PARE,*PNET_PARE;
*/
// Use to convert bytes to KB
#define DIV 1024

#define SystemBasicInformation 0
#define SystemPerformanceInformation 2
#define SystemTimeInformation 3

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))
/*
typedef struct
{
    DWORD dwUnknown1;
    ULONG uKeMaximumIncrement;
    ULONG uPageSize;
    ULONG uMmNumberOfPhysicalPages;
    ULONG uMmLowestPhysicalPage;
    ULONG uMmHighestPhysicalPage;
    ULONG uAllocationGranularity;
    PVOID pLowestUserAddress;
    PVOID pMmHighestUserAddress;
    ULONG uKeActiveProcessors;
    BYTE bKeNumberProcessors;
    BYTE bUnknown2;
    WORD wUnknown3;
} SYSTEM_BASIC_INFORMATION;

typedef struct
{
    LARGE_INTEGER liIdleTime;
    DWORD dwSpare[76];
} SYSTEM_PERFORMANCE_INFORMATION;

typedef struct{
   DWORD memoryPrecent;//物理内存占用率（%）
   DWORDLONG totalPhys;
   DWORDLONG availPhys;
   DWORDLONG totalPageFile;
   DWORDLONG availPageFile;
   DWORDLONG totalVirtual;
   DWORDLONG availVirtual;
   DWORDLONG availExtendedVirtual;
} MemoryInfo;

typedef struct
{
    LARGE_INTEGER liKeBootTime;
    LARGE_INTEGER liKeSystemTime;
    LARGE_INTEGER liExpTimeZoneBias;
    ULONG uCurrentTimeZoneId;
    DWORD dwReserved;
} SYSTEM_TIME_INFORMATION;

typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);
*/
#pragma comment(lib, "advapi32.lib")
void MyRtlAdjustPrivilege();
BOOL WINAPI WindowsProc(HWND nHwnd , LPARAM nLparam);

typedef struct _TASKLIST
{
    std::vector<QString>szExeFile;
    DWORD *th32ProcessID;
    DWORD *cntThreads;
    DWORD *th32ParentProcessID;
    std::vector<QString>szExeFilePath;
    std::vector<QString>WorkingSetSize;
    std::vector<QString>szPriority;
}TASKLIST, *PTASKLIST;

typedef struct _WINDOWLIST{
    std::vector<QString>szExeFile;
    std::vector<DWORD>th32ProcessID;
    std::vector<QString>szExeFilePath;
}WINDOWLIST;

//获得CPU使用率
int GetCpuUsage();

namespace Ui {
class TaskMgr;
}

class TaskMgr : public QMainWindow
{
    Q_OBJECT

public:
    explicit TaskMgr(QWidget *parent = 0);
    ~TaskMgr();
    void addProcessItem(int index , QString name , DWORD pid , QString pri , QString mem , DWORD threadN , DWORD par , QString pa);
    void addWindowItem(int index , QString name , DWORD pid , QString path);
    DWORD EnumTaskList(TASKLIST &nTaskList);
    void GetProcessFilePath(HANDLE hProcess, QString& sFilePath);
    void GetProcessPriority(QString &nState, HANDLE nHandle);
    void resizeEvent(QResizeEvent* size);
    bool AdjustPrivilege();//提权函数
    void setProcessState(DWORD nPid, BOOL nSuspend);
    void endProcess(DWORD nPid);
    void addWindowModel();
    void addProcessModel();

private:
    Ui::TaskMgr *ui;
    QMainWindow *qmw;//子窗口
    TableView *processView;
    TableView *windowView;
    QStandardItemModel *processModel;
    QStandardItemModel *windowModel;
    QGridLayout *processLayout;
    QGridLayout *windowLayout;
    QIcon icon;
    QFileIconProvider iconProvider;
    QString systemPath;
    QMenu *popMenu;
    QMenu *windowMenu;
    QLabel *statusLabel;
    QLabel *processLabel;
    QLabel *memoryLabel;
    int processNum;

    ThreadDlg *td;
    ModuleDlg *md;
    QTimer *timer;
    QAction *actionOpenPath;
    QAction *actionEndProcess;
    QAction *actionSuspendProcess;
    QAction *actionRecoveryProcess;
    QAction *actionReadModule;
    QAction *actionReadThread;
    QAction *actionAttribute;
    QAction *actionWindowOpenPath;
    QAction *actionWindowEndProcess;
    QAction *actionWindowSuspendProcess;
    QAction *actionWindowRecoveryProcess;
    QAction *actionWindowReadModule;
    QAction *actionWindowReadThread;
    QAction *actionWindowAttribute;
    QStandardItem *item0;
    QStandardItem *item1;
    QStandardItem *item2;
    QStandardItem *item3;
    QStandardItem *item4;
    QStandardItem *item5;
    QStandardItem *item6;
    TASKLIST nTaskList = {};
    WINDOWLIST nWindowList = {};

private slots:
    void slotContextMenu(QPoint pos);
    void slotWindowContextMenu(QPoint pos);
    void timeUpdate();
    void reboot();//重启
    void shutdown();//关机
    void logout();//注销
    void openFilePath();//打开文件位置
    void finishProcess();//结束进程
    void suspendProcess();//暂停进程
    void recoveryProcess();//恢复进程
    void viewModule();//查看模块
    void viewThreads();//查看线程
    void viewProperties();//属性

    void openWindowFilePath();//打开窗口程序文件位置
    void finishWindowProcess();//结束窗口程序主进程
    void suspendWindowProcess();//暂停窗口程序主进程
    void recoveryWindowProcess();//恢复窗口程序主进程
    void viewWindowProperties();//查看窗口程序属性

};

#endif // TASKMGR_H
