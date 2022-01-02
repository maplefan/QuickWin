#include "setting.h"
#include "taskbar.h"
#include "ui_setting.h"
#include "ddccli.h"

typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;
extern bool isShowMainWindowFullScreen;
extern QString mainColor;
extern QString mainColorBK;
extern QString taskColor;
extern int isQuickLook;
extern int mainDoubleClick;
extern int taskDoubleClick;
extern int mainShowInfo;
extern int taskShowInfo;
extern int mainShowNum;
extern int taskShowNum;
extern int updateTime;

int getNofX(int x , int n)
{
    return (x>>n)&1;
}

void setNofXto1(int &x , int n)
{
    x^=(x&(1<<n))^(1<<n);
}

void setNofXto0(int &x , int n)
{
    x^=(x&(1<<n))^(0<<n);
}

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("设置"));
    int isAutoStart = Config().Get("Setting" , "AutoStart").toInt();
    QString fontFamily = Config().Get("Setting" , "FontFamily").toString();
    QString fontSize = Config().Get("Setting" , "FontSize").toString();
    int fontWeight = Config().Get("Setting" , "FontWeight").toInt();
    QString language = Config().Get("Setting" , "Language").toString();
    int stockShow = Config().Get("Setting" , "StockShow").toInt();
    QString mainFontFamily = Config().Get("Setting" , "MainFontFamily").toString();
    QString mainFontSize = Config().Get("Setting" , "MainFontSize").toString();
    QString mainFontColor = Config().Get("Setting" , "MainFontColor").toString();
    QString mainFontColorBK = Config().Get("Setting" , "MainFontColorBK").toString();
    QString taskFontFamily = Config().Get("Setting" , "TaskFontFamily").toString();
    QString taskFontSize = Config().Get("Setting" , "TaskFontSize").toString();
    QString taskFontColor = Config().Get("Setting" , "TaskFontColor").toString();
    int mainDoubleClickAction = Config().Get("Setting" , "MainDoubleClickAction").toInt();
    int taskDoubleClickAction = Config().Get("Setting" , "TaskDoubleClickAction").toInt();
    QString mainDoubleClickActionPath = Config().Get("Setting" , "MainDoubleClickActionPath" ).toString();
    QString taskDoubleClickActionPath = Config().Get("Setting" , "TaskDoubleClickActionPath" ).toString();

    //开机自启动
    if(isAutoStart == 1){
        this->ui->checkBoxAutoStart->setChecked(Qt::Checked);
    }
    else{
        this->ui->checkBoxAutoStart->setChecked(Qt::Unchecked);
    }

    if(mainDoubleClickAction == DoubleClickAction::CUSTOM){
        QFontMetrics fontWidth(ui->labelMainDoubleClickPath->font());//得到每个字符的宽度
        QString elideNote = fontWidth.elidedText(mainDoubleClickActionPath, Qt::ElideRight, 220);//最大宽度150像素
        this->ui->labelMainDoubleClickPath->setText(elideNote);
        this->ui->labelMainDoubleClickPath->setToolTip(mainDoubleClickActionPath);
    }
    else{
        this->ui->labelMainDoubleClickPath->setText(tr("未选择自定义打开程序"));
    }
    if(taskDoubleClickAction == DoubleClickAction::CUSTOM){
        QFontMetrics fontWidth(ui->labelTaskDoubleClickPath->font());//得到每个字符的宽度
        QString elideNote = fontWidth.elidedText(taskDoubleClickActionPath, Qt::ElideRight, 220);//最大宽度150像素
        this->ui->labelTaskDoubleClickPath->setText(elideNote);
        this->ui->labelTaskDoubleClickPath->setToolTip(taskDoubleClickActionPath);
    }
    else{
        this->ui->labelTaskDoubleClickPath->setText(tr("未选择自定义打开程序"));
    }
    if(Config().Get("Setting" , "IsShowMainWindowFullScreen") == 2){
        isShowMainWindowFullScreen = false;
        this->ui->checkBoxHideMainWindow->setChecked(Qt::Checked);
    }
    else{
        isShowMainWindowFullScreen = true;
        this->ui->checkBoxHideMainWindow->setChecked(Qt::Unchecked);
    }

    isQuickLook = Config().Get("Setting" , "QuickLook").toInt();
    this->ui->labelFontResult->setText(fontFamily + " " + fontSize);
    this->ui->labelMainFont->setText(mainFontFamily + " " + mainFontSize);
    this->ui->labelMainColor->setStyleSheet(tr("background-color: rgb(%1)").arg(mainFontColor));
    this->ui->labelTaskFont->setText(taskFontFamily + " " + taskFontSize);
    this->ui->labelTaskColor->setStyleSheet(tr("background-color: rgb(%1)").arg(taskFontColor));
    this->ui->labelMainColorBK->setStyleSheet(tr("background-color: rgb(%1)").arg(mainFontColorBK));
    this->ui->comboBoxUpdateTime->setCurrentIndex(updateTime);

    if(fontWeight == QFont::Bold){
        this->ui->checkBoxFontWeight->setChecked(true);
    }
    else{
        this->ui->checkBoxFontWeight->setChecked(false);
    }

    if(language == "Chinese"){
        this->ui->comboBoxLanguage->setCurrentIndex(LANGCHINESE);
    }
    else if(language == "TraditionalChinese"){
        this->ui->comboBoxLanguage->setCurrentIndex(LANGTRADCHINESE);
    }
    else if(language == "English"){
        this->ui->comboBoxLanguage->setCurrentIndex(LANGENGLISH);
    }

    if(stockShow >= 0 && stockShow < this->ui->comboBoxStockShow->count()){
        this->ui->comboBoxStockShow->setCurrentIndex(stockShow);
    }

    if(isQuickLook == 0 || isQuickLook == 2){
        this->ui->checkBoxQuickLook->setCheckState(Qt::Checked);
    }
    else{
        this->ui->checkBoxQuickLook->setCheckState(Qt::Unchecked);
    }

    this->ui->comboBoxMainDoubleClickAction->setCurrentIndex(mainDoubleClickAction);
    this->ui->comboBoxTaskDoubleClickAction->setCurrentIndex(taskDoubleClickAction);

    //下拉列表居中
    QStandardItemModel* modelLanguage =  static_cast<QStandardItemModel*>(this->ui->comboBoxLanguage->model());
    if(modelLanguage)
    {
        for(int i = 0; i < modelLanguage->rowCount(); i ++)
        {
            if(modelLanguage->item(i))
                modelLanguage->item(i)->setTextAlignment(Qt::AlignCenter);
        }
    }
    QStandardItemModel* modelStockShow =  static_cast<QStandardItemModel*>(this->ui->comboBoxStockShow->model());
    if(modelStockShow)
    {
        for(int i = 0; i < modelStockShow->rowCount(); i ++)
        {
            if(modelStockShow->item(i))
                modelStockShow->item(i)->setTextAlignment(Qt::AlignCenter);
        }
    }

    ddccli::populateHandlesMap();
    for(int i = 0 ; i < ddccli::handles.size() ; i++){
        QStringList monitorName = ddccli::handles[i].name.split("#");
        if(monitorName.size() == 4){
            this->ui->comboBoxMonitor->addItem(monitorName[1]);
        }
        else{
            this->ui->comboBoxMonitor->addItem(ddccli::handles[i].name);
        }
    }
    currentMonitorIndex = 0;
    ddccli::MonitorBrightness mb = ddccli::getMonitorBrightness(ddccli::handles[currentMonitorIndex].handle);
    ddccli::MonitorContrast mc = ddccli::getMonitorContrast(ddccli::handles[currentMonitorIndex].handle);
    if((mb.currentBrightness == 0 && mb.maximumBrightness == 0) || (mc.currentContrast == 0 && mc.maximumContrast == 0)){
        QMessageBox::information(this, tr("提示"), tr("该显示器不支持DDC/CI命令！"));
    }
    else{
        this->ui->horizontalSliderMonitorBrightness->setRange(0,mb.maximumBrightness);
        this->ui->horizontalSliderMonitorBrightness->setValue(mb.currentBrightness);
        this->ui->horizontalSliderMonitorContrast->setRange(0,mc.maximumContrast);
        this->ui->horizontalSliderMonitorContrast->setValue(mc.currentContrast);
        this->ui->labelMonitorBrightnessValue->setText(QString::number(mb.currentBrightness));
        this->ui->labelMonitorContrastValue->setText(QString::number(mc.currentContrast));
    }

    if(getNofX(mainShowInfo,1)){
        this->ui->checkBoxMainUploadSpeed->setChecked(true);
    }
    if(getNofX(mainShowInfo,2)){
        this->ui->checkBoxMainDownloadSpeed->setChecked(true);
    }
    if(getNofX(mainShowInfo,3)){
        this->ui->checkBoxMainCPUUtil->setChecked(true);
    }
    if(getNofX(mainShowInfo,4)){
        this->ui->checkBoxMainMemoryUtil->setChecked(true);
    }
    if(getNofX(mainShowInfo,5)){
        this->ui->checkBoxMainMBTemp->setChecked(true);
    }
    if(getNofX(mainShowInfo,6)){
        this->ui->checkBoxMainMBFan->setChecked(true);
    }
    if(getNofX(mainShowInfo,7)){
        this->ui->checkBoxMainCPUTemp->setChecked(true);
    }
    if(getNofX(mainShowInfo,8)){
        this->ui->checkBoxMainGPUTemp->setChecked(true);
    }
    if(getNofX(mainShowInfo,9)){
        this->ui->checkBoxMainCPUPower->setChecked(true);
    }
    if(getNofX(mainShowInfo,10)){
        this->ui->checkBoxMainGPUPower->setChecked(true);
    }
    if(getNofX(mainShowInfo,11)){
        this->ui->checkBoxMainGPUUtil->setChecked(true);
    }
    if(getNofX(mainShowInfo,12)){
        this->ui->checkBoxMainHardDiskTemp->setChecked(true);
    }

    if(getNofX(taskShowInfo,1)){
        this->ui->checkBoxTaskUploadSpeed->setChecked(true);
    }
    if(getNofX(taskShowInfo,2)){
        this->ui->checkBoxTaskDownloadSpeed->setChecked(true);
    }
    if(getNofX(taskShowInfo,3)){
        this->ui->checkBoxTaskCPUUtil->setChecked(true);
    }
    if(getNofX(taskShowInfo,4)){
        this->ui->checkBoxTaskMemoryUtil->setChecked(true);
    }
    if(getNofX(taskShowInfo,5)){
        this->ui->checkBoxTaskMBTemp->setChecked(true);
    }
    if(getNofX(taskShowInfo,6)){
        this->ui->checkBoxTaskMBFan->setChecked(true);
    }
    if(getNofX(taskShowInfo,7)){
        this->ui->checkBoxTaskCPUTemp->setChecked(true);
    }
    if(getNofX(taskShowInfo,8)){
        this->ui->checkBoxTaskGPUTemp->setChecked(true);
    }
    if(getNofX(taskShowInfo,9)){
        this->ui->checkBoxTaskCPUPower->setChecked(true);
    }
    if(getNofX(taskShowInfo,10)){
        this->ui->checkBoxTaskGPUPower->setChecked(true);
    }
    if(getNofX(taskShowInfo,11)){
        this->ui->checkBoxTaskGPUUtil->setChecked(true);
    }
    if(getNofX(taskShowInfo,12)){
        this->ui->checkBoxTaskHardDiskTemp->setChecked(true);
    }

    connect(this->ui->comboBoxLanguage , SIGNAL(currentIndexChanged(int))  ,this , SLOT(comboBoxLanguage_currentIndexChanged(int)));
    connect(this->ui->checkBoxFontWeight , SIGNAL(stateChanged(int))  ,this , SLOT(checkBox_stateChanged(int)));
    connect(this->ui->comboBoxStockShow , SIGNAL(currentIndexChanged(int)) , this , SLOT(comboBoxStockShow_currentIndexChanged(int)));
    connect(this->ui->checkBoxHideMainWindow , SIGNAL(stateChanged(int))  ,this , SLOT(checkBoxHideMainWindow_stateChanged(int)));
    connect(this->ui->checkBoxQuickLook , SIGNAL(stateChanged(int))  ,this , SLOT(checkBoxQuickLook_stateChanged(int)));
    connect(this->ui->comboBoxMainDoubleClickAction , SIGNAL(currentIndexChanged(int)) , this , SLOT(comboBoxMainDoubleClickAction_currentIndexChanged(int)));
    connect(this->ui->comboBoxTaskDoubleClickAction , SIGNAL(currentIndexChanged(int)) , this , SLOT(comboBoxTaskDoubleClickAction_currentIndexChanged(int)));
    connect(this->ui->horizontalSliderMonitorContrast , SIGNAL(valueChanged(int)) , this , SLOT(horizontalSliderMonitorContrast_valueChanged(int)));
    connect(this->ui->horizontalSliderMonitorBrightness , SIGNAL(valueChanged(int)) , this , SLOT(horizontalSliderMonitorBrightness_valueChanged(int)));
    connect(this->ui->comboBoxUpdateTime , SIGNAL(currentIndexChanged(int)) , this , SLOT(comboBoxUpdateTime_currentIndexChanged(int)));

    connect(this->ui->checkBoxMainUploadSpeed , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainUploadSpeed_stateChanged(int)));
    connect(this->ui->checkBoxMainDownloadSpeed , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainDownloadSpeed_stateChanged(int)));
    connect(this->ui->checkBoxMainCPUUtil , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainCPUUtil_stateChanged(int)));
    connect(this->ui->checkBoxMainMemoryUtil , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainMemoryUtil_stateChanged(int)));
    connect(this->ui->checkBoxMainMBTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainMBTemp_stateChanged(int)));
    connect(this->ui->checkBoxMainMBFan , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainMBFan_stateChanged(int)));
    connect(this->ui->checkBoxMainCPUTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainCPUTemp_stateChanged(int)));
    connect(this->ui->checkBoxMainGPUTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainGPUTemp_stateChanged(int)));
    connect(this->ui->checkBoxMainCPUPower , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainCPUPower_stateChanged(int)));
    connect(this->ui->checkBoxMainGPUPower , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainGPUPower_stateChanged(int)));
    connect(this->ui->checkBoxMainGPUUtil , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainGPUUtil_stateChanged(int)));
    connect(this->ui->checkBoxMainHardDiskTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxMainHardDiskTemp_stateChanged(int)));

    connect(this->ui->checkBoxTaskUploadSpeed , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskUploadSpeed_stateChanged(int)));
    connect(this->ui->checkBoxTaskDownloadSpeed , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskDownloadSpeed_stateChanged(int)));
    connect(this->ui->checkBoxTaskCPUUtil , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskCPUUtil_stateChanged(int)));
    connect(this->ui->checkBoxTaskMemoryUtil , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskMemoryUtil_stateChanged(int)));
    connect(this->ui->checkBoxTaskMBTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskMBTemp_stateChanged(int)));
    connect(this->ui->checkBoxTaskMBFan , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskMBFan_stateChanged(int)));
    connect(this->ui->checkBoxTaskCPUTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskCPUTemp_stateChanged(int)));
    connect(this->ui->checkBoxTaskGPUTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskGPUTemp_stateChanged(int)));
    connect(this->ui->checkBoxTaskCPUPower , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskCPUPower_stateChanged(int)));
    connect(this->ui->checkBoxTaskGPUPower , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskGPUPower_stateChanged(int)));
    connect(this->ui->checkBoxTaskGPUUtil , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskGPUUtil_stateChanged(int)));
    connect(this->ui->checkBoxTaskHardDiskTemp , SIGNAL(stateChanged(int)) , this , SLOT(checkBoxTaskHardDiskTemp_stateChanged(int)));
}

