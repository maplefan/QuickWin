#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "PCSearch.h"
#include "ui_PCSearch.h"
#include "Everything.h"
#include "quicklook.h"

QSqlDatabase database;

//通过pid获取窗口句柄
HWND PCSearch::GetHwndByPid(DWORD dwProcessID)
{
    HWND h = GetTopWindow(0);
    HWND retHwnd = NULL;
    while (h)
    {
        DWORD pid = 0;
        DWORD dwTheardId = GetWindowThreadProcessId(h, &pid);
        if (dwTheardId != 0)
        {
            if (pid == dwProcessID && GetParent(h) == NULL && ::IsWindowVisible(h))
            {
                retHwnd = h;    //会有多个相等值
                //    /*
                //char buf[MAX_PATH] = { 0 };
                //sprintf_s(buf, "%0x", h);
                //MessageBox(NULL, buf, "提示", MB_OK);
                //    */
            }
        }
        h = GetNextWindow(h, GW_HWNDNEXT);
    }
    return retHwnd;
}

PCSearch::PCSearch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PCSearch)
{     
    if(GetProcessidFromName(L"Everything.exe") == 0)
    {
        QString filePath = QCoreApplication::applicationDirPath();
        QProcess pro;
        filePath = filePath + "/search_engine.exe -close";
        pro.startDetached(filePath);
    }

    Everything_SetSearch(L".exe");
    Everything_Query(true);
    //不断查询结果，直到查到的结果总数不变，即everything已经扫描完了所有的路径
    int lastResultsCount = 0;
    int resultsCount = -1;
    resultsCount = Everything_GetNumResults();

    while (lastResultsCount != resultsCount)
    {
         lastResultsCount = resultsCount;
         Sleep(500);
         Everything_SetSearch(L".exe");
         Everything_QueryW(true);
         resultsCount = Everything_GetNumResults();
    }

    Everything_SetMax(100);

    //建立并打开数据库
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName("dict.db");
    if (!database.open())
    {
        //qDebug() << "Error: Failed to connect database." << database.lastError();
    }
    else
    {
        //qDebug() << "Succeed to connect database." ;
    }
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(this->width() , 51);
    this->ui->tableView->setGeometry( 0 , 0 , this->width() , this->height());
    model = new QStandardItemModel();
    QStringList labels = QObject::tr("名称,路径,大小,修改时间").simplified().split(",");
    model->setColumnCount(4);
    model->setHorizontalHeaderLabels(labels);

    //初始化宽度
    this->ui->tableView->setColumnWidth( 0 , 200);
    this->ui->tableView->setColumnWidth( 1 , 460);
    this->ui->tableView->setColumnWidth( 2 , 100);
    this->ui->tableView->setColumnWidth( 3 , 200);
    colWidth0 = 200;
    colWidth1 = 460;
    colWidth2 = 100;
    colWidth3 = 200;

    this->ui->tableView->setModel(model);
    this->ui->tableView->show();
    this->ui->tableView->setVisible(false);
    this->ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    this->ui->tableView->setMouseTracking(true);

    // 整行选中
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // 不可编辑
    this->ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->tableView->setStyleSheet("TableView{border:none;background:white;}");
    this->ui->tableView->setStyleSheet("TableView::item:selected{color:white;background:rgb(34, 175, 75);}");
    this->ui->statusBar->setVisible(false);

    this->ui->statusBar->setSizeGripEnabled(false);//去掉状态栏右下角的三角
    this->ui->statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}")); // 设置不显示label的边框
    statusLabel = new QLabel(tr(" 就绪"));
    statusLabel->setAlignment(Qt::AlignLeft);
    this->ui->statusBar->addWidget(statusLabel);

    menu = new QMenu(this->ui->tableView);
    actionView = new QAction();
    actionOpen = new QAction();
    actionOpenPath = new QAction();
    actionCopyFullPath = new QAction();
    actionAttribute = new QAction();

    actionView->setText(tr("预览"));
    actionOpen->setText(tr("打开"));
    actionOpenPath->setText(tr("打开路径"));
    actionCopyFullPath->setText(tr("复制完整路径和文件名"));
    actionAttribute->setText(tr("属性"));

    menu->addAction(actionView);
    menu->addAction(actionOpen);
    menu->addAction(actionOpenPath);
    menu->addAction(actionCopyFullPath);
    menu->addAction(actionAttribute);
    isFileMode = true;

    clipboard = QApplication::clipboard();
    connect(this->ui->tableView , SIGNAL(customContextMenuRequested(QPoint)) , this , SLOT(slotWindowContextMenu(QPoint)));
    connect(this->ui->tableView, SIGNAL(entered(QModelIndex)), this, SLOT(showToolTip(QModelIndex)));
    connect(this->ui->tableView->selectionModel() , SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)) , this , SLOT(keyPressRowChange(const QModelIndex &, const QModelIndex &)));
    connect(actionView , SIGNAL(triggered()) , this , SLOT(viewFile()));
    connect(actionOpen , SIGNAL(triggered()) , this , SLOT(openFile()));
    connect(actionOpenPath , SIGNAL(triggered()) , this , SLOT(openFilePath()));
    connect(actionCopyFullPath , SIGNAL(triggered()) , this , SLOT(copyFullPath()));
    connect(actionAttribute , SIGNAL(triggered()) , this , SLOT(viewProperties()));

    setFocusPolicy(Qt::StrongFocus);
    installEventFilter(this);
}

