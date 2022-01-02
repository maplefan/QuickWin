#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include"systeminfo.h"

class SystemInfoWin
{
public:
//获得CPU使用率
static int GetCpuUsage();

//获得CPU处理器个数
static int GetNumofProcessors();

// 返回可用物理内存,uiAllMemory为out型 所有物理内存。单位 KB
static unsigned int GetMemoryStat(unsigned int & uiAllMemory);

static unsigned int GetMemoryPercent(unsigned int & uiAllMemory);

// 返回整个空闲大小.uiAllDisk为硬盘总大小,和警告信息(如果某个分区剩余太少2%分界线) 单位MB
static unsigned int GetDiskStat(unsigned int & uiAllDisk,string& strdescribe);

//得到所有网络适配器
static bool  GetNetwork(vector<NET_PARE>& vec);

//得到unsigned int的差值
static unsigned int getinterval(unsigned int uilast,unsigned int uinow);
//得到当前上行和下行网络速度
// 单位KB
static bool GetNetSpeed(double & uisendspeed,double & uirecvspeed);

//得到TCP连接个数
static unsigned int GetTcpLink();

//得到内存的相关数据
static void GetMemoryInfo( MemoryInfo &mi );

};
