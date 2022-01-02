#include "timereminder.h"
#include "ui_timereminder.h"

TimeReminder::TimeReminder(QSystemTrayIcon *qsti , QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimeReminder)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->qsti = qsti;
    this->setWindowTitle(tr("定时提醒"));
    remindModel = new QStandardItemModel();
    remindView = this->ui->treeView;
    remindView->setStyleSheet("QTreeView::item{height: 60px;}");
    remindView->header()->setSortIndicator(-1, Qt::AscendingOrder);
    remindView->header()->setStretchLastSection(false);
    remindView->setSortingEnabled(true);
    remindView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList nameList;
    nameList<<tr("事件")<<tr("倒计时")<<tr("提醒时间")<<tr("备注");
    remindView->setColumnWidth(0,150);
    remindView->setColumnWidth(1,100);
    remindView->setColumnWidth(2,100);
    remindView->setColumnWidth(3,100);

    remindModel->setHorizontalHeaderLabels(nameList);
    remindView->setModel(remindModel);

    //信号槽，右键菜单
    remindView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(remindView, &QTreeView::customContextMenuRequested, this, &TimeReminder::slotTreeMenu);

    addAction = remindMenu.addAction(tr("添加"), this, SLOT(slotTreeMenuAdd()));
    editAction = remindMenu.addAction(tr("编辑"), this, SLOT(slotTreeMenuEdit()));
    deleteAction = remindMenu.addAction(tr("删除"), this, SLOT(slotTreeMenuDelete()));

    md = remindView->selectionModel();
    if(md){
        connect(md,&QItemSelectionModel::selectionChanged,this,&TimeReminder::viewSelectCheck);
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("reminder.db");
    if (db.open()) {
        QSqlQuery query;

        query.exec(QString("select count(*) from sqlite_master where type='table' and name='%1'").arg("timer_reminder"));
        if(query.next())
        {
             if(query.value(0).toInt()==0)
             {
                 // 表不存在
                 // 创建登录用户表
                 qDebug()<<"创建登录用户表";
                 query.exec("create table timer_reminder ("
                            "id INTEGER , "
                            "remindType INTEGER , "
                            "remindWeek INTEGER , "
                            "dateTime INTEGER , "
                            "remindEvent TEXT , "
                            "remindDuration INTEGER , "
                            "remindSound TEXT , "
                            "remindPic TEXT , "
                            "remindRemarks TEXT , "
                            "remindTimeStr TEXT)");
                 if(!query.exec())
                 {
                     qDebug() << query.lastError();
                     query.finish();
                 }
                 else
                 {
                     query.finish();
                     qDebug() << "create Sucess!";
                 }
             }
             else
             {
                 //表存在
                 //读取表中数据
                 qDebug()<<"读取表中数据";
                 QString select_sql = "select id , remindType, remindWeek , dateTime , remindEvent , remindDuration , remindSound , remindPic , remindRemarks , remindTimeStr from timer_reminder";
                 if(!query.exec(select_sql))
                 {
                     qDebug()<<query.lastError();
                 }
                 else
                 {
                     while(query.next())
                     {
                         int id = query.value(0).toInt();
                         int remindType = query.value(1).toInt();
                         int remindWeek = query.value(2).toInt();
                         QDateTime dateTime = QDateTime::fromTime_t(query.value(3).toUInt());
                         QString remindEvent = query.value(4).toString();
                         int remindDuration = query.value(5).toInt();
                         QString remindSound = query.value(6).toString();
                         QString remindPic = query.value(7).toString();
                         QString remindRemarks = query.value(8).toString();
                         QString remindTimeStr = query.value(9).toString();
                         ReminderInfo info;
                         info.id = id;
                         info.remindType = remindType;
                         info.remindWeek = remindWeek;
                         info.dateTime = dateTime;
                         info.remindEvent = remindEvent;
                         info.remindDuration = remindDuration;
                         info.remindSound = remindSound;
                         info.remindPic = remindPic;
                         info.remindRemarks = remindRemarks;
                         info.remindTimeStr = remindTimeStr;
                         ri.push_back(info);
                     }
                 }
                 query.finish();
             }
        }
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(1000);
    isStopUpdate = false;
}

TimeReminder::~TimeReminder()
{
    delete ui;
}

void TimeReminder::slotTreeMenu(const QPoint &pos)
{    
    remindMenu.exec(QCursor::pos());  //显示菜单
    isStopUpdate = false;
}

void TimeReminder::slotTreeMenuEdit()
{
    QModelIndex curIndex = ui->treeView->currentIndex();    //当前点击的元素的index
    if(curIndex.isValid()){
            TimeRemindDialog *trdlg = new TimeRemindDialog(ri[curIndex.row()] , curIndex.row() , this);
            connect(trdlg , SIGNAL(sendRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString)) , this , SLOT(getRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString)));
            connect(trdlg , SIGNAL(sendRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString , int)) , this , SLOT(getRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString , int)));
            trdlg->exec();
    }
    isStopUpdate = false;
}