PCSearch::~PCSearch()
{
    delete ui;
    //关闭数据库
    database.close();
}

void PCSearch::on_lineEdit_textChanged(const QString &arg1)
{
    if(Everything_IsDBLoaded())
    {
        Everything_SetMax(100);
        if(arg1.length() == 0){
            this->setFixedSize(this->width() , 51);
            this->ui->tableView->setVisible(false);
            this->ui->statusBar->setVisible(false);
            isFileMode = true;
        }
        else if(arg1.size() > 3)
        {
            if(arg1.left(3) == "fy " )//翻译
            {
                  isFileMode = false;
                  QString searchStr = arg1.right(arg1.length()-3);
                  model->clear();
                  QSqlQuery sql_query;
                  if(IsEnglish(searchStr))//查询的全是英文
                  {
                      sql_query.exec("select * from word where word like '%" + searchStr + "%'");
                  }
                  else{
                      sql_query.exec("select * from word where trans like '%" + searchStr + "%'");
                  }
                  if(!sql_query.exec())
                  {
                      //qDebug()<<sql_query.lastError();
                  }
                  else
                  {
                      QStringList labels = QObject::tr("单词,英式发音,美式发音,释义").simplified().split(",");
                      model->setColumnCount(4);
                      model->setHorizontalHeaderLabels(labels);
                      //初始化宽度
                      this->ui->tableView->setColumnWidth( 0 , 200);
                      this->ui->tableView->setColumnWidth( 1 , 100);
                      this->ui->tableView->setColumnWidth( 2 , 100);
                      this->ui->tableView->setColumnWidth( 3 , 560);
                      int queryCount = 0;
                      QStandardItem* item = 0;
                      while(sql_query.next())
                      {
                          QString word = sql_query.value(0).toString();//单词
                          QString prounce_uk = sql_query.value(1).toString();//英式发音
                          QString prounce_us = sql_query.value(2).toString();//美式发音
                          QString trans = sql_query.value(4).toString();//翻译
                          item = new QStandardItem(word);
                          model->setItem(queryCount,0,item);
                          item = new QStandardItem(prounce_uk);
                          model->setItem(queryCount,1,item);
                          item = new QStandardItem(prounce_us);
                          model->setItem(queryCount,2,item);
                          item = new QStandardItem(trans);
                          model->setItem(queryCount,3,item);
                          queryCount++;
                          if(queryCount >= 100)
                          {
                              break;
                          }
                      }
                  }
                    statusLabel->setText(tr(" 将翻译 ") + searchStr + " 。");
            }
            else if(arg1.left(3) == "bd ")//百度
            {
                  isFileMode = false;
                  model->clear();
                  QStringList label = QObject::tr("Baidu").simplified().split(",");
                  model->setHorizontalHeaderLabels(label);
                  QStandardItem* item = 0;
                  item = new QStandardItem(QString(tr("按回车键百度搜索\"")+arg1.right(arg1.length()-3))+ "\"");
                  model->setItem(0,0,item);
                  this->ui->tableView->setRowHeight( 0 , 50 );
                  this->ui->tableView->setColumnWidth( 0 , this->ui->tableView->width());
                  statusLabel->setText(tr(" Baidu将搜索 ") + arg1.right(arg1.length()-3) + tr(" 。"));
            }
            else if(arg1.left(3) == "by ")//必应
            {
                isFileMode = false;
                model->clear();
                QStringList label = QObject::tr("Bing").simplified().split(",");
                model->setHorizontalHeaderLabels(label);
                QStandardItem* item = 0;
                item = new QStandardItem(QString(tr("按回车键必应搜索\"")+arg1.right(arg1.length()-3))+ "\"");
                model->setItem(0,0,item);
                this->ui->tableView->setRowHeight( 0 , 50 );
                this->ui->tableView->setColumnWidth( 0 , this->ui->tableView->width());
                statusLabel->setText(tr(" Bing将搜索 ") + arg1.right(arg1.length()-3) + tr(" 。"));
            }
            else if(arg1.left(3) == "gg ")//谷歌
            {
                isFileMode = false;
                model->clear();
                QStringList label = QObject::tr("Google").simplified().split(",");
                model->setHorizontalHeaderLabels(label);
                QStandardItem* item = 0;
                item = new QStandardItem(QString(tr("按回车键谷歌搜索\"")+arg1.right(arg1.length()-3))+ "\"");
                model->setItem(0,0,item);
                this->ui->tableView->setRowHeight( 0 , 50 );
                this->ui->tableView->setColumnWidth( 0 , this->ui->tableView->width());
                statusLabel->setText(tr(" Google将搜索 ") + arg1.right(arg1.length()-3) + tr(" 。"));
            }
            else if(arg1.left(3) == "cmd")//命令行
            {
                    isFileMode = false;
                    model->clear();
                    QStringList label = QObject::tr("控制台").simplified().split(",");
                    model->setHorizontalHeaderLabels(label);
                    QStandardItem* item = 0;
                    item = new QStandardItem(QString(tr("按回车键使用控制台执行\"")+arg1.right(arg1.length()-4))+ "\"");
                    model->setItem(0,0,item);
                    this->ui->tableView->setRowHeight( 0 , 50 );
                    this->ui->tableView->setColumnWidth( 0 , this->ui->tableView->width());
                    statusLabel->setText(tr(" 控制台将执行 ") + arg1.right(arg1.length()-4) + " 。");
            }
            this->ui->statusBar->setVisible(true);
        }
        else{
            /*colWidth0 = this->ui->tableView->columnWidth(0);
            colWidth1 = this->ui->tableView->columnWidth(0);
            colWidth2 = this->ui->tableView->columnWidth(0);
            colWidth3 = this->ui->tableView->columnWidth(0);*/
            //需要重新绑定model
            isFileMode = true;
            model->clear();
            QStringList labels = QObject::tr("名称,路径,大小,修改时间").simplified().split(",");
            model->setColumnCount(4);
            model->setHorizontalHeaderLabels(labels);
            this->ui->tableView->setModel(model);
            connect(this->ui->tableView->selectionModel() , SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)) , this , SLOT(keyPressRowChange(const QModelIndex &, const QModelIndex &)));

            this->setFixedSize(this->width() , 600);
            this->ui->tableView->setVisible(true);
            this->ui->tableView->setGeometry(10,59,960,520);
            Everything_SetSearch(arg1.toStdWString().c_str());
            Everything_Query(TRUE);
            QStandardItem* item = 0;
            this->ui->tableView->setUpdatesEnabled(false);
            if(Everything_GetNumResults() >= 100)//暂时只显示前100条
            {
                for(int i = 0;i < 100;i++)
                {
                    QString filePath = QString::fromWCharArray(Everything_GetResultPath(i)) ;
                    QString fileFullPath = filePath + +"\\" + QString::fromWCharArray(Everything_GetResultFileName(i));
                    QFileInfo info(fileFullPath);
                    QIcon tmpIcon = iconProvider.icon(info);
                    item = new QStandardItem(tmpIcon , QString::fromWCharArray(Everything_GetResultFileName(i)));
                    model->setItem(i,0,item);
                    item = new QStandardItem(filePath);
                    model->setItem(i,1,item);
                    QString modifyTime = info.lastModified().toString("yyyy/MM/dd hh:mm:ss");
                    item = new QStandardItem(changeSizeFmt(info.size()));
                    model->setItem(i,2,item);
                    item = new QStandardItem(modifyTime);
                    model->setItem(i,3,item);
                    this->ui->tableView->setModel(model);
                }
                statusLabel->setText(QString(tr(" 显示前100个对象。")));
            }
            else if( Everything_GetNumResults() > 0 ){
                for(int i = 0;i<Everything_GetNumResults();i++)
                {
                    QString filePath = QString::fromWCharArray(Everything_GetResultPath(i)) ;
                    QString fileFullPath = filePath + +"\\" + QString::fromWCharArray(Everything_GetResultFileName(i));
                    QFileInfo info(fileFullPath);
                    QIcon tmpIcon = iconProvider.icon(info);
                    item = new QStandardItem(tmpIcon , QString::fromWCharArray(Everything_GetResultFileName(i)));
                    model->setItem(i,0,item);
                    item = new QStandardItem(filePath);
                    model->setItem(i,1,item);
                    QString modifyTime = info.lastModified().toString("yyyy/MM/dd hh:mm:ss");
                    item = new QStandardItem(changeSizeFmt(info.size()));
                    model->setItem(i,2,item);
                    item = new QStandardItem(modifyTime);
                    model->setItem(i,3,item);
                    this->ui->tableView->setModel(model);
                }
                statusLabel->setText(QString(tr(" 搜索到")) + QString::number(Everything_GetNumResults()) + QString(tr("个对象。")));
            }
            else if( Everything_GetNumResults() == 0 )
            {
                statusLabel->setText(QString(tr(" 搜索到0个对象。")));
            }
            this->ui->tableView->setUpdatesEnabled(true);
            this->ui->tableView->setColumnWidth( 0 , colWidth0);
            this->ui->tableView->setColumnWidth( 1 , colWidth1);
            this->ui->tableView->setColumnWidth( 2 , colWidth2);
            this->ui->tableView->setColumnWidth( 3 , colWidth3);
            this->ui->statusBar->setVisible(true);
        }
        connect(this->ui->tableView->selectionModel() , SIGNAL(currentRowChanged(const QModelIndex &, const QModelIndex &)) , this , SLOT(keyPressRowChange(const QModelIndex &, const QModelIndex &)));
    }
    else{
        statusLabel->setText(QString(tr(" 正在加载！")));
        this->ui->statusBar->setVisible(true);
    }
}

