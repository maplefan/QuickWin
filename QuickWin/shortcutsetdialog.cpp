#include "shortcutsetdialog.h"
#include "ui_shortcutsetdialog.h"

extern MyGlobalShortCut *shortcutStock;
extern MyGlobalShortCut *shortcutHardware;
extern MyGlobalShortCut *shortcutMainTool;
extern MyGlobalShortCut *shortcutReminder;
extern MyGlobalShortCut *shortcutScreenShot;
extern MyGlobalShortCut *shortcutStickyNote;
extern MyGlobalShortCut *shortcutColorPicker;
extern MyGlobalShortCut *shortcutTaskManager;
extern MyGlobalShortCut *shortcutHotkeyManager;
extern MyGlobalShortCut *shortcutTranslator;
extern MyGlobalShortCut *shortcutSearch;

ShortcutSetDialog::ShortcutSetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortcutSetDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    Qt::WindowFlags flags = Qt::Dialog;flags |=Qt::WindowCloseButtonHint;
    setWindowFlags(flags);
    setWindowTitle(tr("快捷键设置"));

    isStockTipNormal = false;
    isHardwareTipNormal = false;
    isMainToolTipNormal = false;
    isReminderTipNormal = false;
    isScreenShotTipNormal = false;
    isStickyNoteTipNormal = false;
    isColorPickerTipNormal = false;
    isTaskManagerTipNormal = false;
    isHotkeyManagerTipNormal = false;
    isSearchTipNormal = false;
    isTranslatorTipNormal = false;

    QString configStock = Config().Get("Shortcut" , "Stock").toString();
    QString configHardware = Config().Get("Shortcut" , "Hardware").toString();
    QString configMainTool = Config().Get("Shortcut" , "MainTool").toString();
    QString configReminder = Config().Get("Shortcut" , "Reminder").toString();
    QString configScreenShot = Config().Get("Shortcut" , "ScreenShot").toString();
    QString configStickyNote = Config().Get("Shortcut" , "StickyNote").toString();
    QString configColorPicker = Config().Get("Shortcut" , "ColorPicker").toString();
    QString configTaskManager = Config().Get("Shortcut" , "TaskManager").toString();
    QString configHotkeyManager = Config().Get("Shortcut" , "HotkeyManager").toString();
    QString configTranslator = Config().Get("Shortcut" , "Translator").toString();
    QString configSearch = Config().Get("Shortcut" , "Search").toString();

    this->ui->lineEditStock->setText(configStock);
    this->ui->lineEditHardware->setText(configHardware);
    this->ui->lineEditMainTool->setText(configMainTool);
    this->ui->lineEditReminder->setText(configReminder);
    this->ui->lineEditScreenShot->setText(configScreenShot);
    this->ui->lineEditStickyNote->setText(configStickyNote);
    this->ui->lineEditColorPicker->setText(configColorPicker);
    this->ui->lineEditTaskManager->setText(configTaskManager);
    this->ui->lineEditHotkeyManager->setText(configHotkeyManager);
    if(configTranslator.length() != 0){
        this->ui->lineEditTranslator->setText(configTranslator);
    }
    else{
        this->ui->lineEditTranslator->setText("Ctrl+3");
    }
    if(configSearch.length() != 0){
        this->ui->lineEditSearch->setText(configSearch);
    }
    else{
        this->ui->lineEditSearch->setText("Ctrl+Space");
    }

    this->ui->lineEditScreenShot->installEventFilter(this);
    this->ui->lineEditStock->installEventFilter(this);
    this->ui->lineEditHardware->installEventFilter(this);
    this->ui->lineEditMainTool->installEventFilter(this);
    this->ui->lineEditReminder->installEventFilter(this);
    this->ui->lineEditStickyNote->installEventFilter(this);
    this->ui->lineEditColorPicker->installEventFilter(this);
    this->ui->lineEditTaskManager->installEventFilter(this);
    this->ui->lineEditHotkeyManager->installEventFilter(this);
    this->ui->lineEditTranslator->installEventFilter(this);
    this->ui->lineEditSearch->installEventFilter(this);
}