Setting::~Setting()
{
    delete ui;
}

bool Setting::IsWow64()
{
  BOOL bIsWow64 = FALSE;
  //IsWow64Process is not available on all supported versions of Windows.
  //Use GetModuleHandle to get a handle to the DLL that contains the function
  //and GetProcAddress to get a pointer to the function if available.
  fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
  GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
  if(NULL != fnIsWow64Process)
  {
    if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
    {
      //handle error
    }
  }
  return bIsWow64;
}

//设置程序自启动 appPath程序路径 b是否自启动
void Setting::SetProcessAutoRunSelf(const QString &appPath , bool b)
{
    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);

    //以程序名称作为注册表中的键
    //根据键获取对应的值（程序路径）
    QFileInfo fInfo(appPath);
    QString name = fInfo.baseName();
    QString path = reg.value(name).toString();

    //如果注册表中的路径和当前程序路径不一样，
    //则表示没有设置自启动或自启动程序已经更换了路径
    //toNativeSeparators的意思是将"/"替换为"\"
    QString newPath = QDir::toNativeSeparators(appPath);
    if(b){
        if (path != newPath)
        {
            reg.setValue(name , newPath);
        }
    }
    else{
        reg.setValue(name , "");
    }

    qDebug()<<"AutoStart"<<appPath;
}

