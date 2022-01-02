#ifndef _PDF_MANAGER_H_
#define _PDF_MANAGER_H_
//加载pdf(加载已经打开的pdf的buffer)
//filename是文件名，需要唯一，dat是打开的pdf的内容（可以用fstream打开，以二进制形式），length是pdf长度
extern "C" __declspec(dllexport) bool __stdcall PDFMANAGER_Loadpdf(const char* filename, char* dat, int length);


//关闭pdf
//filename是文件名，关闭该pdf，打开pdf后需要关闭，否则会内存泄漏
extern "C" __declspec(dllexport) bool __stdcall PDFMANAGER_Closepdf(const char* filename);


//加载页面
//filename是文件名，加载该页面，page是需要显示页数，width是宽，height是高，（可以设置自己要的尺寸，适配可用，为0时，表示1:1渲染）
//size是当前页的大小（无需设置，传出参数），outBmp是是否导出bmp文件（默认为false），返回该页buffer
extern "C" __declspec(dllexport) char* __stdcall PDFMANAGER_LoadPage(const char* filename, int page, float& width, float& height, int& size, bool OutBmp);


//关闭页面
//filename是文件名，关闭该页面，打开页面后需要关闭，否则会内存泄漏
extern "C" __declspec(dllexport) void __stdcall PDFMANAGER_ClosePage(const char* filename, int page);

//获取总页数
//filename是文件名
extern "C" __declspec(dllexport) int __stdcall PDFMANAGER_GetPageCount(const char* filename);

//获取下一页该渲染的页
//filename是文件名
extern "C" __declspec(dllexport) int __stdcall PDFMANAGER_GetCurrentPage(const char* filename);
#endif
