#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef CSIGNAL_H
#define CSIGNAL_H

#include <QThread>
#include <QTimer>
#include <QLibrary>
#include <QMessageBox>

class CTimerSlot : public QObject
{
    Q_OBJECT
public:
    CTimerSlot(QObject * parent = 0);
public slots:
    void OnTimerout();

signals:
    void statusChanged(QString CPUInfo , QString HDDInfo , QString AtiGPUInfo , QString NvidiaGPUInfo , QString IOInfo);
};

class CSignal : public QThread
{
    Q_OBJECT
public:
    CSignal(QObject * parent = 0);
    ~CSignal();

protected:
    virtual void run();
    CTimerSlot *m_timerSlot;
    QTimer *m_timer;

signals:
    void statusChanged(QString CPUInfo , QString HDDInfo , QString AtiGPUInfo , QString NvidiaGPUInfo , QString IOInfo);
};

#endif // CSIGNAL_H