void TimeReminder::slotTreeMenuDelete()
{
    QModelIndex curIndex = ui->treeView->currentIndex();    //当前点击的元素的index
    if(curIndex.isValid()){
        if (db.open()) {
            QSqlQuery query;
            QString insert_sql = "delete from timer_reminder where id = ?";
            query.prepare(insert_sql);
            query.addBindValue(ri[curIndex.row()].id);
            qDebug()<<"index id:"<<ri[curIndex.row()].id;
            if(!query.exec())
            {
                qDebug() << query.lastError();
                query.finish();
            }
            else
            {
                qDebug() << "deleted Sucess!";
                query.finish();
            }
        }
        remindModel->removeRow(curIndex.row());
        ri.erase(ri.begin()+curIndex.row());
    }
    isStopUpdate = false;
}

void TimeReminder::slotTreeMenuAdd()
{
    TimeRemindDialog *trdlg = new TimeRemindDialog(this);
    connect(trdlg , SIGNAL(sendRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString)) , this , SLOT(getRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString)));
    connect(trdlg , SIGNAL(sendRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString , int)) , this , SLOT(getRemindInfo(int , int , QDateTime , QString , int , QString , QString , QString , QString , int)));
    trdlg->exec();
    isStopUpdate = false;
}

void TimeReminder::getRemindInfo(int remindType , int remindWeek , QDateTime dateTime , QString remindEvent, int remindDuration, QString remindSound, QString remindPic, QString remindRemarks , QString remindTimeStr)
{
    ReminderInfo info;
    int id = 0;
    info.remindType = remindType;
    info.remindWeek = remindWeek;
    info.dateTime = dateTime;
    info.remindEvent = remindEvent;
    info.remindDuration = remindDuration;
    info.remindSound = remindSound;
    info.remindPic = remindPic;
    info.remindRemarks = remindRemarks;
    info.remindTimeStr = remindTimeStr;
    if (db.open()) {
        QSqlQuery query;
        QString select_sql = "SELECT max(id) FROM timer_reminder";
        if(!query.exec(select_sql)){
            qDebug()<<query.lastError();
            query.finish();
        }
        else{
            while(query.next())
            {
                id = query.value(0).toInt()+1;
                qDebug()<<id;
            }
            query.finish();
        }

        QString insert_sql = "insert into timer_reminder (id , remindType , remindWeek , dateTime , remindEvent , remindDuration , remindSound , remindPic , remindRemarks , remindTimeStr ) values (? , ? , ? , ? , ? , ? , ? , ? , ? , ?)";
        query.prepare(insert_sql);
        query.addBindValue(id);
        query.addBindValue(remindType);
        query.addBindValue(remindWeek);
        query.addBindValue(dateTime.toTime_t());
        query.addBindValue(remindEvent);
        query.addBindValue(remindDuration);
        query.addBindValue(remindSound);
        query.addBindValue(remindPic);
        query.addBindValue(remindRemarks);
        query.addBindValue(remindTimeStr);
        if(!query.exec())
        {
            qDebug() << query.lastError();
            query.finish();
        }
        else
        {
            qDebug() << "inserted Sucess!";
            query.finish();
        }
    }
    info.id = id;
    ri.push_back(info);
}

