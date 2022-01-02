#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "pcinfowindow.h"
#include "ui_pcinfowindow.h"
#include "getpcinfowin.h"
#include "systeminfowin.h"
#include <vector>

static QString g_hardWareCPUInfo = "";
static QString g_hardWareIOInfo = "";
static QString g_hardWareHDDInfo = "";
static QString g_hardWareNvidiaGPUInfo = "";
static QString g_hardWareAtiGPUInfo = "";

static std::vector<QString> g_hardWareCPUName;
static std::vector<QString> g_hardWareCPUTemp;
static std::vector<QString> g_hardWareCPUClock;
static std::vector<QString> g_hardWareCPULoad;
static std::vector<QString> g_hardWareCPUPower;
static std::vector<QString> g_hardWarePCName;
static std::vector<QString> g_hardWareMainBoard;
static std::vector<QString> g_hardWareVoltage;
static std::vector<QString> g_hardWareTemperature;
static std::vector<QString> g_hardWareFans;
static std::vector<QString> g_hardWareFansControl;
static std::vector<QString> g_hardWareNvidiaGPUName;
static std::vector<QString> g_hardWareNvidiaGPUClock;
static std::vector<QString> g_hardWareNvidiaGPUTemp;
static std::vector<QString> g_hardWareNvidiaGPULoad;
static std::vector<QString> g_hardWareNvidiaGPUControl;
static std::vector<QString> g_hardWareNvidiaGPUData;
static std::vector<QString> g_hardWareAtiGPUName;
static std::vector<QString> g_hardWareAtiGPUClock;
static std::vector<QString> g_hardWareAtiGPUTemp;
static std::vector<QString> g_hardWareAtiGPULoad;
static std::vector<QString> g_hardWareAtiGPUPower;
static std::vector<QString> g_hardWareAtiGPUControl;
static std::vector<QString> g_hardWareAtiGPUVoltage;
static std::vector<QString> g_hardWareHDDName;
static std::vector<QString> g_hardWareHDDTemp;
static std::vector<QString> g_hardWareHDDLoad;
static std::vector<QString> g_hardWareHDDData;
static QString g_hardWareMemoryLoad;
static QString g_hardWareMemoryUsed;
static QString g_hardWareMemoryAvailable;

QString g_strUploadSpeed;
QString g_strDownloadSpeed;
QString g_strCPUUtil;
QString g_strMemoryUtil;
QString g_strMainboardTemp;
QString g_strMainboardFan;
QString g_strCPUTemp;
QString g_strGPUTemp;
QString g_strCPUPower;
QString g_strGPUPower;
QString g_strGPUUtil;
QString g_strDiskTemp;

QJsonObject getJsonObjectFromString(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
    }
    QJsonObject jsonObject = jsonDocument.object();
    return jsonObject;
}

void splitInfo(std::vector<QString>&vec , QString info , char c){
    QStringList sList = info.split(c);
    foreach(QString str , sList){
        vec.push_back(str);
        qDebug()<<str;
    }
}