//设置程序屏幕保护
void Setting::SetProcessScreenProtect()
{
    QProcess p(0);
    QString command = "rundll32.exe desk.cpl,InstallScreenSaver ScreenProtection.scr";
    p.start(command);  //command是要执行的命令
    p.waitForFinished(); //等待完成
}

//开机自启动
void Setting::on_checkBoxAutoStart_stateChanged(int arg1)
{
    if(arg1){
        SetProcessAutoRunSelf(qApp->applicationFilePath() , true);
        Config().Set("Setting" , "AutoStart" , "1");
    }
    else{
        SetProcessAutoRunSelf(qApp->applicationFilePath() , false);
        Config().Set("Setting" , "AutoStart" , "0");
    }
}

void Setting::on_pushButtonSetScreenProtect_clicked()
{
    SetProcessScreenProtect();
}

void Setting::comboBoxLanguage_currentIndexChanged(int index)
{
    if(translator != NULL)
    {
        qApp->removeTranslator(translator);
        delete translator;
        translator = NULL;
    }
    translator = new QTranslator;
    QString qmFilename;
    if(index == LANGCHINESE){//简体中文
        qmFilename = ":/lang_Chinese.qm";
        if (translator->load(qmFilename))
        {
            qApp->installTranslator(translator);
        }
        ui->retranslateUi(this);
        Config().Set("Setting" , "Language" , "Chinese");
    }
    else if(index == LANGTRADCHINESE){//繁体中文
        qmFilename = ":/lang_TraditionalChinese.qm";
        if (translator->load(qmFilename))
        {
            qApp->installTranslator(translator);
        }
        ui->retranslateUi(this);
        Config().Set("Setting" , "Language" , "TraditionalChinese");
    }
    else if(index == LANGENGLISH){//英文
        qmFilename = ":/lang_English.qm";
        if (translator->load(qmFilename))
        {
            qApp->installTranslator(translator);
        }
        ui->retranslateUi(this);
        Config().Set("Setting" , "Language" , "English");
    }
    //重启应用程序
    qApp->exit(1007);

}