ShortcutSetDialog::~ShortcutSetDialog()
{
    delete ui;
}

void ShortcutSetDialog::showMessage(QString msg)
{
    QMessageBox::information(this, tr("信息"), msg, QMessageBox::Ok,QMessageBox::NoButton);
}

bool ShortcutSetDialog::eventFilter(QObject *target, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        int uKey = keyEvent->key();
        Qt::Key key = static_cast<Qt::Key>(uKey);
        if(key == Qt::Key_unknown)
        {
           //nothing {unknown key}
        }

        if(key == Qt::Key_Control || key == Qt::Key_Shift || key == Qt::Key_Alt )
        {
            return true;
        }

        //获取修饰键(Ctrl,Alt,Shift)的状态
        Qt::KeyboardModifiers modifiers = keyEvent->modifiers();
        //判断某个修饰键是否被按下
        if(modifiers & Qt::ShiftModifier)
            uKey += Qt::SHIFT;
        if(modifiers & Qt::ControlModifier)
            uKey += Qt::CTRL;
        if(modifiers & Qt::AltModifier)
            uKey += Qt::ALT;
        QLineEdit *lineEdit = static_cast<QLineEdit*>(target);
        lineEdit->setText(QKeySequence(uKey).toString(QKeySequence::NativeText));
        QMainWindow *w = qobject_cast<QMainWindow*>(parentWidget()->parentWidget());
        if(lineEdit == this->ui->lineEditStock){
            shortcutStock = new MyGlobalShortCut(this->ui->lineEditStock->text(), w);//注册热键
            if(shortcutStock->registerHotKey()){
                this->ui->labelStockTip->setStyleSheet("color:#1EC804;");
                this->ui->labelStockTip->setText(tr("正常"));
                shortcutStock->unregisterHotKey();
                isStockTipNormal = true;
            }
            else{
                this->ui->labelStockTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelStockTip->setText(tr("已被占用"));
                isStockTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditHardware){
            shortcutHardware = new MyGlobalShortCut(this->ui->lineEditHardware->text(), w);//注册热键
            if(shortcutHardware->registerHotKey()){
                this->ui->labelHardwareTip->setStyleSheet("color:#1EC804;");
                this->ui->labelHardwareTip->setText(tr("正常"));
                shortcutHardware->unregisterHotKey();
                isHardwareTipNormal = true;
            }
            else{
                this->ui->labelHardwareTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelHardwareTip->setText(tr("已被占用"));
                isHardwareTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditMainTool){
            shortcutMainTool = new MyGlobalShortCut(this->ui->lineEditMainTool->text(), w);//注册热键
            if(shortcutMainTool->registerHotKey()){
                this->ui->labelMainToolTip->setStyleSheet("color:#1EC804;");
                this->ui->labelMainToolTip->setText(tr("正常"));
                shortcutMainTool->unregisterHotKey();
                isMainToolTipNormal = true;
            }
            else{
                this->ui->labelMainToolTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelMainToolTip->setText(tr("已被占用"));
                isMainToolTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditReminder){
            shortcutReminder = new MyGlobalShortCut(this->ui->lineEditReminder->text(), w);//注册热键
            if(shortcutReminder->registerHotKey()){
                this->ui->labelReminderTip->setStyleSheet("color:#1EC804;");
                this->ui->labelReminderTip->setText(tr("正常"));
                shortcutReminder->unregisterHotKey();
                isReminderTipNormal = true;
            }
            else{
                this->ui->labelReminderTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelReminderTip->setText(tr("已被占用"));
                isReminderTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditScreenShot){
            shortcutScreenShot = new MyGlobalShortCut(this->ui->lineEditScreenShot->text(), w);//注册热键
            if(shortcutScreenShot->registerHotKey()){
                this->ui->labelScreenShotTip->setStyleSheet("color:#1EC804;");
                this->ui->labelScreenShotTip->setText(tr("正常"));
                shortcutScreenShot->unregisterHotKey();
                isScreenShotTipNormal = true;
            }
            else{
                this->ui->labelScreenShotTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelScreenShotTip->setText(tr("已被占用"));
                isScreenShotTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditStickyNote){
            shortcutStickyNote = new MyGlobalShortCut(this->ui->lineEditStickyNote->text(), w);//注册热键
            if(shortcutStickyNote->registerHotKey()){
                this->ui->labelStickyNoteTip->setStyleSheet("color:#1EC804;");
                this->ui->labelStickyNoteTip->setText(tr("正常"));
                shortcutStickyNote->unregisterHotKey();
                isStickyNoteTipNormal = true;
            }
            else{
                this->ui->labelStickyNoteTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelStickyNoteTip->setText(tr("已被占用"));
                isStickyNoteTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditColorPicker){
            shortcutColorPicker = new MyGlobalShortCut(this->ui->lineEditColorPicker->text(), w);//注册热键
            if(shortcutColorPicker->registerHotKey()){
                this->ui->labelColorPickerTip->setStyleSheet("color:#1EC804;");
                this->ui->labelColorPickerTip->setText(tr("正常"));
                shortcutColorPicker->unregisterHotKey();
                isColorPickerTipNormal = true;
            }
            else{
                this->ui->labelColorPickerTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelColorPickerTip->setText(tr("已被占用"));
                isColorPickerTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditTaskManager){
            shortcutTaskManager = new MyGlobalShortCut(this->ui->lineEditTaskManager->text(), w);//注册热键
            if(shortcutTaskManager->registerHotKey()){
                this->ui->labelTaskManagerTip->setStyleSheet("color:#1EC804;");
                this->ui->labelTaskManagerTip->setText(tr("正常"));
                shortcutTaskManager->unregisterHotKey();
                isTaskManagerTipNormal = true;
            }
            else{
                this->ui->labelTaskManagerTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelTaskManagerTip->setText(tr("已被占用"));
                isTaskManagerTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditHotkeyManager){
            shortcutHotkeyManager = new MyGlobalShortCut(this->ui->lineEditHotkeyManager->text(), w);//注册热键
            if(shortcutHotkeyManager->registerHotKey()){
                this->ui->labelHotkeyManagerTip->setStyleSheet("color:#1EC804;");
                this->ui->labelHotkeyManagerTip->setText(tr("正常"));
                shortcutHotkeyManager->unregisterHotKey();
                isHotkeyManagerTipNormal = true;
            }
            else{
                this->ui->labelHotkeyManagerTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelHotkeyManagerTip->setText(tr("已被占用"));
                isHotkeyManagerTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditTranslator){
            shortcutTranslator = new MyGlobalShortCut(this->ui->lineEditTranslator->text(), w);//注册热键
            if(shortcutTranslator->registerHotKey()){
                this->ui->labelTranslatorTip->setStyleSheet("color:#1EC804;");
                this->ui->labelTranslatorTip->setText(tr("正常"));
                shortcutTranslator->unregisterHotKey();
                isTranslatorTipNormal = true;
            }
            else{
                this->ui->labelTranslatorTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelTranslatorTip->setText(tr("已被占用"));
                isTranslatorTipNormal = false;
            }
        }
        else if(lineEdit == this->ui->lineEditSearch){
            shortcutSearch = new MyGlobalShortCut(this->ui->lineEditSearch->text(), w);//注册热键
            if(shortcutSearch->registerHotKey()){
                this->ui->labelSearchTip->setStyleSheet("color:#1EC804;");
                this->ui->labelSearchTip->setText(tr("正常"));
                shortcutSearch->unregisterHotKey();
                isSearchTipNormal = true;
            }
            else{
                this->ui->labelSearchTip->setStyleSheet("color:#FD4E50;");
                this->ui->labelSearchTip->setText(tr("已被占用"));
                isSearchTipNormal = false;
            }
        }

        return true;
    }
    return QDialog::eventFilter(target, event);
}

void ShortcutSetDialog::on_buttonBox_accepted()
{
    QMainWindow *w = qobject_cast<QMainWindow*>(parentWidget()->parentWidget());
    if(this->ui->lineEditStock->text() != Config().Get("Shortcut" , "Stock").toString()){
        Config().Set("Shortcut" , "Stock" , this->ui->lineEditStock->text());
        if(shortcutStock != NULL){
            shortcutStock->unregisterHotKey();
            delete  shortcutStock;
            shortcutStock = NULL;
        }
        if(isStockTipNormal){
            shortcutStock = new MyGlobalShortCut(this->ui->lineEditStock->text(), w);//注册热键
            shortcutStock->registerHotKey();
            QObject::connect(shortcutStock , SIGNAL(activated()) , w , SLOT(showStock()));
        }
        else{

        }
    }
    if(this->ui->lineEditHardware->text() != Config().Get("Shortcut" , "Hardware").toString()){
        Config().Set("Shortcut" , "Hardware" , this->ui->lineEditHardware->text());
        if(shortcutHardware != NULL){
            shortcutHardware->unregisterHotKey();
            delete shortcutHardware;
            shortcutHardware = NULL;
        }
        if(isHardwareTipNormal){
            shortcutHardware = new MyGlobalShortCut(this->ui->lineEditHardware->text(), w);//注册热键
            shortcutHardware->registerHotKey();
            QObject::connect(shortcutHardware , SIGNAL(activated()) , w , SLOT(showHardWare()));
        }
        else{

        }
    }
    if(this->ui->lineEditMainTool->text() != Config().Get("Shortcut" , "MainTool").toString()){
        Config().Set("Shortcut" , "MainTool" , this->ui->lineEditMainTool->text());
        if(shortcutMainTool != NULL){
            shortcutMainTool->unregisterHotKey();
            delete shortcutMainTool;
            shortcutMainTool = NULL;
        }
        if(isMainToolTipNormal){
            shortcutMainTool = new MyGlobalShortCut(this->ui->lineEditMainTool->text(), w);//注册热键
            shortcutMainTool->registerHotKey();
            QObject::connect(shortcutMainTool , SIGNAL(activated()) , w , SLOT(showMainTool()));
        }
        else{

        }
    }
    if(this->ui->lineEditReminder->text() != Config().Get("Shortcut" , "Reminder").toString()){
        Config().Set("Shortcut" , "Reminder" , this->ui->lineEditReminder->text());
        if(shortcutReminder != NULL){
            shortcutReminder->unregisterHotKey();
            delete shortcutReminder;
            shortcutReminder = NULL;
        }
        if(isReminderTipNormal){
            shortcutReminder = new MyGlobalShortCut(this->ui->lineEditReminder->text(), w);//注册热键
            shortcutReminder->registerHotKey();
            QObject::connect(shortcutReminder , SIGNAL(activated()) , w , SLOT(showTimeReminder()));
        }
        else{

        }
    }
    if(this->ui->lineEditScreenShot->text() != Config().Get("Shortcut" , "ScreenShot").toString()){
        Config().Set("Shortcut" , "ScreenShot" , this->ui->lineEditScreenShot->text());
        if(shortcutScreenShot != NULL){
            shortcutScreenShot->unregisterHotKey();
            delete shortcutScreenShot;
            shortcutScreenShot = NULL;
        }
        if(isScreenShotTipNormal){
            shortcutScreenShot = new MyGlobalShortCut(this->ui->lineEditScreenShot->text(), w);//注册热键
            shortcutScreenShot->registerHotKey();
            QObject::connect(shortcutScreenShot , SIGNAL(activated()) , w , SLOT(showCatchScreen()));
        }
        else{

        }
    }
    if(this->ui->lineEditStickyNote->text() != Config().Get("Shortcut" , "StickyNote").toString()){
        Config().Set("Shortcut" , "StickyNote" , this->ui->lineEditStickyNote->text());
        if(shortcutStickyNote != NULL){
            shortcutStickyNote->unregisterHotKey();
            delete shortcutStickyNote;
            shortcutStickyNote = NULL;
        }
        if(isStickyNoteTipNormal){
            shortcutStickyNote = new MyGlobalShortCut(this->ui->lineEditStickyNote->text(), w);//注册热键
            shortcutStickyNote->registerHotKey();
            QObject::connect(shortcutStickyNote , SIGNAL(activated()) , w , SLOT(showStickyNote()));
        }
        else{

        }
    }
    if(this->ui->lineEditColorPicker->text() != Config().Get("Shortcut" , "ColorPicker").toString()){
        Config().Set("Shortcut" , "ColorPicker" , this->ui->lineEditColorPicker->text());
        if(shortcutColorPicker != NULL){
            shortcutColorPicker->unregisterHotKey();
            delete shortcutColorPicker;
            shortcutColorPicker = NULL;
        }
        if(isColorPickerTipNormal){
            shortcutColorPicker = new MyGlobalShortCut(this->ui->lineEditColorPicker->text(), w);//注册热键
            shortcutColorPicker->registerHotKey();
            QObject::connect(shortcutColorPicker , SIGNAL(activated()) , w , SLOT(showCatchColor()));
        }
        else{

        }
    }
    if(this->ui->lineEditTaskManager->text() != Config().Get("Shortcut" , "TaskManager").toString()){
        Config().Set("Shortcut" , "TaskManager" , this->ui->lineEditTaskManager->text());
        if(shortcutTaskManager != NULL){
            shortcutTaskManager->unregisterHotKey();
            delete shortcutTaskManager;
            shortcutTaskManager = NULL;
        }
        if(isTaskManagerTipNormal){
            shortcutTaskManager = new MyGlobalShortCut(this->ui->lineEditTaskManager->text(), w);//注册热键
            shortcutTaskManager->registerHotKey();
            QObject::connect(shortcutTaskManager , SIGNAL(activated()) , w , SLOT(showTaskMgr()));
        }
        else{

        }
    }
    if(this->ui->lineEditHotkeyManager->text() != Config().Get("Shortcut" , "HotkeyManager").toString()){
        Config().Set("Shortcut" , "HotkeyManager" , this->ui->lineEditHotkeyManager->text());
        if(shortcutHotkeyManager != NULL){
            shortcutHotkeyManager->unregisterHotKey();
            delete shortcutHotkeyManager;
            shortcutHotkeyManager = NULL;
        }
        if(isHotkeyManagerTipNormal){
            shortcutHotkeyManager = new MyGlobalShortCut(this->ui->lineEditHotkeyManager->text(), w);//注册热键
            shortcutHotkeyManager->registerHotKey();
            QObject::connect(shortcutHotkeyManager , SIGNAL(activated()) , w , SLOT(showHotkeyManage()));
        }
        else{

        }
    }
    if(this->ui->lineEditTranslator->text() != Config().Get("Shortcut" , "Translator").toString()){
        Config().Set("Shortcut" , "Translator" , this->ui->lineEditTranslator->text());
        if(shortcutTranslator != NULL){
            shortcutTranslator->unregisterHotKey();
            delete shortcutTranslator;
            shortcutTranslator = NULL;
        }
        if(isTranslatorTipNormal){
            shortcutTranslator = new MyGlobalShortCut(this->ui->lineEditTranslator->text(), w);//注册热键
            shortcutTranslator->registerHotKey();
            QObject::connect(shortcutTranslator , SIGNAL(activated()) , w , SLOT(activatedTranslator()));
        }
        else{

        }
    }
    if(this->ui->lineEditSearch->text() != Config().Get("Shortcut" , "Search").toString()){
        Config().Set("Shortcut" , "Search" , this->ui->lineEditSearch->text());
        if(shortcutSearch != NULL){
            shortcutSearch->unregisterHotKey();
            delete shortcutSearch;
            shortcutSearch = NULL;
        }
        if(isSearchTipNormal){
            shortcutSearch = new MyGlobalShortCut(this->ui->lineEditSearch->text(), w);//注册热键
            shortcutSearch->registerHotKey();
            QObject::connect(shortcutSearch , SIGNAL(activated()) , w , SLOT(activatedSearch()));
        }
        else{

        }
    }
}
