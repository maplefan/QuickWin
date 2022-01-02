#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "systeminfowin.h"
#include "taskmgr.h"
#include "ui_taskmgr.h"

static MemoryInfo mi={};

void GetProcessFilePath(HANDLE hProcess, QString& sFilePath)
{
    sFilePath = "";
    TCHAR tsFileDosPath[MAX_PATH + 1];
    ZeroMemory(tsFileDosPath, sizeof(TCHAR)*(MAX_PATH + 1));

    if (0 == GetProcessImageFileNameW(hProcess, tsFileDosPath, MAX_PATH + 1))
    {
        return;
    }

    // 获取Logic Drive String长度

    SIZE_T uiLen = GetLogicalDriveStrings(0, NULL);
    if (0 == uiLen)
    {
        return;
    }

    PTSTR pLogicDriveString = new TCHAR[uiLen + 1];
    ZeroMemory(pLogicDriveString, uiLen + 1);
    uiLen = GetLogicalDriveStrings((DWORD)uiLen, pLogicDriveString);
    if (0 == uiLen)
    {
        delete[]pLogicDriveString;
        return;
    }

    TCHAR szDrive[3] = TEXT(" :");
    PTSTR pDosDriveName = new TCHAR[MAX_PATH];
    PTSTR pLogicIndex = pLogicDriveString;

    do
    {
        szDrive[0] = *pLogicIndex;
        uiLen = QueryDosDevice(szDrive, pDosDriveName, MAX_PATH);
        if (0 == uiLen)
        {
            if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
            {
                break;
            }

            delete[]pDosDriveName;
            pDosDriveName = new TCHAR[uiLen + 1];
            uiLen = QueryDosDevice(szDrive, pDosDriveName, (DWORD)uiLen + 1);
            if (0 == uiLen)
            {
                break;
            }
        }

        uiLen = wcslen(pDosDriveName);
        if (0 == _wcsnicmp(tsFileDosPath, pDosDriveName, uiLen))
        {
            QString fileDOsPath = QString::fromWCharArray(tsFileDosPath + uiLen);
            QString drive = QString::fromWCharArray(szDrive);
            sFilePath = sFilePath + drive + fileDOsPath ;
            //sFilePath.Format(("%s%s"), szDrive, tsFileDosPath + uiLen);
            break;
        }
        while (*pLogicIndex++);
    } while (*pLogicIndex);

    delete[]pLogicDriveString;
    delete[]pDosDriveName;
}

//获取文件图标
HICON getFileIcon(std::string extention)
{
    HICON icon = NULL;
    if (extention.length() > 0)
    {
        LPCSTR name = extention.c_str();

        SHFILEINFOA info;
        if (SHGetFileInfoA(name,
            FILE_ATTRIBUTE_NORMAL,
            &info,
            sizeof(info),
            SHGFI_SYSICONINDEX | SHGFI_ICON | SHGFI_USEFILEATTRIBUTES))
        {
            icon = info.hIcon;
        }
    }
    return icon;
}

void MyRtlAdjustPrivilege()
{
    const int SE_SHUTDOWN_PRIVILEGE = 20;
    int nAddress = 0;
    typedef int(WINAPI*RtlAdjustPrivilege)(int, bool, bool, int*);
    HMODULE module = LoadLibrary(TEXT("ntdll.dll"));
    RtlAdjustPrivilege pRt = (RtlAdjustPrivilege)GetProcAddress(module, "RtlAdjustPrivilege");
    pRt(SE_SHUTDOWN_PRIVILEGE, TRUE, FALSE, &nAddress);
    FreeLibrary(module);
}

BOOL WINAPI WindowsProc(HWND nHwnd , LPARAM nLparam){
    WINDOWLIST *nWindowList = (WINDOWLIST*)nLparam;
    LPRECT rect;

    TCHAR buff[200];
    GetWindowText(nHwnd , buff , _countof(buff));
    if( IsWindowVisible(nHwnd) && wcslen(buff) && wcscmp(buff , TEXT("开始"))  ){
        DWORD nPid = 0;
        QString nFilePath = "";
        HANDLE nHandle;
        nWindowList->szExeFile.push_back(QString((QChar*)buff , wcslen(buff)));
        GetWindowThreadProcessId(nHwnd, &nPid);
        nWindowList->th32ProcessID.push_back(nPid);
        nHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, nPid);
        GetProcessFilePath(nHandle, nFilePath);
        nWindowList->szExeFilePath.push_back(nFilePath);
    }
    return TRUE;

}

