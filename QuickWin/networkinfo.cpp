#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "networkinfo.h"
#include "ui_networkinfo.h"
#include "adapterinfo.h"
NetworkInfo::NetworkInfo(std::vector<NetWorkConection> &adapters , MIB_IFROW* pIfRow , int ac_connection_selected ,SYSTEMTIME startTime ,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NetworkInfo)
{
    setWindowTitle(tr("连接详情"));
    startTimer(1000);
    m_startTime = startTime;
    m_pIfRow = pIfRow;
    m_connections = adapters;
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    m_connection_selected = ac_connection_selected;
    int width = this->width();
    int height = this->height();
    ui->tableView->setGeometry(0,0,width , height);
    model = new QStandardItemModel();
    QStringList labels = QObject::tr("项目,值").simplified().split(",");
    model->setColumnCount(2);
    model->setHorizontalHeaderLabels(labels);
    AdapterInfo::RefreshIpAddress(m_connections);
    MIB_IFROW &network_info = m_pIfRow[m_connections[m_connection_selected].index];

    //定义item
    QStandardItem* item = 0;
            item = new QStandardItem(QString(tr("接口名")));
            model->setItem(0,0,item);
            item = new QStandardItem(QString::fromWCharArray(network_info.wszName));
            model->setItem(0,1,item);

            item = new QStandardItem(QString(tr("接口描述")));
            model->setItem(1,0,item);
            item = new QStandardItem(QString((const char*)network_info.bDescr));
            model->setItem(1,1,item);

            item = new QStandardItem(QString(tr("连接类型")));
            model->setItem(2,0,item);
            item = new QStandardItem(getNetworkType(network_info.dwType));
            model->setItem(2,1,item);

            item = new QStandardItem(QString(tr("速度")));
            model->setItem(3,0,item);
            item = new QStandardItem(QString::number(network_info.dwSpeed / 1000000) + "Mbps");
            model->setItem(3,1,item);

            QString MACAdress = "";
            char buff[3];
            for (size_t i{}; i < network_info.dwPhysAddrLen; i++)
            {
                 sprintf_s(buff, "%.2x", network_info.bPhysAddr[i]);
                 MACAdress += buff;
                 if (i != network_info.dwPhysAddrLen - 1)
                    MACAdress += "-";
            }
            item = new QStandardItem(QString(tr("适配器物理地址")));
            model->setItem(4,0,item);
            item = new QStandardItem(QString(MACAdress));
            model->setItem(4,1,item);

            item = new QStandardItem(QString(tr("IP地址")));
            model->setItem(5,0,item);
            item = new QStandardItem(QString::fromStdWString(adapters[m_connection_selected].ip_address));
            model->setItem(5,1,item);

            item = new QStandardItem(QString(tr("子网掩码")));
            model->setItem(6,0,item);
            item = new QStandardItem(QString::fromStdWString(adapters[m_connection_selected].subnet_mask));
            model->setItem(6,1,item);

            item = new QStandardItem(QString(tr("默认网关")));
            model->setItem(7,0,item);
            item = new QStandardItem(QString::fromStdWString(adapters[m_connection_selected].default_gateway));
            model->setItem(7,1,item);

            item = new QStandardItem(QString(tr("连接状态")));
            model->setItem(8,0,item);
            item = new QStandardItem(getNetworkStatus(network_info.dwOperStatus));
            model->setItem(8,1,item);

            item = new QStandardItem(QString(tr("已接收字节数")));
            model->setItem(9,0,item);
            item = new QStandardItem(QString::number(network_info.dwInOctets) + " ("+ dataSizeToString(network_info.dwInOctets) +")");
            model->setItem(9,1,item);

            item = new QStandardItem(QString(tr("已发送字节数")));
            model->setItem(10,0,item);
            item = new QStandardItem(QString::number(network_info.dwOutOctets) + " ("+ dataSizeToString(network_info.dwOutOctets) +")");
            model->setItem(10,1,item);
/*
            item = new QStandardItem(QString(tr("启动以来已接收字节数")));
            model->setItem(11,0,item);
            //item = new QStandardItem(QString::fromWCharArray(network_info.wszName));
            model->setItem(11,1,item);

            item = new QStandardItem(QString(tr("启动以来已发送字节数")));
            model->setItem(12,0,item);
            //item = new QStandardItem(QString::fromWCharArray(network_info.wszName));
            model->setItem(12,1,item);
*/
            item = new QStandardItem(QString(tr("程序已运行时间")));
            model->setItem(11,0,item);
            SYSTEMTIME current_time , time;
            GetLocalTime(&current_time);
            time = CompareSystemTime(current_time, m_startTime);
            item = new QStandardItem(QString::number(time.wHour)+tr("小时 ")+QString::number(time.wMinute)+tr("分钟 ")+QString::number(time.wSecond)+tr("秒"));
            model->setItem(11,1,item);

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0 , 167);
    ui->tableView->setColumnWidth(1 , 280);
    ui->tableView->show();
}

