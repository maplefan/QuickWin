#include "CStockSignal.h"
#include <QDebug>

bool getStockInfo(QString& stockInfo , const QString URLSTOCK)
{
    QUrl url(URLSTOCK);
    QNetworkAccessManager manager;
    QEventLoop loop;
    QTextCodec *codec;
    QNetworkReply *reply;

    //qDebug() << "Reading html code form " << URLSTOCK;
    reply = manager.get(QNetworkRequest(url));
    //请求结束并下载完成后，退出子事件循环
    QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    //开启子事件循环
    loop.exec();

    codec = QTextCodec::codecForName("gbk");
    QString codeContent = codec->toUnicode(reply->readAll());

    //一定要注意编码问题，否则很容易出现乱码的
    //codec = QTextCodec::codecForHtml(codeContent.toLatin1());
    //codeContent = codec->toUnicode(codeContent.toLatin1());
    stockInfo = codeContent;
    return  true;
}

CStockSignal::CStockSignal(QObject * parent)
    : QThread(parent)
{
    m_timerSlot = NULL;
    m_timer = NULL;
}

CStockSignal::~CStockSignal()
{
    m_timer->stop();
    m_timer->deleteLater();
}

void CStockSignal::run()
{
    m_timer = new QTimer();
    m_timerSlot = new CStockTimerSlot();
    m_timerSlot->setStockList(this->stockList);
    m_timerSlot->OnTimerout();
    connect(m_timer , SIGNAL(timeout()) , m_timerSlot , SLOT(OnTimerout()));
    connect(m_timerSlot , &CStockTimerSlot::statusChanged , this , &CStockSignal::statusChanged);
    //qDebug() << "start thread:" <<QThread::currentThreadId();
    m_timer->start(10000);
    exec();
}

void CStockSignal::setStockList(QString str)
{
    this->stockList = str;
    if(m_timerSlot != NULL){
        m_timerSlot->setStockList(str);
    }
}

CStockTimerSlot::CStockTimerSlot(QObject * parent)
{

}

void CStockTimerSlot::OnTimerout()
{
    //定时的耗时操作
    //qDebug()<<"CSignal::OnTimerOut(),threadid:"<<QThread::currentThreadId();
    QString url = "http://qt.gtimg.cn/q="+getStockList();

    QString stockData;
    getStockInfo(stockData , url);
    emit statusChanged(stockData , getStockList());
}

void CStockTimerSlot::setStockList(QString str)
{
    this->stockList = str;
}

QString CStockTimerSlot::getStockList()
{
    //qDebug()<<"getStockList";
    return this->stockList;
}
