#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "getnetinfothread.h"
#include "systeminfowin.h"

double netUploadex;
double netDownloadex;

GetNetInfoThread::GetNetInfoThread()
{

}

void GetNetInfoThread::run(){
      SystemInfoWin::GetNetSpeed(netUploadex , netDownloadex);
}
