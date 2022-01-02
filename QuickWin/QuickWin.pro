#-------------------------------------------------
#
# Project created by QtCreator 2020-02-13T17:33:18
#
#-------------------------------------------------

QT += core gui
QT += network
QT += axcontainer
QT += webenginewidgets webchannel
QT += widgets multimedia winextras
QT += multimediawidgets
QT += sql
CONFIG += c++11
CONFIG -= qtquickcompiler

#去除所有的qDebug()输出
DEFINES += QT_NO_DEBUG_OUTPUT

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

UI_DIR  = obj/Gui
MOC_DIR = obj/Moc
OBJECTS_DIR = obj/Obj

contains(QT_ARCH, i386) {
    message("32-bit")
    DESTDIR = $${PWD}/bin32
} else {
    message("64-bit")
    DESTDIR = $${PWD}/bin64
}

TARGET = QuickWin
TEMPLATE = app

RC_ICONS = images/tray.ico

include(module/VideoPlayer/VideoPlayer.pri)

include(module/DragAbleWidget/DragAbleWidget.pri)

#win32{
#QMAKE_CXXFLAGS += /source-charset:utf-8 /execution-charset:utf-8
#}

QMAKE_CXXFLAGS += -std=c++11

#管理员模式运行
QMAKE_LFLAGS += \"/MANIFESTUAC:level=\'requireAdministrator\' uiAccess=\'false\'\"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _USE_32BIT_TIME_T
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -luser32 # for using Windows API

SOURCES += \
    CSignal.cpp \
    CStockSignal.cpp \
    ColorItem.cpp \
    Common.cpp \
    Driver_Load.cpp \
    LinePaint.cpp \
    MyGlobalShortcut/MyGlobalShortCut.cpp \
    MyGlobalShortcut/MyWinEventFilter.cpp \
    PCSearch.cpp \
    PictureBox.cpp \
    PointSizeWidget.cpp \
    RectPaint.cpp \
    TextPaint.cpp \
    adapterinfo.cpp \
    addstockdialog.cpp \
    document.cpp \
    fileform.cpp \
    form.cpp \
    helpdlg.cpp \
    highlighter.cpp \
    hotkeymanage.cpp \
    htmlform.cpp \
    imageform.cpp \
    imageview.cpp \
    main.cpp \
    maintool.cpp \
    mainwindow.cpp \
    getnetinfothread.cpp \
    markdownForm.cpp \
    musicplayer.cpp \
    musicwindow.cpp \
    networkinfo.cpp \
    officeform.cpp \
    pdfform.cpp \
    previewpage.cpp \
    quicklook.cpp \
    quickstock.cpp \
    screenShot/controlwidget.cpp \
    screenShot/imageview.cpp \
    screenShot/qslabel.cpp \
    screenShot/screen.cpp \
    screenShot/selectwidget.cpp \
    screenShot/textselectwidget.cpp \
    screenview.cpp \
    selectedtext.cpp \
    setting.cpp \
    shortcutsetdialog.cpp \
    snappit.cpp \
    stickynote.cpp \
    stockreminddialog.cpp \
    systeminfowin.cpp \
    getpcinfowin.cpp \
    pcinfowindow.cpp \
    config.cpp \
    getpublicipthread.cpp \
    colorwidget.cpp \
    delegate.cpp \
    moduledlg.cpp \
    tableview.cpp \
    taskmgr.cpp \
    textForm.cpp \
    threaddlg.cpp \
    taskbar.cpp \
    timechoosedialog.cpp \
    timereminddialog.cpp \
    timereminder.cpp \
    timereminderwindow.cpp \
    translator.cpp \
    translatordlg.cpp \
    volumebutton.cpp \
    src/main.cpp \
    src/AppConfig.cpp \
    src/Base/FunctionTransfer.cpp \
    src/VideoForm.cpp \
    src/Widget/ShowVideoWidget.cpp \
    src/Widget/VideoSlider.cpp \
    words.cpp

