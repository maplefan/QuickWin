#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "mainwindow.h"
#include <QApplication>
#include<MyGlobalShortCut/MyGlobalShortCut.h>
#define MUTEX_NAME L"QuickWin"

static QTranslator *qtl;
MyGlobalShortCut *shortcutStock = NULL;
MyGlobalShortCut *shortcutHardware = NULL;
MyGlobalShortCut *shortcutMainTool = NULL;
MyGlobalShortCut *shortcutReminder = NULL;
MyGlobalShortCut *shortcutScreenShot = NULL;
MyGlobalShortCut *shortcutStickyNote = NULL;
MyGlobalShortCut *shortcutColorPicker = NULL;
MyGlobalShortCut *shortcutTaskManager = NULL;
MyGlobalShortCut *shortcutHotkeyManager = NULL;
MyGlobalShortCut *shortcutSearch = NULL;
MyGlobalShortCut *shortcutTranslator = NULL;

bool IsSingleProcess()
{
    HANDLE hMutex = CreateMutex(NULL, FALSE, MUTEX_NAME);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ::CloseHandle(hMutex);
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

int main(int argc, char *argv[])
{
    if(!IsSingleProcess()){
        return 0;
    }
    QApplication a(argc, argv);
    if(qtl != NULL)
    {
        qApp->removeTranslator(qtl);
        delete qtl;
        qtl = NULL;
    }
    qtl = new QTranslator;
    QString qmFilename;
    QString language = Config().Get("Setting" , "Language").toString();
    QString fontFamily = Config().Get("Setting" , "FontFamily").toString();
    int fontWeight = Config().Get("Setting" , "FontWeight").toInt();
    int fontSize = Config().Get("Setting" , "FontSize").toInt();

    if(fontFamily.length() == 0 && fontSize == 0){
        fontFamily = "Microsoft YaHei";
        fontSize = 10;
        Config().Set("Setting" , "FontFamily" , fontFamily);
        Config().Set("Setting" , "FontSize" , fontSize);
    }

    if(fontWeight == 0){
        fontWeight = QFont::Normal;
        Config().Set("Setting" , "FontWeight" , fontWeight);
    }
    if(language.length() == 0){
        language = "Chinese";
        Config().Set("Setting" , "Language" , language);
    }

    a.setFont(QFont(fontFamily , fontSize , fontWeight));
    if(language == "Chinese"){
        qmFilename = ":/lang_Chinese.qm";
        if (qtl->load(qmFilename))
        {
            qApp->installTranslator(qtl);
        }
    }
    else if(language == "TraditionalChinese"){
        qmFilename = ":/lang_TraditionalChinese.qm";
        if (qtl->load(qmFilename))
        {
            qApp->installTranslator(qtl);
        }
    }
    else if(language == "English"){
        qmFilename = ":/lang_English.qm";
        if (qtl->load(qmFilename))
        {
            qApp->installTranslator(qtl);
        }
    }

    MainWindow w;
    a.installNativeEventFilter(&w);

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

    QSettings reg("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    if(reg.value("QuickWin").toString().length() != 0){
        Config().Set("Setting" , "AutoStart" , "1");
    }
    else{
        Config().Set("Setting" , "AutoStart" , "0");
    }

    if(configStock.length() != 0){
        shortcutStock = new MyGlobalShortCut(configStock,&w);
        shortcutStock->registerHotKey();
        QObject::connect(shortcutStock , SIGNAL(activated()) , &w , SLOT(showStock()));
    }
    if(configHardware.length() != 0){
        shortcutHardware = new MyGlobalShortCut(configHardware,&w);
        shortcutHardware->registerHotKey();
        QObject::connect(shortcutHardware , SIGNAL(activated()) , &w , SLOT(showHardWare()));
    }
    if(configMainTool.length() != 0){
        shortcutMainTool = new MyGlobalShortCut(configMainTool,&w);
        shortcutMainTool->registerHotKey();
        QObject::connect(shortcutMainTool , SIGNAL(activated()) , &w , SLOT(showMainTool()));
    }
    if(configReminder.length() != 0){
        shortcutReminder = new MyGlobalShortCut(configReminder,&w);
        shortcutReminder->registerHotKey();
        QObject::connect(shortcutReminder , SIGNAL(activated()) , &w , SLOT(showTimeReminder()));
    }
    if(configScreenShot.length() != 0){
        shortcutScreenShot = new MyGlobalShortCut(configScreenShot,&w);
        shortcutScreenShot->registerHotKey();
        QObject::connect(shortcutScreenShot , SIGNAL(activated()) , &w , SLOT(showCatchScreen()));
    }
    if(configStickyNote.length() != 0){
        shortcutStickyNote = new MyGlobalShortCut(configStickyNote,&w);
        shortcutStickyNote->registerHotKey();
        QObject::connect(shortcutStickyNote , SIGNAL(activated()) , &w , SLOT(showStickyNote()));
    }
    if(configColorPicker.length() != 0){
        shortcutColorPicker = new MyGlobalShortCut(configColorPicker,&w);
        shortcutColorPicker->registerHotKey();
        QObject::connect(shortcutColorPicker , SIGNAL(activated()) , &w , SLOT(showCatchColor()));
    }
    if(configTaskManager.length() != 0){
        shortcutTaskManager = new MyGlobalShortCut(configTaskManager,&w);
        shortcutTaskManager->registerHotKey();
        QObject::connect(shortcutTaskManager , SIGNAL(activated()) , &w , SLOT(showTaskMgr()));
    }
    if(configHotkeyManager.length() != 0){
        shortcutHotkeyManager = new MyGlobalShortCut(configHotkeyManager,&w);
        shortcutHotkeyManager->registerHotKey();
        QObject::connect(shortcutHotkeyManager , SIGNAL(activated()) , &w , SLOT(showHotkeyManage()));
    }

    if(configSearch.length() != 0){
        shortcutSearch = new MyGlobalShortCut(configSearch,&w);
        shortcutSearch->registerHotKey();
        QObject::connect(shortcutSearch , SIGNAL(activated()) , &w , SLOT(activatedSearch()));
    }
    else{
        shortcutSearch = new MyGlobalShortCut("Ctrl+Space",&w);
        shortcutSearch->registerHotKey();
        QObject::connect(shortcutSearch , SIGNAL(activated()) , &w , SLOT(activatedSearch()));
    }

    if(configTranslator.length() != 0){
        shortcutTranslator = new MyGlobalShortCut(configTranslator,&w);
        shortcutTranslator->registerHotKey();
        QObject::connect(shortcutTranslator , SIGNAL(activated()) , &w , SLOT(activatedTranslator()));
    }
    else{
        shortcutTranslator = new MyGlobalShortCut("Ctrl+3",&w);
        shortcutTranslator->registerHotKey();
        QObject::connect(shortcutTranslator , SIGNAL(activated()) , &w , SLOT(activatedTranslator()));
    }

    w.setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    w.show();

    int e = a.exec();
    if(e == 1007){
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        return 0;
    }

    return e;
}
