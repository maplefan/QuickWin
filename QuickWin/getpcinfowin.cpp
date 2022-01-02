#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "getpcinfowin.h"
//网页地址
const QString URLSTR = "https://www.maplefan.com/ip";

//获得计算机名称
const QString getLocalMachineName()
{
    QString machineName = QHostInfo::localHostName();
    return machineName;
}

//获得本地IP地址
const QString getLocalIP()
{
    QString ip_address;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  ipAddressesList.at(i).toIPv4Address())
        {
            ip_address = ipAddressesList.at(i).toString();
            qDebug()<<ip_address;  //debug
            //break;
        }
    }
    if (ip_address.isEmpty())
        ip_address = QHostAddress(QHostAddress::LocalHost).toString();
    return ip_address;
}

//获取计算机MAC地址
const QString getMacAddress()
{
    QString strMac;

    QList<QNetworkInterface> netList = QNetworkInterface::allInterfaces();
    foreach(QNetworkInterface item, netList)
    {
        if((QNetworkInterface::IsUp & item.flags()) && (QNetworkInterface::IsRunning & item.flags()))
        {
            if(strMac.isEmpty() || strMac < item.hardwareAddress())
            {
                strMac = item.hardwareAddress();
            }
        }
    }
    return strMac;
}

//获取计算机CPU信息
const QString getCpuType()
{
    QString m_cpuDescribe = "";
    QSettings *CPU = new QSettings("HKEY_LOCAL_MACHINE\\HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",QSettings::NativeFormat);
    m_cpuDescribe = CPU->value("ProcessorNameString").toString();
    delete CPU;

    return m_cpuDescribe;
}

const QString getGraphicsCard()
{
    QString dcard = "";
    QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\nvlddmkm\\Device0",QSettings::NativeFormat);
    QString type = DCard->value("Device Description").toString();
    delete DCard;

    QString dType = type;
    dType.trimmed();
    if(!dType.isEmpty()){
        dcard =  dType;
    }

    else{
        QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\CurrentControlSet\\services\\nvlddmkm\\Video",QSettings::NativeFormat);
        QString type = DCard->value("DeviceDesc").toString();
        delete DCard;
        QStringList list = type.split(";");

        QString dType = list[list.size()-1];
        dType.trimmed();
        if(!dType.isEmpty())
            dcard = dType;
    }

    DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\igfx\\Device0",QSettings::NativeFormat);
    type = DCard->value("Device Description").toString();
    delete DCard;

    dType = type;
    dType.trimmed();
    if(!dType.isEmpty())
    {
        dcard = dcard + "\n" +dType;
    }
    else{
        QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\igfx\\Video",QSettings::NativeFormat);
        QString type = DCard->value("DeviceDesc").toString();
        delete DCard;
        QStringList list = type.split(";");

        QString dType = list[list.size()-1];
        dType.trimmed();
        if(!dType.isEmpty())
            dcard = dcard + "\n" +dType;
    }


    DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\amdkmdap\\Device0",QSettings::NativeFormat);
    type = DCard->value("Device Description").toString();
    delete DCard;

    dType = type;
    dType.trimmed();
    if(!dType.isEmpty())
    {
        dcard = dcard + "\n" +dType;
    }
    else{
        QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\amdkmdap\\Video",QSettings::NativeFormat);
        QString type = DCard->value("DeviceDesc").toString();
        delete DCard;
        QStringList list = type.split(";");

        QString dType = list[list.size()-1];
        dType.trimmed();
        if(!dType.isEmpty())
            dcard = dcard + "\n" +dType;
    }

    if(!dType.isEmpty())
    {
        dcard = dcard + "\n" +dType;
    }
    else{
        QSettings *DCard = new QSettings("HKEY_LOCAL_MACHINE\\SYSTEM\\ControlSet001\\Services\\amdkmdag\\Video",QSettings::NativeFormat);
        QString type = DCard->value("DeviceDesc").toString();
        delete DCard;
        QStringList list = type.split(";");

        QString dType = list[list.size()-1];
        dType.trimmed();
        if(!dType.isEmpty())
            dcard = dcard + "\n" +dType;
    }
    dcard.trimmed();


    return dcard;
}

//获取计算机内存
const QString getMemory()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx(&statex);
    double m_totalMem = statex.ullTotalPhys  * 1.0/ GB;

    QString m_memDescribe = QString(QObject::tr("可用") + "%1 GB / " + QObject::tr("共")  + "%2 GB").
            arg(QString::asprintf("%.2f", m_totalMem)).arg(QString::asprintf("%.2f", double(int(m_totalMem+0.5))));

    return m_memDescribe;
}

