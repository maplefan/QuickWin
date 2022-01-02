#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "quickstock.h"
#include "ui_quickstock.h"

QuickStock::QuickStock(QSystemTrayIcon *qsti ,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::QuickStock)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("自选股"));
    this->qsti = qsti;
    stockShow = Config().Get("Setting" , "StockShow").toInt();
    model = new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem((tr("股票"))));
    model->setHorizontalHeaderItem(1, new QStandardItem((tr("最新价"))));
    model->setHorizontalHeaderItem(2, new QStandardItem((tr("涨跌额"))));
    model->setHorizontalHeaderItem(3, new QStandardItem((tr("涨跌幅"))));
    //利用setModel()方法将数据模型与QTableView绑定
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tableView->setColumnWidth(0,100);
    ui->tableView->setColumnWidth(1,60);
    ui->tableView->setColumnWidth(2,55);
    ui->tableView->setColumnWidth(3,55);

    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->verticalHeader()->hide();
    //排序功能
    ui->tableView->setSortingEnabled(true);

    m_stockMenu = new QMenu(this);
    m_stockMenu->addAction((tr("置顶")), this, SLOT(slot_itemToTop()));
    m_stockMenu->addAction((tr("新增")), this, SLOT(slot_addItem()));
    m_stockMenu->addAction((tr("删除")), this, SLOT(slot_deleteItem()));
    m_stockMenu->addAction((tr("浏览器打开")), this, SLOT(slot_open()));
    m_stockMenu->addAction((tr("设置提醒")), this, SLOT(slot_remind()));

    stockConfig = Config().Get("Main" , "stock").toString();
    qDebug()<<"**********"<<stockConfig;

    m_signal.setStockList(stockConfig);
    firstDealStockInfo();
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(slotContextMenu(QPoint)));
    connect(&timer , SIGNAL(timeout()) , this , SLOT(OnTimerout()));
    connect(&m_signal , &CStockSignal::statusChanged , this , &QuickStock::getStockData);
    m_signal.start();
    timer.start(5000);
}

QuickStock::~QuickStock()
{
    timer.stop();
    m_signal.exit();
    delete ui;
}

//更新界面
void QuickStock::dealStockInfo(QString stockData , QString stockInfo)
{
    stockList = stockData.split(";");
    stockInfoList = stockInfo.split(",");
    qDebug()<<"stockList[0]"<<stockList[0];
    for(int i = 0; i < stockList.size()-1 ;i++){
        QStringList stockInfo = stockList[i].split("~");
        qDebug()<<"stockInfo[1]"<<stockInfo[1];
        if(stockInfoList.size() <= i){
            return;
        }
        if(stockInfoList[i].mid(2,2) == "hk"){//港股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/hk.png"),stockInfo[1]);
            model->setItem(i ,0 ,itemName);
        }
        else if(stockInfoList[i].mid(2,2) == "us"){//美股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/us.png"),stockInfo[1]);
            model->setItem(i ,0 ,itemName);
        }
        else if(stockInfoList[i].mid(2,2) == "sh" || stockInfoList[i].mid(2,2) == "sz"){//A股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/cn.png"),stockInfo[1]);
            model->setItem(i ,0 ,itemName);
        }
        QStandardItem *itemNowPrice = new QStandardItem(stockInfo[3]);
        model->setItem(i ,1 ,itemNowPrice);
        if(stockInfo[4].toDouble() > 0){
            stockInfo[4] = "+" + stockInfo[4];
        }
        if(stockInfo[5].toDouble() > 0){
            stockInfo[5] = "+" + stockInfo[5];
        }
        QStandardItem *itemPriceChange = new QStandardItem(stockInfo[4]);
        model->setItem(i ,2 ,itemPriceChange);
        QStandardItem *itemPriceChangeRate = new QStandardItem(stockInfo[5]+"%");
        model->setItem(i ,3 ,itemPriceChangeRate);
        //涨
        if(stockInfo[4].toDouble() > 0){
            if(stockShow == 0){
                model->item(i , 0)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 1)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 2)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 3)->setForeground(QBrush(QColor(253, 78, 80)));
            }
            else if(stockShow == 1){
                model->item(i , 0)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 1)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 2)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 3)->setForeground(QBrush(QColor(30, 200, 4)));
            }
        }
        //跌
        else if(stockInfo[4].toDouble() < 0){
            if(stockShow == 0){
                model->item(i , 0)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 1)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 2)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 3)->setForeground(QBrush(QColor(30, 200, 4)));
            }
            else if(stockShow == 1){
                model->item(i , 0)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 1)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 2)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 3)->setForeground(QBrush(QColor(253, 78, 80)));
            }
        }
        //平
        else{
            model->item(i , 0)->setForeground(QBrush(QColor(0, 0, 0)));
            model->item(i , 1)->setForeground(QBrush(QColor(0, 0, 0)));
            model->item(i , 2)->setForeground(QBrush(QColor(0, 0, 0)));
            model->item(i , 3)->setForeground(QBrush(QColor(0, 0, 0)));
        }
        //跌
        ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,60);
        ui->tableView->setColumnWidth(2,55);
        ui->tableView->setColumnWidth(3,55);
        for(int j = 0; j < sr.size() ;j++){
            qDebug()<<"*****"<<j;
            if(sr[j].stockCode == stockInfo[1]){
                if(sr[j].info == "rate"){
                    if(sr[j].data.toDouble() <= 0 && stockInfo[5].toDouble() <= sr[j].data.toDouble() ){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的上涨")+sr[j].data+"%");
                        sr.erase(sr.begin()+j);
                        qDebug()<<stockInfo[1]+tr("的股价已达到您设置的上涨")+sr[j].data+"%";
                    }
                    else if(sr[j].data.toDouble() >= 0 && stockInfo[5].toDouble() >= sr[j].data.toDouble()){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的下跌")+sr[j].data+"%");
                        sr.erase(sr.begin()+j);
                        qDebug()<<stockInfo[1]+tr("的股价已达到您设置的下跌")+sr[j].data+"%";
                    }
                }
                else if(sr[j].info == "rise"){
                    qDebug()<<stockInfo[3].toDouble()<<" "<<sr[j].data.toDouble();
                    if(stockInfo[3].toDouble() >= sr[j].data.toDouble()){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的股价：")+sr[j].data);
                        sr.erase(sr.begin()+j);
                    }
                }
                else if(sr[j].info == "fall"){
                    if(stockInfo[3].toDouble() <= sr[j].data.toDouble()){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的股价：")+sr[j].data);
                        sr.erase(sr.begin()+j);    
                    }
                }
            }
        }
    }
}

