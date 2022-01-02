#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "mainwindow.h"
#include "taskbar.h"
#include <dwmapi.h>
#include "ui_taskbar.h"
#include "systeminfowin.h"
#include <QDebug>

#pragma comment(lib,"dwmapi.lib")

extern QString taskColor;
int taskDoubleClick;
int taskShowInfo;
int taskShowNum;

std::queue<QString> taskQueue;

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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 函数名称：IsForegroundFullscreen
 * 功能说明：判断当前正在与用户交互的当前激活窗口是否是全屏的。
 * 参数说明：无
 * 返回说明：true：是。
             false：否。
 * 线程安全：是
 * 调用样例：IsForegroundFullscreen ()，表示判断当前正在与用户交互的当前激活窗口是否是全屏的。
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

bool TaskBar::isForegroundFullscreen ()
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

QColor DesktopXYColor(int x,int y){
    QDesktopWidget *desk = QApplication::desktop();
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap p = screen->grabWindow(desk->winId());
    QImage image = p.toImage();
    return  image.pixelColor(x,y);
}

QColor GetWindowsThemeColor()
{
    DWORD crColorization;
    BOOL fOpaqueBlend;
    QColor theme_color{};
    HRESULT result = DwmGetColorizationColor(&crColorization, &fOpaqueBlend);
    if (result == S_OK)
    {
        BYTE r, g, b;
        r = (crColorization >> 16) % 256;
        g = (crColorization >> 8) % 256;
        b = crColorization % 256;
        theme_color = RGB(r, g, b);
    }
    return theme_color;
}

TaskBar::TaskBar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TaskBar)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    //设置字体和字体颜色
    QString taskFontFamily = Config().Get("Setting" , "TaskFontFamily").toString();
    int taskFontSize = Config().Get("Setting" , "TaskFontSize").toInt();
    QString taskFontColor = Config().Get("Setting" , "TaskFontColor").toString();
    taskDoubleClick = Config().Get("Setting" , "TaskDoubleClickAction").toInt();
    taskShowInfo = Config().Get("Setting" , "TaskShowInfo").toInt();
    if(taskShowInfo == 0){
        taskShowInfo = 1+2+4+8+16;//默认为前四项显示
    }
    if(taskFontFamily.length() == 0 && taskFontSize == 0){
        taskFontFamily = "Microsoft YaHei";
        taskFontSize = 10;
        Config().Set("Setting" , "taskFontFamily" , taskFontFamily);
        Config().Set("Setting" , "taskFontSize" , taskFontSize);
    }
    if(taskFontColor.length() == 0){
        taskFontColor = "0, 0, 0";
        Config().Set("Setting" , "taskFontColor" , taskFontColor);
    }
    QFont taskFont(taskFontFamily , taskFontSize);

    ui->labelFirst->setFont(taskFont);
    ui->labelSecond->setFont(taskFont);
    ui->labelThird->setFont(taskFont);
    ui->labelFourth->setFont(taskFont);
    ui->labelFirst->setStyleSheet(tr("color: rgb(%1)").arg(taskFontColor));
    ui->labelSecond->setStyleSheet(tr("color: rgb(%1)").arg(taskFontColor));
    ui->labelThird->setStyleSheet(tr("color: rgb(%1)").arg(taskFontColor));
    ui->labelFourth->setStyleSheet(tr("color: rgb(%1)").arg(taskFontColor));

    ui->labelFirst->setText(QString("Loading..."));
    ui->labelSecond->setText(QString("Loading..."));
    ui->labelThird->setText(QString("Loading..."));
    ui->labelFourth->setText(QString("Loading..."));

    m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);		//寻找类名是Shell_TrayWnd的窗口句柄
    m_hBar = ::FindWindowEx(m_hTaskbar, 0, L"ReBarWindow32", NULL);	//寻找二级容器的句柄
    m_hMin = ::FindWindowEx(m_hBar, 0, L"MSTaskSwWClass", NULL);	//寻找最小化窗口的句柄
    m_hTrayNotify = ::FindWindowEx(m_hTaskbar, 0, L"TrayNotifyWnd", NULL);	//寻找右侧任务通知栏窗口的句柄

    ::GetWindowRect(m_hTrayNotify , &m_rcTrayNotify);
    rcTrayNotifyX = m_rcTrayNotify.left;
    rcTrayNotifyY = m_rcTrayNotify.top;

    taskColor = taskFontColor;
    startTimer(1000);
    showInfoNum = 6;

    ::GetWindowRect(m_hMin , &m_rcMinInit);
    adaptRcMin();
    adaptColor();
}

TaskBar::~TaskBar()
{
    delete ui;
}