TaskMgr::TaskMgr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaskMgr)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("任务管理器"));
    WCHAR systemPathW[MAX_PATH];
    GetSystemDirectory(systemPathW, MAX_PATH);
    systemPath = QString::fromWCharArray(systemPathW);
    QPixmap pixmap = QtWin::fromHICON(getFileIcon(".exe"));
    icon.addPixmap(pixmap);
    //进程列表
    processView = new TableView(this);
    // 设置表头
    processModel = new QStandardItemModel();
    processLayout = new QGridLayout(this->ui->tabProcess);
    processLayout->addWidget(processView);
    MyRtlAdjustPrivilege();//提升权限
    //添加process信息
    addProcessModel();
    //窗口信息
    windowView = new TableView(this);
    // 设置表头
    windowModel = new QStandardItemModel();
    addWindowModel();

    //给进程列表增加右键菜单
    popMenu = new QMenu(processView);
    windowMenu = new QMenu(windowView);
    actionOpenPath = new QAction();
    actionEndProcess = new QAction();
    actionSuspendProcess = new QAction();
    actionRecoveryProcess = new QAction();
    actionReadModule = new QAction();
    actionReadThread = new QAction();
    actionAttribute = new QAction();
    actionOpenPath->setText(tr("打开文件位置"));
    actionEndProcess->setText(tr("结束进程"));
    actionSuspendProcess->setText(tr("暂停进程"));
    actionRecoveryProcess->setText(tr("恢复进程"));
    actionReadModule->setText(tr("查看模块"));
    actionReadThread->setText(tr("查看线程"));
    actionAttribute->setText(tr("属性"));
    popMenu->addAction(actionOpenPath);
    popMenu->addSeparator();
    popMenu->addAction(actionEndProcess);
    popMenu->addAction(actionSuspendProcess);
    popMenu->addAction(actionRecoveryProcess);
    popMenu->addSeparator();
    popMenu->addAction(actionReadModule);
    popMenu->addAction(actionReadThread);
    popMenu->addSeparator();
    popMenu->addAction(actionAttribute);

    //给窗口信息增加右键菜单
    actionWindowOpenPath = new QAction();
    actionWindowEndProcess = new QAction();
    actionWindowSuspendProcess = new QAction();
    actionWindowRecoveryProcess = new QAction();
    actionWindowReadModule = new QAction();
    actionWindowReadThread = new QAction();
    actionWindowAttribute = new QAction();
    actionWindowOpenPath->setText(tr("打开文件位置"));
    actionWindowEndProcess->setText(tr("结束进程"));
    actionWindowSuspendProcess->setText(tr("暂停进程"));
    actionWindowRecoveryProcess->setText(tr("恢复进程"));
    actionWindowReadModule->setText(tr("查看模块"));
    actionWindowReadThread->setText(tr("查看线程"));
    actionWindowAttribute->setText(tr("属性"));
    windowMenu->addAction(actionWindowOpenPath);
    windowMenu->addSeparator();
    windowMenu->addAction(actionWindowEndProcess);
    windowMenu->addAction(actionWindowSuspendProcess);
    windowMenu->addAction(actionWindowRecoveryProcess);
    windowMenu->addSeparator();
    windowMenu->addAction(actionWindowReadModule);
    windowMenu->addAction(actionWindowReadThread);
    windowMenu->addSeparator();
    windowMenu->addAction(actionWindowAttribute);

    connect(processView , SIGNAL(customContextMenuRequested(QPoint)) , this , SLOT(slotContextMenu(QPoint)));
    connect(windowView , SIGNAL(customContextMenuRequested(QPoint)) , this , SLOT(slotWindowContextMenu(QPoint)));
    connect(this->ui->actionLogout , SIGNAL(triggered()) , this , SLOT(logout()));
    connect(this->ui->actionShutdown , SIGNAL(triggered()) , this , SLOT(shutdown()));
    connect(this->ui->actionReboot , SIGNAL(triggered()) , this , SLOT(reboot()));
    connect(actionOpenPath , SIGNAL(triggered()) , this , SLOT(openFilePath()));
    connect(actionEndProcess , SIGNAL(triggered()) , this , SLOT(finishProcess()));
    connect(actionSuspendProcess , SIGNAL(triggered()) , this , SLOT(suspendProcess()));
    connect(actionRecoveryProcess , SIGNAL(triggered()) , this , SLOT(recoveryProcess()));
    connect(actionAttribute , SIGNAL(triggered()) , this , SLOT(viewProperties()));
    connect(actionReadModule , SIGNAL(triggered()) , this , SLOT(viewModule()));
    connect(actionReadThread , SIGNAL(triggered()) , this , SLOT(viewThreads()));
    connect(actionWindowOpenPath , SIGNAL(triggered()) , this , SLOT(openWindowFilePath()));
    connect(actionWindowEndProcess , SIGNAL(triggered()) , this , SLOT(finishWindowProcess()));
    connect(actionWindowSuspendProcess , SIGNAL(triggered()) , this , SLOT(suspendWindowProcess()));
    connect(actionWindowRecoveryProcess , SIGNAL(triggered()) , this , SLOT(recoveryWindowProcess()));
    connect(actionWindowAttribute , SIGNAL(triggered()) , this , SLOT(viewWindowProperties()));
    connect(actionWindowReadModule , SIGNAL(triggered()) , this , SLOT(viewModule()));
    connect(actionWindowReadThread , SIGNAL(triggered()) , this , SLOT(viewThreads()));
    ui->tabProcess->setContentsMargins(0, 0 ,0, 51);//设置底部间距为底部状态栏高度+顶部菜单栏高度
    ui->tabWindow->setContentsMargins(0, 0 ,0, 51);//设置底部间距为底部状态栏高度+顶部菜单栏高度
    processView->setSortingEnabled(true);//允许点击表头排序
    windowView->setSortingEnabled(true);//允许点击表头排序

    statusLabel = new QLabel;
    statusLabel->setFixedWidth(250);
    statusLabel->setText(tr(" 进程数 : ")+ QString::number(processNum));
    ui->statusBar->addWidget(statusLabel);

    processLabel = new QLabel;
    processLabel->setFixedWidth(100);
    processLabel->setText(" CPU : " + QString::number(SystemInfoWin::GetCpuUsage()) + "%");
    ui->statusBar->addWidget(processLabel);
    SystemInfoWin::GetMemoryInfo(mi);
    memoryLabel = new QLabel;
    memoryLabel->setFixedWidth(100);
    memoryLabel->setText(tr(" 内存 : ") + QString::number(mi.memoryPrecent) + "%") ;
    ui->statusBar->addWidget(memoryLabel);

    timer = new QTimer(this);
    timer->start(1000);//更新间隔为1s
    connect(timer , SIGNAL(timeout()) , this , SLOT(timeUpdate()));
}

