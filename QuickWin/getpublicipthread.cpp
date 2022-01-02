#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "getpublicipthread.h"
#include "getpcinfowin.h"

GetPublicIPThread::GetPublicIPThread()
{

}

void GetPublicIPThread::run(){
    getPublicIP(publicIP);
    emit send2UI(publicIP);
}
