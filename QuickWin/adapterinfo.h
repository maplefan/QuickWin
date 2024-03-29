﻿#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef ADAPTERINFO_H
#define ADAPTERINFO_H

#include"Common.h"

//保存一个网络连接信息
struct NetWorkConection
{
    int index{};			//该连接在MIB_IFTABLE中的索引
    std::string description;		//网络描述（获取自GetAdapterInfo）
    std::string description_2;	//网络描述（获取自GetIfTable）
    unsigned int in_bytes;	//初始时已接收字节数
    unsigned int out_bytes;	//初始时已发送字节数
    std::wstring ip_address{ L"-.-.-.-" };	//IP地址
    std::wstring subnet_mask{ L"-.-.-.-" };	//子网掩码
    std::wstring default_gateway{ L"-.-.-.-" };	//默认网关
};

class AdapterInfo
{
public:
    AdapterInfo();
    ~AdapterInfo();

    //获取网络连接列表，填充网络描述、IP地址、子网掩码、默认网关信息
    static void GetAdapterInfo(std::vector<NetWorkConection>& adapters);

    //刷新网络连接列表中的IP地址、子网掩码、默认网关信息
    static void RefreshIpAddress(std::vector<NetWorkConection>& adapters);

    //获取网络列表中每个网络连接的MIB_IFTABLE中的索引、初始时已接收/发送字节数的信息
    static void GetIfTableInfo(std::vector<NetWorkConection>& adapters, MIB_IFTABLE* pIfTable);

    //直接将MIB_IFTABLE中的所有连接添加到adapters容器中
    static void GetAllIfTableInfo(std::vector<NetWorkConection>& adapters, MIB_IFTABLE* pIfTable);
private:
    //根据一个网络连接描述判断是否在IfTable列表里，返回索引，找不到则返回-1
    static int FindConnectionInIfTable(std::string connection, MIB_IFTABLE* pIfTable);

    //根据一个网络连接描述判断是否在IfTable接列表里，返回索引，找不到则返回-1。只需要部分匹配
    static int FindConnectionInIfTableFuzzy(std::string connection, MIB_IFTABLE* pIfTable);
};

#endif // ADAPTERINFO_H