//析构函数
TaskMgr::~TaskMgr()
{
    delete ui;
    delete md;
    delete td;
    delete[] nTaskList.th32ProcessID;
    delete[] nTaskList.cntThreads;
    delete[] nTaskList.th32ParentProcessID;
    delete item0;
    delete item1;
    delete item2;
    delete item3;
    delete item4;
    delete item5;
    delete item6;
    delete processView;
    delete processModel;
    delete processLayout;
    delete windowView;
    delete windowModel;
    delete windowLayout;
    delete popMenu;
    delete windowMenu;
    delete actionOpenPath;
    delete actionEndProcess;
    delete actionSuspendProcess;
    delete actionRecoveryProcess;
    delete actionReadModule;
    delete actionReadThread;
    delete actionAttribute;
    delete actionWindowOpenPath;
    delete actionWindowEndProcess;
    delete actionWindowSuspendProcess;
    delete actionWindowRecoveryProcess;
    delete actionWindowReadModule;
    delete actionWindowReadThread;
    delete actionWindowAttribute;
    delete statusLabel;
    delete processLabel;
    delete memoryLabel;
    delete timer;
    delete qmw;
}

void TaskMgr::addWindowItem(int index ,QString name , DWORD pid , QString path){
    QFileInfo fileInfo(path);
    QIcon tmpIcon = iconProvider.icon(fileInfo);
    item0 = new QStandardItem(tmpIcon , name);
    windowModel->setItem(index, 0 , item0);
    item0->setData(name , Qt::ToolTipRole);

    item1 = new QStandardItem();
    item1->setData(QVariant(double(pid)), Qt::EditRole);
    windowModel->setItem(index , 1 , item1);

    item2 = new QStandardItem(path);
    windowModel->setItem(index, 2 , item2);
    item2->setData(path , Qt::ToolTipRole);

    windowModel->item(index,1 )->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    windowModel->item(index,2 )->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void TaskMgr::addProcessItem(int index , QString name , DWORD pid , QString pri , QString mem , DWORD threadN , DWORD par , QString pa){
    // 添加行
    QFileInfo fileInfo(pa);
    QIcon tmpIcon = iconProvider.icon(fileInfo);
    if(pa.length() == 0 ){
        pa = "System path";
        item0 = new QStandardItem(icon , name);
        processModel->setItem(index, 0 , item0);
        item0->setData(name , Qt::ToolTipRole);
    }
    else if(pa.contains(systemPath , Qt::CaseInsensitive)){
        item0 = new QStandardItem(icon , name);
        processModel->setItem(index, 0 , item0);
        item0->setData(name , Qt::ToolTipRole);
    }
    else{
        item0 = new QStandardItem(tmpIcon , name);
        processModel->setItem(index, 0 , item0);
        item0->setData(name , Qt::ToolTipRole);
    }

    item1 = new QStandardItem();
    item1->setData(QVariant(double(pid)), Qt::EditRole);
    processModel->setItem(index , 1 , item1);

    item2 = new QStandardItem(pri);
    processModel->setItem(index, 2 , item2);
    item2->setData(pri , Qt::ToolTipRole);

    if(pa == "System path"){
        item3 = new QStandardItem("-");
        processModel->setItem(index, 3 , item3);
        item3->setData("-" , Qt::ToolTipRole);
    }
    else{
        item3 = new QStandardItem();
        item3->setData(QVariant(mem.toDouble()), Qt::EditRole);
        processModel->setItem(index , 3 , item3);
    }

    item4 = new QStandardItem();
    item4->setData(QVariant(double(threadN)), Qt::EditRole);
    processModel->setItem(index , 4 , item4);

    item5 = new QStandardItem();
    item5->setData(QVariant(double(par)), Qt::EditRole);
    processModel->setItem(index , 5 , item5);

    /*QStandardItem *item4 = new QStandardItem(QString::number(threadN));
    processModel->setItem(index, 4 , item4);
    item4->setData(QString::number(threadN) , Qt::ToolTipRole);

    QStandardItem *item5 = new QStandardItem(QString::number(par));
    processModel->setItem(index, 5 , item5);
    item5->setData(QString::number(par) , Qt::ToolTipRole);*/

    item6 = new QStandardItem(pa);
    processModel->setItem(index, 6 , item6);
    item6->setData(pa , Qt::ToolTipRole);

    // 居右
    processModel->item(index,1 )->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    processModel->item(index,2 )->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    processModel->item(index,3 )->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    processModel->item(index,4 )->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    processModel->item(index,5 )->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
}

void TaskMgr::GetProcessFilePath(HANDLE hProcess, QString& sFilePath)
{
    sFilePath = "";
    TCHAR tsFileDosPath[MAX_PATH + 1];
    ZeroMemory(tsFileDosPath, sizeof(TCHAR)*(MAX_PATH + 1));
    if (0 == GetProcessImageFileName(hProcess, tsFileDosPath, MAX_PATH + 1))
    {
        return;
    }

    // 获取Logic Drive String长度

    SIZE_T uiLen = GetLogicalDriveStrings(0, NULL);
    if (0 == uiLen)
    {
        return;
    }

    PTSTR pLogicDriveString = new TCHAR[uiLen + 1];
    ZeroMemory(pLogicDriveString, uiLen + 1);
    uiLen = GetLogicalDriveStrings((DWORD)uiLen, pLogicDriveString);
    if (0 == uiLen)
    {
        delete[]pLogicDriveString;
        return;
    }

    TCHAR szDrive[3] = TEXT(" :");
    PTSTR pDosDriveName = new TCHAR[MAX_PATH];
    PTSTR pLogicIndex = pLogicDriveString;

    do
    {
        szDrive[0] = *pLogicIndex;
        uiLen = QueryDosDevice(szDrive, pDosDriveName, MAX_PATH);
        if (0 == uiLen)
        {
            if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
            {
                break;
            }

            delete[]pDosDriveName;
            pDosDriveName = new TCHAR[uiLen + 1];
            uiLen = QueryDosDevice(szDrive, pDosDriveName, (DWORD)uiLen + 1);
            if (0 == uiLen)
            {
                break;
            }
        }

        uiLen = wcslen(pDosDriveName);
        if (0 == _wcsnicmp(tsFileDosPath, pDosDriveName, uiLen))
        {
            QString fileDOsPath = QString::fromWCharArray(tsFileDosPath + uiLen);
            QString drive = QString::fromWCharArray(szDrive);
            sFilePath = sFilePath + drive + fileDOsPath ;
            //sFilePath.Format(("%s%s"), szDrive, tsFileDosPath + uiLen);
            break;
        }
        while (*pLogicIndex++);
    } while (*pLogicIndex);

    delete[]pLogicDriveString;
    delete[]pDosDriveName;
}

void TaskMgr::GetProcessPriority(QString &nState, HANDLE nHandle)
{
    if ((DWORD)nHandle == -1)
    {
        nState = tr("6:无权限");
        return;
    }

    DWORD nClass;
    nClass = GetPriorityClass(nHandle);

    switch (nClass)
    {
    case 256:
        nState = tr("0:实时");
        return;
    case 128:
        nState = tr("1:最高");
        return;
    case 32768:
        nState = tr("2:高于标准");
        return;
    case 32:
        nState = tr("3:标准");
        return;
    case 16384:
        nState = tr("4:低于标准");
        return;
    case 64:
        nState = tr("5:低");
        return;
    case 0:
        nState = tr("1:最高");
        return;
    }
    nState = tr("6:无权限");
}

DWORD TaskMgr::EnumTaskList(TASKLIST &nTaskList)
{
    BOOL nRet;
    DWORD nIndex = 0;
    PROCESSENTRY32 nPT;
    SHFILEINFO nPsfi = { 0 };//文件信息
    nPT.dwSize = sizeof(PROCESSENTRY32);
    HANDLE nSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    nRet = Process32First(nSnapShot, &nPT);
    while (nRet)
    {
        nRet = Process32Next(nSnapShot, &nPT);
        nIndex++;
    }

    //nTaskList.szExeFile = new QString[nIndex];
    nTaskList.th32ProcessID = new DWORD[nIndex];
    nTaskList.cntThreads = new DWORD[nIndex];
    nTaskList.th32ParentProcessID = new DWORD[nIndex];
    //nTaskList.szExeFilePath = new QString[nIndex];
    //nTaskList.WorkingSetSize = new QString[nIndex];
    //nTaskList.szPriority = new QString[nIndex];

    nIndex = 0;
    nRet = Process32First(nSnapShot, &nPT);
    while (nRet)
    {
        HANDLE nHandle;
        QString nFilePath;
        QString nMenory;
        QString nPriority;
        PROCESS_MEMORY_COUNTERS nMen;
        nHandle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, nPT.th32ProcessID);
        GetProcessFilePath(nHandle, nFilePath);
        GetProcessMemoryInfo(nHandle,&nMen,sizeof(PROCESS_MEMORY_COUNTERS));
        double workingMemory = nMen.WorkingSetSize;
        nMenory = nMenory + QString::number(workingMemory / 1024 / 1024, 10 , 1);
        GetProcessPriority(nPriority, nHandle);
        CloseHandle(nHandle);

        QString fileName = QString::fromWCharArray(nPT.szExeFile);
        nTaskList.szExeFile.push_back(fileName);
        //nTaskList.szExeFile[nIndex] = (LPSTR)nPT.szExeFile;
        nTaskList.th32ProcessID[nIndex] = nPT.th32ProcessID;
        nTaskList.cntThreads[nIndex] = nPT.cntThreads;
        nTaskList.th32ParentProcessID[nIndex] = nPT.th32ParentProcessID;
        //nTaskList.szExeFilePath[nIndex] = nFilePath;
        //nTaskList.WorkingSetSize[nIndex] = nMenory;
        //nTaskList.szPriority[nIndex] = nPriority;
        nTaskList.szExeFilePath.push_back(nFilePath);
        nTaskList.WorkingSetSize.push_back(nMenory);
        nTaskList.szPriority.push_back(nPriority);
        nRet = Process32Next(nSnapShot, &nPT);
        nIndex++;
    }
    CloseHandle(nSnapShot);

    //获得进程图标
    /*WCHAR filePath[MAX_PATH];
    QString(nTaskList.szExeFilePath[nIndex]).toWCharArray(filePath);
    DWORD nFileAttributes = SHGFI_SYSICONINDEX | SHGFI_SMALLICON;//获取文件信息
    if (!SHGetFileInfo(filePath, nFileAttributes, &nPsfi, sizeof(SHFILEINFO), SHGFI_ICON))
    {
        SHGetFileInfo(filePath, nFileAttributes, &nPsfi, sizeof(SHFILEINFO), SHGFI_ICON| SHGFI_USEFILEATTRIBUTES| SHGFI_SMALLICON);
    }
    */
    return nIndex;
}

