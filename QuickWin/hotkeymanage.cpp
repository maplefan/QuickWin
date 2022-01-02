#include "hotkeymanage.h"
#include "ui_hotkeymanage.h"

struct {
    std::string vk_str;
    UINT32 vk;
} VkStrTables[] = { { "LBUTTON",0x01 },
{ "RBUTTON",0x02 },
{ "CANCEL",0x03 },
{ "MBUTTON",0x04 },
{ "XBUTTON1",0x05 },
{ "XBUTTON2",0x06 },
{ "BACK",0x08 },
{ "TAB",0x09 },
{ "CLEAR",0x0C },
{ "RETURN",0x0D },
{ "SHIFT",0x10 },
{ "CONTROL",0x11 },
{ "MENU",0x12 },
{ "PAUSE",0x13 },
{ "CAPITAL",0x14 },
{ "KANA",0x15 },
{ "HANGEUL",0x15 },
{ "HANGUL",0x15 },
{ "JUNJA",0x17 },
{ "FINAL",0x18 },
{ "HANJA",0x19 },
{ "KANJI",0x19 },
{ "ESCAPE",0x1B },
{ "CONVERT",0x1C },
{ "NONCONVERT",0x1D },
{ "ACCEPT",0x1E },
{ "MODECHANGE",0x1F },
{ "SPACE",0x20 },
{ "PRIOR",0x21 },
{ "NEXT",0x22 },
{ "END",0x23 },
{ "HOME",0x24 },
{ "LEFT",0x25 },
{ "UP",0x26 },
{ "RIGHT",0x27 },
{ "DOWN",0x28 },
{ "SELECT",0x29 },
{ "PRINT",0x2A },
{ "EXECUTE",0x2B },
{ "SNAPSHOT",0x2C },
{ "INSERT",0x2D },
{ "DELETE",0x2E },
{ "HELP",0x2F },
{ "LWIN",0x5B },
{ "RWIN",0x5C },
{ "APPS",0x5D },
{ "SLEEP",0x5F },
{ "NUMPAD0",0x60 },
{ "NUMPAD1",0x61 },
{ "NUMPAD2",0x62 },
{ "NUMPAD3",0x63 },
{ "NUMPAD4",0x64 },
{ "NUMPAD5",0x65 },
{ "NUMPAD6",0x66 },
{ "NUMPAD7",0x67 },
{ "NUMPAD8",0x68 },
{ "NUMPAD9",0x69 },
{ "MULTIPLY",0x6A },
{ "ADD",0x6B },
{ "SEPARATOR",0x6C },
{ "SUBTRACT",0x6D },
{ "DECIMAL",0x6E },
{ "DIVIDE",0x6F },
{ "F1",0x70 },
{ "F2",0x71 },
{ "F3",0x72 },
{ "F4",0x73 },
{ "F5",0x74 },
{ "F6",0x75 },
{ "F7",0x76 },
{ "F8",0x77 },
{ "F9",0x78 },
{ "F10",0x79 },
{ "F11",0x7A },
{ "F12",0x7B },
{ "F13",0x7C },
{ "F14",0x7D },
{ "F15",0x7E },
{ "F16",0x7F },
{ "F17",0x80 },
{ "F18",0x81 },
{ "F19",0x82 },
{ "F20",0x83 },
{ "F21",0x84 },
{ "F22",0x85 },
{ "F23",0x86 },
{ "F24",0x87 },
{ "NUMLOCK",0x90 },
{ "SCROLL",0x91 },
{ "OEM_NEC_EQUAL",0x92 },
{ "OEM_FJ_JISHO",0x92 },
{ "OEM_FJ_MASSHOU",0x93 },
{ "OEM_FJ_TOUROKU",0x94 },
{ "OEM_FJ_LOYA",0x95 },
{ "OEM_FJ_ROYA",0x96 },
{ "LSHIFT",0xA0 },
{ "RSHIFT",0xA1 },
{ "LCONTROL",0xA2 },
{ "RCONTROL",0xA3 },
{ "LMENU",0xA4 },
{ "RMENU",0xA5 },
{ "BROWSER_BACK",0xA6 },
{ "BROWSER_FORWARD",0xA7 },
{ "BROWSER_REFRESH",0xA8 },
{ "BROWSER_STOP",0xA9 },
{ "BROWSER_SEARCH",0xAA },
{ "BROWSER_FAVORITES",0xAB },
{ "BROWSER_HOME",0xAC },
{ "VOLUME_MUTE",0xAD },
{ "VOLUME_DOWN",0xAE },
{ "VOLUME_UP",0xAF },
{ "MEDIA_NEXT_TRACK",0xB0 },
{ "MEDIA_PREV_TRACK",0xB1 },
{ "MEDIA_STOP",0xB2 },
{ "MEDIA_PLAY_PAUSE",0xB3 },
{ "LAUNCH_MAIL",0xB4 },
{ "LAUNCH_MEDIA_SELECT",0xB5 },
{ "LAUNCH_APP1",0xB6 },
{ "LAUNCH_APP2",0xB7 },
{ "OEM_1",0xBA },
{ "OEM_PLUS",0xBB },
{ "OEM_COMMA",0xBC },
{ "OEM_MINUS",0xBD },
{ "OEM_PERIOD",0xBE },
{ "OEM_2",0xBF },
{ "OEM_3",0xC0 },
{ "OEM_4",0xDB },
{ "OEM_5",0xDC },
{ "OEM_6",0xDD },
{ "OEM_7",0xDE },
{ "OEM_8",0xDF },
{ "OEM_AX",0xE1 },
{ "OEM_102",0xE2 },
{ "ICO_HELP",0xE3 },
{ "ICO_00",0xE4 },
{ "PROCESSKEY",0xE5 },
{ "ICO_CLEAR",0xE6 },
{ "PACKET",0xE7 },
{ "OEM_RESET",0xE9 },
{ "OEM_JUMP",0xEA },
{ "OEM_PA1",0xEB },
{ "OEM_PA2",0xEC },
{ "OEM_PA3",0xED },
{ "OEM_WSCTRL",0xEE },
{ "OEM_CUSEL",0xEF },
{ "OEM_ATTN",0xF0 },
{ "OEM_FINISH",0xF1 },
{ "OEM_COPY",0xF2 },
{ "OEM_AUTO",0xF3 },
{ "OEM_ENLW",0xF4 },
{ "OEM_BACKTAB",0xF5 },
{ "ATTN",0xF6 },
{ "CRSEL",0xF7 },
{ "EXSEL",0xF8 },
{ "EREOF",0xF9 },
{ "PLAY",0xFA },
{ "ZOOM",0xFB },
{ "NONAME",0xFC },
{ "PA1",0xFD },
{ "OEM_CLEAR",0xFE } };

