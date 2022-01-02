#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef PCINFOWINDOW_H
#define PCINFOWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QTreeWidgetItem>
#include <QMessageBox>
#include <QCloseEvent>
#include "CSignal.h"
#include "getpublicipthread.h"

namespace Ui {
class PCInfoWindow;
}

class PCInfoWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PCInfoWindow(QWidget *parent = 0);
    ~PCInfoWindow();
    void timerEvent(QTimerEvent *event);
    void closeEvent(QCloseEvent *event);

    //*******PC Name*******//
    QTreeWidgetItem *itemPCName;

    //*******IO*******//
    QTreeWidgetItem *itemMainBoard;

    //*******IO Name*******//
    QTreeWidgetItem *itemMainBoardName;

    //*******IO Voltage*******//
    QTreeWidgetItem *itemMainBoardVoltage;
    QTreeWidgetItem *itemMainBoardVoltageCPUVCore;
    QTreeWidgetItem *itemMainBoardVoltageAVCC;
    QTreeWidgetItem *itemMainBoardVoltage3VCC;
    QTreeWidgetItem *itemMainBoardVoltage3VSB;
    QTreeWidgetItem *itemMainBoardVoltageVBAT;
    QTreeWidgetItem *itemMainBoardVoltageVTT;

    //*******IO Temp*******//
    QTreeWidgetItem *itemMainBoardTemp;

    //*******IO Fans*******//
    QTreeWidgetItem *itemMainBoardFans;

    //*******IO Fans Control*******//
    QTreeWidgetItem *itemMainBoardControl;

    //*******IO SuperIO*******//
    QTreeWidgetItem *itemMainBoardSuperIO;

    //*******CPU*******//
    QTreeWidgetItem *itemCPU;

    //*******CPU Name*******//
    QTreeWidgetItem *itemCPUName;

    //*******CPU Power*******//
    QTreeWidgetItem *itemCPUPower;
    QTreeWidgetItem *itemCPUPowerPackage;
    QTreeWidgetItem *itemCPUPowerCores;
    QTreeWidgetItem *itemCPUPowerGraphics;
    QTreeWidgetItem *itemCPUPowerDRAM;

    //*******CPU Load*******//
    QTreeWidgetItem *itemCPULoad;

    //*******CPU Clock*******//
    QTreeWidgetItem *itemCPUClock;

    //*******CPU Temp*******//
    QTreeWidgetItem *itemCPUTemp;

    //*******Graphics Card*******//
    QTreeWidgetItem *itemGraphicsCard;

    //*******Ati Graphics Card Name*******//
    QTreeWidgetItem *itemAtiGraphicsCardName;

    //*******Ati Graphics Card Clock*******//
    QTreeWidgetItem *itemAtiGraphicsCardClock;
    QTreeWidgetItem *itemAtiGraphicsCardClockCore;
    QTreeWidgetItem *itemAtiGraphicsCardClockMemory;

    //*******Ati Graphics Card Load*******//
    QTreeWidgetItem *itemAtiGraphicsCardLoad;
    QTreeWidgetItem *itemAtiGraphicsCardLoadCore;

    //*******Ati Graphics Card Data*******//
    QTreeWidgetItem *itemAtiGraphicsCardData;

    //*******Ati Graphics Card Power*******//
    QTreeWidgetItem *itemAtiGraphicsCardPower;
    QTreeWidgetItem *itemAtiGraphicsCardPowerTotal;

    //*******Ati Graphics Card Temp*******//
    QTreeWidgetItem *itemAtiGraphicsCardTemp;
    QTreeWidgetItem *itemAtiGraphicsCardTempCore;
    QTreeWidgetItem *itemAtiGraphicsCardTempMemory;
    QTreeWidgetItem *itemAtiGraphicsCardTempVRMCore;
    QTreeWidgetItem *itemAtiGraphicsCardTempVRMMemory;
    QTreeWidgetItem *itemAtiGraphicsCardTempLiquid;
    QTreeWidgetItem *itemAtiGraphicsCardTempPLX;
    QTreeWidgetItem *itemAtiGraphicsCardTempHotSpot;

    //*******Ati Graphics Card Control*******//
    QTreeWidgetItem *itemAtiGraphicsCardControl;

    //*******Ati Graphics Card Voltage*******//
    QTreeWidgetItem *itemAtiGraphicsCardVoltage;
    QTreeWidgetItem *itemAtiGraphicsCardVoltageCore;

    //*******Nvidia Graphics Card Name*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardName;

    //*******Nvidia Graphics Card Clock*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardClock;
    QTreeWidgetItem *itemNvidiaGraphicsCardClockCore;
    QTreeWidgetItem *itemNvidiaGraphicsCardClockMemory;
    QTreeWidgetItem *itemNvidiaGraphicsCardClockShader;

    //*******Nvidia Graphics Card Load*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardLoad;
    QTreeWidgetItem *itemNvidiaGraphicsCardLoadCore;
    QTreeWidgetItem *itemNvidiaGraphicsCardLoadFrameBuffer;
    QTreeWidgetItem *itemNvidiaGraphicsCardLoadVideoEngine;
    QTreeWidgetItem *itemNvidiaGraphicsCardLoadBusInterface;
    QTreeWidgetItem *itemNvidiaGraphicsCardLoadMemory;

    //*******Nvidia Graphics Card Data*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardData;
    QTreeWidgetItem *itemNvidiaGraphicsCardDataMemoryFree;
    QTreeWidgetItem *itemNvidiaGraphicsCardDataMemoryUsed;
    QTreeWidgetItem *itemNvidiaGraphicsCardDataMemoryTotal;

    //*******Nvidia Graphics Card Power*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardPower;
    QTreeWidgetItem *itemNvidiaGraphicsCardPowerTotal;

    //*******Nvidia Graphics Card Temp*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardTemp;
    QTreeWidgetItem *itemNvidiaGraphicsCardTempCore;

    //*******Nvidia Graphics Card Control*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardControl;

    //*******Nvidia Graphics Card Voltage*******//
    QTreeWidgetItem *itemNvidiaGraphicsCardVoltage;
    QTreeWidgetItem *itemNvidiaGraphicsCardVoltageCore;

    //*******Memory*******//
    QTreeWidgetItem *itemMemory;

    //*******Memory Load*******//
    QTreeWidgetItem *itemMemoryLoad;
    QTreeWidgetItem *itemMemoryLoadRate;
    //*******Memory Data*******//
    QTreeWidgetItem *itemMemoryData;
    QTreeWidgetItem *itemMemoryUsed;
    QTreeWidgetItem *itemMemoryAvailable;

    //*******Disk*******//
    QTreeWidgetItem *itemHardDisk;

    //*******Disk Name*******//
    QTreeWidgetItem *itemHardDiskName;

    //*******Disk Load*******//
    QTreeWidgetItem *itemHardDiskLoad;

    //*******Disk Temp*******//
    QTreeWidgetItem *itemHardDiskTemp;

    //*******Disk Data*******//
    QTreeWidgetItem *itemHardDiskData;

    //*******MacAddress*******//
    QTreeWidgetItem *itemMacAddress;

    //*******LocalIP*******//
    QTreeWidgetItem *itemLocalIP;

    //*******PublicIP*******//
    QTreeWidgetItem *itemPublicIP;

    unsigned int uiAllMemory = 0;
    unsigned int uiAvailMemory = 0;
    double memoryRate;
    double usedMemory;
    double availableMemory;

private:
    Ui::PCInfoWindow *ui;

    CSignal *m_signal;
    GetPublicIPThread *ch;

private slots:
    void updateUI(QString str);
    void OnTimerout();
    void getStatusChanged(QString CPUInfo , QString HDDInfo , QString AtiGPUInfo , QString NvidiaGPUInfo , QString IOInfo);
};

typedef struct {
    QString name;
    int availableDisk;
    int totalDisk;
}diskInfo;
#endif // PCINFOWINDOW_H