void TaskMgr::resizeEvent(QResizeEvent* size){
    this->ui->tabWidget->resize(this->width() - 26 , this->height());
    int column =
    processView->columnWidth(0) +
    processView->columnWidth(1) +
    processView->columnWidth(2) +
    processView->columnWidth(3) +
    processView->columnWidth(4) +
    processView->columnWidth(5);

    processView->setColumnWidth( 6 , processView->width() - column - 23);
}

//弹出右键菜单的函数
void TaskMgr::slotContextMenu(QPoint pos){
    auto index = processView->indexAt(pos);
    if(index.isValid()){
        popMenu->exec(QCursor::pos());//在当前鼠标的位置出现菜单
    }
}

//弹出窗口界面右键菜单的函数
void TaskMgr::slotWindowContextMenu(QPoint pos){
    auto index = windowView->indexAt(pos);
    if(index.isValid()){
        windowMenu->exec(QCursor::pos());
    }
}

void TaskMgr::timeUpdate(){
    statusLabel->setText(tr(" 进程数 : ")+ QString::number(processNum));
    ui->statusBar->addWidget(statusLabel);
    SystemInfoWin::GetMemoryInfo(mi);
    processLabel->setText(tr(" CPU : ") + QString::number(SystemInfoWin::GetCpuUsage()) + "%");
    ui->statusBar->addWidget(processLabel);
    memoryLabel->setText(tr(" 内存 : ") + QString::number(mi.memoryPrecent) + "%") ;
    ui->statusBar->addWidget(memoryLabel);
}