bool TaskBar::IsTaskBarOnTopOrButtom()
{
    RECT *rect = new RECT();
    RECT *rcMin = new RECT();
    RECT *rcBar = new RECT();
    if (m_hTaskbar != 0)
    {
        ::GetWindowRect(m_hMin, rcMin);	//获得最小化窗口的区域
        ::GetWindowRect(m_hBar, rcBar);	//获得二级容器的区域
        if(m_left_space==0)
            m_left_space = rcMin->left - rcBar->left;
        if(m_top_space==0)
            m_top_space = rcMin->top - rcBar->top;

        ::GetWindowRect(m_hTaskbar, rect);			//获取任务栏的矩形区域
        return (rect->right-rect->left >= rect->bottom - rect->top);		//如果任务栏的宽度大于高度，则任务在屏幕的顶部或底部
    }
    else
    {
        return true;
    }
}

void TaskBar::timerEvent(QTimerEvent *event){
    //保证gnit在running
    adaptColor();
    m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);		//寻找类名是Shell_TrayWnd的窗口句柄
    m_hTrayNotify = ::FindWindowEx(m_hTaskbar, 0, L"TrayNotifyWnd", NULL);	//寻找右侧任务通知栏窗口的句柄
    ::GetWindowRect(m_hTrayNotify , &m_rcTrayNotify);
    if(m_rcTrayNotify.left != rcTrayNotifyX || m_rcTrayNotify.top != rcTrayNotifyY){
        m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);		//寻找类名是Shell_TrayWnd的窗口句柄
        m_hBar = ::FindWindowEx(m_hTaskbar, 0, L"ReBarWindow32", NULL);	//寻找二级容器的句柄
        m_hMin = ::FindWindowEx(m_hBar, 0, L"MSTaskSwWClass", NULL);	//寻找最小化窗口的句柄
        ::GetWindowRect(m_hMin , &m_rcMinInit);
        adaptRcMin();
    }
}

void TaskBar::closeEvent(QCloseEvent *event){
    //程序关闭的时候，把最小化窗口的width恢复回去
    if (IsTaskBarOnTopOrButtom())
    {
        ::MoveWindow(m_hMin, 0 , 0, rcMinWidth  , rcMinHeight , TRUE);
    }
    else{
        ::MoveWindow(m_hMin, 0 , 0, rcMinWidth  , rcMinHeight , TRUE);
        qDebug()<<rcMinWidth<< " "<<rcMinHeight;
    }
}

void TaskBar::adaptColor(){
    //全屏状态不修改任务栏
    //获得任务栏的位置
    if(isForegroundFullscreen ()){
        return;
    }
    ::GetWindowRect(m_hTaskbar , &m_rcTaskBar);
    QColor colorTaskBar = DesktopXYColor(m_rcTaskBar.left + 1 , m_rcTaskBar.top + 1);//任务栏颜色
    //得到Windows主题的颜色（暂未使用，仅支持Win8+）
    //QColor bkColor = GetWindowsThemeColor();
    //设置背景颜色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Window, colorTaskBar);
    this->setPalette(palette);

    QPalette paletteTaskBar;
    paletteTaskBar.setColor(QPalette::WindowText , QColor(255 - colorTaskBar.red() , 255 - colorTaskBar.green() , 255 - colorTaskBar.blue() , 255 ));
    //修改任务栏背景颜色
    ui->labelFirst->setPalette(paletteTaskBar);
    ui->labelSecond->setPalette(paletteTaskBar);
    ui->labelThird->setPalette(paletteTaskBar);
    ui->labelFourth->setPalette(paletteTaskBar);

    //修改任务栏文字颜色
    ui->labelFirst->setStyleSheet(tr("color: rgb(%1)").arg(taskColor));
    ui->labelSecond->setStyleSheet(tr("color: rgb(%1)").arg(taskColor));
    ui->labelThird->setStyleSheet(tr("color: rgb(%1)").arg(taskColor));
    ui->labelFourth->setStyleSheet(tr("color: rgb(%1)").arg(taskColor));
    repaint();
}

