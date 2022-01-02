#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef NETWORKINFO_H
#define NETWORKINFO_H

#include <QMainWindow>
#include <QTableView>
#include <QStandardItemModel>
#include "adapterinfo.h"

namespace Ui {
class NetworkInfo;
}

class NetworkInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetworkInfo(std::vector<NetWorkConection> &adapters , MIB_IFROW* pIfRow , int ac_connection_selected , SYSTEMTIME startTime ,QWidget *parent = nullptr);
    ~NetworkInfo();
    QString getNetworkType(IFTYPE type);
    QString getNetworkStatus(INTERNAL_IF_OPER_STATUS status);
    QString dataSizeToString(unsigned long long size);
    SYSTEMTIME CompareSystemTime(SYSTEMTIME a, SYSTEMTIME b);
    void timerEvent(QTimerEvent *event);

private:
    Ui::NetworkInfo *ui;
    std::vector<NetWorkConection> m_connections;
    MIB_IFROW *m_pIfRow;
    int m_connection_selected; //当前对话框显示的连接
    int m_current_connection; //初始选择的连接
    SYSTEMTIME m_startTime;//程序开始时间
    QStandardItemModel *model;
};

#endif // NETWORKINFO_H
