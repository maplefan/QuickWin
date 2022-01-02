#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QString>
#include <QVector>
#ifndef WORDS_H
#define WORDS_H

class Words {

public:
    Words();
    Words(bool, QVector<QString>,QString,QString, QString);
    bool isWord;
    QVector<QString> explains;
    QString phonetic;
    QString query;
    QString voice_url;
};
#endif // WORDS_H
