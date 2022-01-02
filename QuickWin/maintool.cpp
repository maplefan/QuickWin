#include "maintool.h"
#include "ui_maintool.h"

MainTool::MainTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainTool)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("实用工具"));
    connect(ui->cmdBtn, &QPushButton::clicked, [this] {shellRun("cmd.exe", "/k cd /d %userprofile%"); });
    connect(ui->wslBtn, &QPushButton::clicked, [this] {shellRun("wsl.exe", ""); });
    connect(ui->powershellBtn, &QPushButton::clicked, [this] {shellRun("powershell.exe", ""); });
    connect(ui->calcBtn, &QPushButton::clicked, [this] {shellRun("calc.exe", ""); });
    connect(ui->regeditBtn, &QPushButton::clicked, [this] {shellRun("regedit.exe", ""); });
    connect(ui->servicesBtn, &QPushButton::clicked, [this] {shellRun("services.msc", ""); });
    connect(ui->taskmgrBtn, &QPushButton::clicked, [this] {shellRun("taskmgr.exe", ""); });
    connect(ui->programsBtn, &QPushButton::clicked, [this] {shellRun("control.exe", "appwiz.cpl"); });
    connect(ui->envBtn, &QPushButton::clicked, [this] {shellRun("SystemPropertiesAdvanced.exe", ""); });
    connect(ui->pcnameBtn, &QPushButton::clicked, [this] {shellRun("SystemPropertiesComputerName.exe", ""); });
    connect(ui->fastrebootBtn, &QPushButton::clicked, [&] {
        if (QMessageBox::warning(this, tr("Warning"), tr("Are you sure to reboot?"),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            OsFastReboot();
        }
    });
    connect(ui->fastpoweroffBtn, &QPushButton::clicked, [&] {
        if (QMessageBox::warning(this, tr("Warning"), tr("Are you sure to poweroff?"),
            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            OsFastPoweroff();
        }
    });
    connect(ui->controlBtn, &QPushButton::clicked, [this] {shellRun("control", ""); });
    connect(ui->resetexplorerBtn, &QPushButton::clicked, [&] {
        auto pid = -1;
        pid = PsGetPidByWindowW((wchar_t*)L"Progman", (wchar_t*)L"Program Manager");
        auto path = OsWinDirW() + L"\\explorer.exe";
        if (pid != -1) {
            PsKillProcess(pid);
        }
        PsCreateProcessW(path);
    });
    connect(ui->killexplorerBtn, &QPushButton::clicked, [&] {
        auto pid = -1;
        pid = PsGetPidByWindowW((wchar_t*)L"Progman", (wchar_t*)L"Program Manager");
        PsKillProcess(pid);
    });


    connect(ui->sysinfoBtn, &QPushButton::clicked, [this] {shellRun("cmd.exe", "/c systeminfo |more & pause"); });
    connect(ui->datetimeBtn, &QPushButton::clicked, [this] {shellRun("control.exe", "date/time"); });
    connect(ui->tasksBtn, &QPushButton::clicked, [this] {shellRun("taskschd.msc", "/s"); });
    connect(ui->versionBtn, &QPushButton::clicked, [this] {shellRun("winver.exe", ""); });
    connect(ui->deskiconsBtn, &QPushButton::clicked, [this] {shellRun("rundll32.exe", "shell32.dll,Control_RunDLL desk.cpl,,0"); });
    connect(ui->wallpaperBtn, &QPushButton::clicked, [this] {
        if (OsMajorVer() <= 5) shellRun("rundll32.exe", "shell32.dll,Control_RunDLL desk.cpl,,0");
        else shellRun("control.exe", "/name Microsoft.Personalization /page pageWallpaper");
    });
    connect(ui->clearTypeBtn, &QPushButton::clicked, [this] {shellRun("cttune", ""); });
    connect(ui->devmgrBtn, &QPushButton::clicked, [this] {shellRun("devmgmt.msc", ""); });
    connect(ui->diskmgrBtn, &QPushButton::clicked, [this] {shellRun("diskmgmt.msc", ""); });

    connect(ui->resmonBtn, &QPushButton::clicked, [this] {shellRun("resmon.exe", ""); });
    connect(ui->perfBtn, &QPushButton::clicked, [this] {shellRun("perfmon.exe", ""); });
    connect(ui->perfsetBtn, &QPushButton::clicked, [this] {shellRun("SystemPropertiesPerformance.exe", ""); });
    connect(ui->powerBtn, &QPushButton::clicked, [this] {shellRun("control.exe", "powercfg.cpl,,3"); });
    connect(ui->usersBtn, &QPushButton::clicked, [this] {shellRun("lusrmgr.msc", ""); });
    connect(ui->uacBtn, &QPushButton::clicked, [this] {shellRun("UserAccountControlSettings.exe", ""); });
    connect(ui->evtBtn, &QPushButton::clicked, [this] {shellRun("eventvwr.msc", ""); });
    connect(ui->gpoBtn, &QPushButton::clicked, [this] {shellRun("gpedit.msc", ""); });
    connect(ui->secpolBtn, &QPushButton::clicked, [this] {shellRun("secpol.msc", ""); });
    connect(ui->certBtn, &QPushButton::clicked, [this] {shellRun("certmgr.msc", ""); });
    connect(ui->credBtn, &QPushButton::clicked, [this] {shellRun("control.exe", "/name Microsoft.CredentialManager"); });
    connect(ui->RAMBtn, &QPushButton::clicked, [this] {shellRun("mdsched", ""); });

    connect(ui->firewallBtn, &QPushButton::clicked, [this] {shellRun("control.exe", "firewall.cpl"); });
    connect(ui->proxyBtn, &QPushButton::clicked, [this] {shellRun("rundll32.exe", "shell32.dll,Control_RunDLL inetcpl.cpl,,4"); });
    connect(ui->netconnBtn, &QPushButton::clicked, [this] {shellRun("control.exe", "ncpa.cpl"); });
    connect(ui->hostsBtn, &QPushButton::clicked, [&] {shellRun("notepad.exe",QString::fromStdWString(OsSystem32DirW() + L"\\drivers\\etc\\hosts")); });
    connect(ui->ipv4Btn, &QPushButton::clicked, [this] {shellRun("cmd.exe", "/k ipconfig|findstr /i ipv4"); });
    connect(ui->ipv6Btn, &QPushButton::clicked, [this] {shellRun("cmd.exe", "/k ipconfig|findstr /i ipv6"); });
    connect(ui->routeBtn, &QPushButton::clicked, [this] {shellRun("cmd.exe", "/k route print"); });
    connect(ui->sharedBtn, &QPushButton::clicked, [this] {shellRun("fsmgmt.msc", ""); });
    connect(ui->flushdnsBtn, &QPushButton::clicked, [this] {shellRun("cmd.exe", "/k ipconfig /flushdns"); });
}

MainTool::~MainTool()
{
    delete ui;
}

void MainTool::shellOpenUrl(QString url)
{
    ShellExecuteW(NULL, L"open", url.toStdWString().c_str(), NULL, NULL, SW_SHOW);
}

void MainTool::shellRun(QString cmdline, QString param)
{
    ShellExecuteW(NULL, L"open", cmdline.toStdWString().c_str(), param.toStdWString().c_str(), NULL, SW_SHOW);
}

void MainTool::shellRunCmdExe(QString exe, int show)
{
    auto cmdline = "cmd /c " + exe;
    PsCreateProcessW(cmdline.toStdWString(), show);
}

void MainTool::shellRunCmdDir(QString dir)
{
    auto cmdline = "cmd /k cd /D" + dir;
    PsCreateProcessW(cmdline.toStdWString());
}

DWORD MainTool::PsGetPidByWindowW(wchar_t *cls, wchar_t *title)
{
    DWORD pid = 0;
    HWND wnd = FindWindowW(cls, title);
    if (wnd != NULL) {
        GetWindowThreadProcessId(wnd, &pid);
    }
    return pid;
}

bool MainTool::PsCreateProcessW(__in const std::wstring &cmdline, __in UINT cmdshow /*= SW_SHOW*/, __out PROCESS_INFORMATION *proc_info /*= NULL*/)
{
    PROCESS_INFORMATION pi = {0};
    STARTUPINFOW si = {0};
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = (WORD)cmdshow;
    si.cb = sizeof(STARTUPINFOA);
    if (!proc_info)
        proc_info = &pi;
    if (!CreateProcessW(NULL, (LPWSTR)cmdline.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, proc_info))
        return false;
    if (pi.hProcess)
        CloseHandle(pi.hProcess);
    if (pi.hThread)
        CloseHandle(pi.hThread);
    return true;
}

bool MainTool::OsFastReboot()
{
    NTSTATUS status;
    __NtShutdownSystem shutdown_api = (__NtShutdownSystem)
        GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtShutdownSystem");
    if (shutdown_api == NULL) {
        return false;
    }
    SeEnablePrivilegeW(SE_SHUTDOWN_NAME);
    status = shutdown_api(ShutdownReboot);
    if (!NT_SUCCESS(status)) {
        return false;
    }
    return true;
}

bool MainTool::OsFastPoweroff()
{
    NTSTATUS status;
    __NtShutdownSystem shutdown_api = (__NtShutdownSystem)
        GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtShutdownSystem");
    if (shutdown_api == NULL) {
        return false;
    }
    SeEnablePrivilegeW(SE_SHUTDOWN_NAME);
    status = shutdown_api(ShutdownPowerOff);
    if (!NT_SUCCESS(status)) {
        return false;
    }
    return true;
}

std::wstring MainTool::OsWinDirW()
{
    wchar_t windir[MAX_PATH] = { 0 };
    GetWindowsDirectoryW(windir, MAX_PATH);
    return windir;
}

bool MainTool::PsKillProcess(__in DWORD pid)
{
    bool result = false;
    HANDLE phd = VirtualOpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (phd) {
        if (TerminateProcess(phd, 1))
            result = true;
        CloseHandle(phd);
    }
    return result;
}

DWORD MainTool::OsMajorVer()
{
    DWORD number = 0;
    __RtlGetNtVersionNumbers pRtlGetNtVersionNumbers = (__RtlGetNtVersionNumbers)
        GetProcAddress(GetModuleHandle(L"ntdll.dll"),"RtlGetNtVersionNumbers");
    if (pRtlGetNtVersionNumbers) {
        pRtlGetNtVersionNumbers(&number, NULL, NULL);
    }
    return number;
}

std::wstring MainTool::OsSystem32DirW()
{
    std::wstring wstr;
    wchar_t windir[MAX_PATH] = { 0 };
    if (GetWindowsDirectoryW(windir, MAX_PATH)) {
        wstr.append(windir);
        wstr.append(L"\\System32");
    }
    return wstr;
}

bool MainTool::SeEnablePrivilegeW(__in const wchar_t* priv_name, __in DWORD priv_number)
{
    if (priv_name != NULL)
        return OpProcessPrivilegeByApi(priv_name, PRIVILEGE_ENBALE);
    else
        return OpProcessPrivilegeByNative(priv_number, PRIVILEGE_ENBALE);
}

HANDLE WINAPI MainTool::VirtualOpenProcess( _In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId )
{
    typedef HANDLE(WINAPI *pOpenProcess)(_In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId);

    if (PROCESS_VID != TLS_OUT_OF_INDEXES) {
        LPVOID vopen = nullptr;
        InterGetTlsValue(PROCESS_VID, vopen);
        if (vopen) {
            return ((pOpenProcess)vopen)(dwDesiredAccess, bInheritHandle, dwProcessId);
        }
    }

    return OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
}

bool MainTool::OpProcessPrivilegeByApi(const wchar_t* priv_name, PRIVILEGE_OPERATE operate_type)
{
    typedef BOOL (WINAPI* __OpenProcessToken)(
        __in        HANDLE ProcessHandle,
        __in        DWORD DesiredAccess,
        __deref_out PHANDLE TokenHandle
        );
    typedef BOOL (WINAPI* __LookupPrivilegeValueW)(
        __in_opt LPCWSTR lpSystemName,
        __in     LPCWSTR lpName,
        __out    PLUID   lpLuid
        );
    typedef BOOL (WINAPI* __AdjustTokenPrivileges)(
        __in      HANDLE TokenHandle,
        __in      BOOL DisableAllPrivileges,
        __in_opt  PTOKEN_PRIVILEGES NewState,
        __in      DWORD BufferLength,
        __out_bcount_part_opt(BufferLength, *ReturnLength) PTOKEN_PRIVILEGES PreviousState,
        __out_opt PDWORD ReturnLength
        );
    bool result = false;
    HANDLE token;
    LUID name_value;
    TOKEN_PRIVILEGES tp;
    do {
        HMODULE advapi32 = GetModuleHandleW(L"advapi32.dll");
        if (advapi32 == NULL) {
            advapi32 = LoadLibraryW(L"advapi32.dll");
            if (advapi32 == NULL) break;
        }
        __OpenProcessToken pOpenProcessToken = (__OpenProcessToken)GetProcAddress(advapi32, "OpenProcessToken");
        __LookupPrivilegeValueW pLookupPrivilegeValueW = (__LookupPrivilegeValueW)GetProcAddress(advapi32, "LookupPrivilegeValueW");
        __AdjustTokenPrivileges pAdjustTokenPrivileges = (__AdjustTokenPrivileges)GetProcAddress(advapi32, "AdjustTokenPrivileges");
        if (pOpenProcessToken == NULL || pLookupPrivilegeValueW == NULL || pAdjustTokenPrivileges == NULL) {
            break;
        }
        if (!pOpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &token)) {
            break;
        }
        if (!pLookupPrivilegeValueW(NULL, priv_name, &name_value)) {
            CloseHandle(token);
            break;
        }
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = name_value;
        if (operate_type == PRIVILEGE_ENBALE)
            tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        else
            tp.Privileges[0].Attributes = 0;
        if (!pAdjustTokenPrivileges(token, FALSE, &tp, sizeof(tp), NULL, NULL) ||
            GetLastError() != ERROR_SUCCESS) {
            CloseHandle(token);
            break;
        }
        CloseHandle(token);
        result = true;
    } while(0);
    return result;
}

bool MainTool::OpProcessPrivilegeByNative(DWORD priv_number, PRIVILEGE_OPERATE operate_type)
{
    NTSTATUS status;
    BOOLEAN enable;
    BOOLEAN was_enabled = FALSE;
    bool result = false;
    __RtlAdjustPrivilege pRtlAdjustPrivilege = NULL;
    do {
        pRtlAdjustPrivilege = (__RtlAdjustPrivilege)GetProcAddress(
            GetModuleHandleW(L"ntdll.dll"), "RtlAdjustPrivilege");
        if (pRtlAdjustPrivilege == NULL) break;
        enable = (operate_type == PRIVILEGE_ENBALE);
        status = pRtlAdjustPrivilege(priv_number, enable, FALSE, &was_enabled);	//SE_DEBUG_PRIVILEGE=20
        if (!NT_SUCCESS(status)) {
            break;
        }
        result = true;
    } while (0);
    return result;
}

bool MainTool::InterGetTlsValue(DWORD tlsid, LPVOID &val)
{
    if (tlsid == TLS_OUT_OF_INDEXES) return false;
    val = TlsGetValue(tlsid);
    return true;
}