void TaskMgr::logout(){//注销
    AdjustPrivilege();
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, tr("提示"), tr("确定要注销？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes){
        ExitWindowsEx(EWX_LOGOFF, 0);
    }
    else{
        return;
    }
}

void TaskMgr::reboot(){//重启
    AdjustPrivilege();
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, tr("提示"), tr("确定要重启？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes){
        ExitWindowsEx(EWX_REBOOT, 0);
    }
    else{
        return;
    }
}

void TaskMgr::shutdown(){//关机
    AdjustPrivilege();
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, tr("提示"), tr("确定要关机？"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes){
        ExitWindowsEx(EWX_SHUTDOWN, 0);
    }
    else{
        return;
    }
}

//提权函数
bool TaskMgr::AdjustPrivilege()
{
    bool bRet = FALSE;
    TOKEN_PRIVILEGES tp = { 0 };//令牌权限结构
    HANDLE hToken = nullptr;//令牌句柄
    do
    {
        //打开当前进程令牌,并且获取它              //令牌权限修改和查询
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
            TOKEN_QUERY, &hToken))
            break;
        //获取关机注销重启的LUID(Locally Unique Identifier),局部唯一标识
        if (!LookupPrivilegeValue(nullptr, SE_SHUTDOWN_NAME, &tp.Privileges[0].Luid))
            break;
        tp.PrivilegeCount = 1;//修改权限的个数
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;//激活SE_SHUTDOWN_NAME这个权限
                                                           //提升权限//FALSE表示可以修改权限//把需要修改的权限传进来
        if (!AdjustTokenPrivileges(hToken, FALSE, &tp, 0, (PTOKEN_PRIVILEGES)nullptr, 0))
            break;
        bRet = TRUE;
    } while (FALSE);
    if (hToken)
        CloseHandle(hToken);
    return bRet;
}