//更新界面
void QuickStock::dealStockInfo()
{
    for(int i = 0; i < stockList.size()-1 ;i++){
        if(stockList[i] == ""){
            return ;
        }
        QStringList stockInfo = stockList[i].split("~");
        if(stockInfoList[i].mid(2,2) == "hk"){//港股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/hk.png"),stockInfo[1]);
            model->setItem(i ,0 ,itemName);
        }
        else if(stockInfoList[i].mid(2,2) == "us"){//美股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/us.png"),stockInfo[1]);
            model->setItem(i ,0 ,itemName);
        }
        else if(stockInfoList[i].mid(2,2) == "sh" || stockInfoList[i].mid(2,2) == "sz"){//A股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/cn.png"),stockInfo[1]);
            model->setItem(i ,0 ,itemName);
        }
        QStandardItem *itemNowPrice = new QStandardItem(stockInfo[3]);
        model->setItem(i ,1 ,itemNowPrice);
        if(stockInfo[4].toDouble() > 0){
            stockInfo[4] = "+" + stockInfo[4];
        }
        if(stockInfo[5].toDouble() > 0){
            stockInfo[5] = "+" + stockInfo[5];
        }
        QStandardItem *itemPriceChange = new QStandardItem(stockInfo[4]);
        model->setItem(i ,2 ,itemPriceChange);
        QStandardItem *itemPriceChangeRate = new QStandardItem(stockInfo[5]+"%");
        model->setItem(i ,3 ,itemPriceChangeRate);
        //涨
        if(stockInfo[4].toDouble() > 0){
            if(stockShow == 0){
                model->item(i , 0)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 1)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 2)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 3)->setForeground(QBrush(QColor(253, 78, 80)));
            }
            else if(stockShow == 1){
                model->item(i , 0)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 1)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 2)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 3)->setForeground(QBrush(QColor(30, 200, 4)));
            }
        }
        //跌
        else if(stockInfo[4].toDouble() < 0){
            if(stockShow == 0){
                model->item(i , 0)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 1)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 2)->setForeground(QBrush(QColor(30, 200, 4)));
                model->item(i , 3)->setForeground(QBrush(QColor(30, 200, 4)));
            }
            else if(stockShow == 1){
                model->item(i , 0)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 1)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 2)->setForeground(QBrush(QColor(253, 78, 80)));
                model->item(i , 3)->setForeground(QBrush(QColor(253, 78, 80)));
            }
        }
        //平
        else{
            model->item(i , 0)->setForeground(QBrush(QColor(0, 0, 0)));
            model->item(i , 1)->setForeground(QBrush(QColor(0, 0, 0)));
            model->item(i , 2)->setForeground(QBrush(QColor(0, 0, 0)));
            model->item(i , 3)->setForeground(QBrush(QColor(0, 0, 0)));
        }

        ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,60);
        ui->tableView->setColumnWidth(2,55);
        ui->tableView->setColumnWidth(3,55);
        for(int j = 0; j < sr.size() ;j++){
            if(sr[j].stockCode == stockInfo[1]){
                if(sr[j].info == "rate"){
                    if(sr[j].data.toDouble() <= 0 && stockInfo[5].toDouble() <= sr[j].data.toDouble() ){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的上涨")+sr[j].data+"%");
                        sr.erase(sr.begin()+j);
                    }
                    else if(sr[j].data.toDouble() >= 0 && stockInfo[5].toDouble() >= sr[j].data.toDouble()){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的下跌")+sr[j].data+"%");
                        sr.erase(sr.begin()+j);
                    }
                }
                else if(sr[j].info == "rise"){
                    if(stockInfo[3].toDouble() >= sr[j].data.toDouble()){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的股价：")+sr[j].data);
                        sr.erase(sr.begin()+j);
                    }
                }
                else if(sr[j].info == "fall"){
                    if(stockInfo[3].toDouble() <= sr[j].data.toDouble()){
                        //提示
                        this->qsti->showMessage(tr("提醒"), stockInfo[1]+tr("的股价已达到您设置的股价：")+sr[j].data);
                        sr.erase(sr.begin()+j);
                    }
                }
            }
        }
    }
}

