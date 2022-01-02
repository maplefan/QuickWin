#include "translatordlg.h"
#include <QDebug>
#include <QThread>
#include <form.h>
#include <QCursor>
#include "QDesktopWidget"
#include <QMovie>
#include <QMessageBox>
#include "ui_translator.h"
TranslatorDlg::TranslatorDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TranslatorDlg)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setWindowFlags(Qt::SubWindow);
    m_timer = 0;
    onNotice = false;

    //qDebug() << str2 << endl;
    //ui->label->setText(str2);
    m_text = new SelectedText();

    connect(m_text,SIGNAL(newtextselected(QString)),this,SLOT(newselectedtext(QString)));

    MyGlobalShortCut* shortcut = new MyGlobalShortCut("Alt+3",this);
    connect(shortcut,SIGNAL(activated()),this,SLOT(activate()));

    /*this->setWindowIcon(QIcon(":/ico.png"));
    QIcon icon = QIcon( ":/ico.png" );
    trayIcon = new QSystemTrayIcon( this );
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr( "Translator" ));
    trayIcon->show();

    menu = new QMenu(this);
    exitExe = new QAction(tr("退出") , this);
    menu->addAction(exitExe);

    trayIcon->setContextMenu(menu);

    QObject::connect(exitExe,SIGNAL(triggered()),this,SLOT(quitExe()));
    */
    // 手动开启
    //activate();
    //activate();

}
void TranslatorDlg::activate()
{
    if(onNotice)
        return;

    if(m_text->working)
    {
        noticeWindow();
        m_text->uninstallHook();
    }
    else
    {
        noticeWindow();
        m_text->installHook();
    }
}

void TranslatorDlg::adjustWindowPos(Form *window)
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect deskRect;
    deskRect.setWidth(desktop->width());
    deskRect.setHeight(desktop->height());
    // 若窗体超出屏幕，进行调整
    QPoint point = QCursor::pos();
    int maxW = deskRect.width();
    int maxH = deskRect.height();

    int x = point.x()-window->width()/2;
    int y = point.y() + 20;
    int w = window->width();
    int h = window->height();


    if(x < 0)
    {
        x = 0;
    }

    if(x + w > maxW)
    {
        x = maxW - w;
    }
    if(y + h > maxH)
    {
        y = point.y() - h - 10;
    }

   window->setGeometry(x,y,w,h);


}



TranslatorDlg::~TranslatorDlg()
{
    delete ui;
}

void TranslatorDlg::noticeWindow()
{
//    QString str;
//    str = str.fromUtf8("开启划词翻译");
//    if(m_text->working == true)
//        str = str.fromUtf8("关闭划词翻译");

//    notice->setText(str);
//    notice->setStyleSheet("color:#094;font-family: Verdana,Geneva,sans-serif;font-size:50px;font-weight:bold;line-height: 1.25em;");
//    notice ->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
//    notice ->setAttribute(Qt::WA_TranslucentBackground);
//    notice ->show();
//    QDesktopWidget* desktopWidget = QApplication::desktop();
//    QRect deskRect = desktopWidget->screenGeometry();
//    int cenX = deskRect.width()/2;
//    int cenY = deskRect.height() * 0.4;
//    notice->setGeometry(cenX - notice->width()/2,cenY - notice->height()/2,notice->width(),notice->height());
//    m_timer = startTimer(1000);

    notice = new QLabel();

    onNotice = true;

    QMovie *movie;
    if(m_text->working)
        movie = new QMovie(":/off.gif");
    else
        movie = new QMovie(":/on.gif");
    notice->setMovie(movie);


    notice ->setAttribute(Qt::WA_TranslucentBackground);
    notice ->setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);

    notice->resize(200,200);
    notice->show();

    movie->start();
    m_timer = startTimer(1000);

}
void TranslatorDlg::timerEvent(QTimerEvent *)
{

    notice->hide();
    killTimer(m_timer);
    onNotice = false;
}

void TranslatorDlg::newselectedtext(QString str)
{

    if(str.indexOf("file:") == 0)
        return;
    Translator* translator = new Translator(this,str);
    connect(translator,SIGNAL(translateWordFinished(Words)),this,SLOT(translateWordFinished(Words)));
    connect(translator,SIGNAL(translateSentencesFinished(QString)),this,SLOT(translateSentencesFinished(QString)));
    translator->run();

}



void TranslatorDlg::translateWordFinished(Words word)
{
    //qDebug() << "第一个查询窗口" << endl;
    //qDebug() << word.explains << endl;
    Form* window = Form::Instance();
    window->setWord(word);
    window -> setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::SubWindow);
    window -> show();
    adjustWindowPos(window);
}

void TranslatorDlg::translateSentencesFinished(QString sentences)
{
    Form* window = Form::Instance();
    window->setSentences(sentences);
    window -> setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::SubWindow);
    window -> show();
    adjustWindowPos(window);
}

void TranslatorDlg::quitExe()
{
    exit(0);
}

bool TranslatorDlg::getOnNotice()
{
    return onNotice;
}

bool TranslatorDlg::getTextIsWorking()
{
    return m_text->working;
}

void TranslatorDlg::installHook(){
    m_text->installHook();
}

void TranslatorDlg::uninstallHook(){
    m_text->uninstallHook();
}