HEADERS += \
    CGLIB_Common.hpp \
    CGLIB_String_Text.hpp \
    CSignal.h \
    CStockSignal.h \
    ColorItem.h \
    Common.h \
    Driver_Load.h \
    Everything.h \
    LinePaint.h \
    MyGlobalShortcut/MyGlobalShortCut.h \
    MyGlobalShortcut/MyWinEventFilter.h \
    PCSearch.h \
    PictureBox.h \
    PointSizeWidget.h \
    RectPaint.h \
    TextPaint.h \
    adapterinfo.h \
    addstockdialog.h \
    addstockdialog.h \
    ddccli.h \
    document.h \
    fileform.h \
    form.h \
    gethardware.h \
    helpdlg.h \
    highlighter.h \
    hotkeymanage.h \
    htmlform.h \
    imageform.h \
    imageview.h \
    maintool.h \
    mainwindow.h \
    markdownForm.h \
    musicplayer.h \
    musicwindow.h \
    networkinfo.h \
    officeform.h \
    pdfform.h \
    previewpage.h \
    quicklook.h \
    quickstock.h \
    screenShot/controlwidget.h \
    screenShot/imageview.h \
    screenShot/screen.h \
    screenShot/selectwidget.h \
    screenShot/textselectwidget.h \
    screenview.h \
    selectedtext.h \
    setting.h \
    shortcutsetdialog.h \
    snappit.h \
    stickynote.h \
    stockreminddialog.h \
    struct.h \
    systeminfowin.h \
    getnetinfothread.h \
    getpcinfowin.h \
    pcinfowindow.h \
    config.h \
    getpublicipthread.h \
    colorwidget.h \
    delegate.h \
    iview.h \
    moduledlg.h \
    tableview.h \
    taskmgr.h \
    textForm.h \
    threaddlg.h \
    systeminfo.h \
    taskbar.h \
    timechoosedialog.h \
    timereminddialog.h \
    timereminder.h \
    timereminderwindow.h \
    translator.h \
    translatordlg.h \
    volumebutton.h \
    src/AppConfig.h \
    src/Base/FunctionTransfer.h \
    src/VideoForm.h \
    src/Widget/ShowVideoWidget.h \
    src/Widget/VideoSlider.h \
    words.h

FORMS += \
    MarkdownForm.ui \
    Officeform.ui \
    PCSearch.ui \
    addstockdialog.ui \
    addstockdialog.ui \
    fileform.ui \
    fileitemdialog.ui \
    form.ui \
    helpdlg.ui \
    hotkeymanage.ui \
    htmlform.ui \
    imageform.ui \
    maintool.ui \
    mainwindow.ui \
    musicwindow.ui \
    networkinfo.ui \
    pcinfowindow.ui \
    pdfform.ui \
    quicklook.ui \
    quickstock.ui \
    screenShot/controlwidget.ui \
    screenShot/selectwidget.ui \
    screenShot/textselectwidget.ui \
    setting.ui \
    shortcutsetdialog.ui \
    snappit.ui \
    stickynote.ui \
    stockreminddialog.ui \
    taskmgr.ui \
    taskbar.ui \
    src/VideoForm.ui \
    src/Widget/ShowVideoWidget.ui \
    timechoosedialog.ui \
    timereminddialog.ui \
    timereminder.ui \
    timereminderwindow.ui \
    translator.ui

win32: LIBS += -L$$PWD/pdfium/lib/ -lPdf

INCLUDEPATH += $$PWD/pdfium/include

DEPENDPATH += $$PWD/pdfium/include

RESOURCES += \
    driver.qrc \
    maintools.qrc \
    resource.qrc \
    resources/markdowneditor.qrc \
    screenShot/res.qrc \
    translator.qrc
    resources/resources.qrc

RESOURCES += \
    images.qrc \

LIBS += -L$$PWD\Psapi.Lib

LIBS += -L$$PWD\dwmapi.lib

LIBS += -L$$PWD\ -liphlpapi
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lPsapi
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lPsapi

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/./Psapi.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/./Psapi.lib

win32: LIBS += -L$$PWD/./ -ldwmapi

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

INCLUDEPATH += $$PWD/src

DISTFILES +=

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./ -lEverything32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./ -lEverything32d
else:unix: LIBS += -L$$PWD/./ -lEverything32

TRANSLATIONS = lang_English.ts \
               lang_Chinese.ts \
               lang_TraditionalChinese.ts

win32 {
    src_dir = $$PWD\\pdfium\\lib\\Pdf.dll
    dst_dir = $$PWD\\bin32\\

    # dst_dir 最后的 \\ 是必须的，用来标示 xcopy 到一个文件夹，若不存在，创建之

    # Replace slashes in paths with backslashesfor Windows

    src_dir ~= s,/,\\,g

    dst_dir ~= s,/,\\,g

QMAKE_POST_LINK = copy $$src_dir $$dst_dir

}