void Setting::on_pushButtonSetFont_clicked()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok , this);
    if(ok){
        this->ui->labelFontResult->setText(f.family() + " " + QString::number(f.pointSize()));
        Config().Set("Setting" , "FontFamily" , f.family());
        Config().Set("Setting" , "FontSize" , f.pointSize());
        f.setWeight(QFont::Normal);
        qApp->setFont(f);
    }
}

void Setting::checkBox_stateChanged(int arg1)
{
    if(arg1){
        QFont f = qApp->font();
        qApp->setFont(QFont(f.family() , f.pointSize() , QFont::Bold));
        Config().Set("Setting" , "FontWeight" , QFont::Bold);
    }
    else{
        QFont f = qApp->font();
        qApp->setFont(QFont(f.family() , f.pointSize() , QFont::Normal));
        Config().Set("Setting" , "FontWeight" , QFont::Normal);
    }
}

void Setting::comboBoxStockShow_currentIndexChanged(int index)
{
    Config().Set("Setting" , "StockShow" , index);
}

void Setting::on_pushButtonSetHotkey_clicked()
{
    ShortcutSetDialog * ssd = new ShortcutSetDialog(this);
    ssd->show();
}

void Setting::on_pushButtonMainChooseFont_clicked()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok , this);
    if(ok){
        this->ui->labelMainFont->setText(f.family() + " " + QString::number(f.pointSize()));
        Config().Set("Setting" , "MainFontFamily" , f.family());
        Config().Set("Setting" , "MainFontSize" , f.pointSize());
    }
}