void PCSearch::mouseMoveEvent(QMouseEvent *event)
{
    //去表格虚框
    QPoint m_endPos;
    if(event->buttons()==Qt::LeftButton)
    {
        m_endPos = event->globalPos()- m_startPos;
        this->move(m_endPos);
    }
}

void PCSearch::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
    //记录窗口此时的坐标
        m_startPos = event->globalPos() - this->frameGeometry().topLeft();
    }
}

//判断进程是否存在
DWORD PCSearch::GetProcessidFromName(LPCTSTR name)
{
    PROCESSENTRY32 pe;
    DWORD id=0;
    HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    pe.dwSize=sizeof(PROCESSENTRY32);
    if(!Process32First(hSnapshot,&pe))
      return 0;
    while(1)
    {
      pe.dwSize=sizeof(PROCESSENTRY32);
      if(Process32Next(hSnapshot,&pe)==FALSE)
       break;
      if(wcscmp(pe.szExeFile,name)==0)
      {
       id=pe.th32ProcessID;
       break;
      }
      }
    CloseHandle(hSnapshot);
    return id;
}

void PCSearch::on_lineEdit_returnPressed()
{
    QString arg1 = this->ui->lineEdit->text();
    if(arg1.size() > 3)
    {
        if(arg1.left(3) == "bd ")//百度
        {
            QDesktopServices::openUrl(QUrl("https://www.baidu.com/s?wd=" + arg1.right(arg1.length()-3)));
        }
        else if(arg1.left(3) == "by ")//必应
        {
            QDesktopServices::openUrl(QUrl("https://cn.bing.com/search?q=" + arg1.right(arg1.length()-3)));
        }
        else if(arg1.left(3) == "gg ")//谷歌
        {
            QDesktopServices::openUrl(QUrl("https://www.google.com/search?q=" + arg1.right(arg1.length()-3)));
        }
        else if(arg1.left(3) == "cmd")//命令行
        {
            WinExec(("cmd.exe /K " + arg1.right(arg1.length()-3).toStdString()).c_str(),SW_NORMAL);
        }
    }
}

