/********************************************************************************
** Form generated from reading UI file 'textselectwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTSELECTWIDGET_H
#define UI_TEXTSELECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextSelectWidget
{
public:
    QFrame *frame;
    QComboBox *comboBox;
    QPushButton *pushButtonGray;
    QPushButton *pushButtonGreen;
    QPushButton *pushButtonBlue;
    QPushButton *pushButtonYellow;
    QPushButton *pushButtonRed;
    QPushButton *pushButtonWhite;

    void setupUi(QWidget *TextSelectWidget)
    {
        if (TextSelectWidget->objectName().isEmpty())
            TextSelectWidget->setObjectName(QString::fromUtf8("TextSelectWidget"));
        TextSelectWidget->resize(230, 38);
        TextSelectWidget->setMaximumSize(QSize(514, 16777215));
        TextSelectWidget->setStyleSheet(QString::fromUtf8("QFrame#frame{	\n"
"	border-radius: 2px;\n"
"	background-color: rgba(0, 0, 0, 214);\n"
"}\n"
"\n"
"QComboBox{\n"
"    border-radius: 2px;\n"
"}\n"
"\n"
"QPushButton#pushButtonRed {\n"
"    background-color: rgba(250, 0, 0, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonRed:hover {\n"
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
"    border-image:url(:/imag"
                        "e/pc_screenshot_color_hover.png);\n"
"}\n"
"QPushButton#pushButtonBlue:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected.png);\n"
"}\n"
"\n"
"QPushButton#pushButtonGreen {\n"
"    background-color: rgba(116, 224, 0, 1);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#pushButtonGreen:hover {\n"
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
"    border-i"
                        "mage:url(:/image/pc_screenshot_color_hover_white.png);\n"
"}\n"
"QPushButton#pushButtonWhite:checked {\n"
"    border-image:url(:/image/pc_screenshot_color_selected_white.png);\n"
"}"));
        frame = new QFrame(TextSelectWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 230, 38));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        comboBox = new QComboBox(frame);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(16, 9, 60, 20));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(60, 20));
        comboBox->setMaximumSize(QSize(60, 20));
        comboBox->setAutoFillBackground(false);
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox::drop-down {\n"
"	width:0px;\n"
"	image: none;\n"
" }\n"
"\n"
"QComboBox QAbstractItemView {\n"
"	min-height: 87px;\n"
"	max-height:87px;\n"
"	min-width:60px;\n"
"	font-size:12px;	\n"
"	background-color: rgb(255, 255, 255);\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"QComboBox {\n"
"	image: url(:/image/pc_screenshot_textsize_normal.png);\n"
"	color: rgba(0, 0, 0, 0.86);\n"
"     padding-left: 18px;\n"
"	font-size:12px;\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        comboBox->setFrame(false);
        pushButtonGray = new QPushButton(frame);
        pushButtonGray->setObjectName(QString::fromUtf8("pushButtonGray"));
        pushButtonGray->setGeometry(QRect(176, 11, 16, 16));
        pushButtonGray->setMinimumSize(QSize(16, 16));
        pushButtonGray->setMaximumSize(QSize(16, 16));
        pushButtonGray->setIconSize(QSize(16, 16));
        pushButtonGray->setCheckable(true);
        pushButtonGreen = new QPushButton(frame);
        pushButtonGreen->setObjectName(QString::fromUtf8("pushButtonGreen"));
        pushButtonGreen->setGeometry(QRect(154, 11, 16, 16));
        pushButtonGreen->setMinimumSize(QSize(16, 16));
        pushButtonGreen->setMaximumSize(QSize(16, 16));
        pushButtonGreen->setIconSize(QSize(16, 16));
        pushButtonGreen->setCheckable(true);
        pushButtonBlue = new QPushButton(frame);
        pushButtonBlue->setObjectName(QString::fromUtf8("pushButtonBlue"));
        pushButtonBlue->setGeometry(QRect(132, 11, 16, 16));
        pushButtonBlue->setMinimumSize(QSize(16, 16));
        pushButtonBlue->setMaximumSize(QSize(16, 16));
        pushButtonBlue->setStyleSheet(QString::fromUtf8(""));
        pushButtonBlue->setIconSize(QSize(16, 16));
        pushButtonBlue->setCheckable(true);
        pushButtonBlue->setChecked(false);
        pushButtonYellow = new QPushButton(frame);
        pushButtonYellow->setObjectName(QString::fromUtf8("pushButtonYellow"));
        pushButtonYellow->setGeometry(QRect(110, 11, 16, 16));
        pushButtonYellow->setMinimumSize(QSize(16, 16));
        pushButtonYellow->setMaximumSize(QSize(16, 16));
        pushButtonYellow->setAutoFillBackground(false);
        pushButtonYellow->setStyleSheet(QString::fromUtf8(""));
        pushButtonYellow->setIconSize(QSize(16, 16));
        pushButtonYellow->setCheckable(true);
        pushButtonRed = new QPushButton(frame);
        pushButtonRed->setObjectName(QString::fromUtf8("pushButtonRed"));
        pushButtonRed->setGeometry(QRect(88, 11, 16, 16));
        pushButtonRed->setMinimumSize(QSize(16, 16));
        pushButtonRed->setMaximumSize(QSize(16, 16));
        pushButtonRed->setStyleSheet(QString::fromUtf8(""));
        pushButtonRed->setIconSize(QSize(16, 16));
        pushButtonRed->setCheckable(true);
        pushButtonRed->setChecked(true);
        pushButtonWhite = new QPushButton(frame);
        pushButtonWhite->setObjectName(QString::fromUtf8("pushButtonWhite"));
        pushButtonWhite->setGeometry(QRect(198, 11, 16, 16));
        pushButtonWhite->setMinimumSize(QSize(16, 16));
        pushButtonWhite->setMaximumSize(QSize(16, 16));
        pushButtonWhite->setStyleSheet(QString::fromUtf8(""));
        pushButtonWhite->setIconSize(QSize(16, 16));
        pushButtonWhite->setCheckable(true);

        retranslateUi(TextSelectWidget);

        QMetaObject::connectSlotsByName(TextSelectWidget);
    } // setupUi

    void retranslateUi(QWidget *TextSelectWidget)
    {
        TextSelectWidget->setWindowTitle(QCoreApplication::translate("TextSelectWidget", "Form", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("TextSelectWidget", "\345\260\217", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("TextSelectWidget", "\344\270\255", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("TextSelectWidget", "\345\244\247", nullptr));

        pushButtonGray->setText(QString());
        pushButtonGreen->setText(QString());
        pushButtonBlue->setText(QString());
        pushButtonYellow->setText(QString());
        pushButtonRed->setText(QString());
        pushButtonWhite->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TextSelectWidget: public Ui_TextSelectWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTSELECTWIDGET_H
