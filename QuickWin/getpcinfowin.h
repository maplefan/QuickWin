#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef GETPCINFOWIN_H
#define GETPCINFOWIN_H
#define GB (1024*1024*1024)
#define bzero(a, b) memset(a, 0, b)
#include <QScreen>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSysInfo>
#include "QSettings"
#include "QDebug"
#include <QDesktopWidget>
#include <QFileInfoList>
#include <QDir>
#include <QLibrary>
#include <QTimer>
#include <QHostInfo>
#include <QApplication>
#include <QCoreApplication>
#include <QtCore>
#include <QtNetwork>
#include <QFont>
#include <QJsonParseError>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "iphlpapi.h"

//获得计算机名称
const QString getLocalMachineName();

//获得本地IP地址
const QString getLocalIP();

//获得公网IP
bool getPublicIP(QString& ip);

//获取计算机MAC地址
const QString getMacAddress();

//获取计算机CPU信息
const QString getCpuType();

//获取计算机显卡信息
const QString getGraphicsCard();
QString GetDisplayCardInfo(DWORD &dwNum);

//获取计算机内存
const QString getMemory();

//获取计算机操作系统
const QString getOSVersion();
//获取计算机屏幕个数以及像素
const QString getScreenInfo();

//判断计算机是否可以联网
bool isNetLive();

//获取网页所有源码
QString getHtml(QString url);

QJsonDocument getJsonDocumentFromString(const QString jsonString);

bool getDiskSpace(QString disk , int &availSpace , int &totalSpace);

int getNumberBit(int number);

#endif // GETPCINFOWIN_H
