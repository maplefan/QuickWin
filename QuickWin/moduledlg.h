#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef MODULEDLG_H
#define MODULEDLG_H

#include <QTableView>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <TlHelp32.h>
#include <QStandardItemModel>

typedef struct _ModuleList{
    QString *szModule;
    QString *szExePath;
    QString *modBaseAddr;
    QString *dwSize;
}MODULELIST;

class ModuleDlg : public QTableView
{
    Q_OBJECT

public:
    explicit ModuleDlg(QWidget *parent = 0);
    ModuleDlg(DWORD processID , QWidget *parent = 0);
    ~ModuleDlg();
    DWORD EnumModuleList(DWORD pid , MODULELIST &nModuleList );
    std::string DwordToHexString(DWORD dwDword);
    std::string ByteToHexString(BYTE byte);
    std::string ByteToHexChar(BYTE byte);
    std::string DwordToString(DWORD dw);
    QStandardItem *item0;
    QStandardItem *item1;
    QStandardItem *item2;
    QStandardItem *item3;
    QStandardItemModel* model;
    MODULELIST nModuleList = {};
};

#endif // MODULEDLG_H