//第一次更新界面
void QuickStock::firstDealStockInfo()
{
    QStringList stockName = stockConfig.split(",");
    for(int i = 0; i < stockName.size() ;i++){
        if(stockName[i].mid(2,2) == "hk"){//港股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/hk.png"),stockName[i]);
            model->setItem(i ,0 ,itemName);
        }
        else if(stockName[i].mid(2,2) == "us"){//美股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/us.png"),stockName[i]);
            model->setItem(i ,0 ,itemName);
        }
        else if(stockName[i].mid(2,2) == "sh" || stockInfoList[i].mid(2,2) == "sz"){//A股
            QStandardItem *itemName = new QStandardItem(QIcon(":images/cn.png"),stockName[i]);
            model->setItem(i ,0 ,itemName);
        }
        QStandardItem *itemNowPrice = new QStandardItem(tr("加载中..."));
        model->setItem(i ,1 ,itemNowPrice);
        QStandardItem *itemPriceChange = new QStandardItem(tr("加载中..."));
        model->setItem(i ,2 ,itemPriceChange);
        QStandardItem *itemPriceChangeRate = new QStandardItem(tr("加载中..."));
        model->setItem(i ,3 ,itemPriceChangeRate);

        model->item(i , 0)->setForeground(QBrush(QColor(56, 56, 56)));
        model->item(i , 1)->setForeground(QBrush(QColor(56, 56, 56)));
        model->item(i , 2)->setForeground(QBrush(QColor(56, 56, 56)));
        model->item(i , 3)->setForeground(QBrush(QColor(56, 56, 56)));

        ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
        ui->tableView->setColumnWidth(0,100);
        ui->tableView->setColumnWidth(1,60);
        ui->tableView->setColumnWidth(2,55);
        ui->tableView->setColumnWidth(3,55);
    }
}

void QuickStock::closeEvent(QCloseEvent *event)
{
    if(timer.isActive()){
        timer.stop();
    }
        m_signal.exit();
}

void QuickStock::OnTimerout()
{
    qDebug()<<"QuickStock"<<QThread::currentThreadId();
}

void QuickStock::getStockData(QString stockData , QString stockInfo)
{
    dealStockInfo(stockData , stockInfo);
}

void QuickStock::slotContextMenu(QPoint pos)
{
   selectIndex = ui->tableView->indexAt(pos);
   m_stockMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}

void QuickStock::slot_open()
{
    if(selectIndex.isValid()){
        if(selectIndex.row() < stockInfoList.size()){
             QDesktopServices::openUrl(QUrl("https://www.laohu8.com/stock/" + stockInfoList[selectIndex.row()].mid( 4 , stockInfoList[selectIndex.row()].length()-4)));
        }
    }
}