namespace ArkDrvApi {
namespace Process {
    HANDLE arkdrv = INVALID_HANDLE_VALUE;
    HANDLE WINAPI OpenProcessR0(DWORD access, BOOL inherit, DWORD pid);
    HANDLE WINAPI OpenProcess(DWORD access, BOOL inherit, DWORD pid);
    bool IoControlDriver(DWORD ctlcode, DWORD op, PVOID inbuf, DWORD inlen, PVOID *outbuf, DWORD *outlen);
    bool IoControlDriver(DWORD ctlcode, DWORD op, const std::wstring &indata, std::string &outdata);
    bool IoControlDriver(DWORD ctlcode, DWORD op, const std::string &indata, std::string &outdata);
    bool ConnectDriver();
    bool HotkeyRemoveInfo(HOTKEY_ITEM &item);
} // namespace Process
} // namespace ArkDrvApi

static struct {
    QMutex lck;
    QMap<unsigned int, ProcInfo> d;
} proc_info;

static struct {
    QMutex lck;
    QMap<QString, FileBaseInfo> d;
} filebase_info;

HotkeyManage::HotkeyManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HotkeyManage)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    setWindowTitle(tr("热键管理"));
    this->ui->comboBox->addItem(tr("热键"), "hotkey");
    this->ui->comboBox->addItem(tr("名称"), "name");
    this->ui->comboBox->addItem(tr("标题"), "title");
    this->ui->comboBox->addItem(tr("描述"), "desc");
    view = this->ui->treeView;
    hotkeyModel = new QStandardItemModel;
    proxyModel = new QSortFilterProxyModel(this);

    view->header()->setSortIndicator(-1, Qt::AscendingOrder);
    view->header()->setStretchLastSection(false);
    view->setSortingEnabled(true);
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList nameList;
    nameList<<tr("名称")<<tr("进程ID.线程ID")<<tr("热键")<<tr("热键对象地址")<<tr("热键ID")<<tr("句柄")<<tr("标题")<<tr("类名")<<tr("路径")<<tr("描述");
    view->setColumnWidth(0,150);
    view->setColumnWidth(1,100);
    view->setColumnWidth(2,180);
    view->setColumnWidth(3,150);
    view->setColumnWidth(4,100);
    view->setColumnWidth(5,100);
    view->setColumnWidth(6,180);
    view->setColumnWidth(7,180);
    view->setColumnWidth(8,300);
    view->setColumnWidth(9,160);

    hotkeyModel->setHorizontalHeaderLabels(nameList);
    proxyModel->setSourceModel(hotkeyModel);
    view->setModel(proxyModel);//导入模型

    //信号槽，右键菜单
    view->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(view, &QTreeView::customContextMenuRequested, this, &HotkeyManage::slotTreeMenu);
    hotkeyMenu.addAction(tr("刷新"), this, SLOT(slotTreeMenuRefresh()));
    hotkeyMenu.addSeparator();    //添加一个分隔线
    hotkeyMenu.addAction(tr("删除热键"), this, SLOT(slotTreeMenuDeleteHotkey()));
    hotkeyMenu.addSeparator();    //添加一个分隔线
    hotkeyMenu.addAction(tr("打开文件位置"), this, SLOT(slotTreeMenuOpenPath()));
    hotkeyMenu.addAction(tr("属性"), this, SLOT(slotTreeMenuProperty()));

    _Driver_Load = new Driver_Load();
    if(OsIs64()){//64位操作系统
        QString temp_str = QDir().currentPath()+"/driver/OpenArkDrv64.sys";
        qDebug()<<temp_str;
        //初始化驱动
        if (_Driver_Load->Init(temp_str.toStdString()) == false)
        {
            QMessageBox::information(NULL , "Error","Can not find sys file!");
        }
    }
    else{//32位操作系统
        QString temp_str = QDir().currentPath()+"/driver/OpenArkDrv32.sys";
        qDebug()<<temp_str;
        //初始化驱动
        if (_Driver_Load->Init(temp_str.toStdString()) == false)
        {
            QMessageBox::information(NULL , "Error","Can not find sys file!");
        }
    }
    startDriver();
    showHotkey();
}

HotkeyManage::~HotkeyManage()
{
    delete ui;
}

void HotkeyManage::startDriver()
{
    //注册驱动
    driverWay = NO_REGISTER_DRIVER;
    bool result = true;
    if(_Driver_Load->Nt_Register_Driver()){
        driverWay = NT_REGISTER_DRIVER;//NT方式注册驱动
    }
    else if(_Driver_Load->Minifilter_Register_Driver()){
        driverWay = MINIFILTER_REGISTER_DRIVER;//Minifilter方式注册驱动
    }
    else if(_Driver_Load->Register_Driver()){
        driverWay = REGISTER_DRIVER;//注册驱动
    }
    else{
        driverWay = NO_REGISTER_DRIVER;
        QMessageBox::information(NULL , "Error","Cant register driver!");
        Error_Out();
    }

    //开始执行驱动
    if(driverWay == NT_REGISTER_DRIVER){
        result = _Driver_Load->Nt_Start_Driver();
        qDebug()<<"NT Start Driver!";
        if(!result){
            Error_Out();
        }
        qDebug()<<"Load Success!";
    }
    else{
        result = _Driver_Load->Start_Driver();
        qDebug()<<"Start Driver!";
        if(!result){
            Error_Out();
        }
        qDebug()<<"Load Success!";
    }
}

void HotkeyManage::endDriver()
{
    bool result = true;
    //停止执行驱动
    if(driverWay == NT_REGISTER_DRIVER){
        result = _Driver_Load->Nt_Stop_Driver();
        if(!result){
            Error_Out();
        }
    }
    else{
        result = _Driver_Load->Stop_Driver();
        if(!result){
            Error_Out();
        }
    }

    //卸载驱动
    if(driverWay == NT_REGISTER_DRIVER){
        result = _Driver_Load->Nt_UnRegister_Driver();
        if(!result){
            Error_Out();
        }
        qDebug()<<"UnRegister Success!";
    }
    else{
        result = _Driver_Load->UnRegister_Driver();
        if(!result){
            Error_Out();
        }
        qDebug()<<"UnRegister Success!";
    }
}