bool PCSearch::IsEnglish(QString &qstrSrc)//判断是否全是英文
{
    QByteArray ba = qstrSrc.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if((*s>='A' && *s<='Z') || (*s>='a' && *s<='z'))
        {

        }
        else
        {
            bret = false;
            break;
        }
        s++;
    }
    return bret;
}

QString PCSearch::changeSizeFmt(qint64 size)
{
    double curSize = size;
    QString unit = " B";
    if(curSize > 1024){
        curSize /= 1024;
        unit = " KB";
        if(curSize > 1024){
            curSize /= 1024;
            unit = " MB";
            if(curSize > 1024){
                curSize /= 1024;
                unit = " GB";
            }
        }
    }
    QString textSize = QString::number(curSize, 'f', 2);
    textSize.append(unit);

    return textSize;
}

//弹出窗口界面右键菜单的函数
void PCSearch::slotWindowContextMenu(QPoint pos)
{
    auto index = this->ui->tableView->indexAt(pos);
    if(index.isValid()){
        menu->exec(QCursor::pos());//在当前鼠标的位置出现菜单
    }
}

void PCSearch::showToolTip(const QModelIndex &index)
{
    if (!index.isValid()) {
    //qDebug() << "Invalid index";
    return;
    }
    QToolTip::showText(QCursor::pos(), index.data().toString());
}