//打开文件位置
void TaskMgr::openFilePath()
{
    int row = processView->currentIndex().row();
    QModelIndex index = processModel->index(row , 6);//第6项为路径
    QVariant data = processModel->data(index);
    QString dataStr = data.toString();//文件路径
    if(dataStr == "System path"){
        QMessageBox::information(NULL, tr("提示"), tr("系统目录！"));
    }
    else{
        QString fileName;
        QProcess process;
        fileName = dataStr;
        #ifdef WIN32
        fileName.replace("/", "\\");    //***这句windows下必要***
        #endif
        process.startDetached("explorer /select," + fileName);
    }
}

//结束进程
void TaskMgr::finishProcess()
{
    int row = processView->currentIndex().row();
    QModelIndex index = processModel->index(row , 1);//第1项为进程号
    QVariant data = processModel->data(index);
    DWORD dataInt = data.toInt();//进程号
    endProcess(dataInt);
    this->processModel->removeRow(row);
}

//暂停进程
void TaskMgr::suspendProcess()
{
    int row = processView->currentIndex().row();
    QModelIndex index = processModel->index(row , 1);//第1项为进程号
    QVariant data = processModel->data(index);
    DWORD dataInt = data.toInt();//进程号
    setProcessState( dataInt , true );
}

//恢复进程
void TaskMgr::recoveryProcess()
{
    int row = processView->currentIndex().row();
    QModelIndex index = processModel->index(row , 1);//第1项为进程号
    QVariant data = processModel->data(index);
    DWORD dataInt = data.toInt();//进程号
    setProcessState( dataInt , false );
}

//查看模块
void TaskMgr::viewModule()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        int row = processView->currentIndex().row();
        QModelIndex index = processModel->index(row , 1);//第1项为进程号
        QVariant data = processModel->data(index);
        DWORD dataInt = data.toInt();//进程号
        qmw = new QMainWindow(this);
        qmw->setMinimumSize(700 , 400);
        qmw->show();
        md = new ModuleDlg(dataInt , qmw );
        md->show();
    }
    else if(ui->tabWidget->currentIndex() == 1){
        int row = windowView->currentIndex().row();
        QModelIndex index = windowModel->index(row , 1);//第1项为进程号
        QVariant data = windowModel->data(index);
        DWORD dataInt = data.toInt();//进程号
        qmw = new QMainWindow(this);
        qmw->setMinimumSize(700 , 400);
        qmw->show();
        md = new ModuleDlg(dataInt , qmw );
        md->show();
    }
}

//查看线程
void TaskMgr::viewThreads()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        int row = processView->currentIndex().row();
        QModelIndex index = processModel->index(row , 1);//第1项为进程号
        QVariant data = processModel->data(index);
        DWORD dataInt = data.toInt();//进程号
        qmw = new QMainWindow(this);
        qmw->setMinimumSize(700 , 400);
        qmw->show();
        td = new ThreadDlg(dataInt , qmw );
        td->show();
    }
    else if(ui->tabWidget->currentIndex() == 1){
        int row = windowView->currentIndex().row();
        QModelIndex index = windowModel->index(row , 1);//第1项为进程号
        QVariant data = windowModel->data(index);
        DWORD dataInt = data.toInt();//进程号
        qmw = new QMainWindow(this);
        qmw->setMinimumSize(700 , 400);
        qmw->show();
        td = new ThreadDlg(dataInt , qmw );
        td->show();
    }
}