void Setting::on_pushButtonMainChooseColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black,this, tr("选择你要的颜色"));
    //如果颜色无效
    if(!color.isValid())
    {
         return;
    }
    else{
        QString strDecimalValue = tr("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        QString str = tr("background-color: rgb(%1)").arg(strDecimalValue);
        this->ui->labelMainColor->setStyleSheet(str);
        Config().Set("Setting" , "MainFontColor" , strDecimalValue);
        mainColor = strDecimalValue;
    }
}

void Setting::on_pushButtonTaskChooseFont_clicked()
{
    bool ok;
    QFont f = QFontDialog::getFont(&ok , this);
    if(ok){
        this->ui->labelTaskFont->setText(f.family() + " " + QString::number(f.pointSize()));
        Config().Set("Setting" , "TaskFontFamily" , f.family());
        Config().Set("Setting" , "TaskFontSize" , f.pointSize());
    }
}

void Setting::on_pushButtonTaskChooseColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black,this, tr("选择你要的颜色"));
    //如果颜色无效
    if(!color.isValid())
    {
         return;
    }
    else{
        QString strDecimalValue = tr("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        QString str = tr("background-color: rgb(%1)").arg(strDecimalValue);
        this->ui->labelTaskColor->setStyleSheet(str);
        Config().Set("Setting" , "TaskFontColor" , strDecimalValue);
        taskColor = strDecimalValue;
    }
}