void HotkeyManage::showHotkey()
{
    std::vector<HOTKEY_ITEM> infos;
    HotkeyEnumInfo(infos);
    qDebug()<<"infos"<<infos.size();
    for (auto item : infos) {
        auto pid = item.pid;
        ProcInfo cache;
        CacheGetProcInfo(pid, cache);
        auto &&path = cache.path.toStdWString();
        auto &&name = FsPathToNameW(path);
        if (name.empty()) name = StrToW((char*)item.name);
        auto info = CacheGetFileBaseInfo(QString::fromStdWString(path));
        auto name_str = QString::fromStdWString(name);
        auto wnd_str = QString::fromStdWString(StrFormatW(L"0x%X", item.wnd));
        auto title_str = QString::fromStdWString(PsGetWndTextW((HWND)item.wnd));
        auto class_str = QString::fromStdWString(PsGetWndClassNameW((HWND)item.wnd));
        auto hk_str = QString::fromStdWString(StrFormatW(L"0x%p", item.hkobj));
        auto ptid_str = QString::fromStdWString(StrFormatW(L"%d.%d", item.pid, item.tid));
        auto vk_str = QString::fromStdString(HotkeyVkToString(item.vk, item.mod1, item.mod2));
        auto vkid_str = QString::fromStdWString(StrFormatW(L"0x%X", item.id));
        auto path_str = QString::fromStdWString(path);
        auto desc_str = info.desc;
        qDebug()<<
        "Name:"<<name_str<<
        " PID.TID:"<<ptid_str<<
        " Hotkey:"<<vk_str<<
        " HotkeyObject:"<<hk_str<<
        " HotkeyID:"<<vkid_str<<
        " HWND:"<<wnd_str<<
        " Title:"<<title_str<<
        " ClassName:"<<class_str<<
        " Path:"<<path_str<<
        " Description:"<<desc_str;

        auto name_item = new QStandardItem(LoadIcon(QString::fromStdWString(path)), name_str);
        auto wnd_item = new QStandardItem(wnd_str);
        auto title_item = new QStandardItem(title_str);
        auto class_item = new QStandardItem(class_str);
        auto hk_item = new QStandardItem(hk_str);
        auto ptid_item = new QStandardItem(ptid_str);
        auto vk_item = new QStandardItem(vk_str);
        auto vkid_item = new QStandardItem(vkid_str);
        auto path_item = new QStandardItem(path_str);
        auto desc_item = new QStandardItem(desc_str);

        auto count = hotkeyModel->rowCount();
        int i = 0;
        hotkeyModel->setItem(count, i++, name_item);
        hotkeyModel->setItem(count, i++, ptid_item);
        hotkeyModel->setItem(count, i++, vk_item);
        hotkeyModel->setItem(count, i++, hk_item);
        hotkeyModel->setItem(count, i++, vkid_item);
        hotkeyModel->setItem(count, i++, wnd_item);
        hotkeyModel->setItem(count, i++, title_item);
        hotkeyModel->setItem(count, i++, class_item);
        hotkeyModel->setItem(count, i++, path_item);
        hotkeyModel->setItem(count, i++, desc_item);
    }
}

void HotkeyManage::on_lineEdit_textChanged(const QString &arg1)
{
    if(this->ui->comboBox->currentData() == "hotkey"){
        proxyModel->setFilterKeyColumn(2);
    }
    else if(this->ui->comboBox->currentData() == "name"){
        proxyModel->setFilterKeyColumn(0);
    }
    else if(this->ui->comboBox->currentData() == "title"){
        proxyModel->setFilterKeyColumn(6);
    }
    else if(this->ui->comboBox->currentData() == "desc"){
        proxyModel->setFilterKeyColumn(9);
    }
    else{
        qDebug()<<"Not Choose ComboBox!";
        return;
    }
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(QRegExp::FixedString);
    QRegExp regExp(this->ui->lineEdit->text(), Qt::CaseInsensitive, syntax);//不区分大小写
    proxyModel->setFilterRegExp(regExp);
}

void HotkeyManage::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(this->ui->lineEdit->text() == ""){
        return;
    }
    else{
        on_lineEdit_textChanged(arg1);
    }
}

void HotkeyManage::slotTreeMenu(const QPoint &pos)
{
    QModelIndex curIndex = ui->treeView->indexAt(pos);      //当前点击的元素的index
    QModelIndex index = curIndex.sibling(curIndex.row(),0); //该行的第1列元素的index
    if (index.isValid())
    {
        hotkeyMenu.exec(QCursor::pos());  //显示菜单
    }
}

void HotkeyManage::slotTreeMenuRefresh()
{
    hotkeyModel->removeRows(0, hotkeyModel->rowCount());
    showHotkey();
}

void HotkeyManage::slotTreeMenuDeleteHotkey()
{
    QModelIndex curIndex = ui->treeView->currentIndex();    //当前点击的元素的index
    QModelIndex index0 = curIndex.sibling(curIndex.row(),0); //该行的第0列元素的index
    QModelIndex index1 = curIndex.sibling(curIndex.row(),1); //该行的第1列元素的index
    QModelIndex index2 = curIndex.sibling(curIndex.row(),2); //该行的第2列元素的index
    //qDebug()<<this->ui->treeView->model()->itemData(index1).values()[0].toString();//PID.TID
    QModelIndex index4 = curIndex.sibling(curIndex.row(),4); //该行的第4列元素的index
    //qDebug()<<this->ui->treeView->model()->itemData(index4).values()[0].toString();//HotkeyID
    QString nameStr = this->ui->treeView->model()->itemData(index0).values()[0].toString();
    QString hotkeyStr = this->ui->treeView->model()->itemData(index2).values()[0].toString();
    QMessageBox msgBox(this);
    msgBox.setText(tr("提示"));
    msgBox.setInformativeText(tr("确定要删除") + nameStr + tr("的快捷键") + hotkeyStr + tr("吗?"));
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Ok){
        auto arr = this->ui->treeView->model()->itemData(index1).values()[0].toString().split(".");
        ULONG32 pid = StrToIntegerW(arr[0].toStdWString());
        ULONG32 tid = StrToIntegerW(arr[1].toStdWString());
        ULONG32 vkid = StrToHexW(this->ui->treeView->model()->itemData(index4).values()[0].toString().toStdWString());
        HOTKEY_ITEM item;
        item.id = vkid;
        item.pid = pid;
        item.tid = tid;
        qDebug()<<pid<<" "<<tid<<" "<<vkid;
        if(ArkDrvApi::Process::HotkeyRemoveInfo(item)){
            slotTreeMenuRefresh();
            qDebug()<<"Delete hotkey success!";
        }
        else{
            QMessageBox::information(NULL , "Error","Delete hotkey failure!");
        }
    }
}

void HotkeyManage::slotTreeMenuOpenPath()
{
    QModelIndex curIndex = ui->treeView->currentIndex();    //当前点击的元素的index
    QModelIndex index8 = curIndex.sibling(curIndex.row(),8); //该行的第8列元素的index
    QString fileName;
    QProcess process;
    fileName = this->ui->treeView->model()->itemData(index8).values()[0].toString();
#ifdef WIN32
    fileName.replace("/", "\\");    //***这句windows下必要***
#endif
    process.startDetached("explorer /select," + fileName);
}

void HotkeyManage::slotTreeMenuProperty()
{
    QModelIndex curIndex = ui->treeView->currentIndex();    //当前点击的元素的index
    QModelIndex index8 = curIndex.sibling(curIndex.row(),8); //该行的第8列元素的index
    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_INVOKEIDLIST ;
    ShExecInfo.lpVerb = L"properties";
    ShExecInfo.lpFile = (LPCWSTR)this->ui->treeView->model()->itemData(index8).values()[0].toString().unicode();
    ShExecInfo.lpParameters = L"";
    ShExecInfo.lpDirectory = NULL;
    ShExecInfo.nShow = SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    qDebug()<<
    ShellExecuteEx(&ShExecInfo);
}

void HotkeyManage::Error_Out()
{
    char *temp = nullptr;
    if (FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        _Driver_Load->_Last_Error,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (char*)&temp,
        0,
        NULL))
    {
        qDebug()<<QString::fromLocal8Bit(temp);
        LocalFree(temp);
    }
}

