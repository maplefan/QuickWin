#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef HOTKEYMANAGE_H
#define HOTKEYMANAGE_H

#include <QMainWindow>
#include <QTreeView>
#include <QMenu>
#include <QSortFilterProxyModel>
#include <QMutex>
#include <QFileInfo>
#include <QDir>
#include <QStandardItemModel>
#include <QFileIconProvider>
#include <QIcon>
#include <QProcess>
#include <QDebug>
#include "Driver_Load.h"
#include "CGLIB_Common.hpp"

enum REGISTER_DRIVER{
    NO_REGISTER_DRIVER,
    NT_REGISTER_DRIVER,
    MINIFILTER_REGISTER_DRIVER,
    REGISTER_DRIVER
};

enum PROCESS_OPS {
    PROCESS_OPEN,
    THREAD_OPEN,
};

#define ARK_DRV_TYPE 41827
#define HOTKEY_MAX_VK	0x80
#define HOTKEY_PLACEHOLDER_ID 0x99887766
#define IOCTL_ARK_HOTKEY CTL_CODE(ARK_DRV_TYPE, 0x900, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define ARK_USER_SYMBOLINK L"\\\\.\\OpenArkDrv"
#define INVALID_PID -1
#define MAKELONGLONG(a, b) ((LONGLONG(DWORD(a) & 0xFFFFFFFF) << 32 ) | LONGLONG(DWORD(b) & 0xFFFFFFFF))
#define IOCTL_ARK_PROCESS CTL_CODE(ARK_DRV_TYPE, 0x960, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define TO_STREAM(st) std::string((char*)&st, sizeof(st))
#define SYMBOLIC_LINK_QUERY (0x0001)
#define STATUS_BUFFER_TOO_SMALL						((NTSTATUS)0xC0000023L)

enum HOTKEY_OPS {
    HOTKEY_ENUM,
    HOTKEY_REMOVE,
};

#pragma pack(push, 1)
typedef struct _HOTKEY_ITEM {
    UCHAR name[64];
    UINT32 wnd;
    UINT16 mod1;
    UINT16 mod2;
    UINT32 vk;
    UINT32 id;
    UINT32 pid;
    UINT32 tid;
    ULONG64 hkobj;
} HOTKEY_ITEM, *PHOTKEY_ITEM;
typedef struct _HOTKEY_INFO {
    ULONG count;
    HOTKEY_ITEM items[1];
} HOTKEY_INFO, *PHOTKEY_INFO;
#pragma pack(pop)

