#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "helpdlg.h"
#include "ui_helpdlg.h"
#include <QUrl>
#include <QDesktopServices>
HelpDlg::HelpDlg(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HelpDlg)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setWindowTitle(tr("关于 QuickWin"));
    ui->labelBuildTime->setText(buildDateTime());
}

HelpDlg::~HelpDlg()
{
    delete ui;
}

void HelpDlg::on_authorBtn_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("mailto:dengxiaofan@hrbust.edu.cn")));
}

void HelpDlg::on_githubBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/maplefan/QuickWin"));
}

void HelpDlg::on_BlogBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://maplefan.com"));
}

void HelpDlg::on_donateBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/maplefan/QuickWin#捐助"));
}

void HelpDlg::on_thanksBtn_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/maplefan/QuickWin#鸣谢"));
}

void HelpDlg::on_okBtn_clicked()
{
    this->close();
}

static const QString buildDateTime()
{
    static const QDate buildDate = QLocale( QLocale::English ).toDate( QString( __DATE__ ).replace( "  ", " 0" ), "MMM dd yyyy");
    static const QTime buildTime = QTime::fromString( __TIME__, "hh:mm:ss" );
    QString dateTime;
    dateTime += buildDate.toString("yyyy-MM-dd");
    dateTime += " ";
    dateTime += buildTime.toString("hh:mm:ss");
    return "BuildTime : " + dateTime;
}