bool HotkeyManage::HotkeyEnumInfo(std::vector<HOTKEY_ITEM> &hotkeys)
{
    DWORD op = HOTKEY_ENUM;
    PHOTKEY_INFO info;
    DWORD outlen;
    int hkmarks[HOTKEY_MAX_VK+1] = { 0 };
    for (int i = 1; i <= HOTKEY_MAX_VK; i++) {
        if (RegisterHotKey(NULL, HOTKEY_PLACEHOLDER_ID + i, MOD_ALT | MOD_NOREPEAT, i)) {
            hkmarks[i] = ~i;
        } else {
            //OutputDebugStringA(UNONE::StrFormatA("Register err:%s\n", UNONE::OsDosErrorMsgA(GetLastError()).c_str()).c_str());
            qDebug()<<"Register err";
        }
    }
    bool ret = ArkDrvApi::Process::IoControlDriver(IOCTL_ARK_HOTKEY, op, NULL, 0, (PVOID*)&info, &outlen);
    for (int i = 1; i <= HOTKEY_MAX_VK; i++) {
        if (hkmarks[i]) {
            UnregisterHotKey(NULL, HOTKEY_PLACEHOLDER_ID + i);
        }
    }
    if (!ret) return false;
    for (int i = 0; i < info->count; i++) {
        hotkeys.push_back(info->items[i]);
    }
    free(info);
    return true;
}

std::wstring HotkeyManage::FsPathToNameW(__in const std::wstring& fpath)
{
    try {
        return fpath.substr(fpath.find_last_of(L"\\/")+1);
    } catch (...) {
        return L"";
    }
}

std::wstring HotkeyManage::StrToW(__in const std::string& str)
{
    return StrCodeToWide(CP_ACP, str);
}

std::wstring HotkeyManage::StrCodeToWide(__in unsigned int code, __in const std::string& str)
{
    try {
        if (str.empty()) return L"";
        int templen = MultiByteToWideChar(code, 0, str.c_str(), -1, NULL, 0);
        if (!templen) return L"";
        wchar_t* tempstr = new(std::nothrow) wchar_t[templen*2];
        if (!tempstr) return L"";
        memset(tempstr, 0, templen*2);
        MultiByteToWideChar(code, 0, str.c_str(), -1, tempstr, templen);
        std::wstring wstr(tempstr);
        delete[] tempstr;
        return wstr;
    } catch (...) {
        return L"";
    }
}

std::wstring HotkeyManage::StrFormatW(__in const wchar_t* formats, ...)
{
    std::wstring str;
    try {
        va_list lst;
        va_start(lst,formats);
        str = StrFormatVaListW(formats, lst);
        va_end(lst);
    } catch (std::exception& e) {
        str.clear();
        qDebug("c++ exception: %s", e.what());
    } catch (...) {
        str.clear();
        qDebug("c++ exception: unknown");
    }
    return str;
}

std::string HotkeyManage::StrFormatA(__in const char* formats, ...)
{
    std::string str;
    try {
        va_list lst;
        va_start(lst,formats);
        str = StrFormatVaListA(formats, lst);
        va_end(lst);
    } catch (std::exception& e) {
        str.clear();
        qDebug("c++ exception: %s", e.what());
    } catch (...) {
        str.clear();
        qDebug("c++ exception: unknown");
    }
    return str;
}

std::string HotkeyManage::StrTrimA(__in const std::string& str, __in const std::string& charlist)
{
    try {
        if(!str.empty())
            return StrTrimLeftA(StrTrimRightA(str,charlist),charlist);
        else
            return str;
    } catch (...) {
        return "";
    }
}

std::string HotkeyManage::StrTrimRightA(__in const std::string& str, __in const std::string& charlist)
{
    if(!str.empty())
        return str.substr(0,str.find_last_not_of(charlist)+1);
    else
        return str;
}

std::wstring HotkeyManage::StrFormatVaListW(__in const wchar_t* formats, __in va_list lst)
{
    try {
        int bufsize = _vscwprintf(formats, lst) * sizeof(wchar_t);
        if (bufsize == 0)
            return L"";
        bufsize += sizeof(wchar_t);
        wchar_t* buffer = (wchar_t*) malloc(bufsize);
        if (buffer == NULL)
            return L"";
        memset(buffer, 0, bufsize);
        _vsnwprintf_s(buffer, bufsize/sizeof(wchar_t), (bufsize/sizeof(wchar_t))-1, formats, lst);
        std::wstring str(buffer);
        free(buffer);
        return std::move(str);
    } catch (...) {
        return L"";
    }
}

std::string HotkeyManage::StrFormatVaListA(__in const char* formats, __in va_list lst)
{
    try {
        int bufsize = _vscprintf(formats, lst);
        if (bufsize == 0)
            return "";
        bufsize += sizeof(char);
        char* buffer = (char*) malloc(bufsize);
        if (buffer == NULL)
            return "";
        memset(buffer, 0, bufsize);
        _vsnprintf_s(buffer, bufsize/sizeof(char), (bufsize/sizeof(char))-1, formats, lst);
        std::string str(buffer);
        free(buffer);
        return std::move(str);
    } catch (...) {
        return "";
    }
}

std::wstring HotkeyManage::PsGetWndTextW(__in HWND wnd)
{
    int size = GetWindowTextLengthW(wnd);
    if (size == 0) return L"";
    std::wstring text;
    text.resize(size + 1);
    GetWindowTextW(wnd, (LPWSTR)text.data(), size + 1);
    return text.c_str();
}

std::wstring HotkeyManage::PsGetWndClassNameW(__in HWND wnd)
{
    std::wstring name;
    name.resize(MAX_PATH);
    int retlen = GetClassNameW(wnd, (LPWSTR)name.data(), MAX_PATH-1);
    if (retlen == 0) return L"";
    if (retlen < MAX_PATH - 1) return name.c_str();
    name.resize(retlen+1);
    retlen = GetClassNameW(wnd, (LPWSTR)name.data(), retlen+1);
    if (retlen == 0) return L"";
    return name.c_str();
}

std::string HotkeyManage::HotkeyVkToString(UINT32 vk, UINT16 mod1, UINT16 mod2)
{
    std::string vks;
    if (mod1 & MOD_WIN) vks.append("+Win");
    if (mod1 & MOD_CONTROL) vks.append("+Ctrl");
    if (mod1 & MOD_ALT) vks.append("+Alt");
    if (mod1 & MOD_SHIFT) vks.append("+Shift");
    //if (mod2 & MOD_NOREPEAT) vks.append("[NoRepeat]");
    if (vk >= 0x30 && vk <= 0x5A) {
        vks.append("+");
        vks.push_back((char)vk);
    } else {
        if (vk) {
            std::string cap;
            for (auto t : VkStrTables) {
                if (t.vk == vk) {
                    cap = StrToLowerA(t.vk_str);
                    cap[0] -= 32;
                    vks.append("+" + cap);
                    break;
                }
            }
            if (cap.empty()) vks.append(StrFormatA("+(Unknown VK:%d)", vk));
        }
    }
    vks = StrTrimA(vks, "+");
    return std::move(vks);
}