PCInfoWindow::PCInfoWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PCInfoWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));

    //*******PC Name*******//
    itemPCName = NULL;

    //*******IO*******//
    itemMainBoard = NULL;

    //*******IO Name*******//
    itemMainBoardName = NULL;

    //*******IO Voltage*******//
    itemMainBoardVoltage = NULL;
    itemMainBoardVoltageCPUVCore = NULL;
    itemMainBoardVoltageAVCC = NULL;
    itemMainBoardVoltage3VCC = NULL;
    itemMainBoardVoltage3VSB = NULL;
    itemMainBoardVoltageVBAT = NULL;
    itemMainBoardVoltageVTT = NULL;

    //*******IO Temp*******//
    itemMainBoardTemp = NULL;

    //*******IO Fans*******//
    itemMainBoardFans = NULL;

    //*******IO Fans Control*******//
    itemMainBoardControl = NULL;

    //*******CPU*******//
    itemCPU = NULL;

    //*******CPU Name*******//
    itemCPUName = NULL;

    //*******CPU Power*******//
    itemCPUPower = NULL;
    itemCPUPowerPackage = NULL;
    itemCPUPowerCores = NULL;
    itemCPUPowerGraphics = NULL;
    itemCPUPowerDRAM = NULL;

    //*******CPU Load*******//
    itemCPULoad = NULL;

    //*******CPU Clock*******//
    itemCPUClock = NULL;

    //*******CPU Temp*******//
    itemCPUTemp = NULL;

    //*******Graphics Card*******//
    itemGraphicsCard = NULL;

    //*******Ati Graphics Card Name*******//
    itemAtiGraphicsCardName = NULL;

    //*******Ati Graphics Card Clock*******//
    itemAtiGraphicsCardClock = NULL;
    itemAtiGraphicsCardClockCore = NULL;
    itemAtiGraphicsCardClockMemory = NULL;

    //*******Ati Graphics Card Load*******//
    itemAtiGraphicsCardLoad = NULL;
    itemAtiGraphicsCardLoadCore = NULL;

    //*******Ati Graphics Card Data*******//
    itemAtiGraphicsCardData = NULL;

    //*******Ati Graphics Card Power*******//
    itemAtiGraphicsCardPower = NULL;
    itemAtiGraphicsCardPowerTotal = NULL;

    //*******Ati Graphics Card Temp*******//
    itemAtiGraphicsCardTemp = NULL;
    itemAtiGraphicsCardTempCore = NULL;
    itemAtiGraphicsCardTempMemory = NULL;
    itemAtiGraphicsCardTempVRMCore = NULL;
    itemAtiGraphicsCardTempVRMMemory = NULL;
    itemAtiGraphicsCardTempLiquid = NULL;
    itemAtiGraphicsCardTempPLX = NULL;
    itemAtiGraphicsCardTempHotSpot = NULL;

    //*******Ati Graphics Card Control*******//
    itemAtiGraphicsCardControl = NULL;

    //*******Ati Graphics Card Voltage*******//
    itemAtiGraphicsCardVoltage = NULL;
    itemAtiGraphicsCardVoltageCore = NULL;

    //*******Nvidia Graphics Card Name*******//
    itemNvidiaGraphicsCardName = NULL;

    //*******Nvidia Graphics Card Clock*******//
    itemNvidiaGraphicsCardClock = NULL;
    itemNvidiaGraphicsCardClockCore = NULL;
    itemNvidiaGraphicsCardClockMemory = NULL;
    itemNvidiaGraphicsCardClockShader = NULL;

    //*******Nvidia Graphics Card Load*******//
    itemNvidiaGraphicsCardLoad = NULL;
    itemNvidiaGraphicsCardLoadCore = NULL;
    itemNvidiaGraphicsCardLoadFrameBuffer = NULL;
    itemNvidiaGraphicsCardLoadVideoEngine = NULL;
    itemNvidiaGraphicsCardLoadBusInterface = NULL;
    itemNvidiaGraphicsCardLoadMemory = NULL;

    //*******Nvidia Graphics Card Data*******//
    itemNvidiaGraphicsCardData = NULL;
    itemNvidiaGraphicsCardDataMemoryFree = NULL;
    itemNvidiaGraphicsCardDataMemoryUsed = NULL;
    itemNvidiaGraphicsCardDataMemoryTotal = NULL;

    //*******Nvidia Graphics Card Power*******//
    itemNvidiaGraphicsCardPower = NULL;
    itemNvidiaGraphicsCardPowerTotal = NULL;

    //*******Nvidia Graphics Card Temp*******//
    itemNvidiaGraphicsCardTemp = NULL;
    itemNvidiaGraphicsCardTempCore = NULL;

    //*******Nvidia Graphics Card Control*******//
    itemNvidiaGraphicsCardControl = NULL;

    //*******Nvidia Graphics Card Voltage*******//
    itemNvidiaGraphicsCardVoltage = NULL;
    itemNvidiaGraphicsCardVoltageCore = NULL;

    //*******Memory*******//
    itemMemory = NULL;

    //*******Memory Load*******//
    itemMemoryLoad = NULL;
    itemMemoryLoadRate = NULL;

    //*******Memory Data*******//
    itemMemoryData = NULL;
    itemMemoryUsed = NULL;
    itemMemoryAvailable = NULL;

    //*******Disk*******//
    itemHardDisk = NULL;

    //*******Disk Name*******//
    itemHardDiskName = NULL;

    //*******Disk Load*******//
    itemHardDiskLoad = NULL;

    //*******Disk Temp*******//
    itemHardDiskTemp = NULL;

    //*******Disk Data*******//
    itemHardDiskData = NULL;

    //*******MacAddress*******//
    itemMacAddress = NULL;

    //*******LocalIP*******//
    itemLocalIP = NULL;

    //*******PublicIP*******//
    itemPublicIP = NULL;

    QStringList listHeader;
    listHeader<<"Sensor"<<"Value";
    ui->treeWidget->setHeaderLabels(listHeader);
    ui->treeWidget->header()->resizeSection(0 /*column index*/, 240 /*width*/);

    itemMainBoard = new QTreeWidgetItem(QStringList()<<tr("主板"));
    itemPCName = new QTreeWidgetItem(QStringList()<<"PC");
    itemMainBoardName = new QTreeWidgetItem(QStringList()<<"Loading...");//Name
    itemMainBoardVoltage = new QTreeWidgetItem(QStringList()<<"Voltage"<<"Loading...");
    itemMainBoardTemp = new QTreeWidgetItem(QStringList()<<"Temperatures"<<"Loading...");
    itemMainBoardFans = new QTreeWidgetItem(QStringList()<<"Fans"<<"Loading...");
    itemMainBoardControl = new QTreeWidgetItem(QStringList()<<"Fans Control"<<"Loading...");
    itemMainBoard->addChild(itemMainBoardName);
    itemMainBoardName->addChild(itemMainBoardVoltage);
    itemMainBoardName->addChild(itemMainBoardTemp);
    itemMainBoardName->addChild(itemMainBoardFans);
    itemMainBoardName->addChild(itemMainBoardControl);

    itemCPU = new QTreeWidgetItem(QStringList()<<"CPU");
    itemCPUName = new QTreeWidgetItem(QStringList()<<"Loading...");//Name
    itemCPUPower = new QTreeWidgetItem(QStringList()<<"Power"<<"Loading...");
    itemCPULoad = new QTreeWidgetItem(QStringList()<<"Load"<<"Loading...");
    itemCPUClock = new QTreeWidgetItem(QStringList()<<"Clocks"<<"Loading...");
    itemCPUTemp = new QTreeWidgetItem(QStringList()<<"Temperatures"<<"Loading...");

    itemCPU->addChild(itemCPUName);
    itemCPUName->addChild(itemCPUPower);
    itemCPUName->addChild(itemCPULoad);
    itemCPUName->addChild(itemCPUClock);
    itemCPUName->addChild(itemCPUTemp);

    uiAvailMemory = SystemInfoWin::GetMemoryStat(uiAllMemory);
    memoryRate = 1.0-((double)uiAvailMemory/(double)uiAllMemory);
    usedMemory = ((double)uiAllMemory-(double)uiAvailMemory)/1024/1024;
    availableMemory = (double)uiAvailMemory/1024/1024;

    itemMemory = new QTreeWidgetItem(QStringList()<<tr("内存"));
    itemMemoryLoad = new QTreeWidgetItem(QStringList()<<"Load");
    itemMemoryLoadRate = new QTreeWidgetItem(QStringList()<<"Memory"<<QString::number(memoryRate*100,'f',1)+" %");
    itemMemoryData = new QTreeWidgetItem(QStringList()<<"Data");
    itemMemoryUsed = new QTreeWidgetItem(QStringList()<<"Used Memory"<<QString::number(usedMemory,'f',1)+" GB");
    itemMemoryAvailable = new QTreeWidgetItem(QStringList()<<"Available Memory"<<QString::number(availableMemory,'f',1)+" GB");
    itemMemoryLoad->addChild(itemMemoryLoadRate);
    itemMemoryData->addChild(itemMemoryUsed);
    itemMemoryData->addChild(itemMemoryAvailable);
    itemMemory->addChild(itemMemoryLoad);
    itemMemory->addChild(itemMemoryData);

    itemGraphicsCard = new QTreeWidgetItem(QStringList()<<tr("显卡"));
    itemAtiGraphicsCardName = new QTreeWidgetItem(QStringList()<<"Loading...");//Name
    itemAtiGraphicsCardClock = new QTreeWidgetItem(QStringList()<<"Clocks"<<"Loading...");
    itemAtiGraphicsCardLoad = new QTreeWidgetItem(QStringList()<<"Load"<<"Loading...");
    itemAtiGraphicsCardPower = new QTreeWidgetItem(QStringList()<<"Powers"<<"Loading...");
    itemAtiGraphicsCardTemp = new QTreeWidgetItem(QStringList()<<"Temperatures"<<"Loading...");
    itemAtiGraphicsCardVoltage = new QTreeWidgetItem(QStringList()<<"Voltage"<<"Loading...");
    itemGraphicsCard->addChild(itemAtiGraphicsCardName);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardClock);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardLoad);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardPower);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardData);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardTemp);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardControl);
    itemAtiGraphicsCardName->addChild(itemAtiGraphicsCardVoltage);

    itemHardDisk = new QTreeWidgetItem(QStringList()<<tr("硬盘"));

    itemMacAddress = new QTreeWidgetItem(QStringList()<<tr("MAC地址")<<getMacAddress());
    itemLocalIP = new QTreeWidgetItem(QStringList()<<tr("本地IP")<<getLocalIP());
    itemPublicIP = new QTreeWidgetItem(QStringList()<<tr("公网IP")<<tr("正在查询中..."));

    itemPCName->addChild(itemMainBoard);
    itemPCName->addChild(itemCPU);
    itemPCName->addChild(itemGraphicsCard);
    itemPCName->addChild(itemMemory);
    itemPCName->addChild(itemHardDisk);

    ui->treeWidget->addTopLevelItem(itemPCName);
    ui->treeWidget->addTopLevelItem(itemMacAddress);
    ui->treeWidget->addTopLevelItem(itemLocalIP);
    ui->treeWidget->addTopLevelItem(itemPublicIP);

    ch = new GetPublicIPThread();
    // 连接线程发过来的信号
    connect(ch, SIGNAL(send2UI(QString)), this, SLOT(updateUI(QString)));
    // 启动线程
    ch->start();

    m_signal = new CSignal();
    connect(m_signal , &CSignal::statusChanged , this , &PCInfoWindow::getStatusChanged);
    m_signal->start();
}