void PCSearch::openFile()
{
    int row = this->ui->tableView->currentIndex().row();
    QModelIndex index1 = model->index(row , 1);//第1项为路径
    QVariant data1 = model->data(index1);
    QString dataStr1 = data1.toString();//文件路径

    QModelIndex index0 = model->index(row , 0);//第0项为文件名
    QVariant data0 = model->data(index0);
    QString dataStr0 = data0.toString();//文件名
    QString dataStr =  dataStr1 + "\\" + dataStr0;
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataStr));
}

void PCSearch::viewFile()
{
    int row = this->ui->tableView->currentIndex().row();
    QModelIndex index1 = model->index(row , 1);//第1项为路径
    QVariant data1 = model->data(index1);
    QString dataStr1 = data1.toString();//文件路径

    QModelIndex index0 = model->index(row , 0);//第0项为文件名
    QVariant data0 = model->data(index0);
    QString dataStr0 = data0.toString();//文件名
    QString dataStr =  dataStr1 + "\\" + dataStr0;

    QuickLook *ql = new QuickLook(dataStr , this );
    ql->setAttribute(Qt::WA_DeleteOnClose,  true);
}

void PCSearch::openFilePath()
{
    int row = this->ui->tableView->currentIndex().row();
    QModelIndex index1 = model->index(row , 1);//第1项为路径
    QVariant data1 = model->data(index1);
    QString dataStr1 = data1.toString();//文件路径
    QDesktopServices::openUrl(QUrl::fromLocalFile(dataStr1));
}