//属性
void TaskMgr::viewProperties()
{
    int row = processView->currentIndex().row();
    QModelIndex index = processModel->index(row , 6);//第6项为路径
    QVariant data = processModel->data(index);
    QString dataStr = data.toString();//文件路径
    if(dataStr == "System path"){
        QMessageBox::information(NULL, tr("提示"), tr("系统目录！"));
    }
    else{
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST ;
        ShExecInfo.lpVerb = L"properties";
        ShExecInfo.lpFile = dataStr.toStdWString().c_str();
        ShExecInfo.lpParameters = L"";
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_SHOW;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
    }
}

//打开窗口程序文件位置
void TaskMgr::openWindowFilePath()
{
    int row = windowView->currentIndex().row();
    QModelIndex index = windowModel->index(row , 2);//第6项为路径
    QVariant data = windowModel->data(index);
    QString dataStr = data.toString();//文件路径
    if(dataStr == "System path"){
        QMessageBox::information(NULL, tr("提示"), tr("系统目录！"));
    }
    else{
        QString fileName;
        QProcess process;
        fileName = dataStr;
        #ifdef WIN32
        fileName.replace("/", "\\");    //***这句windows下必要***
        #endif
        process.startDetached("explorer /select," + fileName);
    }
}

//结束窗口程序主进程
void TaskMgr::finishWindowProcess()
{
    int row = windowView->currentIndex().row();
    QModelIndex index = windowModel->index(row , 1);//第1项为进程号
    QVariant data = windowModel->data(index);
    DWORD dataInt = data.toInt();//进程号
    endProcess(dataInt);
    this->windowModel->removeRow(row);
}

//暂停窗口程序主进程
void TaskMgr::suspendWindowProcess()
{
    int row = windowView->currentIndex().row();
    QModelIndex index = windowModel->index(row , 1);//第1项为进程号
    QVariant data = windowModel->data(index);
    DWORD dataInt = data.toInt();//进程号
    setProcessState( dataInt , true );
}

//恢复窗口程序主进程
void TaskMgr::recoveryWindowProcess()
{
    int row = windowView->currentIndex().row();
    QModelIndex index = windowModel->index(row , 1);//第1项为进程号
    QVariant data = windowModel->data(index);
    DWORD dataInt = data.toInt();//进程号
    setProcessState( dataInt , false );
}

//窗口程序属性
void TaskMgr::viewWindowProperties()
{
    int row = windowView->currentIndex().row();
    QModelIndex index = windowModel->index(row , 2);//第6项为路径
    QVariant data = windowModel->data(index);
    QString dataStr = data.toString();//文件路径
    if(dataStr == "System path"){
        QMessageBox::information(NULL, tr("提示"), tr("系统目录！"));
    }
    else{
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST ;
        ShExecInfo.lpVerb = L"properties";
        ShExecInfo.lpFile = dataStr.toStdWString().c_str();
        ShExecInfo.lpParameters = L"";
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_SHOW;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
    }
}

void TaskMgr::setProcessState(DWORD nPid, BOOL nSuspend)//设置进程状态
{
    HANDLE nHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, nPid);

    if (nSuspend)
    {
        typedef int(WINAPI*ZwSuspendProcess)(HANDLE);
        HMODULE module = LoadLibrary(TEXT("ntdll.dll"));
        ZwSuspendProcess ZwSuspend = (ZwSuspendProcess)GetProcAddress(module, "ZwSuspendProcess");
        ZwSuspend(nHandle);//暂停
        FreeLibrary(module);
    }
    else
    {
        typedef int(WINAPI*ZwResumeProcess)(HANDLE);
        HMODULE module = LoadLibrary(TEXT("ntdll.dll"));
        ZwResumeProcess ZwResume = (ZwResumeProcess)GetProcAddress(module, "ZwResumeProcess");
        ZwResume(nHandle);//恢复
        FreeLibrary(module);
    }
    CloseHandle(nHandle);
}

void TaskMgr::endProcess(DWORD nPid)
{
    HANDLE nHandle = OpenProcess(PROCESS_TERMINATE, FALSE, nPid);
    TerminateProcess(nHandle, 0);
    CloseHandle(nHandle);
}

