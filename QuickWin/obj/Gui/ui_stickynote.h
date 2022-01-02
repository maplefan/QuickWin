/********************************************************************************
** Form generated from reading UI file 'stickynote.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STICKYNOTE_H
#define UI_STICKYNOTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StickyNote
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QPushButton *addBtn;
    QPushButton *topBtn;
    QPushButton *editBtn;
    QPushButton *minBtn;
    QPushButton *settingBtn;
    QPushButton *deleteBtn;
    QLineEdit *lineEdit;
    QLabel *titleLabel;

    void setupUi(QMainWindow *StickyNote)
    {
        if (StickyNote->objectName().isEmpty())
            StickyNote->setObjectName(QString::fromUtf8("StickyNote"));
        StickyNote->resize(800, 800);
        centralwidget = new QWidget(StickyNote);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(15, 45, 395, 360));
        textEdit->setFrameShape(QFrame::NoFrame);
        addBtn = new QPushButton(centralwidget);
        addBtn->setObjectName(QString::fromUtf8("addBtn"));
        addBtn->setGeometry(QRect(5, 3, 36, 36));
        topBtn = new QPushButton(centralwidget);
        topBtn->setObjectName(QString::fromUtf8("topBtn"));
        topBtn->setGeometry(QRect(46, 3, 36, 36));
        editBtn = new QPushButton(centralwidget);
        editBtn->setObjectName(QString::fromUtf8("editBtn"));
        editBtn->setGeometry(QRect(87, 3, 36, 36));
        minBtn = new QPushButton(centralwidget);
        minBtn->setObjectName(QString::fromUtf8("minBtn"));
        minBtn->setGeometry(QRect(302, 3, 36, 36));
        settingBtn = new QPushButton(centralwidget);
        settingBtn->setObjectName(QString::fromUtf8("settingBtn"));
        settingBtn->setGeometry(QRect(343, 3, 36, 36));
        deleteBtn = new QPushButton(centralwidget);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        deleteBtn->setGeometry(QRect(384, 3, 36, 36));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(130, 3, 165, 36));
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(130, 3, 165, 36));
        StickyNote->setCentralWidget(centralwidget);

        retranslateUi(StickyNote);

        QMetaObject::connectSlotsByName(StickyNote);
    } // setupUi

    void retranslateUi(QMainWindow *StickyNote)
    {
        StickyNote->setWindowTitle(QCoreApplication::translate("StickyNote", "StickyNote", nullptr));
        addBtn->setText(QString());
        topBtn->setText(QString());
        editBtn->setText(QString());
        minBtn->setText(QString());
        settingBtn->setText(QString());
        deleteBtn->setText(QString());
        titleLabel->setText(QCoreApplication::translate("StickyNote", "Title", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StickyNote: public Ui_StickyNote {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STICKYNOTE_H