NetworkInfo::~NetworkInfo()
{
    delete ui;
}

QString NetworkInfo::getNetworkType(IFTYPE type){
    QString resStr = "";
    switch (type) {
        case IF_TYPE_OTHER:
            resStr = tr("其他类型网络");
            break;
        case IF_TYPE_ETHERNET_CSMACD:
            resStr = tr("以太网网络");
            break;
        case IF_TYPE_ISO88025_TOKENRING:
            resStr = tr("令牌环网络");
            break;
        case IF_TYPE_FDDI:
            resStr = tr("光纤分布式数据接口 (FDDI) 网络");
            break;
        case IF_TYPE_PPP:
            resStr = tr("PPP 网络");
            break;
        case IF_TYPE_SOFTWARE_LOOPBACK:
            resStr = tr("软件环回网络");
            break;
        case IF_TYPE_ATM:
            resStr = tr("ATM 网络");
            break;
        case IF_TYPE_IEEE80211:
            resStr = tr("IEEE 802.11 无线网络");
            break;
        case IF_TYPE_TUNNEL:
            resStr = tr("隧道类型封装网络");
            break;
        case IF_TYPE_IEEE1394:
            resStr = tr("IEEE 1394 (Firewire) 高性能串行总线网络");
            break;
        case IF_TYPE_IEEE80216_WMAN:
            resStr = tr("对于 WiMax 设备的移动宽带");
            break;
        case IF_TYPE_WWANPP:
            resStr = tr("基于 GSM 网络设备的移动宽带");
            break;
        case IF_TYPE_WWANPP2:
            resStr = tr("基于 CDMA 的设备移动宽带");
            break;
        default:
            resStr = tr("未知网络");
            break;
    }
    return resStr;
}

QString NetworkInfo::getNetworkStatus(INTERNAL_IF_OPER_STATUS status){
    QString resStr = "";
    switch (status) {
        case IF_OPER_STATUS_NON_OPERATIONAL:
            resStr = tr("LAN 适配器已被禁用");
            break;
        case IF_OPER_STATUS_UNREACHABLE:
            resStr = tr("WAN 适配器未连接");
            break;
        case IF_OPER_STATUS_DISCONNECTED:
            resStr = tr("网络电缆断开连接或无载体");
            break;
        case IF_OPER_STATUS_CONNECTING:
            resStr = tr("WAN 适配器正在连接");
            break;
        case IF_OPER_STATUS_CONNECTED:
            resStr = tr("WAN 适配器连接到远程对等方");
            break;
        case IF_OPER_STATUS_OPERATIONAL:
            resStr = tr("LAN 适配器已连接");
            break;
        default:
            resStr = tr("未知状态");
            break;
    }
    return resStr;
}

QString NetworkInfo::dataSizeToString(unsigned long long size){
    QString resStr = "";
    if (size < 1024 * 10)					//10KB以下以KB为单位，保留2位小数
        resStr = QString::number(size / 1024.0 , 'f' , 2) + " KB";
    else if (size < 1024 * 1024)			//1MB以下以KB为单位，保留1位小数
        resStr = QString::number(size / 1024.0 , 'f' , 1) + " KB";
    else if (size < 1024 * 1024 * 1024)		//1GB以下以MB为单位，保留2位小数
        resStr = QString::number(size / 1024.0 / 1024.0 , 'f' , 2) + " MB";
    else
        resStr = QString::number(size / 1024.0 / 1024.0 / 1024.0 , 'f' , 2) + " GB";
    return resStr;
}

SYSTEMTIME NetworkInfo::CompareSystemTime(SYSTEMTIME a, SYSTEMTIME b)
{
    SYSTEMTIME result{};
    short hour = a.wHour - b.wHour;
    short minute = a.wMinute - b.wMinute;
    short second = a.wSecond - b.wSecond;

    if (second < 0)
    {
        second += 60;
        minute--;
    }

    if (minute < 0)
    {
        minute += 60;
        hour--;
    }

    if (hour < 0)
    {
        hour += 24;
    }
    result.wHour = hour;
    result.wMinute = minute;
    result.wSecond = second;
    return result;
}

void NetworkInfo::timerEvent(QTimerEvent *event){
    QStandardItem* item = 0;
    SYSTEMTIME current_time, time;
    GetLocalTime(&current_time);
    time = CompareSystemTime(current_time, m_startTime);
    item = new QStandardItem(QString::number(time.wHour)+tr("小时 ")+QString::number(time.wMinute)+tr("分钟 ")+QString::number(time.wSecond)+tr("秒"));
    model->setItem(11,1,item);
    this->ui->tableView->setModel(model);
}
