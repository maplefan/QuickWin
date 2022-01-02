#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pcinfowindow.h"
#include "systeminfowin.h"
#include <iostream>

extern double netUploadex;
extern double netDownloadex;

int g_cpuPercent;
int g_memoryPercent;
double g_uploadSpeed;
double g_downloadSpeed;
HHOOK g_hHook;
_GetSelectedFromDesktop GetSelectedFromDesktop;
_GetSelectedFromExplorer GetSelectedFromExplorer;
_GetFocusedWindowType GetFocusedWindowType;
typedef void(*_Init)();
typedef int(*_getType)();
typedef void (*_getSelect)(PWCHAR buffer);
_Init Init;
_getType getType;
_getSelect getSelect;

QString lastPath;//路径
QString qstr;
WCHAR wstr[MAX_PATH] = {'\0'};
MainWindow *mw;
QuickLook *ql = nullptr;
bool isShowMainWindowFullScreen;
QString mainColor;
QString mainColorBK;
QString taskColor;
int isQuickLook; // 0不存在 1关闭 2开启
int mainDoubleClick;
int mainShowInfo;
int mainShowNum;
int updateTime;
int monitorInterval;
extern QString g_strUploadSpeed;
extern QString g_strDownloadSpeed;
extern QString g_strCPUUtil;
extern QString g_strMemoryUtil;
extern QString g_strMainboardTemp;
extern QString g_strMainboardFan;
extern QString g_strCPUTemp;
extern QString g_strGPUTemp;
extern QString g_strCPUPower;
extern QString g_strGPUPower;
extern QString g_strGPUUtil;
extern QString g_strDiskTemp;

std::queue<QString> mainQueue;

//键盘钩子回调函数
LRESULT  CALLBACK  MainWindow::KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    char c[2];
    c[1] = 0;
     if ((wParam == WM_KEYDOWN) && (HC_ACTION == nCode)) {		//有键按下
        KBDLLHOOKSTRUCT* keyNum = (KBDLLHOOKSTRUCT*)lParam;
        if(keyNum->vkCode == VK_SPACE){
            qDebug()<<"quickLook:"<<"space"<<isQuickLook;
            if(isQuickLook == 2 || isQuickLook == 0){
                //当按下空格键时
                //调用QuickLook模块
                if(getType() != 0){
                    if(ql){
                        ql->destoryThis();
                        delete ql;
                        ql = nullptr;
                    }
                    ql = new QuickLook(qstr , mw );
                    ql->setAttribute(Qt::WA_DeleteOnClose,  true);
                    //ql->show();
                }
            }
            //返回1表示截取消息不再传递,返回0表示不作处理,消息继续传递
            return 0;
        }
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /*
    QLibrary hookLib("QuickLookDll");
    if(hookLib.load()){
        GetFocusedWindowType = (_GetFocusedWindowType)hookLib.resolve("GetFocusedWindowType");
        GetSelectedFromExplorer = (_GetSelectedFromExplorer)hookLib.resolve("GetSelectedFromExplorer");
        GetSelectedFromDesktop = (_GetSelectedFromDesktop)hookLib.resolve("GetSelectedFromDesktop");
    }
    */
    mw = this;
    HMODULE module = LoadLibrary(L"QuickLook.Native32.dll");
    if(module == NULL){

    }
    Init = (_Init)GetProcAddress(module , "Init");
    getType = (_getType)GetProcAddress(module , "GetFocusedWindowType");
    getSelect = (_getSelect)GetProcAddress(module , "GetCurrentSelection");
    Init();
    m_nTimerIDHook = startTimer(100);
    QString configPath =  QCoreApplication::applicationDirPath() + "/config";
    if(!isDirExist(configPath)){
        QMessageBox::information(NULL, tr("提示"), tr("无法创建配置文件！"));
    }
    else{
        //读取配置文件
         configShowMainWindow = Config().Get("Main" , "showMainWindow").toInt();
         configAlwaysTop = Config().Get("Main" , "alwaysTop").toInt();
         configKeepSide = Config().Get("Main" , "keepSide").toInt();
         configLockWindow = Config().Get("Main" , "lockWindow").toInt();
         configShowOnTaskBar = Config().Get("Main" , "showOnTaskBar").toInt();
         configPacity = Config().Get("Main" , "pacity").toInt();
         configSelectedConnection = Config().Get("Main" , "selectedConnection").toString();
    }

    //获得程序启动时间
    GetLocalTime(&startTime);

    gnit = new GetNetInfoThread();
    tld = new TranslatorDlg();
    st = NULL;
    snap = NULL;
    tm = NULL;
    cw = NULL;
    piw = NULL;
    qs = NULL;
    tb = NULL;
    mt = NULL;
    trd = NULL;
    hm = NULL;
    pcs = NULL;
    sc = NULL;
    snWidget = NULL;
    g_hHook = NULL;
    netUpload = 0;
    netDownload = 0;
    cpuPercent = 0;
    memoryPercent = 0;
    windowWidth = 260;
    windowHeight = 70;
    ac_connection_selected = 0;

    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));

    QString mainFontFamily = Config().Get("Setting" , "MainFontFamily").toString();
    int mainFontSize = Config().Get("Setting" , "MainFontSize").toInt();
    QString mainFontColor = Config().Get("Setting" , "MainFontColor").toString();
    QString mainFontColorBK = Config().Get("Setting" , "MainFontColorBK").toString();
    mainDoubleClick = Config().Get("Setting" , "MainDoubleClickAction").toInt();
    mainShowInfo = Config().Get("Setting" , "MainShowInfo").toInt();
    if(mainShowInfo == 0){
        mainShowInfo = 1+2+4+8+16;//默认为前四项显示
    }
    if(Config().Get("Setting" , "IsShowMainWindowFullScreen").toInt() == 0){
        isShowMainWindowFullScreen = true;
    }
    else{
        isShowMainWindowFullScreen = false;
    }

    if(Config().Get("Setting" , "QuickLook").toInt() == 0){
        isQuickLook = 2;
    }
    if(mainFontFamily.length() == 0 && mainFontSize == 0){
        mainFontFamily = "Microsoft YaHei";
        mainFontSize = 10;
        Config().Set("Setting" , "mainFontFamily" , mainFontFamily);
        Config().Set("Setting" , "mainFontSize" , mainFontSize);
    }
    if(mainFontColor.length() == 0){
        mainFontColor = "255, 255, 255";
        Config().Set("Setting" , "mainFontColor" , mainFontColor);
    }
    if(mainFontColorBK.length() == 0){
        mainFontColorBK = "0, 0, 0";
        Config().Set("Setting" , "mainFontColorBK" , mainFontColorBK);
    }
    updateTime = Config().Get("Setting" , "updateTime").toInt();

    fontTitle = new QFont ( mainFontFamily, mainFontSize, 100);
    fontLabel = new QFont ( mainFontFamily, mainFontSize);
    fontInfo = new QFont ( mainFontFamily, mainFontSize);