std::string HotkeyManage::StrToLowerA(__in const std::string& str)
{
    try {
        std::string tmp(str);
        for (size_t i = 0; i < tmp.size(); i++) {
            tmp[i] = tolower(tmp[i]);
        }
        return std::move(tmp);
    } catch (...) {
        return "";
    }
}

std::string HotkeyManage::StrTrimLeftA(__in const std::string& str, __in const std::string& charlist)
{
    if(!str.empty())
        return str.substr(str.find_first_not_of(charlist));
    else
        return str;
}

ProcInfo HotkeyManage::CacheGetProcInfo(unsigned int pid, ProcInfo& info)
{
    QMutexLocker locker(&proc_info.lck);
    if (proc_info.d.contains(pid)) {
        auto it = proc_info.d.find(pid);
        info = it.value();
        if (!info.path.isEmpty()) {
            return info;
        }
    }
    info.pid = pid;
    if (info.ppid == -1) info.ppid = PsGetParentPid(pid);
    if (info.parent_existed == -1) {
        // May be parent id occupied by someone implies parent not existed
        info.parent_existed = 1;
        auto ppid = info.ppid;
        auto tm1 = ProcessCreateTimeValue(pid);
        auto tm2 = ProcessCreateTimeValue(ppid);
        if (PsIsDeleted(ppid) || (tm1 && tm2 && tm1 < tm2))
            info.parent_existed = 0;
    }
    bool activate = false;
    auto &&path = PsGetProcessPathW(pid);
    if (path.empty()) {
        InterCreateTlsValue(ArkDrvApi::Process::OpenProcessR0, PROCESS_VID);
        path = PsGetProcessPathW(pid);
        activate = true;
    }
    static bool is_os64 = OsIs64();
    info.path = QString::fromStdWString(path);
    if (!path.empty() && path != L"System") {
        std::wstring corp, desc;
        FsGetFileInfoW(path, L"CompanyName", corp);
        FsGetFileInfoW(path, L"FileDescription", desc);
        info.corp = QString::fromStdWString(corp);
        info.desc = QString::fromStdWString(desc);
    }
    if (info.name.isEmpty()) info.name = QString::fromStdWString(FsPathToNameW(path));
    info.ctime = QString::fromStdWString(ProcessCreateTime(pid));
    if (is_os64 && !PsIsX64(pid))	info.name.append(" *32");
    proc_info.d.insert(pid, info);

    if (activate) InterDeleteTlsValue(PROCESS_VID);

    return info;
}

FileBaseInfo HotkeyManage::CacheGetFileBaseInfo(QString path)
{
    QMutexLocker locker(&filebase_info.lck);
    if (filebase_info.d.contains(path)) {
        auto it = filebase_info.d.find(path);
        return it.value();
    }
    std::wstring corp, desc, ver;
    auto w_path = path.toStdWString();
    FsGetFileInfoW(w_path, L"CompanyName", corp);
    FsGetFileInfoW(w_path, L"FileDescription", desc);
    FsGetFileVersionW(w_path, ver);
    auto info = FileBaseInfo{ path, QString::fromStdWString(desc), QString::fromStdWString(ver),  QString::fromStdWString(corp) };
    filebase_info.d.insert(path, info);
    return info;
}

DWORD HotkeyManage::PsGetParentPid(__in DWORD pid)
{
    DWORD ppid = INVALID_PID;
    HANDLE process = VirtualOpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!process) return INVALID_PID;
    if (PsIsX64(pid)) {
        PROCESS_BASIC_INFORMATION64 pbi64;
        if (PsGetPbi64(process, pbi64))
            ppid = (DWORD)pbi64.InheritedFromUniqueProcessId;
    } else {
        PROCESS_BASIC_INFORMATIONEX32 pbi32;
        if (PsGetPbi32(process, pbi32))
            ppid = (DWORD)pbi32.InheritedFromUniqueProcessId;
    }
    CloseHandle(process);
    return ppid;
}

LONGLONG HotkeyManage::ProcessCreateTimeValue(__in DWORD pid)
{
    HANDLE phd = ArkDrvApi::Process::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!phd) {
        return 0;
    }
    FILETIME create_tm;
    FILETIME exit_tm;
    FILETIME kern_tm;
    FILETIME user_tm;
    if (!GetProcessTimes(phd, &create_tm, &exit_tm, &kern_tm, &user_tm)) {
        CloseHandle(phd);
        return 0;
    }
    CloseHandle(phd);
    return TmFileTimeToMs(create_tm);
}

bool HotkeyManage::PsIsDeleted(__in DWORD pid)
{
    bool result = false;
    HANDLE phd = VirtualOpenProcess(SYNCHRONIZE, FALSE, pid);
    if (phd) {
        if (WaitForSingleObject(phd, 0) == WAIT_OBJECT_0)	//signal
            result = true;
        CloseHandle(phd);
    } else {
        if (GetLastError() == ERROR_INVALID_PARAMETER)	//87
            result = true;
    }
    return result;
}

std::wstring HotkeyManage::PsGetProcessPathW(__in DWORD pid)
{
    WCHAR path[MAX_PATH*2] = {0};
    DWORD path_size = (MAX_PATH*2-1) * sizeof(WCHAR);

    if (pid == 0) return L"System Idle Process";
    if (pid == 4) return L"System";

    HANDLE phd = NULL;
    phd = VirtualOpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ, FALSE, pid);
    if (phd != NULL) {
        if (GetModuleFileNameExW(phd, NULL, path, path_size) != 0) {
            CloseHandle(phd);
            return path;
        }
    }

    if (phd == NULL)
        phd = VirtualOpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (phd == NULL) {
        qDebug("VirtualOpenProcess pid:%d err:%d", pid, GetLastError());
        return L"";
    }
    if (GetProcessImageFileNameW(phd, path, path_size) == 0) {
        qDebug("GetProcessImageFileNameW pid:%d err:%d", pid, GetLastError());
        CloseHandle(phd);
        return L"";
    }
    CloseHandle(phd);
    std::wstring dos_path;
    ObParseToDosPathW(path, dos_path);
    return dos_path;
}

bool HotkeyManage::InterCreateTlsValue(LPVOID val, DWORD &tlsid)
{
    DWORD idx = tlsid;
    if (idx == TLS_OUT_OF_INDEXES) {
        idx = TlsAlloc();
    }
    if (idx == TLS_OUT_OF_INDEXES) return false;
    tlsid = idx;
    bool ret = TlsSetValue(idx, val);
    if (!ret) {
        TlsFree(idx);
        return false;
    }
    return true;
}

bool HotkeyManage::OsIs64()
{
    bool result = false;
    SYSTEM_INFO si;
    RtlZeroMemory(&si, sizeof(SYSTEM_INFO));
    GetNativeSystemInfo(&si);
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
        result = true;
    return result;
}

bool HotkeyManage::FsGetFileInfoW(__in const std::wstring& path, __in const wchar_t* type, __out std::wstring& info, __in const wchar_t* translation)
{
    bool ret = false;
    std::wstring verinfo;
    if (GetResourceVersionInfoW(path, verinfo)) {
        ret = GetFileInfoByBlockW(verinfo, type, info, translation);
    }
    return ret;
}

