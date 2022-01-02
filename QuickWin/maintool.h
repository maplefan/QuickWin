#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef MAINTOOL_H
#define MAINTOOL_H

/****************************************************************************
**
** Copyright (C) 2019 BlackINT3
** Contact: https://github.com/BlackINT3/none
**
** GNU Lesser General Public License Usage (LGPL)
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/
#define NT_SUCCESS(Status)								((NTSTATUS)(Status) >= 0)

#include <QMainWindow>
#include <Windows.h>
#include <QMessageBox>

typedef enum _SHUTDOWN_ACTION {
    ShutdownNoReboot,
    ShutdownReboot,
    ShutdownPowerOff
} SHUTDOWN_ACTION;

typedef LONG(NTAPI *__NtShutdownSystem)(
    __in SHUTDOWN_ACTION Action
    );

// RtlGetNtVersionNumbers
typedef VOID (NTAPI* __RtlGetNtVersionNumbers)(
    OUT PULONG MajorVer,
    OUT PULONG MinorVer,
    OUT PULONG BuildNumber
);

enum PRIVILEGE_OPERATE {
    PRIVILEGE_UNKNOWN,
    PRIVILEGE_ENBALE,
    PRIVILEGE_DISABLE
};

// RtlAdjustPrivilege
typedef LONG (NTAPI* __RtlAdjustPrivilege)(
    ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN Client,
    PBOOLEAN PsGetPidByWindowW
);

namespace Ui {
class MainTool;
}

class MainTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainTool(QWidget *parent = nullptr);
    ~MainTool();

    void shellOpenUrl(QString url);
    void shellRun(QString cmdline, QString param);
    void shellRunCmdExe(QString exe, int show);
    void shellRunCmdDir(QString dir);
    DWORD PsGetPidByWindowW(wchar_t *cls, wchar_t *title);
    bool PsCreateProcessW(__in const std::wstring &cmdline, __in UINT cmdshow = SW_SHOW, __out PROCESS_INFORMATION *proc_info = NULL);
    bool OsFastReboot();
    bool OsFastPoweroff();
    std::wstring OsWinDirW();
    bool PsKillProcess(__in DWORD pid);
    DWORD OsMajorVer();
    std::wstring OsSystem32DirW();
    DWORD PROCESS_VID = TLS_OUT_OF_INDEXES;

    bool SeEnablePrivilegeW(__in const wchar_t* priv_name, __in DWORD priv_number = 0);
    HANDLE WINAPI VirtualOpenProcess( _In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId );
    bool OpProcessPrivilegeByApi(const wchar_t* priv_name, PRIVILEGE_OPERATE operate_type);
    bool OpProcessPrivilegeByNative(DWORD priv_number, PRIVILEGE_OPERATE operate_type);
    bool InterGetTlsValue(DWORD tlsid, LPVOID &val);
    /****************************************************************************/

private:
    Ui::MainTool *ui;
};

#endif // MAINTOOL_H
