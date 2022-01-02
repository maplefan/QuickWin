#ifndef APPCONFIG_H
#define APPCONFIG_H

#include <QFile>
#include <QString>
#include <QTranslator>
#include <QDateTime>

#define CURRENT_TIME QDateTime::currentDateTime().toString("[yyyy-MM-dd hh:mm:ss]")

#ifdef QT_NO_KEYWORDS
#define foreach Q_FOREACH
#endif

class MainWindow;

class AppConfig
{
public:
    AppConfig();

    static QString APPID;
    static int VERSION;
    static QString VERSION_NAME;

    /// ����ȫ�ֱ���
    static QString AppDataPath_Main; //����������Ŀ¼
    static QString AppDataPath_Data; //�������ݵ�dataĿ¼
    static QString AppDataPath_Tmp; //��ʱĿ¼(�����˳�ʱ����մ�Ŀ¼)
    static QString AppDataPath_TmpFile; //��������ʱ �������ļ����˳�ʱɾ�����ļ��������жϳ����Ƿ������˳�
    static QString AppFilePath_Log; //��־Ŀ¼
    static QString AppFilePath_LogFile; //��־�ļ�
    static QString AppFilePath_EtcFile; //������Ϣ

    static MainWindow *gMainWindow;
    static QRect gMainWindowRect; //�����ڵ�λ�� - ���ڱ���ڷ�ȫ��ģʽ�µĵ�����С
    static QRect gScreenRect;

    static bool gVideoKeepAspectRatio; //��Ƶ����������
    static bool gVideoHardDecoder; //Ӳ�����
    static QString gVideoFilePath; //����Ƶ�ļ���Ĭ��λ��


    static void MakeDir(QString dirName);
    static void InitAllDataPath(); //��ʼ���������ݱ����·��

    static QString bufferToString(QByteArray sendbuf);
    static QByteArray StringToBuffer(QString);
    static QString getFileMd5(QString filePath,qint64 size=-1);

    ///�����ļ�
    static void loadConfigInfoFromFile();
    static void saveConfigInfoToFile();

    ///д��־
    static void WriteLog(QString str);
    static void InitLogFile();
    static QString getSizeInfo(qint64 size);

    static QImage ImagetoGray( QImage image); //���ɻҶ�ͼ

    ///�����ļ���
    static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);

    ///ɾ��Ŀ¼
    static bool removeDirectory(QString dirName);

    ///�������
    static bool restartSelf();

    ///���ߺ���(����)
    static void mSleep(int mSecond);
};

#endif // APPCONFIG_H
