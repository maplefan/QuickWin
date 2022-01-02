#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef COMMON_H
#define COMMON_H

#include<WinSock2.h>
#include<iphlpapi.h>
#include<vector>
#include<string>
#include<QObject>

class CCommon
{
public:
    CCommon();
    ~CCommon();
    //将const char*字符串转换成宽字符字符串
    static std::wstring StrToUnicode(const char* str, bool utf8 = false);

    static std::string UnicodeToStr(const wchar_t* wstr, bool utf8 = false);

    /// <summary>
    /// 字符串相似度算法-编辑距离法
    /// </summary>
    /// <returns>返回的值为0~1，越大相似度越高</returns>
    static double StringSimilarDegree_LD(const std::string& srcString, const std::string& matchString);
};

#endif // COMMON_H
