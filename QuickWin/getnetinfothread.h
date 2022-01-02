#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#pragma once
#ifndef GETNETINFOTHREAD_H
#define GETNETINFOTHREAD_H

#include <QObject>
#include <QThread>

class GetNetInfoThread : public QThread
{
Q_OBJECT
public:
    GetNetInfoThread();
    void run();
};

#endif // GETNETINFOTHREAD_H
