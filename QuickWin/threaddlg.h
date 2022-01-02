#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef THREADDLG_H
#define THREADDLG_H

#include <QDialog>
#include <QTableView>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <QStandardItemModel>
#include <QMainWindow>
typedef struct _THREADLIST
{
    QString *th32ThreadID;
    QString *th32OwnerProcessID;
    QString *tpBasePri;
    QString *szExePath;
    QString *szThreadState;

}THREADLIST, *PTHREADLIST;

class ThreadDlg : public QTableView
{
    Q_OBJECT

public:
    explicit ThreadDlg(QWidget *parent = 0);
    ThreadDlg(DWORD processID , QWidget *parent = 0);
    ~ThreadDlg();
    void GetProcessName(QString &nProcessName,DWORD nPid);
    void GetThreadState(QString &nState, DWORD nThreadid);
    DWORD EnumThreadList(THREADLIST &nThreadList, DWORD nPid);
    std::string DwordToString(DWORD dw);
    QStandardItem *item0;
    QStandardItem *item1;
    QStandardItem *item2;
    QStandardItem *item3;
    QStandardItem *item4;
    QStandardItemModel* model;
    THREADLIST nThreadList = {};
};

#endif // THREADDLG_H