//设置字体和字体颜色
    ui->labelFirst->setFont(*fontInfo);
    ui->labelSecond->setFont(*fontInfo);
    ui->labelThird->setFont(*fontInfo);
    ui->labelFourth->setFont(*fontInfo);

    ui->labelFirst->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainFontColor).arg(mainFontColorBK));
    ui->labelSecond->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainFontColor).arg(mainFontColorBK));
    ui->labelThird->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainFontColor).arg(mainFontColorBK));
    ui->labelFourth->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainFontColor).arg(mainFontColorBK));
    ui->centralWidget->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainFontColor).arg(mainFontColorBK));

    mainColor = mainFontColor;
    mainColorBK = mainFontColorBK;

    dwSize = sizeof(MIB_IFTABLE);
    m_pIfTable = (MIB_IFTABLE *)malloc(dwSize);
    int rtn;
    rtn = ::GetIfTable(m_pIfTable, &dwSize, FALSE);
    if (rtn == ERROR_INSUFFICIENT_BUFFER)	//如果函数返回值为ERROR_INSUFFICIENT_BUFFER，说明m_pIfTable的大小不够
    {
        free(m_pIfTable);
        m_pIfTable = (MIB_IFTABLE *)malloc(dwSize);	//用新的大小重新开辟一块内存
     }
    GetIfTable(m_pIfTable , &dwSize , FALSE);
    //如果不是显示全部接口
    AdapterInfo::GetAdapterInfo(adapters);
    AdapterInfo::GetIfTableInfo(adapters , m_pIfTable);

    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinimizeButtonHint);//去掉标题栏
    this->setFixedSize( windowWidth, windowHeight);//固定大小260*70
    QScreen *screen = QGuiApplication::primaryScreen ();
    desktopRect = screen->availableVirtualGeometry();
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setToolTip("QuickWin");
    //设置图标.
    m_trayIcon->setIcon(QIcon(":/images/tray.ico"));
    connect(m_trayIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onActivated(QSystemTrayIcon::ActivationReason)));
    menu = new QMenu(this);
    menuOpacity = new QMenu(tr("窗口不透明度"));
    menuAdapter = new QMenu(tr("选择网络连接"));
    //menu->setFont(*fontInfo);
    //menuOpacity->setFont(*fontInfo);
    //menuAdapter->setFont(*fontInfo);

    acSet100Opacity = menuOpacity->addAction("100%");
    acSet80Opacity = menuOpacity->addAction("80%");
    acSet60Opacity = menuOpacity->addAction("60%");
    acSet40Opacity = menuOpacity->addAction("40%");
    QSignalMapper *signalMapper = new QSignalMapper(this);

    menu->addMenu(menuAdapter);
    acSelectAuto = menuAdapter->addAction(QString(tr("自动选择")));
    acSelectAll = menuAdapter->addAction(QString(tr("选择全部")));
    acSelectAuto->setCheckable(true);
    acSelectAll->setCheckable(true);
    connect(acSelectAuto, SIGNAL(triggered()), this, SLOT(setSelectAuto()));
    connect(acSelectAll, SIGNAL(triggered()), this, SLOT(setSelectAll()));
    for(int i = 0; i < adapters.size() ;i++){
        //menuAdapter->addSection(QString::fromStdString(adapters[i].description));
        QAction *ac = menuAdapter->addAction(QString::fromStdString(adapters[i].description));
        connect(ac, SIGNAL(triggered()), signalMapper, SLOT(map()));
        signalMapper->setMapping(ac , ac->text());
        ac->setCheckable(true);
        acConnection.push_back(ac);
    }
    if(configSelectedConnection == "")
    {
        acSelectAll->setChecked(true);
        Config().Set("Main" , "selectedConnection" , "All");
    }
    else if(configSelectedConnection == "Auto"){//自动选择网卡
        acSelectAuto->setChecked(true);
    }
    else if(configSelectedConnection == "All"){
        acSelectAll->setChecked(true);
    }
    else{
        for(int i = 0; i < acConnection.size() ;i++){
            if(acConnection[i]->text() == configSelectedConnection){
                acConnection[i]->setChecked(true);
                ac_connection_selected = i;
            }
        }
    }
    connect(signalMapper , SIGNAL(mapped(QString)) , this , SLOT(setSelectAdapter(QString)));
    acTrafficStat = menu->addAction(tr("连接详情"));
    menu->addSeparator();//分离线
    acShowMainWindow = menu->addAction(tr("显示主窗口"));
    acAlwaysTop = menu->addAction(tr("总是置顶"));
    acKeepSide = menu->addAction(tr("靠边隐藏"));
    acLockWindow = menu->addAction(tr("锁定窗口位置"));
    acShowOnTaskBar = menu->addAction(tr("显示任务栏窗口"));
    menu->addMenu(menuOpacity);
    acOtherSetting = menu->addAction(tr("其他设置"));
    menu->addSeparator();//分离线
    acCatchScreen = menu->addAction(tr("截图工具"));
    acStickyNote = menu->addAction(tr("便利贴"));
    //acSniffer = menu->addAction("抓包");
    acCatchColor = menu->addAction(tr("颜色拾取"));
    acTaskMgr = menu->addAction(tr("任务管理器"));
    acMainTool = menu->addAction(tr("实用工具"));
    acTimeReminder = menu->addAction(tr("定时提醒"));
    acHotkeyManage = menu->addAction(tr("热键管理"));
    acShowStock = menu->addAction(tr("自选股"));
    acShowHardWare = menu->addAction(tr("查看硬件信息"));
    menu->addSeparator();//分离线
    acHelp = menu->addAction(tr("帮助"));
    acExit = menu->addAction(tr("退出"));

//设置可被选中
    acShowMainWindow->setCheckable(true);
    acAlwaysTop->setCheckable(true);
    acKeepSide->setCheckable(true);
    acLockWindow->setCheckable(true);
    acShowOnTaskBar->setCheckable(true);
    acSet100Opacity->setCheckable(true);
    acSet80Opacity->setCheckable(true);
    acSet60Opacity->setCheckable(true);
    acSet40Opacity->setCheckable(true);

