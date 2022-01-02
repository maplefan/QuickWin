#include "Common.h"

CCommon::CCommon()
{
}


CCommon::~CCommon()
{
}

std::wstring CCommon::StrToUnicode(const char* str, bool utf8)
{
    std::wstring result;
    int size;
    size = MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, NULL, 0);
    if (size <= 0) return std::wstring();
    wchar_t* str_unicode = new wchar_t[size + 1];
    MultiByteToWideChar((utf8 ? CP_UTF8 : CP_ACP), 0, str, -1, str_unicode, size);
    result.assign(str_unicode);
    delete[] str_unicode;
    return result;
}

std::string CCommon::UnicodeToStr(const wchar_t * wstr, bool utf8)
{
    std::string result;
    int size{ 0 };
    size = WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, NULL, 0, NULL, NULL);
    if (size <= 0) return std::string();
    char* str = new char[size + 1];
    WideCharToMultiByte((utf8 ? CP_UTF8 : CP_ACP), 0, wstr, -1, str, size, NULL, NULL);
    result.assign(str);
    delete[] str;
    return result;
}

double CCommon::StringSimilarDegree_LD(const std::string & srcString, const std::string & matchString)
{
    int n = srcString.size();
    int m = matchString.size();
    //int[, ] d = new int[n + 1, m + 1]; // matrix
    std::vector<std::vector<int>> d(n + 1, std::vector<int>(m + 1));
    int cost; // cost
              // Step 1（如果其中一个字符串长度为0，则相似度为1）？
              //if (n == 0) return (double)m / max(srcString.size(), matchString.size());
              //if (m == 0) return (double)n / max(srcString.size(), matchString.size());
    if (n == 0 || m == 0) return 0.0;	//如果其中一个字符串长度为0，则相似度为0
                                        // Step 2
    for (int i = 0; i <= n; d[i][0] = i++);
    for (int j = 0; j <= m; d[0][j] = j++);
    // Step 3
    for (int i = 1; i <= n; i++)
    {
        //Step 4
        for (int j = 1; j <= m; j++)
        {
            // Step 5
            cost = (matchString.substr(j - 1, 1) == srcString.substr(i - 1, 1) ? 0 : 1);
            // Step 6
            d[i][j] = min(min(d[i - 1][j] + 1, d[i][j - 1] + 1), d[i - 1][j - 1] + cost);
        }
    }

    // Step 7
    double ds = 1 - (double)d[n][m] / max(srcString.size(), matchString.size());

    return ds;
}