void TimeReminder::getRemindInfo(int remindType , int remindWeek , QDateTime dateTime , QString remindEvent, int remindDuration, QString remindSound, QString remindPic, QString remindRemarks , QString remindTimeStr ,int index)
{
    ReminderInfo info;
    info.remindType = remindType;
    info.remindWeek = remindWeek;
    info.dateTime = dateTime;
    info.remindEvent = remindEvent;
    info.remindDuration = remindDuration;
    info.remindSound = remindSound;
    info.remindPic = remindPic;
    info.remindRemarks = remindRemarks;
    info.remindTimeStr = remindTimeStr;
    if (db.open()) {
        QSqlQuery query;
        QString insert_sql = "update timer_reminder set "
                             "remindType = :remindType , "
                             "remindWeek = :remindWeek , "
                             "dateTime = :dateTime , "
                             "remindEvent = :remindEvent , "
                             "remindDuration = :remindDuration , "
                             "remindSound = :remindSound , "
                             "remindPic = :remindPic , "
                             "remindRemarks = :remindRemarks , "
                             "remindTimeStr = :remindTimeStr "
                             "where id = :id";
        query.prepare(insert_sql);
        query.bindValue(":remindType" , remindType);
        query.bindValue(":remindWeek" , remindWeek);
        query.bindValue(":dateTime" , dateTime.toTime_t());
        query.bindValue(":remindEvent" , remindEvent);
        query.bindValue(":remindDuration" , remindDuration);
        query.bindValue(":remindSound" , remindSound);
        query.bindValue(":remindPic" , remindPic);
        query.bindValue(":remindRemarks" , remindRemarks);
        query.bindValue(":remindTimeStr" , remindTimeStr);
        query.bindValue(":id" , ri[index].id);
        qDebug()<<"remindDuration"<<remindDuration;
        qDebug()<<index+1;
        if(!query.exec())
        {
            qDebug() << query.lastError();
            qDebug()<<query.executedQuery();
            query.finish();
        }
        else
        {
            qDebug() << "updated Sucess!";
            qDebug()<<query.executedQuery();
            query.finish();
        }
    }
    ri.erase(ri.begin() + index);
    ri.push_back(info);
}