//更新选中状态
    if(configPacity == 80){
        acSet100Opacity->setChecked(false);
        acSet80Opacity->setChecked(true);
        acSet60Opacity->setChecked(false);
        acSet40Opacity->setChecked(false);
    }
    else if(configPacity == 60){
        acSet100Opacity->setChecked(false);
        acSet80Opacity->setChecked(false);
        acSet60Opacity->setChecked(true);
        acSet40Opacity->setChecked(false);
    }
    else if(configPacity == 40){
        acSet100Opacity->setChecked(false);
        acSet80Opacity->setChecked(false);
        acSet60Opacity->setChecked(false);
        acSet40Opacity->setChecked(true);
    }
    else{
        acSet100Opacity->setChecked(true);
        acSet80Opacity->setChecked(false);
        acSet60Opacity->setChecked(false);
        acSet40Opacity->setChecked(false);
    }
    acShowMainWindow->setChecked(configShowMainWindow);
    acAlwaysTop->setChecked(configAlwaysTop);
    acKeepSide->setChecked(configKeepSide);
    acLockWindow->setChecked(configLockWindow);
    acShowOnTaskBar->setChecked(configShowOnTaskBar);

    //连接信号与槽
    //connect(acSetNetCard, SIGNAL(triggered()), this, SLOT(setNetCard()));
    connect(acTrafficStat, SIGNAL(triggered()), this, SLOT(showTrafficStat()));
    connect(acShowMainWindow, SIGNAL(triggered()), this, SLOT(showMainWindow()));
    connect(acAlwaysTop, SIGNAL(triggered()), this, SLOT(setAlwaysTop()));
    connect(acKeepSide, SIGNAL(triggered()), this, SLOT(setKeepSide()));
    connect(acLockWindow, SIGNAL(triggered()), this, SLOT(setLockWindow()));
    connect(acShowOnTaskBar, SIGNAL(triggered()), this, SLOT(showOnTaskBar()));
    connect(acOtherSetting, SIGNAL(triggered()), this, SLOT(showOtherSetting()));
    connect(acCatchScreen, SIGNAL(triggered()), this, SLOT(showCatchScreen()));
    connect(acStickyNote , SIGNAL(triggered()), this, SLOT(showStickyNote()));
    connect(acCatchColor, SIGNAL(triggered()), this, SLOT(showCatchColor()));
    //connect(acSniffer, SIGNAL(triggered()), this, SLOT(showSniffer()));
    connect(acTaskMgr, SIGNAL(triggered()), this, SLOT(showTaskMgr()));
    connect(acMainTool, SIGNAL(triggered()), this, SLOT(showMainTool()));
    connect(acTimeReminder, SIGNAL(triggered()), this, SLOT(showTimeReminder()));
    connect(acHotkeyManage, SIGNAL(triggered()), this, SLOT(showHotkeyManage()));
    connect(acShowHardWare, SIGNAL(triggered()), this, SLOT(showHardWare()));
    connect(acShowStock, SIGNAL(triggered()), this, SLOT(showStock()));
    connect(acHelp, SIGNAL(triggered()), this, SLOT(showHelp()));
    connect(acExit, SIGNAL(triggered()), this, SLOT(quitExe()));
    connect(acSet100Opacity, SIGNAL(triggered()), this, SLOT(set100Opacity()));
    connect(acSet80Opacity, SIGNAL(triggered()), this, SLOT(set80Opacity()));
    connect(acSet60Opacity, SIGNAL(triggered()), this, SLOT(set60Opacity()));
    connect(acSet40Opacity, SIGNAL(triggered()), this, SLOT(set40Opacity()));
    m_trayIcon->show();
    windowX = this->x();
    windowY = this->y();

    setWindowOpacity((double)configPacity / 100);
    show();

    if(updateTime == 0){
        m_nTimerIDInfo = startTimer(1000);
        monitorInterval = 1;
    }
    else if(updateTime == 1){
        m_nTimerIDInfo = startTimer(2000);
        monitorInterval = 2;
    }
    else if(updateTime == 2){
        m_nTimerIDInfo = startTimer(3000);
        monitorInterval = 3;
    }
    else if(updateTime == 3){
        m_nTimerIDInfo = startTimer(4000);
        monitorInterval = 4;
    }
    else if(updateTime == 4){
        m_nTimerIDInfo = startTimer(5000);
        monitorInterval = 5;
    }
    else if(updateTime == 5){
        m_nTimerIDInfo = startTimer(7000);
        monitorInterval = 7;
    }
    else if(updateTime == 6){
        m_nTimerIDInfo = startTimer(10000);
        monitorInterval = 10;
    }

    if(configShowOnTaskBar){
        if(tb){
             tb->show();
        }
        else{
             tb = new TaskBar();
             connect(tb , SIGNAL(showBrowserEvent()) , this , SLOT(showBrowser()));
             connect(tb , SIGNAL(showCatchScreenEvent()) , this , SLOT(showCatchScreen()));
             connect(tb , SIGNAL(showStickyNoteEvent()) , this , SLOT(showStickyNote()));
             connect(tb , SIGNAL(showCatchColorEvent()) , this , SLOT(showCatchColor()));
             connect(tb , SIGNAL(showTaskMgrEvent()) , this , SLOT(showTaskMgr()));
             connect(tb , SIGNAL(showMainToolEvent()) , this , SLOT(showMainTool()));
             connect(tb , SIGNAL(showTimeReminderEvent()) , this , SLOT(showTimeReminder()));
             connect(tb , SIGNAL(showHotkeyManageEvent()) , this , SLOT(showHotkeyManage()));
             connect(tb , SIGNAL(showStockEvent()) , this , SLOT(showStock()));
             connect(tb , SIGNAL(showHardWareEvent()) , this , SLOT(showHardWare()));
             connect(tb , SIGNAL(activatedTranslatorEvent()) , this , SLOT(activatedTranslator()));
             connect(tb , SIGNAL(activatedSearchEvent()) , this , SLOT(activatedSearch()));
             connect(tb , SIGNAL(showCustomEvent()) , this , SLOT(showCustom()));

             tb->show();
        }
    }

    //安装键盘钩子监听空格键，用于QuickLook
    g_hHook = SetWindowsHookExA(WH_KEYBOARD_LL, MainWindow::KeyboardProc, GetModuleHandle(NULL), NULL);
    //设置右键菜单.
   // m_trayIcon->setContextMenu(m_menu);
    windowX = Config().Get("Main" , "WindowX" ).toInt();
    windowY = Config().Get("Main" , "WindowY" ).toInt();
    if(windowX != 0 && windowY != 0){
        this->setGeometry(windowX , windowY , this->width() , this->height());
    }

    //定时提醒在后台运行
    trd = new TimeReminder(m_trayIcon , this);
    qs = new QuickStock( m_trayIcon , this);
    piw = new PCInfoWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete snap;
    snap = NULL;
    delete tm;
    tm = NULL;
    delete mt;
    trd = NULL;
    delete trd;
    mt = NULL;
    delete hm;
    hm = NULL;
    delete cw;
    cw = NULL;
    delete piw;
    piw = NULL;
    delete qs;
    qs = NULL;
    delete tb;
    tb = NULL;
    UnhookWindowsHookEx(g_hHook);//卸载键盘钩子
    Config().Set("Main" , "WindowX" , this->x());
    Config().Set("Main" , "WindowY" , this->y());
}

void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
       case QEvent::FontChange:
          break;
       case QEvent::LanguageChange:
          ui->retranslateUi(this);
          break;
       default:
          break;
    }
}