std::wstring HotkeyManage::ProcessCreateTime(__in DWORD pid)
{
    HANDLE Process = ArkDrvApi::Process::OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (!Process) {
        return L"";
    }

    FILETIME create_tm;
    FILETIME exit_tm;
    FILETIME kern_tm;
    FILETIME user_tm;
    if (!GetProcessTimes(Process, &create_tm, &exit_tm, &kern_tm, &user_tm)) {
        CloseHandle(Process);
        return L"";
    }
    CloseHandle(Process);
    return FormatFileTime(&create_tm);
}

bool HotkeyManage::PsIsX64(__in DWORD pid)
{
    return OsIs64() && !PsIsWow64(HANDLE(pid));
}

bool HotkeyManage::InterDeleteTlsValue(DWORD &tlsid)
{
    if (tlsid == TLS_OUT_OF_INDEXES) return false;
    TlsSetValue(tlsid, nullptr);
    TlsFree(tlsid);
    tlsid = TLS_OUT_OF_INDEXES;
    return true;
}

LONGLONG HotkeyManage::FsGetFileVersionW(__in const std::wstring& path, __out std::wstring& version)
{
    LONGLONG vernumber = 0;
    std::wstring verinfo;

    if (!GetResourceVersionInfoW(path, verinfo)) {
        return -1;
    }

    UINT fixed_size = 0;
    VS_FIXEDFILEINFO* fixed_info = NULL;
    if (!VerQueryValueW(verinfo.data(), L"\\", (VOID **)&fixed_info, &fixed_size)) {
        qDebug("VerQueryValueW err:%d", GetLastError());
        return -1;
    }

    if (fixed_info == NULL || fixed_size != sizeof(VS_FIXEDFILEINFO)) {
        qDebug("fixed_info:%#x fixed_size:%#x", fixed_info, fixed_size);
        return -1;
    }

    WORD ver1 = HIWORD(fixed_info->dwFileVersionMS);
    WORD ver2 = LOWORD(fixed_info->dwFileVersionMS);
    WORD ver3 = HIWORD(fixed_info->dwFileVersionLS);
    WORD ver4 = LOWORD(fixed_info->dwFileVersionLS);
    StrFormatW(version.c_str(), L"%d.%d.%d.%d", ver1, ver2, ver3, ver4);
    vernumber = MAKELONGLONG(MAKELONG(ver2, ver1), MAKELONG(ver4, ver3));

    return vernumber;
}

HANDLE HotkeyManage::VirtualOpenProcess( _In_ DWORD dwDesiredAccess, _In_ BOOL bInheritHandle, _In_ DWORD dwProcessId )
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

