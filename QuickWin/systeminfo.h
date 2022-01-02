#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "iphlpapi.h"
#include <string>
#include <vector>
#include <new>
#include <QString>
#include <QObject>
using namespace std;

#pragma comment(lib,"Iphlpapi.lib")

typedef struct tagpare_net
{
    DWORD dwsend;
    DWORD dwrecv;
}NET_PARE,*PNET_PARE;
// Use to convert bytes to KB
#define DIV 1024

#define SystemBasicInformation 0
#define SystemPerformanceInformation 2
#define SystemTimeInformation 3

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

typedef struct{
   DWORD memoryPrecent;//物理内存占用率（%）
   DWORDLONG totalPhys;
   DWORDLONG availPhys;
   DWORDLONG totalPageFile;
   DWORDLONG availPageFile;
   DWORDLONG totalVirtual;
   DWORDLONG availVirtual;
   DWORDLONG availExtendedVirtual;
} MemoryInfo;

#endif // SYSTEMINFO_H