//窗口刷新
void MainWindow::paintEvent(QPaintEvent *event){
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::Antialiasing);  // 反锯齿
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);
}

//定时器
void MainWindow::timerEvent(QTimerEvent *e){
    //开多个线程获得数据
    if(e->timerId() == m_nTimerIDHook){
        if(getType){
            int type = getType();
            if(type == 1){
                if(getSelect){
                    getSelect(wstr);
                    qDebug()<<wstr<<endl;
                    qstr = QString::fromWCharArray(wstr);
                    qDebug()<<qstr<<endl;
                }
            }
            else if(type == 2){
                if(getSelect){
                    getSelect(wstr);
                    qDebug()<<wstr<<endl;
                    qstr = qstr = QString::fromWCharArray(wstr);
                    qDebug()<<qstr<<endl;
                }
            }
            if(qstr != "NULL"){
                lastPath = qstr;
            }
        }

    }
    else if(e->timerId() == m_nTimerIDInfo){
        if(isShowMainWindowFullScreen){
            this->window()->setVisible(true);
        }
        else{
            if(isForegroundFullscreen()){
                this->window()->setVisible(false);
            }
            else{
                this->window()->setVisible(true);
            }
        }

        gnit->start();
        cpuPercent = SystemInfoWin::GetCpuUsage();
        SystemInfoWin::GetMemoryInfo(mi);
        memoryPercent = mi.memoryPrecent;
        int rtn = GetIfTable(m_pIfTable, &dwSize, FALSE);
        m_in_bytes = 0;
        m_out_bytes = 0;
        if(acSelectAll->isChecked() || acSelectAuto->isChecked())//选择全部的时候
        {
            for(int i = 0 ; i < acConnection.size() ; i++){
                m_in_bytes += m_pIfTable->table[adapters[i].index].dwInOctets;
                m_out_bytes += m_pIfTable->table[adapters[i].index].dwOutOctets;
            }
        }
        else{
            m_in_bytes = m_pIfTable->table[adapters[ac_connection_selected].index].dwInOctets;
            m_out_bytes = m_pIfTable->table[adapters[ac_connection_selected].index].dwOutOctets;
            //netUploadex = m_pIfTable->table[adapters[ac_connection_selected].index].dwInOctets - m_last_in_bytes;
            //netDownloadex = m_pIfTable->table[adapters[ac_connection_selected].index].dwOutOctets - m_last_out_bytes;
        }
        if((m_in_bytes == 0 && m_out_bytes == 0) || (m_last_in_bytes == 0 && m_last_out_bytes == 0))
        {
            netUploadex = 0;
            netDownloadex = 0;
        }
        else{
            if(monitorInterval != 0){
                netDownloadex = static_cast<unsigned int>(m_in_bytes - m_last_in_bytes)/monitorInterval;
                netUploadex = static_cast<unsigned int>(m_out_bytes - m_last_out_bytes)/monitorInterval;
            }
        }
        m_last_in_bytes = m_in_bytes;
        m_last_out_bytes = m_out_bytes;
        if (netUploadex > 1073741824)
                    netUploadex = 0;
        if (netDownloadex > 1073741824)
                    netDownloadex = 0;

        netUpload = netUploadex;
        netDownload = netDownloadex;

        if(netUploadex >= 1024*1024){
            g_strUploadSpeed = (QString::number(netUpload/1024/1024 , 'f' , 2) + " MB/s");
        }
        else{
            g_strUploadSpeed = (QString::number(netUpload/1024 , 'f' , 2) + " KB/s");
        }
        if(netDownloadex >= 1024*1024){
            g_strDownloadSpeed = (QString::number(netDownload/1024/1024 , 'f' , 2) + " MB/s");
        }
        else{
            g_strDownloadSpeed = (QString::number(netDownload/1024 , 'f' , 2) + " KB/s");
        }
        g_strCPUUtil = QString::number(cpuPercent) + " %";
        g_strMemoryUtil = QString::number(memoryPercent) + " %";

        /*
        ui->cpu->setText(QString::number(cpuPercent) + "%");
        ui->memory->setText(QString::number(memoryPercent) + "%");
        if(netUpload >= 1024*1024){
            ui->netUpload->setText(QString::number(netUpload/1024/1024 , 'f' , 2) + " MB/s");
        }
        else{
            ui->netUpload->setText(QString::number(netUpload/1024 , 'f' , 2) + " KB/s");
        }
        if(netDownload >= 1024*1024){
            ui->netDownload->setText(QString::number(netDownload/1024/1024 , 'f' , 2) + " MB/s");
        }
        else{
            ui->netDownload->setText(QString::number(netDownload/1024 , 'f' , 2) + " KB/s");
        }*/

        if(mainQueue.empty()){
            if(getNofX(mainShowInfo , 1))
            {
                if(g_strUploadSpeed != ""){
                    mainQueue.push("↑: " + g_strUploadSpeed);
                }
            }
            if(getNofX(mainShowInfo , 2))
            {
                if(g_strDownloadSpeed != ""){
                    mainQueue.push("↓: " + g_strDownloadSpeed);
                }
            }
            if(getNofX(mainShowInfo , 3))
            {
                if(g_strCPUUtil != ""){
                    mainQueue.push("CPU: " + g_strCPUUtil);
                }
            }
            if(getNofX(mainShowInfo , 4))
            {
                if(g_strMemoryUtil != ""){
                    mainQueue.push("RAM: " + g_strMemoryUtil);
                }
            }
            if(getNofX(mainShowInfo , 5))
            {
                if(g_strMainboardTemp != ""){
                    mainQueue.push("MB: " + g_strMainboardTemp);
                }
            }
            if(getNofX(mainShowInfo , 6))
            {
                if(g_strMainboardFan != ""){
                    mainQueue.push("MB: " + g_strMainboardFan);
                }
            }
            if(getNofX(mainShowInfo , 7))
            {
                if(g_strCPUTemp != ""){
                    mainQueue.push("CPU: " + g_strCPUTemp);
                }
            }
            if(getNofX(mainShowInfo , 8))
            {
                if(g_strGPUTemp != ""){
                    mainQueue.push("GPU: " + g_strGPUTemp);
                }
            }
            if(getNofX(mainShowInfo , 9))
            {
                if(g_strCPUPower != ""){
                    mainQueue.push("CPU: " + g_strCPUPower);
                }
            }
            if(getNofX(mainShowInfo , 10))
            {
                if(g_strGPUPower != ""){
                    mainQueue.push("GPU: " + g_strGPUPower);
                }
            }
            if(getNofX(mainShowInfo , 11))
            {
                if(g_strGPUUtil != ""){
                    mainQueue.push("GPU: " + g_strGPUUtil);
                }
            }
            if(getNofX(mainShowInfo , 12))
            {
                if(g_strDiskTemp != ""){
                    mainQueue.push("Disk: " + g_strDiskTemp);
                }
            }
        }

        if(mainQueue.size() >= 4){
            this->ui->labelFirst->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelSecond->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelThird->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelFourth->setText(mainQueue.front());
            mainQueue.pop();
            if(tb){
                tb->changeLabel();
            }
        }
        else if(mainQueue.size() == 3){
            this->ui->labelFirst->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelSecond->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelThird->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelFourth->setText("");
            if(tb){
                tb->changeLabel();
            }
        }
        else if(mainQueue.size() == 2){
            this->ui->labelFirst->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelSecond->setText(mainQueue.front());
            mainQueue.pop();
            this->ui->labelThird->setText("");
            this->ui->labelFourth->setText("");
            if(tb){
                tb->changeLabel();
            }
        }
        else if(mainQueue.size() == 1){
            this->ui->labelFirst->setText(mainQueue.front());
            this->ui->labelSecond->setText("");
            this->ui->labelThird->setText("");
            this->ui->labelFourth->setText("");
            mainQueue.pop();
            if(tb){
                tb->changeLabel();
            }
        }

        ui->labelFirst->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainColor).arg(mainColorBK));
        ui->labelSecond->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainColor).arg(mainColorBK));
        ui->labelThird->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainColor).arg(mainColorBK));
        ui->labelFourth->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainColor).arg(mainColorBK));
        ui->centralWidget->setStyleSheet(tr("color: rgb(%1) ; background-color: rgb(%2)").arg(mainColor).arg(mainColorBK));
        repaint();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    if (y() <= desktopRect.y())
        {
            m_eEdgeStatus = EG_TOP;
            qDebug()<<"EG_TOP";
        }
        else if (desktopRect.x() + desktopRect.width() <= (this->x() + width()))
        {
            m_eEdgeStatus = EG_RIGHT;
            qDebug()<<"EG_RIGHT";
        }
        else if (this->x() <= desktopRect.x())
        {
            m_eEdgeStatus = EG_LEFT;
            qDebug()<<"EG_LEFT";
        }
        else
        {
            m_eEdgeStatus = EG_NORMAL;
        }
    QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(!configLockWindow)
    {
        if(bPressFlag)
        {
          QPoint relaPos(QCursor::pos() - beginDrag);
        //设置窗口仅可以在用户界面上
          if(relaPos.y() + windowHeight > desktopRect.y() + desktopRect.height()){
             relaPos.setY(desktopRect.y() + desktopRect.height() - windowHeight);
          }
          if(relaPos.x() + windowWidth > desktopRect.x() + desktopRect.width()){
             relaPos.setX(desktopRect.x() + desktopRect.width() - windowWidth);
          }
          if(relaPos.y() < desktopRect.y() ){
              relaPos.setY(desktopRect.y());
           }
           if(relaPos.x() < desktopRect.x() ){
             relaPos.setX(desktopRect.x());
          }
            move(relaPos);
          }
            QWidget::mouseMoveEvent(event);
    }
}