PCInfoWindow::~PCInfoWindow()
{
    ch->exit(0);
    m_signal->exit(0);
    ch->deleteLater();
    m_signal->deleteLater();
    delete ui;
}

void PCInfoWindow::updateUI(QString publicIP){
    //更新公网IP
    qDebug()<<"updateIP";
    itemPublicIP->setText(1 , publicIP);
}

void PCInfoWindow::timerEvent(QTimerEvent *event){
    /*g_hardWareCPUInfo = getCPUInfo();
    g_hardWareHDDInfo = getHDDInfo();
    g_hardWareAtiGPUInfo = getAtiGPUInfo();
    g_hardWareNvidiaGPUInfo = getNvidiaGPUInfo();
    g_hardWareIOInfo = getIOInfo();
*/
}

void PCInfoWindow::OnTimerout()
{
    qDebug()<<"PCInfoWindow"<<QThread::currentThreadId();
}

void PCInfoWindow::getStatusChanged(QString CPUInfo , QString HDDInfo , QString AtiGPUInfo , QString NvidiaGPUInfo , QString IOInfo)
{
    qDebug()<<"PCInfoWindow getStatusChanged";
    qDebug()<<CPUInfo;
    qDebug()<<HDDInfo;
    qDebug()<<AtiGPUInfo;
    qDebug()<<NvidiaGPUInfo;
    qDebug()<<IOInfo;
    //CPU
    if(CPUInfo != ""){
        QJsonParseError jsonError;
        QJsonDocument doucmentCPU = QJsonDocument::fromJson(CPUInfo.toUtf8(), &jsonError);  // 转化为 JSON 文档
        if (!doucmentCPU.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if (doucmentCPU.isObject()) { // JSON 文档为对象
                QJsonObject object = doucmentCPU.object();  // 转化为对象
                if (object.contains("name")) {  //CPU name
                    QJsonValue value = object.value("name");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareCPUName.clear();
                        splitInfo(g_hardWareCPUName , strName , '|');
                        qDebug() << "CPU name: " << strName;
                    }
                }
                if (object.contains("power")) {  //CPU power
                    QJsonValue value = object.value("power");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareCPUPower.clear();
                        splitInfo(g_hardWareCPUPower , strName , '|');
                        qDebug() << "CPU power: " << strName;
                    }
                }
                if (object.contains("load")) {  //CPU load
                    QJsonValue value = object.value("load");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareCPULoad.clear();
                        splitInfo(g_hardWareCPULoad , strName , '|');
                        qDebug() << "CPU load: " << strName;
                    }
                }
                if (object.contains("clock")) {  //CPU clock
                    QJsonValue value = object.value("clock");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareCPUClock.clear();
                        splitInfo(g_hardWareCPUClock , strName , '|');
                        qDebug() << "CPU clock: " << strName;
                    }
                }
                if (object.contains("temp")) {  //CPU temp
                    QJsonValue value = object.value("temp");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareCPUTemp.clear();
                        splitInfo(g_hardWareCPUTemp , strName , '|');
                        qDebug() << "CPU temp: " << strName;
                    }
                }
            }
        }
    }

    //HDD
    if(HDDInfo != ""){
        QJsonParseError jsonError;
        QJsonDocument doucmentHDD = QJsonDocument::fromJson(HDDInfo.toUtf8(), &jsonError);  // 转化为 JSON 文档
        if (!doucmentHDD.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if (doucmentHDD.isObject()) { // JSON 文档为对象
                QJsonObject object = doucmentHDD.object();  // 转化为对象
                if (object.contains("name")) {  //HDD name
                    QJsonValue value = object.value("name");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareHDDName.clear();
                        splitInfo(g_hardWareHDDName , strName , '|');
                        qDebug() << "HDD name: " << strName;
                    }
                }
                if (object.contains("load")) {  //HDD load
                    QJsonValue value = object.value("load");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareHDDLoad.clear();
                        splitInfo(g_hardWareHDDLoad , strName , '|');
                        qDebug() << "HDD load: " << strName;
                    }
                }
                if (object.contains("temp")) {  //HDD temp
                    QJsonValue value = object.value("temp");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareHDDTemp.clear();
                        splitInfo(g_hardWareHDDTemp , strName , '|');
                        qDebug() << "HDD temp: " << strName;
                    }
                }
                if (object.contains("data")) {  //HDD data
                    QJsonValue value = object.value("data");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareHDDData.clear();
                        splitInfo(g_hardWareHDDData , strName , '|');
                        qDebug() << "HDD data: " << strName;
                    }
                }
            }
        }
    }

    //IO
    if(IOInfo != ""){
        QJsonParseError jsonError;
        QJsonDocument doucmentIO = QJsonDocument::fromJson(IOInfo.toUtf8(), &jsonError);  // 转化为 JSON 文档
        if (!doucmentIO.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if (doucmentIO.isObject()) { // JSON 文档为对象
                QJsonObject object = doucmentIO.object();  // 转化为对象
                if (object.contains("name")) {  //IO name
                    QJsonValue value = object.value("name");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWarePCName.clear();
                        splitInfo(g_hardWarePCName , strName , '|');
                        qDebug() << "IO name: " << strName;
                    }
                }
                if (object.contains("mainboard")) {  //IO mainboard
                    QJsonValue value = object.value("mainboard");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareMainBoard.clear();
                        splitInfo(g_hardWareMainBoard , strName , '|');
                        qDebug() << "IO mainboard: " << strName;
                    }
                }
                if (object.contains("voltage")) {  //IO voltage
                    QJsonValue value = object.value("voltage");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareVoltage.clear();
                        splitInfo(g_hardWareVoltage , strName , '|');
                        qDebug() << "IO voltage: " << strName;
                    }
                }
                if (object.contains("fan")) {  //IO fan
                    QJsonValue value = object.value("fan");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareFans.clear();
                        splitInfo(g_hardWareFans , strName , '|');
                        qDebug() << "IO fan: " << strName;
                    }
                }
                if (object.contains("fanControl")) {  //IO fanControl
                    QJsonValue value = object.value("fanControl");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareFansControl.clear();
                        splitInfo(g_hardWareFansControl , strName , '|');
                        qDebug() << "IO fanControl: " << strName;
                    }
                }
                if (object.contains("temp")) {  //IO temp
                    QJsonValue value = object.value("temp");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareTemperature.clear();
                        splitInfo(g_hardWareTemperature , strName , '|');
                        qDebug() << "IO temp: " << strName;
                    }
                }
            }
        }
    }

    if(AtiGPUInfo != ""){
        QJsonParseError jsonError;
        QJsonDocument doucmentAtiGPU = QJsonDocument::fromJson(AtiGPUInfo.toUtf8(), &jsonError);  // 转化为 JSON 文档
        if (!doucmentAtiGPU.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if (doucmentAtiGPU.isObject()) { // JSON 文档为对象
                QJsonObject object = doucmentAtiGPU.object();  // 转化为对象
                if (object.contains("name")) {  //Ati GPU name
                    QJsonValue value = object.value("name");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPUName.clear();
                        splitInfo(g_hardWareAtiGPUName , strName , '|');
                        qDebug() << "Ati GPU name: " << strName;
                    }
                }
                if (object.contains("clock")) {  //Ati GPU clock
                    QJsonValue value = object.value("clock");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPUClock.clear();
                        splitInfo(g_hardWareAtiGPUClock , strName , '|');
                        qDebug() << "Ati GPU clock: " << strName;
                    }
                }
                if (object.contains("load")) {  //Ati GPU load
                    QJsonValue value = object.value("load");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPULoad.clear();
                        splitInfo(g_hardWareAtiGPULoad , strName , '|');
                        qDebug() << "Ati GPU load: " << strName;
                    }
                }
                if (object.contains("control")) {  //Ati GPU control
                    QJsonValue value = object.value("control");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPUControl.clear();
                        splitInfo(g_hardWareAtiGPUControl , strName , '|');
                        qDebug() << "Ati GPU control: " << strName;
                    }
                }
                if (object.contains("voltage")) {  //Ati GPU voltage
                    QJsonValue value = object.value("voltage");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPUVoltage.clear();
                        splitInfo(g_hardWareAtiGPUVoltage , strName , '|');
                        qDebug() << "Ati GPU voltage: " << strName;
                    }
                }
                if (object.contains("temp")) {  //Ati GPU temp
                    QJsonValue value = object.value("temp");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPUTemp.clear();
                        splitInfo(g_hardWareAtiGPUTemp , strName , '|');
                        qDebug() << "Ati GPU temp: " << strName;
                    }
                }
                if (object.contains("power")) {  //Ati GPU power
                    QJsonValue value = object.value("temp");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareAtiGPUPower.clear();
                        splitInfo(g_hardWareAtiGPUPower , strName , '|');
                        qDebug() << "Ati GPU power: " << strName;
                    }
                }
            }
        }
    }

    if(NvidiaGPUInfo != ""){
        QJsonParseError jsonError;
        QJsonDocument doucmentNvidiaGPU = QJsonDocument::fromJson(NvidiaGPUInfo.toUtf8(), &jsonError);  // 转化为 JSON 文档
        if (!doucmentNvidiaGPU.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
            if (doucmentNvidiaGPU.isObject()) { // JSON 文档为对象
                QJsonObject object = doucmentNvidiaGPU.object();  // 转化为对象
                if (object.contains("name")) {  //Nvidia GPU name
                    QJsonValue value = object.value("name");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareNvidiaGPUName.clear();
                        splitInfo(g_hardWareNvidiaGPUName , strName , '|');
                        qDebug() << "Nvidia GPU name: " << strName;
                    }
                }
                if (object.contains("clock")) {  //Nvidia GPU clock
                    QJsonValue value = object.value("clock");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareNvidiaGPUClock.clear();
                        splitInfo(g_hardWareNvidiaGPUClock , strName , '|');
                        qDebug() << "Nvidia GPU clock: " << strName;
                    }
                }
                if (object.contains("load")) {  //Nvidia GPU load
                    QJsonValue value = object.value("load");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareNvidiaGPULoad.clear();
                        splitInfo(g_hardWareNvidiaGPULoad , strName , '|');
                        qDebug() << "Nvidia GPU load: " << strName;
                    }
                }
                if (object.contains("control")) {  //Nvidia GPU control
                    QJsonValue value = object.value("control");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareNvidiaGPUControl.clear();
                        splitInfo(g_hardWareNvidiaGPUControl , strName , '|');
                        qDebug() << "Nvidia GPU control: " << strName;
                    }
                }
                if (object.contains("data")) {  //Nvidia GPU data
                    QJsonValue value = object.value("data");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareNvidiaGPUData.clear();
                        splitInfo(g_hardWareNvidiaGPUData , strName , '|');
                        qDebug() << "Nvidia GPU data: " << strName;
                    }
                }

                if (object.contains("temp")) {  //Nvidia GPU temp
                    QJsonValue value = object.value("temp");  // 获取指定 key 对应的 value
                    if (value.isString()) {  // 判断 value 是否为字符串
                        QString strName = value.toString();  // 将 value 转化为字符串
                        g_hardWareNvidiaGPUTemp.clear();
                        splitInfo(g_hardWareNvidiaGPUTemp , strName , '|');
                        qDebug() << "Nvidia GPU temp: " << strName;
                    }
                }
            }
        }
    }

    //更新数据
    if(g_hardWareMainBoard.size() > 0){
        if(g_hardWareMainBoard[0] != "" && g_hardWareMainBoard[0] != "#"){
            itemMainBoardName->setText(0 , g_hardWareMainBoard[0]);
        }
    }

    for(int i = 0 ; i < g_hardWareVoltage.size() ; i++){
        if(g_hardWareVoltage[i] == "" || g_hardWareVoltage[i] == "#"){
            break;
        }
        itemMainBoardVoltage->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemMainBoardVoltageCPUVCore == NULL){
                itemMainBoardVoltageCPUVCore = new QTreeWidgetItem(QStringList()<<"CPU VCore"<<QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                itemMainBoardVoltage->addChild(itemMainBoardVoltageCPUVCore);
            }
            else{
                itemMainBoardVoltageCPUVCore->setText(1 , QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
            }
            break;
        }
        case 1:{
            if(itemMainBoardVoltageAVCC == NULL){
                itemMainBoardVoltageAVCC = new QTreeWidgetItem(QStringList()<<"CPU AVCC"<<QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                itemMainBoardVoltage->addChild(itemMainBoardVoltageAVCC);
            }
            else{
                itemMainBoardVoltageAVCC->setText(1 , QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
            }
            break;
        }
        case 2:{
             if(itemMainBoardVoltage3VCC == NULL){
                 itemMainBoardVoltage3VCC = new QTreeWidgetItem(QStringList()<<"CPU 3VCC"<<QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                 itemMainBoardVoltage->addChild(itemMainBoardVoltage3VCC);
             }
             else{
                 itemMainBoardVoltage3VCC->setText(1 , QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
             }
             break;
        }
        case 3:{
              if(itemMainBoardVoltage3VSB == NULL){
                  itemMainBoardVoltage3VSB = new QTreeWidgetItem(QStringList()<<"CPU 3VSB"<<QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                  itemMainBoardVoltage->addChild(itemMainBoardVoltage3VSB);
              }
              else{
                  itemMainBoardVoltage3VSB->setText(1 , QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
              }
              break;
        }
        case 4:{
               if(itemMainBoardVoltageVBAT == NULL){
                   itemMainBoardVoltageVBAT = new QTreeWidgetItem(QStringList()<<"CPU VBAT"<<QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                   itemMainBoardVoltage->addChild(itemMainBoardVoltageVBAT);
               }
               else{
                   itemMainBoardVoltageVBAT->setText(1 , QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
               }
               break;
        }
        case 5:{
                if(itemMainBoardVoltageVTT == NULL){
                    itemMainBoardVoltageVTT = new QTreeWidgetItem(QStringList()<<"CPU VTT"<<QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                    itemMainBoardVoltage->addChild(itemMainBoardVoltageVTT);
                }
                else{
                    itemMainBoardVoltageVTT->setText(1 , QString::number(g_hardWareVoltage[i].toDouble() , 'f' , 3) + " V");
                }
                break;
        }
        }
    }

    for(int i = 0; i < g_hardWareTemperature.size() ; i++){
        if(g_hardWareTemperature[i] == "" || g_hardWareTemperature[i] == "#"){
            break;
        }
        itemMainBoardTemp->setText(1 , "");
        if(i == 0){
            g_strMainboardTemp = QString::number(g_hardWareTemperature[i].toDouble() , 'f' , 1) + " ℃";
        }
        if(itemMainBoardTemp->childCount() <= i){
             QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"Temperature #" + QString::number(i+1)<<QString::number(g_hardWareTemperature[i].toDouble() , 'f' , 1) + " ℃");
             itemMainBoardTemp->addChild(item);
        }
        else{
            itemMainBoardTemp->child(i)->setText(1 , QString::number(g_hardWareTemperature[i].toDouble() , 'f' , 1) + " ℃");
        }
    }

    for(int i = 0; i < g_hardWareFans.size() ; i++){
        if(g_hardWareFans[i] == "" || g_hardWareFans[i] == "#"){
            break;
        }
        itemMainBoardFans->setText(1 , "");
        if(i == 0){
            g_strMainboardFan = QString::number(g_hardWareFans[i].toDouble() , 'f' , 0) + " RPM";
        }
        if(itemMainBoardFans->childCount() <= i){
             QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"Fan #" + QString::number(i+1)<<QString::number(g_hardWareFans[i].toDouble() , 'f' , 0) + " RPM");
             itemMainBoardFans->addChild(item);
        }
        else{
            itemMainBoardFans->child(i)->setText(1 , QString::number(g_hardWareFans[i].toDouble() , 'f' , 0) + " RPM");
        }
    }

    for(int i = 0; i < g_hardWareFansControl.size() ; i++){
        if(g_hardWareFansControl[i] == "" || g_hardWareFansControl[i] == "#"){
            break;
        }
        itemMainBoardControl->setText(1 , "");
        if(itemMainBoardControl->childCount() <= i){
             QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"Fan Control #" + QString::number(i+1)<<QString::number(g_hardWareFansControl[i].toDouble() , 'f' , 1) + " %");
             itemMainBoardControl->addChild(item);
        }
        else{
            itemMainBoardControl->child(i)->setText(1 , QString::number(g_hardWareFansControl[i].toDouble() , 'f' , 1) + " %");
        }
    }

    if(g_hardWareCPUName.size() > 0){
        if(g_hardWareCPUName[0] != "" && g_hardWareCPUName[0] != "#"){
            itemCPUName->setText(0 , g_hardWareCPUName[0]);
        }
    }

    double hardWareCPUTotalPower = 0;
    for(int i = 0 ; i < g_hardWareCPUPower.size() ; i++){
        if(g_hardWareCPUPower[i] == "" || g_hardWareCPUPower[i] == "#"){
            break;
        }
        itemCPUPower->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemCPUPowerPackage == NULL){
                itemCPUPowerPackage = new QTreeWidgetItem(QStringList()<<"CPU Package"<<QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
                itemCPUPower->addChild(itemCPUPowerPackage);
            }
            else{
                itemCPUPowerPackage->setText(1 , QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
            }
            break;
        }
        case 1:{
            if(itemCPUPowerCores == NULL){
                itemCPUPowerCores = new QTreeWidgetItem(QStringList()<<"CPU Cores"<<QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
                itemCPUPower->addChild(itemCPUPowerCores);
            }
            else{
                itemCPUPowerCores->setText(1 , QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
            }
            break;
        }
        case 2:{
             if(itemCPUPowerGraphics == NULL){
                 itemCPUPowerGraphics = new QTreeWidgetItem(QStringList()<<"CPU Graphics"<<QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
                 itemCPUPower->addChild(itemCPUPowerGraphics);
             }
             else{
                 itemCPUPowerGraphics->setText(1 , QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
             }
             break;
        }
        case 3:{
              if(itemCPUPowerDRAM == NULL){
                  itemCPUPowerDRAM = new QTreeWidgetItem(QStringList()<<"CPU DRAM"<<QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
                  itemCPUPower->addChild(itemCPUPowerDRAM);
              }
              else{
                  itemCPUPowerDRAM->setText(1 , QString::number(g_hardWareCPUPower[i].toDouble() , 'f' , 1) + " W");
              }
              break;
        }

        }
        hardWareCPUTotalPower = hardWareCPUTotalPower + g_hardWareCPUPower[i].toDouble();
    }
    g_strCPUPower = QString::number(hardWareCPUTotalPower , 'f' , 1) + " W";

    for(int i = 0; i < g_hardWareCPUClock.size() ; i++){
        if(g_hardWareCPUClock[i] == "" || g_hardWareCPUClock[i] == "#"){
            break;
        }
        itemCPUClock->setText(1 , "");
        if(itemCPUClock->childCount() <= i){
            if(i == 0){
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"Bus Speed" <<QString::number(g_hardWareCPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemCPUClock->addChild(item);
            }
            else{
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"CPU Core #" + QString::number(i)<<QString::number(g_hardWareCPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemCPUClock->addChild(item);
            }
        }
        else{
            itemCPUClock->child(i)->setText(1 , QString::number(g_hardWareCPUClock[i].toDouble() , 'f' , 1) + " MHz");
        }
    }

    for(int i = 0; i < g_hardWareCPULoad.size() ; i++){
        if(g_hardWareCPULoad[i] == "" || g_hardWareCPULoad[i] == "#"){
            break;
        }
        itemCPULoad->setText(1 , "");
        if(itemCPULoad->childCount() <= i){
            if(i == 0){
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"CPU Total" <<QString::number(g_hardWareCPULoad[i].toDouble() , 'f' , 1) + " %");
                itemCPULoad->addChild(item);
            }
            else{
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"CPU Core #" + QString::number(i)<<QString::number(g_hardWareCPULoad[i].toDouble() , 'f' , 1) + " %");
                itemCPULoad->addChild(item);
            }
        }
        else{
            itemCPULoad->child(i)->setText(1 , QString::number(g_hardWareCPULoad[i].toDouble() , 'f' , 1) + " %");
        }
    }

    for(int i = 0; i < g_hardWareCPUTemp.size() ; i++){
        if(g_hardWareCPUTemp[i] == "" || g_hardWareCPUTemp[i] == "#"){
            break;
        }
        if(i == 0){
            g_strCPUTemp = QString::number(g_hardWareCPUTemp[i].toDouble() , 'f' , 1) + " ℃";
        }
        itemCPUTemp->setText(1 , "");
        if(itemCPUTemp->childCount() <= i){
            if(i == itemCPUTemp->childCount()){
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"CPU Package" <<QString::number(g_hardWareCPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemCPUTemp->addChild(item);
            }
            else{
                QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<"CPU Core #" + QString::number(i+1)<<QString::number(g_hardWareCPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemCPUTemp->addChild(item);
            }
        }
        else{
            itemCPUTemp->child(i)->setText(1 , QString::number(g_hardWareCPUTemp[i].toDouble() , 'f' , 1) + " ℃");
        }
    }

    if(g_hardWareAtiGPUName.size() > 0){
        if(g_hardWareAtiGPUName[0] != "" && g_hardWareAtiGPUName[0] != "#"){
            itemAtiGraphicsCardName->setText(0 , g_hardWareAtiGPUName[0]);
        }
    }

    for(int i = 0 ; i < g_hardWareAtiGPUClock.size() ; i++){
        if(g_hardWareAtiGPUClock[i] == "" || g_hardWareAtiGPUClock[i] == "#"){
            break;
        }
        itemAtiGraphicsCardClock->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemAtiGraphicsCardClockCore == NULL){
                itemAtiGraphicsCardClockCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareAtiGPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemAtiGraphicsCardClock->addChild(itemAtiGraphicsCardClockCore);
            }
            else{
                itemAtiGraphicsCardClockCore->setText(1 , QString::number(g_hardWareAtiGPUClock[i].toDouble() , 'f' , 1) + " MHz");
            }
            break;
        }
        case 1:{
            if(itemAtiGraphicsCardClockMemory == NULL){
                itemAtiGraphicsCardClockMemory = new QTreeWidgetItem(QStringList()<<"GPU Memory"<<QString::number(g_hardWareAtiGPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemAtiGraphicsCardClock->addChild(itemAtiGraphicsCardClockMemory);
            }
            else{
                itemAtiGraphicsCardClockMemory->setText(1 , QString::number(g_hardWareAtiGPUClock[i].toDouble() , 'f' , 1) + " MHz");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareAtiGPUVoltage.size() ; i++){
        if(g_hardWareAtiGPUVoltage[i] == "" || g_hardWareAtiGPUVoltage[i] == "#"){
            break;
        }
        itemAtiGraphicsCardVoltage->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemAtiGraphicsCardVoltageCore == NULL){
                itemAtiGraphicsCardVoltageCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareAtiGPUVoltage[i].toDouble() , 'f' , 1) + " V");
                itemAtiGraphicsCardVoltage->addChild(itemAtiGraphicsCardVoltageCore);
            }
            else{
                itemAtiGraphicsCardVoltageCore->setText(1 , QString::number(g_hardWareAtiGPUVoltage[i].toDouble() , 'f' , 1) + " V");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareAtiGPUTemp.size() ; i++){
        if(g_hardWareAtiGPUTemp[i] == "" || g_hardWareAtiGPUTemp[i] == "#"){
            break;
        }
        if(i == 0){
            g_strGPUTemp = QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃";
        }
        itemAtiGraphicsCardTemp->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemAtiGraphicsCardTempCore == NULL){
                itemAtiGraphicsCardTempCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempCore);
            }
            else{
                itemAtiGraphicsCardTempCore->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        case 1:{
            if(itemAtiGraphicsCardTempMemory == NULL){
                itemAtiGraphicsCardTempMemory = new QTreeWidgetItem(QStringList()<<"GPU Memory"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempMemory);
            }
            else{
                itemAtiGraphicsCardTempMemory->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        case 2:{
            if(itemAtiGraphicsCardTempVRMCore == NULL){
                itemAtiGraphicsCardTempVRMCore = new QTreeWidgetItem(QStringList()<<"GPU VRM Core"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempVRMCore);
            }
            else{
                itemAtiGraphicsCardTempVRMCore->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        case 3:{
            if(itemAtiGraphicsCardTempVRMMemory == NULL){
                itemAtiGraphicsCardTempVRMMemory = new QTreeWidgetItem(QStringList()<<"GPU VRM Memory"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempVRMMemory);
            }
            else{
                itemAtiGraphicsCardTempVRMMemory->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        case 4:{
            if(itemAtiGraphicsCardTempLiquid == NULL){
                itemAtiGraphicsCardTempLiquid = new QTreeWidgetItem(QStringList()<<"GPU Liquid"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempLiquid);
            }
            else{
                itemAtiGraphicsCardTempLiquid->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        case 5:{
            if(itemAtiGraphicsCardTempPLX == NULL){
                itemAtiGraphicsCardTempPLX = new QTreeWidgetItem(QStringList()<<"GPU PLX"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempPLX);
            }
            else{
                itemAtiGraphicsCardTempPLX->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        case 6:{
            if(itemAtiGraphicsCardTempHotSpot == NULL){
                itemAtiGraphicsCardTempHotSpot = new QTreeWidgetItem(QStringList()<<"GPU Hot Spot"<<QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemAtiGraphicsCardTempHotSpot);
            }
            else{
                itemAtiGraphicsCardTempHotSpot->setText(1 , QString::number(g_hardWareAtiGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareAtiGPULoad.size() ; i++){
        if(g_hardWareAtiGPULoad[i] == "" || g_hardWareAtiGPULoad[i] == "#"){
            break;
        }
        if(i == 0){
            g_strGPUUtil = QString::number(g_hardWareAtiGPULoad[i].toDouble() , 'f' , 1) + " W";
        }
        itemAtiGraphicsCardLoad->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemAtiGraphicsCardLoadCore == NULL){
                itemAtiGraphicsCardLoadCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareAtiGPULoad[i].toDouble() , 'f' , 1) + " %");
                itemAtiGraphicsCardLoad->addChild(itemAtiGraphicsCardLoadCore);
            }
            else{
                itemAtiGraphicsCardLoadCore->setText(1 , QString::number(g_hardWareAtiGPULoad[i].toDouble() , 'f' , 1) + " %");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareAtiGPUPower.size() ; i++){
        if(g_hardWareAtiGPUPower[i] == "" || g_hardWareAtiGPUPower[i] == "#"){
            break;
        }
        if(i == 0){
            g_strGPUPower = QString::number(g_hardWareAtiGPUPower[i].toDouble() , 'f' , 1) + " W";
        }
        itemAtiGraphicsCardPower->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemAtiGraphicsCardPowerTotal == NULL){
                itemAtiGraphicsCardPowerTotal = new QTreeWidgetItem(QStringList()<<"GPU Total"<<QString::number(g_hardWareAtiGPUPower[i].toDouble() , 'f' , 1) + " W");
                itemAtiGraphicsCardPower->addChild(itemAtiGraphicsCardPowerTotal);
            }
            else{
                itemAtiGraphicsCardPowerTotal->setText(1 , QString::number(g_hardWareAtiGPUPower[i].toDouble() , 'f' , 1) + " W");
            }
            break;
        }
        }
    }

    if(g_hardWareNvidiaGPUName.size() > 0){
        if(g_hardWareNvidiaGPUName[0] != "" && g_hardWareNvidiaGPUName[0] != "#"){
            itemNvidiaGraphicsCardName = new QTreeWidgetItem(QStringList()<<g_hardWareNvidiaGPUName[0]);//Name
            itemNvidiaGraphicsCardClock = new QTreeWidgetItem(QStringList()<<"Clocks");
            itemNvidiaGraphicsCardLoad = new QTreeWidgetItem(QStringList()<<"Load");
            itemNvidiaGraphicsCardData = new QTreeWidgetItem(QStringList()<<"Data");
            itemNvidiaGraphicsCardTemp = new QTreeWidgetItem(QStringList()<<"Temperatures");
            itemGraphicsCard->addChild(itemNvidiaGraphicsCardName);
            itemNvidiaGraphicsCardName->addChild(itemNvidiaGraphicsCardClock);
            itemNvidiaGraphicsCardName->addChild(itemNvidiaGraphicsCardLoad);
            itemNvidiaGraphicsCardName->addChild(itemNvidiaGraphicsCardData);
            itemNvidiaGraphicsCardName->addChild(itemNvidiaGraphicsCardTemp);
        }
    }

    for(int i = 0 ; i < g_hardWareNvidiaGPUClock.size() ; i++){
        if(g_hardWareNvidiaGPUClock[i] == "" || g_hardWareNvidiaGPUClock[i] == "#"){
            break;
        }
        itemNvidiaGraphicsCardClock->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemNvidiaGraphicsCardClockCore == NULL){
                itemNvidiaGraphicsCardClockCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareNvidiaGPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemNvidiaGraphicsCardClock->addChild(itemNvidiaGraphicsCardClockCore);
            }
            else{
                itemNvidiaGraphicsCardClockCore->setText(1 , QString::number(g_hardWareNvidiaGPUClock[i].toDouble() , 'f' , 1) + " MHz");
            }
            break;
        }
        case 1:{
            if(itemNvidiaGraphicsCardClockMemory == NULL){
                itemNvidiaGraphicsCardClockMemory = new QTreeWidgetItem(QStringList()<<"GPU Memory"<<QString::number(g_hardWareNvidiaGPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemNvidiaGraphicsCardClock->addChild(itemNvidiaGraphicsCardClockMemory);
            }
            else{
                itemNvidiaGraphicsCardClockMemory->setText(1 , QString::number(g_hardWareNvidiaGPUClock[i].toDouble() , 'f' , 1) + " MHz");
            }
            break;
        }
        case 2:{
            if(itemNvidiaGraphicsCardClockShader == NULL){
                itemNvidiaGraphicsCardClockShader = new QTreeWidgetItem(QStringList()<<"GPU Shader"<<QString::number(g_hardWareNvidiaGPUClock[i].toDouble() , 'f' , 1) + " MHz");
                itemNvidiaGraphicsCardClock->addChild(itemNvidiaGraphicsCardClockShader);
            }
            else{
                itemNvidiaGraphicsCardClockShader->setText(1 , QString::number(g_hardWareNvidiaGPUClock[i].toDouble() , 'f' , 1) + " MHz");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareNvidiaGPUTemp.size() ; i++){
        if(g_hardWareNvidiaGPUTemp[i] == "" || g_hardWareNvidiaGPUTemp[i] == "#"){
            break;
        }
        if(i == 0){
            g_strGPUTemp = QString::number(g_hardWareNvidiaGPUTemp[i].toDouble() , 'f' , 1) + " ℃";
        }
        itemNvidiaGraphicsCardTemp->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemNvidiaGraphicsCardTempCore == NULL){
                itemNvidiaGraphicsCardTempCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareNvidiaGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemAtiGraphicsCardTemp->addChild(itemNvidiaGraphicsCardTempCore);
            }
            else{
                itemNvidiaGraphicsCardTempCore->setText(1 , QString::number(g_hardWareNvidiaGPUTemp[i].toDouble() , 'f' , 1) + " ℃");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareNvidiaGPULoad.size() ; i++){
        if(g_hardWareNvidiaGPULoad[i] == "" || g_hardWareNvidiaGPULoad[i] == "#"){
            break;
        }
        if(i == 0){
            g_strGPUUtil = QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " W";
        }
        itemNvidiaGraphicsCardLoad->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemNvidiaGraphicsCardLoadCore == NULL){
                itemNvidiaGraphicsCardLoadCore = new QTreeWidgetItem(QStringList()<<"GPU Core"<<QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
                itemNvidiaGraphicsCardLoad->addChild(itemNvidiaGraphicsCardLoadCore);
            }
            else{
                itemNvidiaGraphicsCardLoadCore->setText(1 , QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
            }
            break;
        }
        case 1:{
            if(itemNvidiaGraphicsCardLoadFrameBuffer == NULL){
                itemNvidiaGraphicsCardLoadFrameBuffer = new QTreeWidgetItem(QStringList()<<"GPU Frame Buffer"<<QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
                itemNvidiaGraphicsCardLoad->addChild(itemNvidiaGraphicsCardLoadFrameBuffer);
            }
            else{
                itemNvidiaGraphicsCardLoadFrameBuffer->setText(1 , QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
            }
            break;
        }
        case 2:{
            if(itemNvidiaGraphicsCardLoadVideoEngine == NULL){
                itemNvidiaGraphicsCardLoadVideoEngine = new QTreeWidgetItem(QStringList()<<"GPU Video Engine"<<QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
                itemNvidiaGraphicsCardLoad->addChild(itemNvidiaGraphicsCardLoadVideoEngine);
            }
            else{
                itemNvidiaGraphicsCardLoadVideoEngine->setText(1 , QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
            }
            break;
        }
        case 3:{
            if(itemNvidiaGraphicsCardLoadBusInterface == NULL){
                itemNvidiaGraphicsCardLoadBusInterface = new QTreeWidgetItem(QStringList()<<"GPU Bus Interface"<<QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
                itemNvidiaGraphicsCardLoad->addChild(itemNvidiaGraphicsCardLoadBusInterface);
            }
            else{
                itemNvidiaGraphicsCardLoadBusInterface->setText(1 , QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
            }
            break;
        }
        case 4:{
            if(itemNvidiaGraphicsCardLoadMemory == NULL){
                itemNvidiaGraphicsCardLoadMemory = new QTreeWidgetItem(QStringList()<<"GPU Memory"<<QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
                itemNvidiaGraphicsCardLoad->addChild(itemNvidiaGraphicsCardLoadMemory);
            }
            else{
                itemNvidiaGraphicsCardLoadMemory->setText(1 , QString::number(g_hardWareNvidiaGPULoad[i].toDouble() , 'f' , 1) + " %");
            }
            break;
        }
        }
    }

    for(int i = 0 ; i < g_hardWareNvidiaGPUData.size() ; i++){
        if(g_hardWareNvidiaGPUData[i] == "" || g_hardWareNvidiaGPUData[i] == "#"){
            break;
        }
        itemNvidiaGraphicsCardData->setText(1 , "");
        switch (i) {
        case 0:{
            if(itemNvidiaGraphicsCardDataMemoryFree == NULL){
                itemNvidiaGraphicsCardDataMemoryFree = new QTreeWidgetItem(QStringList()<<"GPU Memory Free"<<QString::number(g_hardWareNvidiaGPUData[i].toDouble() , 'f' , 1) + " MB");
                itemNvidiaGraphicsCardData->addChild(itemNvidiaGraphicsCardDataMemoryFree);
            }
            else{
                itemNvidiaGraphicsCardDataMemoryFree->setText(1 , QString::number(g_hardWareNvidiaGPUData[i].toDouble() , 'f' , 1) + " MB");
            }
            break;
        }
        case 1:{
            if(itemNvidiaGraphicsCardDataMemoryUsed == NULL){
                itemNvidiaGraphicsCardDataMemoryUsed = new QTreeWidgetItem(QStringList()<<"GPU Memory Used"<<QString::number(g_hardWareNvidiaGPUData[i].toDouble() , 'f' , 1) + " MB");
                itemNvidiaGraphicsCardData->addChild(itemNvidiaGraphicsCardDataMemoryUsed);
            }
            else{
                itemNvidiaGraphicsCardDataMemoryUsed->setText(1 , QString::number(g_hardWareNvidiaGPUData[i].toDouble() , 'f' , 1) + " MB");
            }
            break;
        }
        case 2:{
            if(itemNvidiaGraphicsCardDataMemoryTotal == NULL){
                itemNvidiaGraphicsCardDataMemoryTotal = new QTreeWidgetItem(QStringList()<<"GPU Memory Total"<<QString::number(g_hardWareNvidiaGPUData[i].toDouble() , 'f' , 1) + " MB");
                itemNvidiaGraphicsCardData->addChild(itemNvidiaGraphicsCardDataMemoryTotal);
            }
            else{
                itemNvidiaGraphicsCardData->setText(1 , QString::number(g_hardWareNvidiaGPUData[i].toDouble() , 'f' , 1) + " MB");
            }
            break;
        }
        }
    }

    for(int i = 0; i < g_hardWareHDDName.size() ; i++){
        if(g_hardWareHDDName[i] == "" || g_hardWareHDDName[i] == "#"){
            break;
        }
        if(itemHardDisk->childCount() <= i){
             QTreeWidgetItem *item = new QTreeWidgetItem(QStringList()<<g_hardWareHDDName[i]);
             if(i >= g_hardWareHDDTemp.size() || i >= g_hardWareHDDLoad.size()){
                 return;
             }
             if(g_hardWareHDDTemp[i] != "" && g_hardWareHDDTemp[i] != "#"){
                 QTreeWidgetItem *itemDiskTemp = new QTreeWidgetItem(QStringList()<<"Temperature"<<QString::number(g_hardWareHDDTemp[i].toDouble() , 'f' , 1) + " ℃");
                 g_strDiskTemp = QString::number(g_hardWareHDDTemp[i].toDouble() , 'f' , 1) + " ℃";
                 item->addChild(itemDiskTemp);
             }
             if(g_hardWareHDDLoad[i] != "" && g_hardWareHDDLoad[i] != "#"){
                 QTreeWidgetItem *itemDiskLoad = new QTreeWidgetItem(QStringList()<<"Used Space"<<QString::number(g_hardWareHDDLoad[i].toDouble() , 'f' , 1) + " %");
                 item->addChild(itemDiskLoad);
             }
             itemHardDisk->addChild(item);
        }
        else{
            itemHardDisk->child(i)->setText(0 , g_hardWareHDDName[i]);
            if(i >= g_hardWareHDDTemp.size() || i >= g_hardWareHDDLoad.size()){
                return;
            }
            if(itemHardDisk->child(i)->childCount() == 1){
                itemHardDisk->child(i)->child(0)->setText(1 , QString::number(g_hardWareHDDLoad[i].toDouble() , 'f' , 1) + " %");
            }
            else if(itemHardDisk->child(i)->childCount() == 2){
                itemHardDisk->child(i)->child(0)->setText(1 , QString::number(g_hardWareHDDTemp[i].toDouble() , 'f' , 1) + " ℃");
                itemHardDisk->child(i)->child(1)->setText(1 , QString::number(g_hardWareHDDLoad[i].toDouble() , 'f' , 1) + " %");
            }
        }
    }

    uiAvailMemory = SystemInfoWin::GetMemoryStat(uiAllMemory);
    memoryRate = 1.0-((double)uiAvailMemory/(double)uiAllMemory);
    usedMemory = ((double)uiAllMemory-(double)uiAvailMemory)/1024/1024;
    availableMemory = (double)uiAvailMemory/1024/1024;

    itemMemoryLoadRate->setText(1 , QString::number(memoryRate*100,'f',1)+" %");
    itemMemoryUsed->setText(1 , QString::number(usedMemory,'f',1)+" GB");
    itemMemoryAvailable->setText(1 , QString::number(availableMemory,'f',1)+" GB");

}

void PCInfoWindow::closeEvent(QCloseEvent *event)
{
    qDebug()<<"close";
    m_signal->exit(0);
}