void QuickStock::slot_remind()
{
    if(selectIndex.isValid()){
        if(selectIndex.row() < stockInfoList.size()){
            StockRemindDialog *srd = new StockRemindDialog( stockList[selectIndex.row()] , this );
            connect(srd , SIGNAL(sendData(QString , QString , QString)) , this , SLOT(recvStockRemindDialogData(QString , QString , QString )));
            srd->show();
        }
    }
}

void QuickStock::slot_addItem()
{
    AddStockDialog *asd = new AddStockDialog( stockConfig , this );
    connect(asd , SIGNAL(sendData(QString)) , this , SLOT(recvAddStockDialogData(QString)));
    asd->show();
}

void QuickStock::recvAddStockDialogData(QString data){
    qDebug()<<"recvAddStockDialogData"<<data;
    if(data == "cn"){
        QMessageBox::about(this, tr("提示"), tr("请检查A股代码！"));
        return;
    }
    else if(data == "hk"){
        QMessageBox::about(this, tr("提示"), tr("请检查港股代码！"));
        return;
    }
    else if(data == "repeat"){
        QMessageBox::about(this, tr("提示"), tr("您添加的股票代码已经存在！"));
        return;
    }
    else if(data == "us"){
        QMessageBox::about(this, tr("提示"), tr("请检查美股代码！"));
        return;
    }
    //上海交易所的股票代码以600、601、603开头，深圳交易所的股票代码以000、002、003开头，创业板的股票代码以300开头（深圳交易所上市），科创板的股票代码以688开头（上海交易所上市）
    stockInfoList.append(data);
    QStringList stockConfigList = stockConfig.split(",");
    stockConfigList.append(data);
    QString tmp0 = "\nv_s_usBIDU=\"200~百度~BIDU.OQ~226.31~4.31~1.94~4972706~1117881078~759.55965~\"";
    stockList.append( tmp0);
    QStringList tmp1;
    for(int i = 0; i < stockConfigList.size() ;i++)
    {
        tmp1<<stockConfigList[i];
    }
    QString tmp2 = tmp1.join(",");
    stockConfig = tmp2;
    m_signal.setStockList(tmp2);
    Config().Set("Main" , "stock" , tmp2);
    firstDealStockInfo();//更新界面
}

void QuickStock::slot_itemToTop()
{
    if(selectIndex.isValid()){
        if(selectIndex.row() < stockInfoList.size()){
            QString tmp1 = stockInfoList[selectIndex.row()];
            stockInfoList.removeAt(selectIndex.row());
            stockInfoList.insert(0 , tmp1);
            qDebug()<<"tmp1"<<tmp1;
            QString tmp2 = stockList[selectIndex.row()];
            stockList.removeAt(selectIndex.row());
            stockList.insert(0 , tmp2);
            qDebug()<<"tmp2"<<tmp2;
            QStringList stockConfigList = stockConfig.split(",");
            QString tmp3 = stockConfigList[selectIndex.row()];
            stockConfigList.removeAt(selectIndex.row());
            stockConfigList.insert(0, tmp3);
            qDebug()<<"tmp3"<<tmp3;

            QStringList tmp4;
            for(int i = 0; i < stockConfigList.size() ;i++)
            {
                tmp4<<stockConfigList[i];
            }
            QString tmp5 = tmp4.join(",");
            qDebug()<<"tmp4"<<tmp4;
            stockConfig = tmp5;
            qDebug()<<"tmp5"<<tmp5;
            m_signal.setStockList(tmp5);
            Config().Set("Main" , "stock" , tmp5);
            dealStockInfo();//更新界面
        }
    }
}

void QuickStock::slot_deleteItem()
{
    if(selectIndex.isValid()){
        if(selectIndex.row() < stockInfoList.size()){
            stockInfoList.removeAt(selectIndex.row());
            stockList.removeAt(selectIndex.row());

            QStringList stockConfigList = stockConfig.split(",");
            stockConfigList.removeAt(selectIndex.row());

            QStringList tmp;
            for(int i = 0; i < stockConfigList.size() ;i++)
            {
                tmp<<stockConfigList[i];
            }
            QString tmp1 = tmp.join(",");
            stockConfig = tmp1;
            m_signal.setStockList(tmp1);
            Config().Set("Main" , "stock" , tmp1);
            model->removeRow(selectIndex.row());
            dealStockInfo();//更新界面
        }
    }
}

void QuickStock::recvStockRemindDialogData(QString stockCode , QString info , QString data){
    stockRemind recvSr;
    recvSr.stockCode = stockCode;
    recvSr.info = info;
    recvSr.data = data;
    sr.push_back(recvSr);
    qDebug()<<stockCode<<" "<<info<<" "<<data;
}