void MainWindow::moveEvent(QMoveEvent *event)
{

}

//窗口的进入事件(enterEvent)
void MainWindow::enterEvent(QEvent *event)
{
    if( configKeepSide ){
    switch (m_eEdgeStatus)
    {
    case EG_TOP:
        setGeometry(pos().x(), desktopRect.top(), width(), height());
        break;
    case EG_LEFT:
        setGeometry(desktopRect.left() , y(), width(), height());
        break;
    case EG_RIGHT:
        setGeometry(desktopRect.x() + desktopRect.width() - width()-10 , y(), width(), height());
        break;
    }
    return QWidget::enterEvent(event);
    }
}

//窗口的离开事件（leaveEvent）
void MainWindow::leaveEvent(QEvent *event)
{
    if( configKeepSide ){
    switch (m_eEdgeStatus)
    {
    case EG_TOP:
        setGeometry(pos().x(), -height() + desktopRect.top() +4, width(), height());
        break;
    case EG_LEFT:
        setGeometry(-width() + desktopRect.left() +4, pos().y(), width(), height());
        break;
    case EG_RIGHT:
        setGeometry(desktopRect.x() + desktopRect.width() -20, pos().y(), width(), height());
        break;
    }
    return QWidget::leaveEvent(event);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    if((desktopRect.height() - cursor().pos().y() < menu->height()) &&
            (desktopRect.width() - cursor().pos().x() > menu->width())){
        menu->move(cursor().pos().x() , cursor().pos().y() - menu->height());
    }
    else if((desktopRect.height() - cursor().pos().y() > menu->height()) &&
            (desktopRect.width() - cursor().pos().x() < menu->width())){
        menu->move(cursor().pos().x() - menu->width() , cursor().pos().y());
    }
    else if((desktopRect.height() - cursor().pos().y() < menu->height()) &&
            (desktopRect.width() - cursor().pos().x() < menu->width())){
        menu->move(cursor().pos().x() - menu->width() , cursor().pos().y() - menu->height());
    }
    else{
        menu->move(cursor().pos());
    }
    menu->show();
}

void MainWindow::closeEvent(QCloseEvent *event){
    killTimer(m_nTimerIDHook);
    killTimer(m_nTimerIDInfo);
   if(tb != NULL){
       tb->close();
   }
}


void MainWindow::setNetCard(){

}

//显示连接详情
void MainWindow::showTrafficStat(){
    NetworkInfo *ni = new NetworkInfo(adapters , m_pIfTable->table , ac_connection_selected ,startTime , this);
    ni->showNormal();
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect m_screenRect = screen->availableVirtualGeometry();
    if(ni->y() <= m_screenRect.y()){
        ni->move( ni->x() , m_screenRect.y());
    }
}

void MainWindow::showMainWindow(){
     if(configShowMainWindow){
          configShowMainWindow = false;
          Config().Set("Main" , "showMainWindow" , "0");
     }
     else{
         configShowMainWindow = true;
         Config().Set("Main" , "showMainWindow" , "1");
     }
}

void MainWindow::setAlwaysTop(){
    if(configAlwaysTop){
        configAlwaysTop = false;
        Config().Set("Main" , "alwaysTop" , "0");
        setWindowFlags(Qt::FramelessWindowHint | Qt::Tool );
        ::SetWindowPos((HWND)this->winId(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        show();
    }
    else{
        configAlwaysTop = true;
        Config().Set("Main" , "alwaysTop" , "1");
        setWindowFlags(Qt::FramelessWindowHint | Qt::Tool );
        ::SetWindowPos((HWND)this->winId(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        //setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
        show();
    }
}

//设置靠边隐藏
void MainWindow::setKeepSide(){
    if(configKeepSide){
        configKeepSide = false;
        Config().Set("Main" , "keepSide" , "0");
        switch (m_eEdgeStatus)
        {
        case EG_TOP:
            setGeometry(pos().x(), desktopRect.top(), width(), height());
            break;
        case EG_LEFT:
            setGeometry(desktopRect.left() , y(), width(), height());
            break;
        case EG_RIGHT:
            setGeometry(desktopRect.x() + desktopRect.width() - width() , y(), width(), height());
            break;
        }
    }
    else{
        configKeepSide = true;
        Config().Set("Main" , "keepSide" , "1");
        switch (m_eEdgeStatus)
        {
        case EG_TOP:
            setGeometry(pos().x(), -height() + desktopRect.top() +4, width(), height());
            break;
        case EG_LEFT:
            setGeometry(-width() + desktopRect.left() +4, pos().y(), width(), height());
            break;
        case EG_RIGHT:
            setGeometry(desktopRect.x() + desktopRect.width() -4, pos().y(), width(), height());
            break;
        }
    }
}

void MainWindow::setLockWindow(){
    if(configLockWindow){
        configLockWindow = false;
        Config().Set("Main" , "lockWindow" , "0");
    }
    else{
        configLockWindow = true;
        Config().Set("Main" , "lockWindow" , "1");
    }
}

void MainWindow::showOnTaskBar(){
    if(configShowOnTaskBar){//不在任务栏显示
        configShowOnTaskBar = false;
        Config().Set("Main" , "showOnTaskBar" , "0");
        if(tb){
            tb->close();
            tb = NULL;
        }
    }
    else{//任务栏显示
        configShowOnTaskBar = true;
        Config().Set("Main" , "showOnTaskBar" , "1");
        if(tb){
          tb->show();
        }
        else{
          tb = new TaskBar();
          connect(tb , SIGNAL(showBrowserEvent()) , this , SLOT(showBrowser()));
          connect(tb , SIGNAL(showCatchScreenEvent()) , this , SLOT(showCatchScreen()));
          connect(tb , SIGNAL(showStickyNoteEvent()) , this , SLOT(showStickyNote()));
          connect(tb , SIGNAL(showCatchColorEvent()) , this , SLOT(showCatchColor()));
          connect(tb , SIGNAL(showTaskMgrEvent()) , this , SLOT(showTaskMgr()));
          connect(tb , SIGNAL(showMainToolEvent()) , this , SLOT(showMainTool()));
          connect(tb , SIGNAL(showTimeReminderEvent()) , this , SLOT(showTimeReminder()));
          connect(tb , SIGNAL(showHotkeyManageEvent()) , this , SLOT(showHotkeyManage()));
          connect(tb , SIGNAL(showStockEvent()) , this , SLOT(showStock()));
          connect(tb , SIGNAL(showHardWareEvent()) , this , SLOT(showHardWare()));
          connect(tb , SIGNAL(activatedTranslatorEvent()) , this , SLOT(activatedTranslator()));
          connect(tb , SIGNAL(activatedSearchEvent()) , this , SLOT(activatedSearch()));
          connect(tb , SIGNAL(showCustomEvent()) , this , SLOT(showCustom()));
          tb->show();
        }
    }
}

void MainWindow::setOpacity(){

}

void MainWindow::showOtherSetting(){
    if(st == NULL){
        st = new Setting(this);
        st->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(st->y() <= m_screenRect.y()){
            st->move( st->x() , m_screenRect.y());
        }
    }
    else{
        st->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(st->y() <= m_screenRect.y()){
            st->move( st->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showCatchScreen(){//截图
    /*if(snap == NULL)
    {
        snap = new snappit(this);
        snap->show();
    }
    else{
        snap->show();
    }*/
    if(sc == NULL)
    {
        delete sc;
        sc = NULL;
        sc = new Screen(this);
        sc->show();
    }
    else{
        delete sc;
        sc = NULL;
        sc = new Screen(this);
        sc->show();
    }
}

void MainWindow::showStickyNote(){//便利贴
        snWidget = new QWidget;
        snWidget->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
        snWidget->setMinimumSize(280, 45);
        snWidget->setMaximumSize(800 , 800);
        snWidget->resize(425, 425);
        //设置窗口背景颜色
        QPalette palWidget = snWidget->palette();
        palWidget.setBrush(QPalette::Background, QColor(240 , 248 , 255));
        snWidget->setPalette(palWidget);

        StickyNote *sn = new StickyNote(snWidget);
        sn->setWidget(snWidget);
        snWidget->showNormal();
}

void MainWindow::showCatchColor(){//颜色拾取
    if(cw == NULL){
        cw = ColorWidget::Instance(this);
        cw->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(cw->y() <= m_screenRect.y()){
            cw->move( cw->x() , m_screenRect.y());
        }
    }
    else{
        cw->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(cw->y() <= m_screenRect.y()){
            cw->move( cw->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showSniffer(){//抓包

}

void MainWindow::showTaskMgr(){//任务管理器
    if(tm == NULL){
        tm = new TaskMgr(this);
        tm->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(tm->y() <= m_screenRect.y()){
            tm->move( tm->x() , m_screenRect.y());
        }
    }
    else{
        tm->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(tm->y() <= m_screenRect.y()){
            tm->move( tm->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showMainTool(){//实用工具
    if(mt == NULL){
        mt = new MainTool(this);
        mt->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(mt->y() <= m_screenRect.y()){
            mt->move( mt->x() , m_screenRect.y());
        }
    }
    else{
        mt->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(mt->y() <= m_screenRect.y()){
            mt->move( mt->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showTimeReminder(){//定时提醒
    if(trd == NULL){
        trd = new TimeReminder(m_trayIcon , this);
        trd->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(trd->y() <= m_screenRect.y()){
            trd->move( trd->x() , m_screenRect.y());
        }
    }
    else{
        trd->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(trd->y() <= m_screenRect.y()){
            trd->move( trd->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showHotkeyManage(){//热键管理
    if(hm == NULL){
        hm = new HotkeyManage(this);
        hm->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(hm->y() <= m_screenRect.y()){
            hm->move( hm->x() , m_screenRect.y());
        }
    }
    else{
        hm->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(hm->y() <= m_screenRect.y()){
            hm->move( hm->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showHardWare(){//显示硬件信息
    if(piw == NULL){
        piw = new PCInfoWindow(this);
        piw->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(piw->y() <= m_screenRect.y()){
            piw->move( piw->x() , m_screenRect.y());
        }
    }
    else{
        piw->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(piw->y() <= m_screenRect.y()){
            piw->move( piw->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showStock(){//显示自选股
    if(qs == NULL){
        qs = new QuickStock( m_trayIcon , this);
        qs->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(qs->y() <= m_screenRect.y()){
            qs->move( qs->x() , m_screenRect.y());
        }
    }
    else{
        qs->showNormal();
        QScreen *screen = QGuiApplication::primaryScreen ();
        QRect m_screenRect = screen->availableVirtualGeometry();
        if(qs->y() <= m_screenRect.y()){
            qs->move( qs->x() , m_screenRect.y());
        }
    }
}

void MainWindow::showHelp(){
    HelpDlg *hd = new HelpDlg(this);
    hd->showNormal();
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect m_screenRect = screen->availableVirtualGeometry();
    if(hd->y() <= m_screenRect.y()){
        hd->move( hd->x() , m_screenRect.y());
    }
}

void MainWindow::quitExe(){
    if(tb != NULL){
        tb->close();
        delete tb;
        tb = NULL;
    }
    if(st != NULL){
        st->close();
        delete st;
        st = NULL;
    }
    if(pcs != NULL){
        pcs->close();
        delete pcs;
        pcs = NULL;
    }
    if(tld != NULL){
        tld->close();
        delete tld;
        tld = NULL;
    }
    if(tm != NULL){
        tm->close();
        delete tm;
        tm = NULL;
    }
    if(cw != NULL){
        cw->close();
        delete cw;
        cw = NULL;
    }
    if(piw != NULL){
        piw->close();
        delete piw;
        piw = NULL;
    }
    if(snWidget != NULL){
        snWidget->close();
        delete snWidget;
        snWidget = NULL;
    }
    if(mt != NULL){
        mt->close();
        delete mt;
        mt = NULL;
    }
    if(trd != NULL){
        trd->close();
        delete trd;
        trd = NULL;
    }
    if(hm != NULL){
        hm->close();
        delete hm;
        hm = NULL;
    }
    if(snap != NULL){
        snap->close();
        delete snap;
        snap = NULL;
    }
    if(sc != NULL){
        sc->close();
        delete sc;
        sc = NULL;
    }
    if(qs != NULL){
        qs->close();
        delete qs;
        qs = NULL;
    }
    QApplication* app;
    app->exit(0);
}

void MainWindow::set100Opacity(){
    configPacity = 100;
    Config().Set("Main" , "pacity" , "100");
    setWindowOpacity(1);
    acSet100Opacity->setChecked(true);
    acSet80Opacity->setChecked(false);
    acSet60Opacity->setChecked(false);
    acSet40Opacity->setChecked(false);
}

void MainWindow::set80Opacity(){
    configPacity = 80;
    Config().Set("Main" , "pacity" , "80");
    setWindowOpacity(0.8);
    acSet100Opacity->setChecked(false);
    acSet80Opacity->setChecked(true);
    acSet60Opacity->setChecked(false);
    acSet40Opacity->setChecked(false);
}

void MainWindow::set60Opacity(){
    configPacity = 60;
    Config().Set("Main" , "pacity" , "60");
    setWindowOpacity(0.6);
    acSet100Opacity->setChecked(false);
    acSet80Opacity->setChecked(false);
    acSet60Opacity->setChecked(true);
    acSet40Opacity->setChecked(false);
}

void MainWindow::set40Opacity(){
    configPacity = 40;
    Config().Set("Main" , "pacity" , "40");
    setWindowOpacity(0.4);
    acSet100Opacity->setChecked(false);
    acSet80Opacity->setChecked(false);
    acSet60Opacity->setChecked(false);
    acSet40Opacity->setChecked(true);
}

void MainWindow::setSelectAdapter(QString str){
    acSelectAll->setChecked(false);
    acSelectAuto->setChecked(false);
    for(int i = 0 ; i < acConnection.size() ; i++)
    {
        if(acConnection[i]->text() == str){
            acConnection[i]->setChecked(true);
            ac_connection_selected = i;
        }
        else{
            acConnection[i]->setChecked(false);
        }
    }
    Config().Set("Main" , "selectedConnection" , str);
}

void MainWindow::setSelectAuto(){
    acSelectAll->setChecked(false);
    acSelectAuto->setChecked(true);
    for(int i = 0 ; i < acConnection.size() ; i++)
    {
        acConnection[i]->setChecked(false);
    }
    Config().Set("Main" , "selectedConnection" , "Auto");
}

void MainWindow::setSelectAll(){
    acSelectAll->setChecked(true);
    acSelectAuto->setChecked(false);
    for(int i = 0 ; i < acConnection.size() ; i++)
    {
        acConnection[i]->setChecked(false);
    }
    Config().Set("Main" , "selectedConnection" , "All");
}

bool MainWindow::isDirExist(QString fullPath)
{
    QDir dir(fullPath);
    QFileInfo dirFile(fullPath + "/config.ini");
    if( dirFile.isFile())
    {
      return true;
    }
    else
    {
       bool ok = dir.mkpath(fullPath);//创建多级目录
       createFile(fullPath , "config.ini" );
       Config().Set("Main" , "showMainWindow" , "1");
       Config().Set("Main" , "alwaysTop" , "1");
       Config().Set("Main" , "keepSide" , "1");
       Config().Set("Main" , "lockWindow" , "0");
       Config().Set("Main" , "showOnTaskBar" , "1");
       Config().Set("Main" , "pacity" , "100");
       Config().Set("Main" , "selectedConnection" , "All");
       configShowMainWindow = 1;
       configAlwaysTop = 1;
       configKeepSide = 1;
       configLockWindow = 0;
       configShowOnTaskBar = 1;
       configPacity = 100;
       return ok;
    }
}

void MainWindow::createFile(QString filePath,QString fileName)
{
    QDir tempDir;
    //临时保存程序当前路径
    QString currentDir = tempDir.currentPath();
    //如果filePath路径不存在，创建它
    if(!tempDir.exists(filePath))
    {
        qDebug()<<QObject::tr("不存在该路径")<<endl;
        tempDir.mkpath(filePath);
    }
    QFile *tempFile = new QFile;
    //将程序的执行路径设置到filePath下
    tempDir.setCurrent(filePath);
    qDebug()<<tempDir.currentPath();
    //检查filePath路径下是否存在文件fileName,如果停止操作。
    if(tempFile->exists(fileName))
    {
        qDebug()<<QObject::tr("文件存在");
        return ;
    }
    //此时，路径下没有fileName文件，使用下面代码在当前路径下创建文件
    tempFile->setFileName(fileName);
    if(!tempFile->open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<QObject::tr("打开失败");
    }
    tempFile->close();
    //将程序当前路径设置为原来的路径
    tempDir.setCurrent(currentDir);
    qDebug()<<tempDir.currentPath();
}

// 激活系统托盘
void MainWindow::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    case QSystemTrayIcon::Context://请求托盘菜单
    {
        m_trayIcon->setContextMenu(menu);
        m_trayIcon->show();
        break;
    }
    default:
        break;
    }
}

QMainWindow* getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
            return mainWin;
    return nullptr;
}

void MainWindow::activatedSearch()
{
    //QMessageBox::information(this,"title","热键已经按下");
    if(pcs == NULL)
    {
        pcs = new PCSearch();
        pcs->setWindowFlag(Qt::SubWindow);
        pcs->show();
        pcs->activateWindow();
        pcs->raise();
    }
    else if(pcs->isVisible() && pcs->isActiveWindow())
    {
        pcs->hide();
    }
    else{
        pcs->show();
        pcs->activateWindow();
        pcs->raise();
    }
}

void MainWindow::activatedTranslator()
{
    if(tld->getOnNotice())
    {
        return;
    }
    if(tld->getTextIsWorking())
    {
        tld->noticeWindow();
        tld->uninstallHook();
    }
    else{
        tld->noticeWindow();
        tld->installHook();
    }
}

bool MainWindow::nativeEventFilter(const QByteArray & eventType, void * message, long * result)
{
    if (eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
    {
        MSG * pMsg = reinterpret_cast<MSG *>(message);

        if (pMsg->message == WM_DWMCOLORIZATIONCOLORCHANGED )//任务栏颜色变化
        {
            if(tb){
                tb->adaptColor();
            }
        }
    }

    return false;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 函数名称：IsForegroundFullscreen
 * 功能说明：判断当前正在与用户交互的当前激活窗口是否是全屏的。
 * 参数说明：无
 * 返回说明：true：是。
             false：否。
 * 线程安全：是
 * 调用样例：IsForegroundFullscreen ()，表示判断当前正在与用户交互的当前激活窗口是否是全屏的。
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool MainWindow::isForegroundFullscreen ()
{
    bool bFullscreen = false;//存放当前激活窗口是否是全屏的，true表示是，false表示不是
    HWND hWnd;
    RECT rcApp;
    RECT rcDesk;

    hWnd = GetForegroundWindow ();//获取当前正在与用户交互的当前激活窗口句柄

    if ((hWnd != GetDesktopWindow ()) && (hWnd != GetShellWindow ()))//如果当前激活窗口不是桌面窗口，也不是控制台窗口
    {
        GetWindowRect (hWnd, &rcApp);//获取当前激活窗口的坐标
        GetWindowRect (GetDesktopWindow(), &rcDesk);//根据桌面窗口句柄，获取整个屏幕的坐标

        if (rcApp.left <= rcDesk.left && //如果当前激活窗口的坐标完全覆盖住桌面窗口，就表示当前激活窗口是全屏的
            rcApp.top <= rcDesk.top &&
            rcApp.right >= rcDesk.right &&
            rcApp.bottom >= rcDesk.bottom)
        {

            char szTemp[100];

            if (::GetClassNameA (hWnd, szTemp, sizeof (szTemp)) > 0)//如果获取当前激活窗口的类名成功
            {
                if (strcmp (szTemp, "WorkerW") != 0)//如果不是桌面窗口的类名，就认为当前激活窗口是全屏窗口
                    bFullscreen = true;
            }
            else bFullscreen = true;//如果获取失败，就认为当前激活窗口是全屏窗口
        }
    }//如果当前激活窗口是桌面窗口，或者是控制台窗口，就直接返回不是全屏

    return bFullscreen;
}

void MainWindow::showBrowser()
{
    QDesktopServices::openUrl(QUrl("www.baidu.com"));
}

void MainWindow::showCustom()
{
    qDebug()<<"showCustom";
    QProcess pro;
    QString strPath = Config().Get("Setting" , "TaskDoubleClickActionPath" ).toString();
    qDebug()<<strPath;
    if(strPath.length() != 0){
        pro.startDetached(strPath);
    }
    else{
        QMessageBox::information(NULL, tr("提示"), tr("无法执行该文件！"));
    }
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(mainDoubleClick == DoubleClickAction::BROWSER){
            this->showBrowser();
        }
        else if(mainDoubleClick == DoubleClickAction::SCREENSHOT){
            this->showCatchScreen();
        }
        else if(mainDoubleClick == DoubleClickAction::STICKYNOTE){
            this->showStickyNote();
        }
        else if(mainDoubleClick == DoubleClickAction::COLORPICKER){
            this->showCatchColor();
        }
        else if(mainDoubleClick == DoubleClickAction::TASKMANAGER){
            this->showTaskMgr();
        }
        else if(mainDoubleClick == DoubleClickAction::MAINTOOL){
            this->showMainTool();
        }
        else if(mainDoubleClick == DoubleClickAction::REMINDER){
            this->showTimeReminder();
        }
        else if(mainDoubleClick == DoubleClickAction::HOTKEYMANAGER){
            this->showHotkeyManage();
        }
        else if(mainDoubleClick == DoubleClickAction::STOCK){
            this->showStock();
        }
        else if(mainDoubleClick == DoubleClickAction::HARDWARE){
            this->showHardWare();
        }
        else if(mainDoubleClick == DoubleClickAction::TRANSLATOR){
            this->activatedTranslator();
        }
        else if(mainDoubleClick == DoubleClickAction::SEARCH){
            this->activatedSearch();
        }
        else if(mainDoubleClick == DoubleClickAction::CUSTOM){
            this->showCustom();
        }
    }
}

bool MainWindow::event(QEvent *event){
    if (event->type() == QEvent::ToolTip) {
        QString toolTip = "";
        if(!g_strUploadSpeed.isEmpty()){
            toolTip = toolTip + "↑: " + g_strUploadSpeed + "\n";
        }
        if(!g_strDownloadSpeed.isEmpty()){
            toolTip = toolTip + "↓: " + g_strDownloadSpeed + "\n";
        }
        if(!g_strCPUUtil.isEmpty()){
            toolTip = toolTip + "CPU: " + g_strCPUUtil + "\n";
        }
        if(!g_strMemoryUtil.isEmpty()){
            toolTip = toolTip + "RAM: " + g_strMemoryUtil + "\n";
        }
        if(!g_strMainboardTemp.isEmpty()){
            toolTip = toolTip + "MB: " + g_strMainboardTemp + "\n";
        }
        if(!g_strMainboardFan.isEmpty()){
            toolTip = toolTip + "MB: " + g_strMainboardFan + "\n";
        }
        if(!g_strCPUTemp.isEmpty()){
            toolTip = toolTip + "CPU: " + g_strCPUTemp + "\n";
        }
        if(!g_strGPUTemp.isEmpty()){
            toolTip = toolTip + "GPU: " + g_strGPUTemp + "\n";
        }
        if(!g_strCPUPower.isEmpty()){
            toolTip = toolTip + "CPU: " + g_strCPUPower + "\n";
        }
        if(!g_strGPUPower.isEmpty()){
            toolTip = toolTip + "GPU: " + g_strGPUPower + "\n";
        }
        if(!g_strGPUUtil.isEmpty()){
            toolTip = toolTip + "GPU: " + g_strGPUUtil + "\n";
        }
        if(!g_strDiskTemp.isEmpty()){
            toolTip = toolTip + "Disk: " + g_strDiskTemp;
        }
        QToolTip::showText(QCursor::pos() , toolTip);
        return true;
    }
    return QWidget::event(event);
}