//获取计算机操作系统
const QString getOSVersion()
{
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    LPFN_ISWOW64PROCESS fnIsWow64Process;
    BOOL bIsWow64 = FALSE;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress( GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
    if (NULL != fnIsWow64Process)
    {
        fnIsWow64Process(GetCurrentProcess(),&bIsWow64);
    }
    QString sysBit = "unknown";
    if(bIsWow64)
        sysBit = QString(QObject::tr("64位"));
    else
        sysBit = QString(QObject::tr("32位"));

    QString m_osDescirbe = QSysInfo::prettyProductName() + " " + sysBit;
    return m_osDescirbe;
}

//获取计算机屏幕个数以及像素
const QString getScreenInfo()
{

    QString m_screenDescribe = "";
    QList<QSize> screenSizeList;
    QList <int> screenCountList;
    QList<QScreen *> list_screen = QGuiApplication::screens();
    for(int i=0; i< list_screen.size(); i++)
    {
        QRect screenRect = list_screen.at(i)->geometry();
        QSize size(screenRect.width(), screenRect.height());

        bool bExist = false;
        for(int j=0; j<screenSizeList.length(); j++)
        {
            QSize existSize = screenSizeList.at(j);
            if(size == existSize)
            {
                screenCountList[j]++;
                bExist = true;
                break;
            }
        }

        if(!bExist)
        {
            screenSizeList.append(size);
            screenCountList.append(1);
        }
    }

    QSize m_maxScreenSize = screenSizeList.at(0);
    for(int i=0; i<screenSizeList.length(); i++)
    {
        int width = screenSizeList.at(i).width();
        int height = screenSizeList.at(i).height();

        if(width > m_maxScreenSize.width() && height > m_maxScreenSize.height())
            m_maxScreenSize = screenSizeList.at(i);

        m_screenDescribe += QString(QString("(%1") + QObject::tr("像素") +" x %2" + QObject::tr("像素")+ ") x " + "%3" + QObject::tr("个")).arg(width).arg(height).arg(screenCountList.at(i));
        if(i!= screenSizeList.length()-1)
            m_screenDescribe += "、 ";
    }
    return m_screenDescribe;
}

//判断计算机是否可以联网
bool isNetLive()
{
    //能接通百度IP说明可以通外网
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost("202.108.22.5", 80);
    //100毫秒没有连接上则判断不在线
    return tcpClient.waitForConnected(100);
}

//获取网页所有源代码
QString getHtml(QString url)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl(url)));
    QByteArray responseData;
    QEventLoop eventLoop;
    QTimer *timer = new QTimer();
    timer->setSingleShot(true);

    //connect(manager, SIGNAL(finished(QNetworkReply *)), &eventLoop, SLOT(quit()));
    //connect(timer, SIGNAL(timeout()), &eventLoop, SLOT(quit()));

    timer->start(300);
    eventLoop.exec();
    responseData = reply->readAll();

    delete timer;

    return QString(responseData);
}

bool getPublicIP(QString& ip)
{
    QUrl url(URLSTR);
    QNetworkAccessManager manager;
    QEventLoop loop;
    QTextCodec *codec;
    QNetworkReply *reply;
    //5.6以前版本：
    //先用reply->rawHeader("Location")获取跳转的url，然后重新请求此url。注意可能会重定向多次，重复执行前面步骤即可。
    //5.6之后的版本，包括5.6
    //在managerNetwork->get之前，调用req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);让Qt自动为你跳转
    QNetworkRequest request;
    request.setUrl(url);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    qDebug() << "Reading html code form " << URLSTR;
    reply = manager.get(request);
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();
    QString codeContent = reply->readAll();
    //一定要注意编码问题，否则很容易出现乱码的
    codec = QTextCodec::codecForHtml(codeContent.toLatin1());
    codeContent = codec->toUnicode(codeContent.toLatin1());
    ip = codeContent;
    return  true;
}

bool getDiskSpace(QString disk , int &availSpace , int &totalSpace){
    unsigned long long freeBytesToCaller=0,totalBytes=0,freeBytes=0;
    bool b;
    disk = disk + "/";
    b=GetDiskFreeSpaceEx(disk.toStdWString().c_str(),(PULARGE_INTEGER)&freeBytesToCaller,
      (PULARGE_INTEGER)&totalBytes,(PULARGE_INTEGER)&freeBytes);
    availSpace = freeBytesToCaller / 1024 / 1024 / 1024;
    totalSpace = totalBytes / 1024 / 1024 / 1024;
    return b;
}

int getNumberBit(int number){
    int count = 0;
    while(number  != 0){
        number = number / 10;
        count++;
    }
    return count;
}
