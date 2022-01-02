#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "threaddlg.h"
#include <QDebug>

std::string ThreadDlg::DwordToString(DWORD dw)
{
    using namespace std;

    const int n = snprintf(NULL, 0, "%lu", dw);
    vector<char> buf(n + 1);
    if (n < 0) {
        return "";
    }
    int c = snprintf(&buf[0], n + 1, "%lu", dw);
    string str(&buf[0]);
    return str;
}

void ThreadDlg::GetProcessName(QString &nProcessName,DWORD nPid)
{
    PROCESSENTRY32 nPT;
    nPT.dwSize = sizeof(nPT);
    HANDLE nSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    BOOL nRet = Process32First(nSnapShot, &nPT);
    while (nRet)
    {
        if (nPid==nPT.th32ProcessID)
        {
            nProcessName = QString::fromWCharArray(nPT.szExeFile);
            return;
        }
        nRet = Process32Next(nSnapShot, &nPT);
    }
}

void ThreadDlg::GetThreadState(QString &nState, DWORD nThreadid)
{
    HANDLE nHandle = OpenThread(PROCESS_ALL_ACCESS, FALSE, nThreadid);

    DWORD WaitCode;
    WaitCode = WaitForSingleObject(nHandle, 0);

    CloseHandle(nHandle);

    switch (WaitCode)
    {
    case 258:
        nState = tr("正在运行");
        return;
    case  WAIT_OBJECT_0:
        nState = tr("已销毁");
        return;
    }
    nState = tr("已结束");
}

ThreadDlg::ThreadDlg(QWidget *parent) :
    QTableView()
{
    QStandardItemModel* model = new QStandardItemModel(this);
    this->setModel(model);
}

ThreadDlg::ThreadDlg(DWORD processID , QWidget *parent ) :
    QTableView(parent)
{
    this->setMinimumSize(700 , 400);
    DWORD index = EnumThreadList( nThreadList , processID );
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("线程ID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("进程名")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("进程ID")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("优先级")));
    model->setHorizontalHeaderItem(4, new QStandardItem(tr("线程状态")));
    for(int i = 0; i < index ;i++){
        item0 = new QStandardItem(nThreadList.th32ThreadID[i]);
        model->setItem(i, 0 , item0);
        item0->setData(nThreadList.th32ThreadID[i] , Qt::ToolTipRole);

        item1 = new QStandardItem(nThreadList.szExePath[i]);
        model->setItem(i, 1 , item1);
        item1->setData(nThreadList.szExePath[i] , Qt::ToolTipRole);

        item2 = new QStandardItem(nThreadList.th32OwnerProcessID[i]);
        model->setItem(i, 2 , item2);
        item2->setData(nThreadList.th32OwnerProcessID[i] , Qt::ToolTipRole);

        item3 = new QStandardItem(nThreadList.tpBasePri[i]);
        model->setItem(i, 3 , item3);
        item3->setData(nThreadList.tpBasePri[i] , Qt::ToolTipRole);

        item4 = new QStandardItem(nThreadList.szThreadState[i]);
        model->setItem(i, 4 , item4);
        item4->setData(nThreadList.szThreadState[i] , Qt::ToolTipRole);
    }
    // 整行选中
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    // 不可编辑
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setStyleSheet("QTableView{border:none;background:white;}");
    this->setStyleSheet("QTableView::item:selected{color:white;background:rgb(34, 175, 75);}");
    this->setSortingEnabled(true);//允许点击表头排序
    this->setModel(model);
    this->setColumnWidth( 0 , 120);
    this->setColumnWidth( 1 , 200);
    this->setColumnWidth( 2 , 100);
    this->setColumnWidth( 3 , 110);
    this->setColumnWidth( 4 , 110);
}

//枚举线程列表
DWORD ThreadDlg::EnumThreadList(THREADLIST &nThreadList, DWORD nPid)
{
    BOOL nRet;
    DWORD nIndex = 0;
    THREADENTRY32 nThread;

    nThread.dwSize = sizeof(THREADENTRY32);
    HANDLE nSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, nPid);

    nRet = Thread32First(nSnapShot, &nThread);
    while (nRet)
    {
        if ((nThread.th32OwnerProcessID == nPid || nPid==0xABCDEF)&&nThread.th32OwnerProcessID!=0)nIndex++;
        nRet = Thread32Next(nSnapShot, &nThread);

    }

    nThreadList.th32ThreadID = new QString[nIndex];
    nThreadList.th32OwnerProcessID = new QString[nIndex];
    nThreadList.tpBasePri = new QString[nIndex];
    nThreadList.szExePath = new QString[nIndex];
    nThreadList.szThreadState = new QString[nIndex];

    nIndex = 0;
    nRet = Thread32First(nSnapShot, &nThread);
    while (nRet)
    {
        if ((nThread.th32OwnerProcessID == nPid || nPid == 0xABCDEF)&&nThread.th32OwnerProcessID != 0)
        {
            nThreadList.th32ThreadID[nIndex] = QString::fromStdString(DwordToString(nThread.th32ThreadID));
            nThreadList.th32OwnerProcessID[nIndex] = QString::fromStdString(DwordToString(nThread.th32OwnerProcessID));
            nThreadList.tpBasePri[nIndex] = QString::fromStdString(DwordToString(nThread.tpBasePri));

            QString nProcessName;
            GetProcessName(nProcessName, nThread.th32OwnerProcessID);
            nThreadList.szExePath[nIndex] = nProcessName;

            QString nThreadState;
            GetThreadState(nThreadState, nThread.th32ThreadID);
            nThreadList.szThreadState[nIndex] = nThreadState;

            nIndex++;
        }
        nRet = Thread32Next(nSnapShot, &nThread);
    }

    CloseHandle(nSnapShot);

    return nIndex;
}

ThreadDlg::~ThreadDlg()
{
    delete model;
    delete item0;
    delete item1;
    delete item2;
    delete item3;
    delete item4;
    delete [] nThreadList.th32ThreadID;
    delete [] nThreadList.th32OwnerProcessID;
    delete [] nThreadList.tpBasePri;
    delete [] nThreadList.szExePath;
    delete [] nThreadList.szThreadState;
}
