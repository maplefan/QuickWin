#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef CSTOCKSIGNAL_H
#define CSTOCKSIGNAL_H

#include <QThread>
#include <QTimer>
#include <QLibrary>
#include <QMessageBox>
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

class CStockTimerSlot : public QObject
{
    Q_OBJECT
public:
    CStockTimerSlot(QObject * parent = 0);
    void setStockList(QString list);
    QString getStockList();
public slots:
    void OnTimerout();

signals:
    void statusChanged(QString stockData , QString stockInfo);

private:
    QString stockList;
};

class CStockSignal : public QThread
{
    Q_OBJECT
public:
    CStockSignal(QObject * parent = 0);
    ~CStockSignal();
    void setStockList(QString str);

protected:
    virtual void run();
    CStockTimerSlot *m_timerSlot;
    QTimer *m_timer;
    QString stockList;

signals:
    void statusChanged(QString stockData , QString stockInfo);
};

#endif // CSTOCKSIGNAL_H