void Setting::checkBoxHideMainWindow_stateChanged(int arg1)
{
    if(arg1){
        Config().Set("Setting" , "IsShowMainWindowFullScreen" , Qt::Checked);
        isShowMainWindowFullScreen = false;
    }
    else{
        Config().Set("Setting" , "IsShowMainWindowFullScreen" , Qt::Unchecked);
        isShowMainWindowFullScreen = true;
    }
}

void Setting::on_pushButtonMainChooseColorBK_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black,this, tr("选择你要的颜色"));
    //如果颜色无效
    if(!color.isValid())
    {
         return;
    }
    else{
        QString strDecimalValue = tr("%1, %2, %3").arg(color.red()).arg(color.green()).arg(color.blue());
        QString str = tr("background-color: rgb(%1)").arg(strDecimalValue);
        this->ui->labelMainColorBK->setStyleSheet(str);
        Config().Set("Setting" , "MainFontColorBK" , strDecimalValue);
        mainColorBK = strDecimalValue;
    }
}

void Setting::checkBoxQuickLook_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        isQuickLook = 2;
        Config().Set("Setting" , "QuickLook" , 2);
    }
    else if(arg1 == Qt::Unchecked){
        isQuickLook = 1;
        Config().Set("Setting" , "QuickLook" , 1);
    }
}

void Setting::comboBoxMainDoubleClickAction_currentIndexChanged(int index)
{
    if(index == DoubleClickAction::CUSTOM)
    {
        QString fileName = QFileDialog::getOpenFileName(this,tr("选择文件"),".","*.exe");
        if(fileName.length() != 0){
            Config().Set("Setting" , "MainDoubleClickActionPath" , fileName);
            QFontMetrics fontWidth(ui->labelMainDoubleClickPath->font());//得到每个字符的宽度
            QString elideNote = fontWidth.elidedText(fileName, Qt::ElideRight, 220);//最大宽度150像素
            this->ui->labelMainDoubleClickPath->setText(elideNote);
            this->ui->labelMainDoubleClickPath->setToolTip(fileName);
            mainDoubleClick = index;
            Config().Set("Setting" , "MainDoubleClickAction" , index);
        }
        else{
            this->ui->comboBoxMainDoubleClickAction->setCurrentIndex(mainDoubleClick);
        }
    }
    else{
        mainDoubleClick = index;
        this->ui->labelMainDoubleClickPath->setText(tr("未选择自定义打开程序"));
    }
}