void TimeReminder::onTimeout()
{
    if(isStopUpdate){
        return;
    }
    for(int i = 0; i < ri.size() ;i++){
        QStandardItem *eventItem = new QStandardItem(ri[i].remindEvent);
        QStandardItem *remindTimeItem = new QStandardItem(ri[i].remindTimeStr);
        QStandardItem *remarksItem = new QStandardItem(ri[i].remindRemarks);
        QStandardItem *remindCountDown;
        QDateTime currTime = QDateTime::currentDateTime();
        if(ri[i].remindType == DESIGNATEDDATE){
            qint64 intervalTime = currTime.secsTo(ri[i].dateTime);
            if(intervalTime == 0){
                qsti->showMessage(tr("提醒"), ri[i].remindTimeStr + " " + ri[i].remindEvent + " " + ri[i].remindRemarks);
                TimeReminderWindow *trw = new TimeReminderWindow(
                            ri[i].remindType ,
                            ri[i].remindWeek ,
                            ri[i].dateTime ,
                            ri[i].remindEvent ,
                            ri[i].remindDuration ,
                            ri[i].remindSound ,
                            ri[i].remindPic ,
                            ri[i].remindRemarks ,
                            ri[i].remindTimeStr ,
                            this);
                trw->showMaximized();
                if (db.open()) {
                    QSqlQuery query;
                    QString insert_sql = "delete from timer_reminder where id = ?";
                    query.prepare(insert_sql);
                    query.addBindValue(ri[i].id);
                    qDebug()<<"index id:"<<ri[i].id;
                    if(!query.exec())
                    {
                        qDebug() << query.lastError();
                        query.finish();
                    }
                    else
                    {
                        qDebug() << "deleted Sucess!";
                        query.finish();
                    }
                }
                remindModel->removeRow(i);
                ri.erase(ri.begin()+i);
                continue;
            }
            remindCountDown = new QStandardItem(getCountDown(intervalTime));
        }
        else if(ri[i].remindType == EVERYYEAR){
            ri[i].dateTime.setDate(QDate(currTime.date().year() , ri[i].dateTime.date().month() , ri[i].dateTime.date().day()));
            qint64 intervalTime = currTime.secsTo(ri[i].dateTime);
            if(intervalTime == 0){
                qsti->showMessage(tr("提醒"), ri[i].remindTimeStr + " " + ri[i].remindEvent + " " + ri[i].remindRemarks);
                TimeReminderWindow *trw = new TimeReminderWindow(this);
                trw->showMaximized();
                continue;
            }
            while(intervalTime < 0){
                ri[i].dateTime = ri[i].dateTime.addYears(1);
                intervalTime = currTime.secsTo(ri[i].dateTime);
            }
            remindCountDown = new QStandardItem(getCountDown(intervalTime));
        }
        else if(ri[i].remindType == EVERYMONTH){
            ri[i].dateTime.setDate(QDate(currTime.date().year() , currTime.date().month() , ri[i].dateTime.date().day()));
            qint64 intervalTime = currTime.secsTo(ri[i].dateTime);
            if(intervalTime == 0){
                qsti->showMessage(tr("提醒"), ri[i].remindTimeStr + " " + ri[i].remindEvent + " " + ri[i].remindRemarks);
                TimeReminderWindow *trw = new TimeReminderWindow(this);
                trw->showMaximized();
                continue;
            }
            while(intervalTime < 0){
                ri[i].dateTime = ri[i].dateTime.addMonths(1);
                intervalTime = currTime.secsTo(ri[i].dateTime);
            }
            remindCountDown = new QStandardItem(getCountDown(intervalTime));
        }
        else if(ri[i].remindType == EVERYDAY){
            ri[i].dateTime.setDate(QDate(currTime.date().year() , currTime.date().month() , currTime.date().day()));
            qint64 intervalTime = currTime.secsTo(ri[i].dateTime);
            if(intervalTime == 0){
                qsti->showMessage(tr("提醒"), ri[i].remindTimeStr + " " + ri[i].remindEvent + " " + ri[i].remindRemarks);
                TimeReminderWindow *trw = new TimeReminderWindow(this);
                trw->showMaximized();
                continue;
            }
            while(intervalTime < 0){
                ri[i].dateTime = ri[i].dateTime.addDays(1);
                intervalTime = currTime.secsTo(ri[i].dateTime);
            }
            remindCountDown = new QStandardItem(getCountDown(intervalTime));
        }
        else if(ri[i].remindType == EVERYWEEK){
            ri[i].dateTime.setDate(QDate(currTime.date().year() , currTime.date().month() , currTime.date().day()));
            QString currWeek = ri[i].dateTime.toString("ddd");
            int week = 0;
            if(currWeek == "周一"){
                week = 1;
            }
            else if(currWeek == "周二"){
                week = 2;
            }
            else if(currWeek == "周三"){
                week = 3;
            }
            else if(currWeek == "周四"){
                week = 4;
            }
            else if(currWeek == "周五"){
                week = 5;
            }
            else if(currWeek == "周六"){
                week = 6;
            }
            else if(currWeek == "周日"){
                week = 7;
            }
            qint64 intervalTime = currTime.secsTo(ri[i].dateTime);
            if(intervalTime == 0){
                qsti->showMessage(tr("提醒"), ri[i].remindTimeStr + " " + ri[i].remindEvent + " " + ri[i].remindRemarks);
                TimeReminderWindow *trw = new TimeReminderWindow(this);
                trw->showMaximized();
                continue;
            }
            while(!(ri[i].remindWeek & int(qPow(2 , week-1))) || intervalTime < 0){
                week = week + 1;
                week = week % 7;
                ri[i].dateTime = ri[i].dateTime.addDays(1);
                intervalTime = currTime.secsTo(ri[i].dateTime);
            }
            qDebug()<<intervalTime;
            remindCountDown = new QStandardItem(getCountDown(intervalTime));
        }
        int j = 0;
        auto count = i;
        remindModel->setItem(count, j++, eventItem);
        remindModel->setItem(count, j++, remindCountDown);
        remindModel->setItem(count, j++, remindTimeItem);
        remindModel->setItem(count, j++, remarksItem);
    }
}

QString TimeReminder::getCountDown(qint64 sec)
{
    qint64 day = 0;
    qint64 hour = 0;
    qint64 minute = 0;
    qint64 second = 0;
    if(sec >= 3600*24){
        day = sec/(3600*24);
        sec = sec%(3600*24);
    }
    if(sec >= 3600){
        hour = sec/3600;
        sec = sec%3600;
    }
    if(sec >= 60){
        minute = sec/60;
        sec = sec%60;
    }
    second = sec;
    return QString::number(day) + tr("天") + QString::number(hour) + ":" + QString::number(minute) + ":" + QString::number(second);
}

void TimeReminder::viewSelectCheck(const QItemSelection & selected, const QItemSelection & deselected)
{
    qDebug()<<"select";
    isStopUpdate = true;
}