void TaskMgr::addWindowModel(){
    windowModel->setHorizontalHeaderItem(0, new QStandardItem(tr("当前窗口")));
    windowModel->setHorizontalHeaderItem(1, new QStandardItem(tr("进程号")));
    windowModel->setHorizontalHeaderItem(2, new QStandardItem(tr("路径")));
    windowView->setModel(windowModel);
    windowView->setColumnWidth( 0 , 200);
    windowView->setColumnWidth( 1 , 80);
    windowView->setColumnWidth( 2 , 350);
    windowView->setContextMenuPolicy(Qt::CustomContextMenu);//可弹出右键菜单
    // 隐藏行头
    windowView->verticalHeader()->hide();
    // 整行选中
    windowView->setSelectionBehavior(QAbstractItemView::SelectRows);
    windowView->setSelectionMode(QAbstractItemView::SingleSelection);
    // 不可编辑
    windowView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    windowView->setStyleSheet("TableView{border:none;background:white;}");
    windowView->setStyleSheet("TableView::item:selected{color:white;background:rgb(34, 175, 75);}");
    // 添加布局
    windowLayout = new QGridLayout(this->ui->tabWindow);

    windowLayout->addWidget(windowView);
    EnumWindows(WindowsProc,(LPARAM)&nWindowList);
    int count = 0;
    for(int i = 0; i < nWindowList.szExeFile.size() ; i++){
        if(nWindowList.szExeFilePath[i].length() != 0 && !nWindowList.szExeFilePath[i].contains(systemPath , Qt::CaseInsensitive)){
            addWindowItem(count++ , nWindowList.szExeFile[i] , nWindowList.th32ProcessID[i] , nWindowList.szExeFilePath[i]);
        }
    }
}

void TaskMgr::addProcessModel(){
    processModel->setHorizontalHeaderItem(0, new QStandardItem(tr("进程名字")));
    processModel->setHorizontalHeaderItem(1, new QStandardItem(tr("进程号")));
    processModel->setHorizontalHeaderItem(2, new QStandardItem(tr("优先级")));
    processModel->setHorizontalHeaderItem(3, new QStandardItem(tr("内存使用(M)")));
    processModel->setHorizontalHeaderItem(4, new QStandardItem(tr("线程数量")));
    processModel->setHorizontalHeaderItem(5, new QStandardItem(tr("父进程号")));
    processModel->setHorizontalHeaderItem(6, new QStandardItem(tr("进程路径")));
    processView->setModel(processModel);
    processView->setColumnWidth( 0 , 130);
    int column =
    processView->columnWidth(0) +
    processView->columnWidth(1) +
    processView->columnWidth(2) +
    processView->columnWidth(3) +
    processView->columnWidth(4) +
    processView->columnWidth(5);
    processView->setColumnWidth( 1 , 60);
    processView->setColumnWidth( 2 , 60);
    processView->setColumnWidth( 3 , 95);
    processView->setColumnWidth( 4 , 70);
    processView->setColumnWidth( 5 , 70);
    processView->setColumnWidth( 6 , 135);
    processView->setContextMenuPolicy(Qt::CustomContextMenu);//可弹出右键菜单
    // 隐藏行头
    processView->verticalHeader()->hide();
    // 整行选中
    processView->setSelectionBehavior(QAbstractItemView::SelectRows);
    processView->setSelectionMode(QAbstractItemView::SingleSelection);
    // 不可编辑
    processView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    processView->setStyleSheet("TableView{border:none;background:white;}");
    processView->setStyleSheet("TableView::item:selected{color:white;background:rgb(34, 175, 75);}");
    // 添加布局

    //actionLogout = new QAction(this->ui->actionLogout);
    //actionShutdown = new QAction(this->ui->actionShutdown);
    //actionReboot = new QAction(this->ui->actionReboot);

    DWORD nNum = EnumTaskList(nTaskList);//枚举进程列表
    int count = 0;
    for(int i = 0; i < nNum ;i++){
        if(nTaskList.szExeFilePath[i].length() != 0){
        addProcessItem( count++,
                       nTaskList.szExeFile[i] ,
                       nTaskList.th32ProcessID[i] ,
                       nTaskList.szPriority[i] ,
                       nTaskList.WorkingSetSize[i] ,
                       nTaskList.cntThreads[i] ,
                       nTaskList.th32ParentProcessID[i] ,
                       nTaskList.szExeFilePath[i]
                       );
        }
    }
    for(int i = 0; i < nNum ;i++){
        if(nTaskList.szExeFilePath[i].length() == 0){
        addProcessItem( count++,
                       nTaskList.szExeFile[i] ,
                       nTaskList.th32ProcessID[i] ,
                       nTaskList.szPriority[i] ,
                       nTaskList.WorkingSetSize[i] ,
                       nTaskList.cntThreads[i] ,
                       nTaskList.th32ParentProcessID[i] ,
                       nTaskList.szExeFilePath[i]
                       );
        }
    }
    processNum = nNum;
}
