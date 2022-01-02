/********************************************************************************
** Form generated from reading UI file 'selectwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTWIDGET_H
#define UI_SELECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SelectWidget
{
public:
    QFrame *frame;
    QFrame *line;
    QPushButton *pushButtonSmall;
    QPushButton *pushButtonMiddle;
    QPushButton *pushButtonLarge;
    QPushButton *pushButtonBlue;
    QPushButton *pushButtonYellow;
    QPushButton *pushButtonRed;
    QPushButton *pushButtonGreen;
    QPushButton *pushButtonGray;
    QPushButton *pushButtonWhite;

    void setupUi(QWidget *SelectWidget)
    {
        if (SelectWidget->objectName().isEmpty())
            SelectWidget->setObjectName(QString::fromUtf8("SelectWidget"));
        SelectWidget->resize(245, 38);
        SelectWidget->setMaximumSize(QSize(514, 16777215));
        SelectWidget->setStyleSheet(QString::fromUtf8("QFrame#frame{	\n"
"	border-radius: 2px;\n"
"	background-color: rgba(0, 0, 0, 214);\n"
"}\n"
"QPushButton#pushButtonSmall {\n"
"    background-color: rgba(176, 176, 176, 1);\n"
"    border-radius: 3px;\n"
"}\n"
"QPushButton#pushButtonSmall:hover {\n"
"}\n"
"QPushButton#pushButtonSmall:checked {\n"
"    background-color:rgba(0, 89, 255, 1);\n"
"}\n"
"\n"
"QPushButton#pushButtonMiddle{\n"
"    background-color: rgba(176, 176, 176, 1);\n"
"    border-radius: 5px;\n"
"}\n"
"QPushButton#pushButtonMiddle:hover {\n"
"}\n"
"QPushButton#pushButtonMiddle:checked {\n"
"    background-color:rgba(0, 89, 255, 1);\n"
"}\n"
"\n"
"QPushButton#pushButtonLarge {\n"
"    background-color: rgba(176, 176, 176, 1);\n"
"    border-radius: 7px;\n"
"}\n"
"QPushButton#pushButtonLarge:hover {\n"
"}\n"
"QPushButton#pushButtonLarge:checked {\n"
"    background-color:rgba(0, 89, 255, 1);\n"
"}\n"
"\n"
"QPushButton#pushButtonRed {\n"
"    background-color: rgba(250, 0, 0, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonRed:hov"
                        "er {\n"
"    border-image:url(:/image/pc_screenshot_color_hover.png);\n"
"}\n"
"QPushButton#pushButtonRed:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected.png);\n"
"}\n"
"\n"
"QPushButton#pushButtonYellow {\n"
"    background-color: rgba(255, 204, 0, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonYellow:hover {\n"
"    border-image:url(:/image/pc_screenshot_color_hover.png);\n"
"}\n"
"QPushButton#pushButtonYellow:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected.png);\n"
"}\n"
"\n"
"QPushButton#pushButtonBlue {\n"
"    background-color: rgba(69, 134, 255, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonBlue:hover {\n"
"    border-image:url(:/image/pc_screenshot_color_hover.png);\n"
"}\n"
"QPushButton#pushButtonBlue:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected.png);\n"
"}\n"
"\n"
"QPushButton#pushButtonGreen {\n"
"    background-color: rgba(116, 224, 0, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#p"
                        "ushButtonGreen:hover {\n"
"    border-image:url(:/image/pc_screenshot_color_hover.png);\n"
"}\n"
"QPushButton#pushButtonGreen:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected.png);\n"
"}\n"
"\n"
"QPushButton#pushButtonGray {\n"
"    background-color: rgba(74, 74, 74, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonGray:hover {\n"
"    border-image:url(:/image/pc_screenshot_color_hover.png);\n"
"}\n"
"QPushButton#pushButtonGray:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected.png);\n"
"}\n"
"\n"
"QPushButton#pushButtonWhite{\n"
"    background-color: rgba(255, 255, 255, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonWhite:hover {\n"
"    border-image:url(:/image/pc_screenshot_color_hover_white.png);\n"
"}\n"
"QPushButton#pushButtonWhite:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected_white.png);\n"
"}"));
        frame = new QFrame(SelectWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 245, 38));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setEnabled(false);
        line->setGeometry(QRect(90, 10, 1, 18));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(18);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMaximumSize(QSize(1, 18));
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0.30);"));
        line->setFrameShadow(QFrame::Sunken);
        line->setFrameShape(QFrame::VLine);
        pushButtonSmall = new QPushButton(frame);
        pushButtonSmall->setObjectName(QString::fromUtf8("pushButtonSmall"));
        pushButtonSmall->setGeometry(QRect(16, 16, 6, 6));
        pushButtonSmall->setMinimumSize(QSize(6, 6));
        pushButtonSmall->setMaximumSize(QSize(6, 6));
        pushButtonSmall->setCheckable(true);
        pushButtonSmall->setChecked(true);
        pushButtonMiddle = new QPushButton(frame);
        pushButtonMiddle->setObjectName(QString::fromUtf8("pushButtonMiddle"));
        pushButtonMiddle->setGeometry(QRect(38, 14, 10, 10));
        pushButtonMiddle->setMinimumSize(QSize(10, 10));
        pushButtonMiddle->setMaximumSize(QSize(10, 10));
        pushButtonMiddle->setCheckable(true);
        pushButtonLarge = new QPushButton(frame);
        pushButtonLarge->setObjectName(QString::fromUtf8("pushButtonLarge"));
        pushButtonLarge->setGeometry(QRect(64, 12, 14, 14));
        pushButtonLarge->setMinimumSize(QSize(14, 14));
        pushButtonLarge->setMaximumSize(QSize(14, 14));
        pushButtonLarge->setCheckable(true);
        pushButtonBlue = new QPushButton(frame);
        pushButtonBlue->setObjectName(QString::fromUtf8("pushButtonBlue"));
        pushButtonBlue->setGeometry(QRect(147, 11, 16, 16));
        pushButtonBlue->setMinimumSize(QSize(16, 16));
        pushButtonBlue->setMaximumSize(QSize(16, 16));
        pushButtonBlue->setStyleSheet(QString::fromUtf8(""));
        pushButtonBlue->setIconSize(QSize(16, 16));
        pushButtonBlue->setCheckable(true);
        pushButtonBlue->setChecked(false);
        pushButtonYellow = new QPushButton(frame);
        pushButtonYellow->setObjectName(QString::fromUtf8("pushButtonYellow"));
        pushButtonYellow->setGeometry(QRect(125, 11, 16, 16));
        pushButtonYellow->setMinimumSize(QSize(16, 16));
        pushButtonYellow->setMaximumSize(QSize(16, 16));
        pushButtonYellow->setAutoFillBackground(false);
        pushButtonYellow->setStyleSheet(QString::fromUtf8(""));
        pushButtonYellow->setIconSize(QSize(16, 16));
        pushButtonYellow->setCheckable(true);
        pushButtonRed = new QPushButton(frame);
        pushButtonRed->setObjectName(QString::fromUtf8("pushButtonRed"));
        pushButtonRed->setGeometry(QRect(103, 11, 16, 16));
        pushButtonRed->setMinimumSize(QSize(16, 16));
        pushButtonRed->setMaximumSize(QSize(16, 16));
        pushButtonRed->setStyleSheet(QString::fromUtf8(""));
        pushButtonRed->setIconSize(QSize(16, 16));
        pushButtonRed->setCheckable(true);
        pushButtonRed->setChecked(true);
        pushButtonGreen = new QPushButton(frame);
        pushButtonGreen->setObjectName(QString::fromUtf8("pushButtonGreen"));
        pushButtonGreen->setGeometry(QRect(169, 11, 16, 16));
        pushButtonGreen->setMinimumSize(QSize(16, 16));
        pushButtonGreen->setMaximumSize(QSize(16, 16));
        pushButtonGreen->setIconSize(QSize(16, 16));
        pushButtonGreen->setCheckable(true);
        pushButtonGray = new QPushButton(frame);
        pushButtonGray->setObjectName(QString::fromUtf8("pushButtonGray"));
        pushButtonGray->setGeometry(QRect(191, 11, 16, 16));
        pushButtonGray->setMinimumSize(QSize(16, 16));
        pushButtonGray->setMaximumSize(QSize(16, 16));
        pushButtonGray->setIconSize(QSize(16, 16));
        pushButtonGray->setCheckable(true);
        pushButtonWhite = new QPushButton(frame);
        pushButtonWhite->setObjectName(QString::fromUtf8("pushButtonWhite"));
        pushButtonWhite->setGeometry(QRect(213, 11, 16, 16));
        pushButtonWhite->setMinimumSize(QSize(16, 16));
        pushButtonWhite->setMaximumSize(QSize(16, 16));
        pushButtonWhite->setStyleSheet(QString::fromUtf8(""));
        pushButtonWhite->setIconSize(QSize(16, 16));
        pushButtonWhite->setCheckable(true);

        retranslateUi(SelectWidget);

        QMetaObject::connectSlotsByName(SelectWidget);
    } // setupUi

    void retranslateUi(QWidget *SelectWidget)
    {
        SelectWidget->setWindowTitle(QCoreApplication::translate("SelectWidget", "Form", nullptr));
        pushButtonSmall->setText(QString());
        pushButtonMiddle->setText(QString());
        pushButtonLarge->setText(QString());
        pushButtonBlue->setText(QString());
        pushButtonYellow->setText(QString());
        pushButtonRed->setText(QString());
        pushButtonGreen->setText(QString());
        pushButtonGray->setText(QString());
        pushButtonWhite->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SelectWidget: public Ui_SelectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTWIDGET_H
