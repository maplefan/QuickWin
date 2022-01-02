#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef GETPUBLICIPTHREAD_H
#define GETPUBLICIPTHREAD_H

#include <QObject>
#include <QThread>

class GetPublicIPThread: public QThread
{
Q_OBJECT
public:
    GetPublicIPThread();
    void run();

private:
    QString publicIP;
signals:
     // 自定义信号
     void send2UI(QString str);
};

#endif // GETPUBLICIPTHREAD_H