bool HotkeyManage::PsGetPbi32(__in HANDLE phd, __out PROCESS_BASIC_INFORMATIONEX32 &pbi32)
{
    NTSTATUS status;
    ULONG retlen;
    PROCESS_BASIC_INFORMATIONEX pbi;
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
    auto pNtQueryInformationProcess = (__NtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");
    if (!pNtQueryInformationProcess)
        return false;
    status = pNtQueryInformationProcess(phd, ProcessBasicInformation, &pbi, sizeof(PROCESS_BASIC_INFORMATION), &retlen);
    if (!NT_SUCCESS(status))
        return false;
    pbi32.ExitStatus = pbi.ExitStatus;
    pbi32.PebBaseAddress = (ULONG)pbi.PebBaseAddress;
    pbi32.AffinityMask = (ULONG)pbi.AffinityMask;
    pbi32.BasePriority = pbi.BasePriority;
    pbi32.UniqueProcessId = (ULONG)pbi.UniqueProcessId;
    pbi32.InheritedFromUniqueProcessId = (ULONG)pbi.InheritedFromUniqueProcessId;
    return true;
}

bool HotkeyManage::PsGetPbi64(__in HANDLE phd, __out PROCESS_BASIC_INFORMATION64 &pbi64)
{
    NTSTATUS status;
    ULONG retlen;
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
#ifdef _M_IX86
    auto pNtQueryInformationProcess = (__NtWow64QueryInformationProcess64)GetProcAddress(ntdll, "NtWow64QueryInformationProcess64");
#else
    auto pNtQueryInformationProcess = (__NtQueryInformationProcess)GetProcAddress(ntdll, "NtQueryInformationProcess");
#endif
    if (!pNtQueryInformationProcess)
        return false;
    status = pNtQueryInformationProcess(phd, ProcessBasicInformation, &pbi64, sizeof(PROCESS_BASIC_INFORMATION64), &retlen);
    if (!NT_SUCCESS(status)) {
        qDebug("query process information err:%x", status);
        return false;
    }
    return true;
}

LONGLONG HotkeyManage::TmFileTimeToMs(__in const FILETIME& ft)
{
    LARGE_INTEGER li;
    li.HighPart = ft.dwHighDateTime;
    li.LowPart = ft.dwLowDateTime;
    return li.QuadPart / 10000;
}

bool HotkeyManage::ObParseToDosPathW(__in std::wstring ori_path, __out std::wstring& dos_path)
{
    bool result = false;

    //symbolic name
    std::wstring dospath, wstr, symlnk;
    WCHAR* path = (WCHAR*)ori_path.c_str();
    if (wcsncmp(path,L"\\??\\",sizeof(L"\\??\\")/2-1) == 0) {
        symlnk = path;
        symlnk = StrTruncateW(symlnk,L"\\??\\",L"\\");
        symlnk = L"\\??\\" + symlnk;
        if (ObParseSymbolicLinkW(symlnk,wstr)) {
            WCHAR* subpath = path + symlnk.size();
            ori_path = wstr + subpath;
        }
    }

    //parse nt path
    const DWORD driveslen = sizeof(DWORD)*('Z'-'A'+2);
    WCHAR drives[driveslen] = {0};
    DWORD size = GetLogicalDriveStringsW(driveslen, drives);
    if (size < driveslen) {
        DWORD i = 0;
        while (i < size) {
            WCHAR target[MAX_PATH*2] = {0};
            WCHAR volume[3] = L" :";
            volume[0] = drives[i];
            i += sizeof(DWORD);
            if (QueryDosDeviceW(volume, target, MAX_PATH*2-1) == 0)
                continue;
            int targetlen = (int)wcslen(target);
            if (_wcsnicmp(ori_path.c_str(), target, targetlen) == 0) {
                dos_path = volume + ori_path.substr(targetlen);
                result = true;
                break;
            }
        }
    }
    return result;
}

bool HotkeyManage::GetFileInfoByBlockW(__in const std::wstring& block, __in const wchar_t* type, __out std::wstring& name, __in const wchar_t* sub_translation)
{
    bool ret = false;
    struct LANGANDCODEPAGE {
        WORD language;
        WORD codepage;
    };
    UINT size = 0;
    WCHAR sub_block[MAX_PATH] = { 0 };
    if (sub_translation == NULL) {
        LANGANDCODEPAGE* Translation = NULL;
        if (!VerQueryValueW(block.c_str(), L"\\VarFileInfo\\Translation", (LPVOID*)&Translation, &size)) {
            qDebug("VerQueryValueW err:%d", GetLastError());
            return false;
        }
        _snwprintf_s(sub_block, MAX_PATH - 1,	L"\\StringFileInfo\\%04X%04X\\%s",
            Translation->language, Translation->codepage, type);
    } else {
        _snwprintf_s(sub_block, MAX_PATH - 1, L"\\StringFileInfo\\%s\\%s",
            sub_translation, type);
    }
    LPVOID buf = NULL;
    if (VerQueryValueW(block.data(), sub_block, (LPVOID*)&buf, &size)) {
        if (buf != NULL) {
            name = (WCHAR*)buf;
            ret = true;
        }
    } else {
        qDebug("VerQueryValueW %s err:%d", sub_block, GetLastError());
    }
    return ret;
}

bool HotkeyManage::GetResourceVersionInfoW(__in const std::wstring& path, __out std::wstring& verinfo)
{
    DWORD reserved1;
    DWORD reserved2 = NULL;
    DWORD versize = GetFileVersionInfoSizeW(path.c_str(), &reserved1);
    if (versize == 0) {
        qDebug("GetFileVersionInfoSizeW err:%d", GetLastError());
        return false;
    }
    verinfo.resize(versize);
    memset((void*)verinfo.c_str(), 0, versize*2);
    if (!GetFileVersionInfoW(path.c_str(), reserved2, versize, (LPVOID)verinfo.c_str())) {
        qDebug("GetFileVersionInfoW err:%d", GetLastError());
        return false;
    }
    return true;
}

std::wstring HotkeyManage::FormatFileTime(FILETIME *file_tm)
{
    SYSTEMTIME systm;
    FileTimeToSystemTime(file_tm, &systm);
    TmConvertZoneTime(systm, NULL);
    return TmFormatSystemTimeW(systm, L"Y-M-D H:W:S");
}

bool HotkeyManage::PsIsWow64(__in HANDLE phd)
{
    typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
    LPFN_ISWOW64PROCESS pIsWow64Process = NULL;
    BOOL is_wow64 = FALSE;
    pIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")),"IsWow64Process");
    if (NULL != pIsWow64Process) {
        if (!pIsWow64Process(phd,&is_wow64)) {
            // handle error
        }
    }
    return is_wow64 == TRUE;
}

bool HotkeyManage::InterGetTlsValue(DWORD tlsid, LPVOID &val)
{
    if (tlsid == TLS_OUT_OF_INDEXES) return false;
    val = TlsGetValue(tlsid);
    return true;
}

bool HotkeyManage::TmConvertZoneTime(__inout SYSTEMTIME& systm, __in LPTIME_ZONE_INFORMATION zone)
{
    return SystemTimeToTzSpecificLocalTime(zone, &systm, &systm) ? true : false;
}

std::wstring HotkeyManage::TmFormatSystemTimeW(__in const SYSTEMTIME& systm, __in const std::wstring& format)
{
    std::wstring wstr = format;
    StrReplaceW(wstr, L"y", StrFormatW(L"%d", systm.wYear));
    StrReplaceW(wstr, L"Y", StrFormatW(L"%04d", systm.wYear));
    StrReplaceW(wstr, L"m", StrFormatW(L"%d", systm.wMonth));
    StrReplaceW(wstr, L"M", StrFormatW(L"%02d", systm.wMonth));
    StrReplaceW(wstr, L"d", StrFormatW(L"%d", systm.wDay));
    StrReplaceW(wstr, L"D", StrFormatW(L"%02d", systm.wDay));
    StrReplaceW(wstr, L"h", StrFormatW(L"%d", systm.wHour));
    StrReplaceW(wstr, L"H", StrFormatW(L"%02d", systm.wHour));
    StrReplaceW(wstr, L"w", StrFormatW(L"%d", systm.wMinute));
    StrReplaceW(wstr, L"W", StrFormatW(L"%02d", systm.wMinute));
    StrReplaceW(wstr, L"s", StrFormatW(L"%d", systm.wSecond));
    StrReplaceW(wstr, L"S", StrFormatW(L"%02d", systm.wSecond));
    StrReplaceW(wstr, L"x", StrFormatW(L"%d", systm.wMilliseconds));
    StrReplaceW(wstr, L"X", StrFormatW(L"%03d", systm.wMilliseconds));
    return wstr;
}

bool HotkeyManage::StrReplaceW(__inout std::wstring& source, __in const std::wstring& pattern, __in std::wstring replaced)
{
    try {
        bool result = false;
        if (source.empty() || pattern.empty())
            return false;
        size_t pos = 0;
        while ((pos = source.find(pattern, pos)) != std::wstring::npos) {
            source.replace(pos, pattern.size(), replaced);
            pos += replaced.size();
            result = true;
        }
        return result;
    } catch (...) {
        return false;
    }
}

std::wstring HotkeyManage::StrTruncateW(__in const std::wstring& str, __in const std::wstring& startsep, __in const std::wstring& endsep)
{
    try {
        size_t start = str.find(startsep);
        if (start == std::wstring::npos)
            return L"";
        start += startsep.size();
        size_t end = str.find(endsep,start);
        if (end == std::wstring::npos)
            return L"";
        if (end <= start)
            return L"";
        return str.substr(start, end-start);
    } catch (...) {
        return L"";
    }
}

bool HotkeyManage::ObParseSymbolicLinkW(__in const std::wstring& symlnk, __out std::wstring& target)
{
    bool result = false;
    do {
        WCHAR* buff;
        ULONG retlen;
        HANDLE symlnk_obj;
        OBJECT_ATTRIBUTES oa;
        UNICODE_STRING ustr, name_str;
        HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");
        __RtlInitUnicodeString pRtlInitUnicodeString = (__RtlInitUnicodeString)GetProcAddress(ntdll,"RtlInitUnicodeString");
        if (pRtlInitUnicodeString == NULL)
            break;
        __NtOpenSymbolicLinkObject pNtOpenSymbolicLinkObject = (__NtOpenSymbolicLinkObject)GetProcAddress(ntdll,"NtOpenSymbolicLinkObject");
        if (pNtOpenSymbolicLinkObject == NULL)
            break;
        __NtQuerySymbolicLinkObject pNtQuerySymbolicLinkObject = (__NtQuerySymbolicLinkObject) GetProcAddress(ntdll,"NtQuerySymbolicLinkObject");
        if (pNtQuerySymbolicLinkObject == NULL)
            break;
        __NtClose pNtClose = (__NtClose)GetProcAddress(ntdll,"NtClose");
        if (!pNtClose)
            break;
        pRtlInitUnicodeString(&ustr, symlnk.c_str());
        InitializeObjectAttributes(&oa, &ustr, OBJ_CASE_INSENSITIVE, NULL, NULL);
        NTSTATUS status = pNtOpenSymbolicLinkObject(&symlnk_obj, SYMBOLIC_LINK_QUERY, &oa);
        if (!NT_SUCCESS(status))
            break;
        buff = new(std::nothrow) WCHAR[512];
        if (!buff)
            break;
        RtlZeroMemory(buff, 512*2);
        name_str.Buffer = buff;
        name_str.Length = 0;
        name_str.MaximumLength = 512*2;
        status = pNtQuerySymbolicLinkObject(symlnk_obj, &name_str, &retlen);
        if (!NT_SUCCESS(status)) {
            delete[] buff;
            if (status != STATUS_BUFFER_TOO_SMALL)
                break;
            buff = new(std::nothrow) WCHAR[retlen/2];
            if (!buff)
                break;
            RtlZeroMemory(buff, retlen);
            name_str.Buffer = buff;
            name_str.Length = 0;
            name_str.MaximumLength = (USHORT)retlen;
            status = pNtQuerySymbolicLinkObject(symlnk_obj, &name_str, &retlen);
            if (!NT_SUCCESS(status))
                break;
        }
        target.assign(name_str.Buffer, name_str.Length/2);
        result = true;
        delete[] buff;
    } while (0);
    return result;
}

QIcon HotkeyManage::LoadIcon(QString file_path)
{
    static struct {
        QMutex lck;
        QMap<QString, QIcon> d;
    } icon_cache;
    QMutexLocker locker(&icon_cache.lck);
    if (icon_cache.d.contains(file_path)) {
        auto it = icon_cache.d.find(file_path);
        return it.value();
    }
    QFileInfo file_info(file_path);
    QFileIconProvider provider;
    QIcon ico = provider.icon(file_info);
    for (auto qs : ico.availableSizes()) {
        if (!ico.pixmap(qs).isNull()) {
            icon_cache.d.insert(file_path, ico);
            return ico;
        }
    }
    ico = QIcon(":/QuickWin/maintools/default.ico");
    icon_cache.d.insert(file_path, ico);
    return ico;
}

int HotkeyManage::StrToIntegerW(__in const std::wstring& wstr)
{
    return (int)wcstoul(wstr.c_str(), NULL, 10);
}

unsigned int HotkeyManage::StrToHexW(__in const std::wstring& wstr)
{
    return (unsigned int)wcstoul(wstr.c_str(), NULL, 16);
}

namespace ArkDrvApi {
namespace Process {

bool HotkeyRemoveInfo(HOTKEY_ITEM &item)
{
    DWORD op = HOTKEY_REMOVE;
    DWORD out;
    DWORD outlen;
    bool ret = IoControlDriver(IOCTL_ARK_HOTKEY, op, &item, sizeof(item), (PVOID*)&out, &outlen);
    if (!ret) return false;
    return true;
}

HANDLE WINAPI OpenProcessR0(DWORD access, BOOL inherit, DWORD pid)
{
    std::string outdata;
    PROCESS_OPEN_INFO info;
    info.access = access;
    info.inherit = inherit;
    info.pid = pid;
    bool ret = IoControlDriver(IOCTL_ARK_PROCESS, PROCESS_OPEN, TO_STREAM(info), outdata);
    if (!ret) return NULL;
    HANDLE phd = (HANDLE)*(DWORD*)outdata.c_str();
    return phd;
}

HANDLE WINAPI OpenProcess(DWORD access, BOOL inherit, DWORD pid)
{
    if (pid == -1) return NULL;

    HANDLE phd = ::OpenProcess(access, inherit, pid);
    if (phd) return phd;

    if (GetLastError() != ERROR_ACCESS_DENIED) {
        qDebug("OpenProcess pid:%d err:%d", pid, GetLastError());
        return NULL;
    }

    phd = OpenProcessR0(access, inherit, pid);
    if (!phd) {
        qDebug("OpenProcess by Kernel pid:%d err:%d", pid, GetLastError());
        return NULL;
    }

    return phd;
}

bool IoControlDriver(DWORD ctlcode, DWORD op, PVOID inbuf, DWORD inlen, PVOID *outbuf, DWORD *outlen)
{
    DWORD retlen = 0;
    arkdrv = CreateFileW(
        ARK_USER_SYMBOLINK,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    if (arkdrv == INVALID_HANDLE_VALUE)
        return false;

    *outbuf = NULL;
    *outlen = 0;
    DWORD wrap_inlen = sizeof(op) + inlen;
    PUCHAR wrap_inbuf = (PUCHAR)malloc(wrap_inlen);
    if (!wrap_inbuf) return false;
    memcpy(wrap_inbuf, &op, sizeof(op));
    if (inbuf) memcpy(wrap_inbuf + sizeof(op), inbuf, inlen);

    bool ret = DeviceIoControl(
                arkdrv,
                ctlcode,
                wrap_inbuf,
                wrap_inlen,
                NULL,
                0,
                &retlen,
                NULL);
    if (ret) {
        free(wrap_inbuf);
        return true;
    }

    if (GetLastError() != ERROR_MORE_DATA) {
        free(wrap_inbuf);
        //ERR(L"DeviceIoControl err:%d", GetLastError());
        return false;
    }

    auto bufsize = retlen;
    auto buf = (PVOID)calloc(bufsize, 1);
    if (!buf) return false;
    if (!DeviceIoControl(
        arkdrv,
        ctlcode,
        wrap_inbuf,
        wrap_inlen,
        buf,
        bufsize,
        &retlen,
        NULL)) {
        free(buf);
        free(wrap_inbuf);
        //ERR(L"DeviceIoControl err:%d", GetLastError());
        return false;
    }
    *outbuf = buf;
    *outlen = retlen;
    free(wrap_inbuf);
    return true;
}

bool IoControlDriver(DWORD ctlcode, DWORD op, const std::wstring &indata, std::string &outdata)
{
    if (!ConnectDriver()) return false;
    DWORD outlen;
    CHAR *info;
    WCHAR *tempdata = NULL;
    DWORD tempsize = 0;
    if (indata.size()) {
        tempdata = (WCHAR*)indata.c_str();
        tempsize = (indata.size() + 1) * 2;
    }
    bool ret = IoControlDriver(ctlcode, op, (PVOID)tempdata, tempsize, (PVOID*)&info, &outlen);
    if (!ret) return false;
    if (outlen) outdata.assign(info, outlen);
    if (info) free(info);
    return true;
}

bool IoControlDriver(DWORD ctlcode, DWORD op, const std::string &indata, std::string &outdata)
{
    if (!ConnectDriver()) return false;
    DWORD outlen;
    CHAR *info;
    CHAR *tempdata = NULL;
    DWORD tempsize = 0;
    if (indata.size()) {
        tempdata = (CHAR*)indata.c_str();
        tempsize = indata.size();
    }
    bool ret = IoControlDriver(ctlcode, op, (PVOID)tempdata, tempsize, (PVOID*)&info, &outlen);
    if (!ret) return false;
    outdata.assign(info, outlen);
    if (info) free(info);
    return true;
}

bool ConnectDriver()
{
    if (ArkDrvApi::Process::arkdrv != INVALID_HANDLE_VALUE) return true;
    ArkDrvApi::Process::arkdrv = CreateFileW(
        ARK_USER_SYMBOLINK,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    if (ArkDrvApi::Process::arkdrv == INVALID_HANDLE_VALUE) {
        return false;
    }
    return true;
}
}
}