void PCSearch::copyFullPath()
{
    int row = this->ui->tableView->currentIndex().row();
    QModelIndex index1 = model->index(row , 1);//第1项为路径
    QVariant data1 = model->data(index1);
    QString dataStr1 = data1.toString();//文件路径

    QModelIndex index0 = model->index(row , 0);//第0项为文件名
    QVariant data0 = model->data(index0);
    QString dataStr0 = data0.toString();//文件名
    QString dataStr =  dataStr1 + "\\" + dataStr0;
    clipboard->setText(dataStr);
}

void PCSearch::viewProperties()
{
    int row = this->ui->tableView->currentIndex().row();
    QModelIndex index1 = model->index(row , 1);//第1项为路径
    QVariant data1 = model->data(index1);
    QString dataStr1 = data1.toString();//文件路径

    QModelIndex index0 = model->index(row , 0);//第0项为文件名
    QVariant data0 = model->data(index0);
    QString dataStr0 = data0.toString();//文件名
    QString dataStr =  dataStr1 + "\\" + dataStr0;
    if(dataStr1 == "System path" ){
        QMessageBox::information(NULL, tr("提示"), tr("系统目录！"));
    }
    else{
        const wchar_t* wstr = reinterpret_cast<const wchar_t *>(dataStr.utf16());
        SHELLEXECUTEINFO ShExecInfo = {0};
        ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
        ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST ;
        ShExecInfo.lpVerb = L"properties";
        ShExecInfo.lpFile = wstr;
        ShExecInfo.lpParameters = L"";
        ShExecInfo.lpDirectory = NULL;
        ShExecInfo.nShow = SW_SHOW;
        ShExecInfo.hInstApp = NULL;
        ShellExecuteEx(&ShExecInfo);
    }
}

void PCSearch::keyPressRowChange(const QModelIndex &current, const QModelIndex &previous)
{
    QModelIndex index1 = this->ui->tableView->model()->index(current.row(), 1);//路径
    QModelIndex index2 = this->ui->tableView->model()->index(current.row(), 2);//文件大小
    QModelIndex index3 = this->ui->tableView->model()->index(current.row(), 3);//修改时间
    if(isFileMode){
        statusLabel->setText(QString(tr(" 大小：") + index2.data().toString() + tr("，修改时间：") + index3.data().toString() + tr("，路径：") + index1.data().toString()));
    }
    else{
        statusLabel->setText(QString(index2.data().toString() + " " + index3.data().toString() + " " + index1.data().toString()));
    }
}

bool PCSearch::eventFilter(QObject* object, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)//选中一项时按空格或者回车键触发QuickLook
        {
            QString arg1 = this->ui->lineEdit->text();
            if(arg1.size() > 3)
            {
                if(arg1.left(3) == "bd ")//百度
                {
                    QDesktopServices::openUrl(QUrl("https://www.baidu.com/s?wd=" + arg1.right(arg1.length()-3)));
                }
                else if(arg1.left(3) == "by ")//必应
                {
                    QDesktopServices::openUrl(QUrl("https://cn.bing.com/search?q=" + arg1.right(arg1.length()-3)));
                }
                else if(arg1.left(3) == "gg ")//谷歌
                {
                    QDesktopServices::openUrl(QUrl("https://www.google.com/search?q=" + arg1.right(arg1.length()-3)));
                }
                else if(arg1.left(3) == "cmd")//命令行
                {
                    WinExec(("cmd.exe /K " + arg1.right(arg1.length()-3).toStdString()).c_str(),SW_NORMAL);
                }
                else{
                    viewFile();
                }
            }
            else{
                viewFile();
            }
        }
    }
    return false;
}