void TaskBar::adaptRcMin()
{
    m_hTaskbar = ::FindWindow(L"Shell_TrayWnd", NULL);		//寻找类名是Shell_TrayWnd的窗口句柄
    m_hBar = ::FindWindowEx(m_hTaskbar, 0, L"ReBarWindow32", NULL);	//寻找二级容器的句柄
    m_hMin = ::FindWindowEx(m_hBar, 0, L"MSTaskSwWClass", NULL);	//寻找最小化窗口的句柄
    m_hTrayNotify = ::FindWindowEx(m_hTaskbar, 0, L"TrayNotifyWnd", NULL);	//寻找右侧任务通知栏窗口的句柄
    ::GetWindowRect(m_hTrayNotify , &m_rcTrayNotify);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint |Qt::WindowMinimizeButtonHint);//去掉标题栏
    //this->setWindowOpacity(1.0);//设置窗体不透明度
    SetWindowPos((HWND)this->winId(),HWND_TOPMOST,this->pos().x(),this->pos().y(),this->width(),this->height(),SWP_SHOWWINDOW);
    //计算应该显示的高度和宽度
    ::GetWindowRect(m_hMin , &m_rcMin);
    rcMinWidth = m_rcMin.right - m_rcMin.left;
    rcMinInitWidth = m_rcMinInit.right - m_rcMinInit.left;
    rcMinInitHeight = m_rcMinInit.bottom = m_rcMinInit.top;
    rcMinHeight = m_rcMin.bottom - m_rcMin.top;
    rcMinX = m_rcMin.left;
    rcMinY = m_rcMin.top;
    rcTrayNotifyX = m_rcTrayNotify.left;
    rcTrayNotifyY = m_rcTrayNotify.top;
    //::GetWindowRect(m_hBar , m_rcBar);
    //考虑任务栏在桌面其他位置

    if(IsTaskBarOnTopOrButtom()){//水平方向任务栏

        //taskBarWidth = showInfoNum / 2 * 50;
        taskBarWidth = 200;
        taskBarHeight = m_rcMin.bottom - m_rcMin.top;
        ::SetParent((HWND)(this->winId()) , m_hBar);//把程序窗口设置成任务栏的子窗口用于永久置顶在任务栏
        this->setGeometry( rcMinInitWidth - taskBarWidth , 0 , taskBarWidth , taskBarHeight );
        ::MoveWindow(m_hMin , 0 , 0 , rcMinInitWidth - taskBarWidth , rcMinHeight , true);//设置任务栏左侧宽度
        qDebug()<<"rcMin"<<rcMinWidth<<" "<<taskBarWidth<<" "<<m_rcMin.left;

        //考虑到小任务栏的情况
        ui->labelFirst->setGeometry(taskBarWidth/2,0,taskBarWidth/2 , taskBarHeight/2);
        ui->labelSecond->setGeometry(taskBarWidth/2,taskBarHeight/2,taskBarWidth/2 , taskBarHeight/2);
        ui->labelThird->setGeometry(0,0,taskBarWidth/2 , taskBarHeight/2);
        ui->labelFourth->setGeometry(0,taskBarHeight/2,taskBarWidth/2 , taskBarHeight/2);
    }
    else{//垂直方向任务栏
        taskBarWidth = m_rcBar.right - m_rcBar.left;
        taskBarHeight = 100;
        this->setFixedHeight(taskBarHeight);
        ::SetParent((HWND)(this->winId()) , m_hBar);//把程序窗口设置成任务栏的子窗口用于永久置顶在任务栏
        this->setGeometry( 0 , rcMinHeight - taskBarHeight , taskBarWidth , taskBarHeight );
        ::MoveWindow(m_hMin , 0 , 0 , rcMinWidth , rcMinHeight - taskBarHeight , true);//设置任务栏顶部高度

        //考虑到小任务栏的情况
        ui->labelFirst->setGeometry(0,taskBarHeight/4*0 , 100,taskBarHeight/4);
        ui->labelSecond->setGeometry(0,taskBarHeight/4*1 , 100,taskBarHeight/4);
        ui->labelThird->setGeometry(0,taskBarHeight/4*2 , 100,taskBarHeight/4);
        ui->labelFourth->setGeometry(0,taskBarHeight/4*3 , 100,taskBarHeight/4);
        ui->labelFirst->setAlignment(Qt::AlignLeft);
        ui->labelSecond->setAlignment(Qt::AlignLeft);
        ui->labelThird->setAlignment(Qt::AlignLeft);
        ui->labelFourth->setAlignment(Qt::AlignLeft);
    }
}

void TaskBar::changeLabel(int cpuPercent , int memoryPercent , double netUploadex , double netDownloadex){//修改任务栏数据
    ui->labelFirst->setText(QString(tr("CPU: ")) + QString::number(cpuPercent) + "%");
    ui->labelSecond->setText(QString(tr("内存: ")) + QString::number(memoryPercent) + "%");
    if(netUploadex/1024 >= 1024){
        ui->labelThird->setText(QString("↑ ") + QString::number(netUploadex/1024/1024 , 'f' , 2) + " MB/s");
    }
    else{
        ui->labelThird->setText(QString("↑ ") + QString::number(netUploadex/1024 , 'f' , 2) + " KB/s");
    }
    if(netDownloadex/1024 >= 1024){
        ui->labelFourth->setText(QString("↓ ") + QString::number(netDownloadex/1024/1024 , 'f' , 2) + " MB/s");
    }
    else{
        ui->labelFourth->setText(QString("↓ ") + QString::number(netDownloadex/1024 , 'f' , 2) + " KB/s");
    }
}