void Setting::comboBoxTaskDoubleClickAction_currentIndexChanged(int index)
{
    if(index == DoubleClickAction::CUSTOM)
    {
        QString fileName = QFileDialog::getOpenFileName(this,tr("选择文件"),".","*.exe");
        qDebug()<<"fileName.length():"<<fileName.length();
        if(fileName.length() != 0){
            Config().Set("Setting" , "TaskDoubleClickActionPath" , fileName);
            QFontMetrics fontWidth(ui->labelTaskDoubleClickPath->font());//得到每个字符的宽度
            QString elideNote = fontWidth.elidedText(fileName, Qt::ElideRight, 220);//最大宽度150像素
            this->ui->labelTaskDoubleClickPath->setText(elideNote);
            this->ui->labelTaskDoubleClickPath->setToolTip(fileName);
            taskDoubleClick = index;
            Config().Set("Setting" , "TaskDoubleClickAction" , index);
        }
        else{
            this->ui->comboBoxTaskDoubleClickAction->setCurrentIndex(taskDoubleClick);
        }
    }
    else{
        taskDoubleClick = index;
        this->ui->labelTaskDoubleClickPath->setText(tr("未选择自定义打开程序"));
    }
}

void Setting::on_comboBoxMonitor_currentIndexChanged(int index)
{
    ddccli::MonitorBrightness mb = ddccli::getMonitorBrightness(ddccli::handles[index].handle);
    ddccli::MonitorContrast mc = ddccli::getMonitorContrast(ddccli::handles[index].handle);
    if(mb.currentBrightness == 0 && mb.maximumBrightness == 0){
        QMessageBox::information(this, tr("提示"), tr("该显示器不支持DDC/CI命令！"));
        this->ui->comboBoxMonitor->setCurrentIndex(currentMonitorIndex);
        return;
    }
    else{
        this->ui->horizontalSliderMonitorBrightness->rangeChanged(0 , mb.maximumBrightness);
        horizontalSliderMonitorBrightness_valueChanged(mb.currentBrightness);
    }

    if(mc.currentContrast == 0 && mc.maximumContrast == 0){
        QMessageBox::information(this, tr("提示"), tr("该显示器不支持DDC/CI命令！"));
        this->ui->comboBoxMonitor->setCurrentIndex(currentMonitorIndex);
        return;
    }
    else{
        this->ui->horizontalSliderMonitorContrast->rangeChanged(0,mc.maximumContrast);
        horizontalSliderMonitorContrast_valueChanged(mc.currentContrast);
    }
    currentMonitorIndex = index;
}

void Setting::horizontalSliderMonitorBrightness_valueChanged(int value)
{
    if(currentMonitorIndex < ddccli::handles.size()){
        ddccli::setMonitorBrightness(ddccli::handles[currentMonitorIndex].handle , value);
        this->ui->labelMonitorBrightnessValue->setText(QString::number(value));
    }
}

void Setting::horizontalSliderMonitorContrast_valueChanged(int value)
{
    if(currentMonitorIndex < ddccli::handles.size()){
        ddccli::setMonitorContrast(ddccli::handles[currentMonitorIndex].handle , value);
        this->ui->labelMonitorContrastValue->setText(QString::number(value));
    }
}

void Setting::checkBoxMainUploadSpeed_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 1);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 1);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainDownloadSpeed_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 2);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 2);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainCPUUtil_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 3);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 3);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainMemoryUtil_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 4);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 4);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainMBTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 5);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 5);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainMBFan_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 6);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 6);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainCPUTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 7);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 7);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainGPUTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 8);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 8);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainCPUPower_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 9);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 9);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainGPUPower_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 10);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 10);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainGPUUtil_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 11);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 11);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxMainHardDiskTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(mainShowInfo , 12);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(mainShowInfo , 12);
    }
    Config().Set("Setting" , "MainShowInfo" , mainShowInfo);
}

void Setting::checkBoxTaskUploadSpeed_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 1);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 1);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskDownloadSpeed_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 2);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 2);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskCPUUtil_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 3);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 3);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskMemoryUtil_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 4);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 4);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskMBTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 5);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 5);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskMBFan_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 6);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 6);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskCPUTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 7);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 7);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskGPUTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 8);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 8);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskCPUPower_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 9);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 9);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskGPUPower_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 10);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 10);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskGPUUtil_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 11);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 11);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::checkBoxTaskHardDiskTemp_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        setNofXto1(taskShowInfo , 12);
    }
    else if(arg1 == Qt::Unchecked){
        setNofXto0(taskShowInfo , 12);
    }
    Config().Set("Setting" , "TaskShowInfo" , taskShowInfo);
}

void Setting::comboBoxUpdateTime_currentIndexChanged(int index)
{
    Config().Set("Setting" , "UpdateTime" , index);
}