typedef struct _PROCESS_BASIC_INFORMATION64
{
    NTSTATUS ExitStatus;
    ULONG Pad1;
    ULONG64 PebBaseAddress;
    ULONG64 AffinityMask;
    KPRIORITY BasePriority;
    ULONG Pad2;
    ULONG64 UniqueProcessId;
    ULONG64 InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION64, *PPROCESS_BASIC_INFORMATION64;

typedef struct _PROCESS_BASIC_INFORMATION32 {
    NTSTATUS ExitStatus;
    ULONG PebBaseAddress;
    ULONG AffinityMask;
    KPRIORITY BasePriority;
    ULONG UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATION32;

#pragma pack(push, 1)
typedef struct _PROCESS_OPEN_INFO {
    DWORD access;
    BOOL inherit;
    DWORD pid;
} PROCESS_OPEN_INFO, *PPROCESS_OPEN_INFO;
#pragma pack(pop)

typedef VOID (NTAPI* __RtlInitUnicodeString)(
    PUNICODE_STRING DestinationString,
    PCWSTR SourceString
);

typedef NTSTATUS (NTAPI* __NtOpenSymbolicLinkObject) (
    OUT PHANDLE SymbolicLinkHandle,
    IN ACCESS_MASK DesiredAccess,
    IN POBJECT_ATTRIBUTES ObjectAttributes
);

typedef NTSTATUS (NTAPI* __NtQuerySymbolicLinkObject) (
    IN HANDLE SymbolicLinkHandle,
    OUT PUNICODE_STRING NameString,
    OUT PULONG ResultLength OPTIONAL
);

typedef NTSTATUS (NTAPI* __NtClose)(
    IN  HANDLE Handle
);

// NtQueryInformationProcess
typedef NTSTATUS (NTAPI *__NtQueryInformationProcess)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS InformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

// NtWow64QueryInformationProcess64
typedef NTSTATUS(NTAPI *__NtWow64QueryInformationProcess64)(
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS InformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL
);

typedef struct _PROCESS_BASIC_INFORMATIONEX {
    NTSTATUS ExitStatus;
    PPEB PebBaseAddress;
    ULONG_PTR AffinityMask;
    KPRIORITY BasePriority;
    ULONG_PTR UniqueProcessId;
    ULONG_PTR InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATIONEX;

typedef struct _PROCESS_BASIC_INFORMATIONEX32 {
    NTSTATUS ExitStatus;
    ULONG PebBaseAddress;
    ULONG AffinityMask;
    KPRIORITY BasePriority;
    ULONG UniqueProcessId;
    ULONG InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATIONEX32;

typedef struct _PROCESS_BASIC_INFORMATIONEX64
{
    NTSTATUS ExitStatus;
    ULONG Pad1;
    ULONG64 PebBaseAddress;
    ULONG64 AffinityMask;
    KPRIORITY BasePriority;
    ULONG Pad2;
    ULONG64 UniqueProcessId;
    ULONG64 InheritedFromUniqueProcessId;
} PROCESS_BASIC_INFORMATIONEX64, *PPROCESS_BASIC_INFORMATIONEX64;

struct ProcInfo {
    DWORD pid;
    DWORD ppid = -1;
    DWORD parent_existed = -1;
    QString name;
    QString desc;
    QString corp;
    QString ctime;
    QString path;
};

struct FileBaseInfo {
    QString path;
    QString desc;
    QString ver;
    QString corp;
};

namespace Ui {
class HotkeyManage;
}

class HotkeyManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit HotkeyManage(QWidget *parent = nullptr);
    ~HotkeyManage();
    void startDriver();
    void endDriver();
    void showHotkey();
    void Error_Out();
    bool HotkeyEnumInfo(std::vector<HOTKEY_ITEM> &hotkeys);
    std::wstring FsPathToNameW(__in const std::wstring& fpath);
    std::wstring StrToW(__in const std::string& str);
    std::wstring StrCodeToWide(__in unsigned int code, __in const std::string& str);
    std::wstring StrFormatW(__in const wchar_t* formats, ...);
    std::string StrFormatA(__in const char* formats, ...);
    std::string StrTrimA(__in const std::string& str, __in const std::string& charlist = " \n\r\t");
    std::string StrTrimRightA(__in const std::string& str, __in const std::string& charlist = " \n\r\t");
    std::wstring StrFormatVaListW(__in const wchar_t* formats, __in va_list lst);
    std::string StrFormatVaListA(__in const char* formats, __in va_list lst);
    std::wstring PsGetWndTextW(__in HWND wnd);
    std::wstring PsGetWndClassNameW(__in HWND wnd);
    std::string HotkeyVkToString(UINT32 vk, UINT16 mod1, UINT16 mod2);
    std::string StrToLowerA(__in const std::string& str);
    std::string StrTrimLeftA(__in const std::string& str, __in const std::string& charlist = " \n\r\t");
    FileBaseInfo CacheGetFileBaseInfo(QString path);
    ProcInfo CacheGetProcInfo(unsigned int pid, ProcInfo& info);
    DWORD PsGetParentPid(__in DWORD pid);
    LONGLONG ProcessCreateTimeValue(__in DWORD pid);
    bool PsIsDeleted(__in DWORD pid);
    std::wstring PsGetProcessPathW(__in DWORD pid = GetCurrentProcessId());
    bool InterCreateTlsValue(LPVOID val, DWORD &tlsid);
    bool OsIs64();
    bool FsGetFileInfoW(__in const std::wstring& path, __in const wchar_t* type, __out std::wstring& info, __in const wchar_t* translation = NULL);
    std::wstring ProcessCreateTime(__in DWORD pid);
    bool PsIsX64(__in DWORD pid);
    bool InterDeleteTlsValue(DWORD &tlsid);
    LONGLONG FsGetFileVersionW(__in const std::wstring& path, __out std::wstring& version);
    HANDLE VirtualOpenProcess( _In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId );
    bool PsGetPbi32(__in HANDLE phd, __out PROCESS_BASIC_INFORMATIONEX32 &pbi32);
    bool PsGetPbi64(__in HANDLE phd, __out PROCESS_BASIC_INFORMATION64 &pbi64);
    LONGLONG TmFileTimeToMs(__in const FILETIME& ft);
    bool ObParseToDosPathW(__in std::wstring ori_path, __out std::wstring& dos_path);
    bool GetFileInfoByBlockW(__in const std::wstring& block, __in const wchar_t* type, __out std::wstring& name, __in const wchar_t* sub_translation = NULL);
    bool GetResourceVersionInfoW(__in const std::wstring& path, __out std::wstring& verinfo);
    std::wstring FormatFileTime(FILETIME *file_tm);
    bool PsIsWow64(__in HANDLE phd = GetCurrentProcess());
    bool InterGetTlsValue(DWORD tlsid, LPVOID &val);
    bool TmConvertZoneTime(__inout SYSTEMTIME& systm, __in LPTIME_ZONE_INFORMATION zone);
    std::wstring TmFormatSystemTimeW(__in const SYSTEMTIME& systm, __in const std::wstring& format);
    bool StrReplaceW(__inout std::wstring& source, __in const std::wstring& pattern, __in std::wstring replaced = L"");
    std::wstring StrTruncateW(__in const std::wstring& str, __in const std::wstring& startsep, __in const std::wstring& endsep);
    bool ObParseSymbolicLinkW(__in const std::wstring& symlnk, __out std::wstring& target);
    QIcon LoadIcon(QString file_path);
    int StrToIntegerW(__in const std::wstring& wstr);
    unsigned int StrToHexW(__in const std::wstring& wstr);

private slots:
    void on_lineEdit_textChanged(const QString &arg1);
    void on_comboBox_currentTextChanged(const QString &arg1);

public slots:
    void slotTreeMenu(const QPoint &pos);
    void slotTreeMenuRefresh();
    void slotTreeMenuDeleteHotkey();
    void slotTreeMenuOpenPath();
    void slotTreeMenuProperty();

private:
    Ui::HotkeyManage *ui;
    Driver_Load *_Driver_Load;
    int driverWay;
    DWORD PROCESS_VID = TLS_OUT_OF_INDEXES;
    WORD global_idx = TLS_OUT_OF_INDEXES;
    QTreeView *view;
    QStandardItemModel *hotkeyModel;
    QSortFilterProxyModel *proxyModel;
    QMenu hotkeyMenu;
};

#endif // HOTKEYMANAGE_H