void TaskBar::changeLabel(QString labelFirst , QString labelSecond , QString labelThird , QString labelFourth){//修改任务栏数据
    ui->labelFirst->setText(labelFirst);
    ui->labelSecond->setText(labelSecond);
    ui->labelThird->setText(labelThird);
    ui->labelFourth->setText(labelFourth);
}

void TaskBar::changeLabel(){
    if(taskQueue.empty()){
        if(getNofX(taskShowInfo , 1))
        {
            if(g_strUploadSpeed != ""){
                taskQueue.push("↑: " + g_strUploadSpeed);
            }
        }
        if(getNofX(taskShowInfo , 2))
        {
            if(g_strDownloadSpeed != ""){
                taskQueue.push("↓: " + g_strDownloadSpeed);
            }
        }
        if(getNofX(taskShowInfo , 3))
        {
            if(g_strCPUUtil != ""){
                taskQueue.push("CPU: " + g_strCPUUtil);
            }
        }
        if(getNofX(taskShowInfo , 4))
        {
            if(g_strMemoryUtil != ""){
                taskQueue.push("RAM: " + g_strMemoryUtil);
            }
        }
        if(getNofX(taskShowInfo , 5))
        {
            if(g_strMainboardTemp != ""){
                taskQueue.push("MB: " + g_strMainboardTemp);
            }
        }
        if(getNofX(taskShowInfo , 6))
        {
            if(g_strMainboardFan != ""){
                taskQueue.push("MB: " + g_strMainboardFan);
            }
        }
        if(getNofX(taskShowInfo , 7))
        {
            if(g_strCPUTemp != ""){
                taskQueue.push("CPU: " + g_strCPUTemp);
            }
        }
        if(getNofX(taskShowInfo , 8))
        {
            if(g_strGPUTemp != ""){
                taskQueue.push("GPU: " + g_strGPUTemp);
            }
        }
        if(getNofX(taskShowInfo , 9))
        {
            if(g_strCPUPower != ""){
                taskQueue.push("CPU: " + g_strCPUPower);
            }
        }
        if(getNofX(taskShowInfo , 10))
        {
            if(g_strGPUPower != ""){
                taskQueue.push("GPU: " + g_strGPUPower);
            }
        }
        if(getNofX(taskShowInfo , 11))
        {
            if(g_strGPUUtil != ""){
                taskQueue.push("GPU: " + g_strGPUUtil);
            }
        }
        if(getNofX(taskShowInfo , 12))
        {
            if(g_strDiskTemp != ""){
                taskQueue.push("Disk: " + g_strDiskTemp);
            }
        }
    }

    if(taskQueue.size() >= 4){
        this->ui->labelFirst->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelSecond->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelThird->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelFourth->setText(taskQueue.front());
        taskQueue.pop();
    }
    else if(taskQueue.size() == 3){
        this->ui->labelFirst->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelSecond->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelThird->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelFourth->setText("");
    }
    else if(taskQueue.size() == 2){
        this->ui->labelFirst->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelSecond->setText(taskQueue.front());
        taskQueue.pop();
        this->ui->labelThird->setText("");
        this->ui->labelFourth->setText("");
    }
    else if(taskQueue.size() == 1){
        this->ui->labelFirst->setText(taskQueue.front());
        this->ui->labelSecond->setText("");
        this->ui->labelThird->setText("");
        this->ui->labelFourth->setText("");
        taskQueue.pop();
    }
    else if(taskQueue.size() == 0){
        this->ui->labelFirst->setText("");
        this->ui->labelSecond->setText("");
        this->ui->labelThird->setText("");
        this->ui->labelFourth->setText("");
    }
}

void TaskBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(taskDoubleClick == DoubleClickAction::BROWSER){
            emit showBrowserEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::SCREENSHOT){
            emit showCatchScreenEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::STICKYNOTE){
            emit showStickyNoteEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::COLORPICKER){
            emit showCatchColorEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::TASKMANAGER){
            emit showTaskMgrEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::MAINTOOL){
            emit showMainToolEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::REMINDER){
            emit showTimeReminderEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::HOTKEYMANAGER){
            emit showHotkeyManageEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::STOCK){
            emit showStockEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::HARDWARE){
            emit showHardWareEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::TRANSLATOR){
            emit activatedTranslatorEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::SEARCH){
            emit activatedSearchEvent();
        }
        else if(taskDoubleClick == DoubleClickAction::CUSTOM){
            emit showCustomEvent();
        }
    }
}

bool TaskBar::event(QEvent *event){
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
