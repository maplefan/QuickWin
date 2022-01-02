#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


#include "moduledlg.h"
#include <QDebug>

std::string ModuleDlg::DwordToString(DWORD dw)
{
    using namespace std;

    const int n = snprintf(NULL, 0, "%lu", dw);
    vector<char> buf(n + 1);
    if (n < 0) {
        return "";
    }
    int c = snprintf(&buf[0], n + 1, "%lu", dw);
    string str(&buf[0]);
    return str;
}

std::string ModuleDlg::DwordToHexString(DWORD dwDword)
{
    return	ByteToHexString((dwDword >> 24) & 0xFF) +
            ByteToHexString((dwDword >> 16) & 0xFF) +
            ByteToHexString((dwDword >> 8) & 0xFF) +
            ByteToHexString(dwDword & 0xFF);
}

std::string ModuleDlg::ByteToHexString(BYTE byte)
{
    std::string ret = "";

    BYTE char1 = (byte & 0x0F);
    BYTE char2 = (byte & 0xF0) >> 4;

    ret = ret + ByteToHexChar(char2) + ByteToHexChar(char1);
    return ret;
}

std::string ModuleDlg::ByteToHexChar(BYTE byte)
{
    std::string	hexChar = "";

    if(byte >= 0 && byte <= 9)
    {
        // 48 == ASCII Zero
        hexChar += (char) (byte + 48);
    }
    else if(byte >= 10 && byte <= 15)
    {
        // 97 = ASCII 'a' (small a)
        hexChar += (char) (byte + 97 - 10);
    }
    else
    {
        hexChar = "?";
    }
    return hexChar;
}

ModuleDlg::ModuleDlg(QWidget *parent) :
    QTableView(parent)
{
    model = new QStandardItemModel(this);
    this->setModel(model);
}

ModuleDlg::ModuleDlg(DWORD processID , QWidget *parent ) :
    QTableView(parent)
{
    this->setMinimumSize(700 , 400);
    DWORD index = EnumModuleList(processID , nModuleList);
    QStandardItemModel* model = new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0, new QStandardItem(tr("模块名")));
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("模块路径")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("模块地址")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("模块大小（B）")));
    for(int i = 0; i < index ;i++){
        item0 = new QStandardItem(nModuleList.szModule[i]);
        model->setItem(i, 0 , item0);
        item0->setData(nModuleList.szModule[i] , Qt::ToolTipRole);

        item1 = new QStandardItem(nModuleList.szExePath[i]);
        model->setItem(i, 1 , item1);
        item1->setData(nModuleList.szExePath[i] , Qt::ToolTipRole);

        item2 = new QStandardItem(nModuleList.modBaseAddr[i]);
        model->setItem(i, 2 , item2);
        item2->setData(nModuleList.modBaseAddr[i] , Qt::ToolTipRole);

        item3 = new QStandardItem(nModuleList.dwSize[i]);
        model->setItem(i, 3 , item3);
        item3->setData(nModuleList.dwSize[i] , Qt::ToolTipRole);
       /*

        model->setItem(i, 0, new QStandardItem(nModuleList.szModule[i]));
        model->setItem(i, 1, new QStandardItem(nModuleList.szExePath[i]));
        model->setItem(i, 2, new QStandardItem(nModuleList.modBaseAddr[i]));
        model->setItem(i, 3, new QStandardItem(nModuleList.dwSize[i]));*/
    }
    // 整行选中
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    // 不可编辑
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setStyleSheet("QTableView{border:none;background:white;}");
    this->setStyleSheet("QTableView::item:selected{color:white;background:rgb(34, 175, 75);}");
    this->setSortingEnabled(true);//允许点击表头排序
    this->setModel(model);
    this->setColumnWidth( 0 , 120);
    this->setColumnWidth( 1 , 310);
    this->setColumnWidth( 2 , 100);
    this->setColumnWidth( 3 , 110);
}

DWORD ModuleDlg::EnumModuleList(DWORD pid , MODULELIST &nModuleList){
    bool nRet;
    DWORD nIndex = 0;
    MODULEENTRY32 nModule;

    nModule.dwSize = sizeof(MODULEENTRY32);
    HANDLE nSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);

    nRet = Module32First(nSnapShot, &nModule);
    while (nRet)
    {
        nRet = Module32Next(nSnapShot, &nModule);
        nIndex++;
    }

    nModuleList.szModule = new QString[nIndex];
    nModuleList.szExePath = new QString[nIndex];
    nModuleList.modBaseAddr = new QString[nIndex];
    nModuleList.dwSize = new QString[nIndex];

    nIndex = 0;
    nRet = Module32First(nSnapShot, &nModule);
    while (nRet)
    {
        nModuleList.szModule[nIndex] = QString::fromWCharArray(nModule.szModule);
        nModuleList.szExePath[nIndex] = QString::fromWCharArray(nModule.szExePath);
        nModuleList.modBaseAddr[nIndex] = QString::fromStdString("0x"+DwordToHexString((DWORD)nModule.modBaseAddr));
        nModuleList.dwSize[nIndex] = QString::fromStdString(DwordToString((DWORD)nModule.modBaseSize));

        nRet = Module32Next(nSnapShot, &nModule);
        nIndex++;
    }
    CloseHandle(nSnapShot);
    return nIndex;
}

ModuleDlg::~ModuleDlg()
{
    delete model;
    delete item0;
    delete item1;
    delete item2;
    delete item3;
    delete []nModuleList.szModule;
    delete []nModuleList.szExePath;
    delete []nModuleList.modBaseAddr;
    delete []nModuleList.dwSize;
}
