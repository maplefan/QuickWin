#include "CSignal.h"
#include <QDebug>
#include "gethardware.h"

static QString g_hardWareCPUInfo = "";
static QString g_hardWareIOInfo = "";
static QString g_hardWareHDDInfo = "";
static QString g_hardWareNvidiaGPUInfo = "";
static QString g_hardWareAtiGPUInfo = "";

CSignal::CSignal(QObject * parent)
    : QThread(parent)
{
    QLibrary library("./CPPOpenHardWareMonitor.dll");
    if(library.load()){
        getHDDInfo = (getHDDInfoFunc)library.resolve("?getHDDInfo@@YAPADXZ");
        getCPUInfo = (getHDDInfoFunc)library.resolve("?getCPUInfo@@YAPADXZ");
        getIOInfo = (getHDDInfoFunc)library.resolve("?getIOInfo@@YAPADXZ");
        getNvidiaGPUInfo = (getHDDInfoFunc)library.resolve("?getNvidiaGPUInfo@@YAPADXZ");
        getAtiGPUInfo = (getHDDInfoFunc)library.resolve("?getAtiGPUInfo@@YAPADXZ");
    }
    else{
        QMessageBox::about(NULL,  "Tips",  "Can not find CPPOpenHardWareMonitor.dll!");
    }
}

CSignal::~CSignal()
{

}

void CSignal::run()
{
    m_timer = new QTimer();
    m_timerSlot = new CTimerSlot();
    m_timerSlot->OnTimerout();
    connect(m_timer , SIGNAL(timeout()) , m_timerSlot , SLOT(OnTimerout()));
    connect(m_timerSlot , &CTimerSlot::statusChanged , this , &CSignal::statusChanged);
    //qDebug() << "start thread:" <<QThread::currentThreadId();
    m_timer->start(5000);
    exec();
}

CTimerSlot::CTimerSlot(QObject * parent)
{

}

void CTimerSlot::OnTimerout()
{
    //qDebug()<<"CSignal::OnTimerOut(),threadid:"<<QThread::currentThreadId();
    g_hardWareCPUInfo = getCPUInfo();
    g_hardWareHDDInfo = getHDDInfo();
    g_hardWareAtiGPUInfo = getAtiGPUInfo();
    g_hardWareNvidiaGPUInfo = getNvidiaGPUInfo();
    g_hardWareIOInfo = getIOInfo();
    emit statusChanged(g_hardWareCPUInfo , g_hardWareHDDInfo , g_hardWareAtiGPUInfo , g_hardWareNvidiaGPUInfo , g_hardWareIOInfo);
}
