#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef MYWINEVENTFILTER_H
#define MYWINEVENTFILTER_H
#include <QAbstractNativeEventFilter>
class MyGlobalShortCut;

class MyWinEventFilter : public QAbstractNativeEventFilter
{
public:
    MyWinEventFilter();
    MyWinEventFilter(MyGlobalShortCut *shortcut);
    ~MyWinEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);
private:
    MyGlobalShortCut *m_shortcut;
};

#endif
