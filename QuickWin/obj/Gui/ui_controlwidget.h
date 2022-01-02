/********************************************************************************
** Form generated from reading UI file 'controlwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLWIDGET_H
#define UI_CONTROLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlWidget
{
public:
    QFrame *frame;
    QFrame *line;
    QPushButton *returneditBtn;
    QPushButton *drawLineBtn;
    QPushButton *arrowBtn;
    QPushButton *textEditBtn;
    QPushButton *rectangleBtn;
    QPushButton *drawRoundBtn;
    QPushButton *saveBtn;
    QPushButton *cancelBtn;
    QPushButton *finishBtn;
    QPushButton *stayBtn;
    QPushButton *drawMarkLineBtn;

    void setupUi(QWidget *ControlWidget)
    {
        if (ControlWidget->objectName().isEmpty())
            ControlWidget->setObjectName(QString::fromUtf8("ControlWidget"));
        ControlWidget->resize(350, 38);
        ControlWidget->setMaximumSize(QSize(389, 38));
        ControlWidget->setAutoFillBackground(false);
        ControlWidget->setStyleSheet(QString::fromUtf8("QFrame#frame{	\n"
"	border-radius: 2px;\n"
"	background-color: rgba(0, 0, 0, 214);\n"
"}\n"
"QPushButton#rectangleBtn {\n"
"	border-image:url(:/image/pc_screenshot_rectangle_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#rectangleBtn:hover {\n"
"    border-image:url(:/image/pc_screenshot_rectangle_hover.png);\n"
"}\n"
"QPushButton#rectangleBtn:pressed {\n"
"	border-image: url(:/image/pc_screenshot_rectangle_click.png);	\n"
"}\n"
"QPushButton#rectangleBtn:checked {\n"
"	border-image: url(:/image/pc_screenshot_rectangle_click.png);	\n"
"}\n"
"\n"
"QPushButton#drawRoundBtn {\n"
"    border-image: url(:/image/pc_screenshot_circle_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#drawRoundBtn:hover {\n"
"	border-image:url(:/image/pc_screenshot_circle_hover.png);\n"
"}\n"
"QPushButton#drawRoundBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_circle_click.png);\n"
"}\n"
"QPushButton#drawRoundBtn:checked {\n"
"    border-image:url(:/image/pc_screenshot_circle_click.png);\n"
"}\n"
""
                        "\n"
"QPushButton#arrowBtn {\n"
"    border-image: url(:/image/pc_screenshot_arrow_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#arrowBtn:hover {\n"
"	border-image: url(:/image/pc_screenshot_arrow_hover.png);\n"
"}\n"
"QPushButton#arrowBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_arrow_click.png);\n"
"}\n"
"QPushButton#arrowBtn:checked {\n"
"    border-image:url(:/image/pc_screenshot_arrow_click.png);\n"
"}\n"
"\n"
"QPushButton#drawLineBtn{\n"
"    border-image: url(:/image/pc_screenshot_pen_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#drawLineBtn:hover {\n"
"	border-image:url(:/image/pc_screenshot_pen_hover.png)\n"
"}\n"
"QPushButton#drawLineBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_pen_click.png);\n"
"}\n"
"QPushButton#drawLineBtn:checked {\n"
"    border-image:url(:/image/pc_screenshot_pen_click.png);\n"
"}\n"
"\n"
"QPushButton#textEditBtn {\n"
"    border-image: url(:/image/pc_screenshot_text_normal.png);\n"
"    border-radius: 1px;\n"
"}"
                        "\n"
"QPushButton#textEditBtn:hover {\n"
"    border-image:url(:/image/pc_screenshot_text_hover.png);\n"
"}\n"
"QPushButton#textEditBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_text_click.png);\n"
"}\n"
"QPushButton#textEditBtn:checked {\n"
"    border-image:url(:/image/pc_screenshot_text_click.png);\n"
"}\n"
"\n"
"Line#line{\n"
"	background-color: rgba(255, 255, 255, 0x4D);\n"
"}\n"
"\n"
"QPushButton#returneditBtn {\n"
"    border-image: url(:/image/pc_screenshot_recall_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#returneditBtn:disabled {\n"
"    border-image: url(:/image/pc_screenshot_disabled_click.png);\n"
"}\n"
"QPushButton#returneditBtn:hover {\n"
"    border-image: url(:/image/pc_screenshot_recall_hover.png);\n"
"}\n"
"QPushButton#returneditBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_recall_click.png);\n"
"}\n"
"\n"
"QPushButton#saveBtn{\n"
"    border-image: url(:/image/pc_screenshot_save_normal2x.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#"
                        "saveBtn:hover {\n"
"    border-image:url(:/image/pc_screenshot_save_hover.png);\n"
"}\n"
"QPushButton#saveBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_save_click.png);\n"
"}\n"
"\n"
"QPushButton#cancelBtn {\n"
"    border-image: url(:/image/pc_screenshot_cancel_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#cancelBtn:hover {\n"
"    border-image: url(:/image/pc_screenshot_cancel_hover.png);\n"
"}\n"
"QPushButton#cancelBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_cancel_click.png);\n"
"}\n"
"\n"
"QPushButton#finishBtn {\n"
"    border-image:url(:/image/pc_screenshot_complete_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#finishBtn:hover {\n"
"    border-image:url(:/image/pc_screenshot_complete_hover.png);\n"
"}\n"
"QPushButton#finishBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_conplete_click.png);\n"
"}\n"
"\n"
"QPushButton#drawMarkLineBtn {\n"
"    border-image:url(:/image/pc_screenshot_markpen_normal.png);\n"
"    border-radius: 1"
                        "px;\n"
"}\n"
"QPushButton#drawMarkLineBtn:hover {\n"
"    border-image:url(:/image/pc_screenshot_markpen_hover.png);\n"
"}\n"
"QPushButton#drawMarkLineBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_markpen_click.png);\n"
"}\n"
"\n"
"QPushButton#stayBtn {\n"
"    border-image:url(:/image/pc_screenshot_rectangle_stay_normal.png);\n"
"    border-radius: 1px;\n"
"}\n"
"QPushButton#stayBtn:hover {\n"
"    border-image:url(:/image/pc_screenshot_rectangle_stay_hover.png);\n"
"}\n"
"QPushButton#stayBtn:pressed {\n"
"    border-image:url(:/image/pc_screenshot_stay_click.png);\n"
"}"));
        frame = new QFrame(ControlWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 350, 38));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(220, 10, 1, 18));
        line->setMaximumSize(QSize(1, 18));
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0.30);"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        returneditBtn = new QPushButton(frame);
        returneditBtn->setObjectName(QString::fromUtf8("returneditBtn"));
        returneditBtn->setGeometry(QRect(190, 9, 20, 20));
        returneditBtn->setMaximumSize(QSize(20, 20));
        returneditBtn->setIconSize(QSize(20, 20));
        returneditBtn->setCheckable(false);
        returneditBtn->setAutoExclusive(false);
        drawLineBtn = new QPushButton(frame);
        drawLineBtn->setObjectName(QString::fromUtf8("drawLineBtn"));
        drawLineBtn->setGeometry(QRect(100, 9, 20, 20));
        drawLineBtn->setMaximumSize(QSize(20, 20));
        drawLineBtn->setIconSize(QSize(20, 20));
        drawLineBtn->setCheckable(true);
        drawLineBtn->setAutoExclusive(false);
        arrowBtn = new QPushButton(frame);
        arrowBtn->setObjectName(QString::fromUtf8("arrowBtn"));
        arrowBtn->setGeometry(QRect(70, 9, 20, 20));
        arrowBtn->setMaximumSize(QSize(20, 20));
        arrowBtn->setIconSize(QSize(20, 20));
        arrowBtn->setCheckable(true);
        arrowBtn->setAutoExclusive(false);
        textEditBtn = new QPushButton(frame);
        textEditBtn->setObjectName(QString::fromUtf8("textEditBtn"));
        textEditBtn->setGeometry(QRect(130, 9, 20, 20));
        textEditBtn->setMaximumSize(QSize(20, 20));
        textEditBtn->setIconSize(QSize(20, 20));
        textEditBtn->setCheckable(true);
        textEditBtn->setAutoExclusive(false);
        rectangleBtn = new QPushButton(frame);
        rectangleBtn->setObjectName(QString::fromUtf8("rectangleBtn"));
        rectangleBtn->setGeometry(QRect(10, 9, 20, 20));
        rectangleBtn->setMaximumSize(QSize(20, 20));
        rectangleBtn->setIconSize(QSize(20, 20));
        rectangleBtn->setCheckable(true);
        rectangleBtn->setAutoExclusive(false);
        drawRoundBtn = new QPushButton(frame);
        drawRoundBtn->setObjectName(QString::fromUtf8("drawRoundBtn"));
        drawRoundBtn->setGeometry(QRect(40, 9, 20, 20));
        drawRoundBtn->setMaximumSize(QSize(20, 20));
        drawRoundBtn->setIconSize(QSize(20, 20));
        drawRoundBtn->setCheckable(true);
        drawRoundBtn->setAutoExclusive(false);
        saveBtn = new QPushButton(frame);
        saveBtn->setObjectName(QString::fromUtf8("saveBtn"));
        saveBtn->setGeometry(QRect(230, 9, 20, 20));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(saveBtn->sizePolicy().hasHeightForWidth());
        saveBtn->setSizePolicy(sizePolicy1);
        saveBtn->setMaximumSize(QSize(20, 20));
        saveBtn->setIconSize(QSize(20, 20));
        cancelBtn = new QPushButton(frame);
        cancelBtn->setObjectName(QString::fromUtf8("cancelBtn"));
        cancelBtn->setGeometry(QRect(290, 9, 20, 20));
        cancelBtn->setMaximumSize(QSize(20, 20));
        cancelBtn->setIconSize(QSize(20, 20));
        finishBtn = new QPushButton(frame);
        finishBtn->setObjectName(QString::fromUtf8("finishBtn"));
        finishBtn->setGeometry(QRect(320, 9, 20, 20));
        sizePolicy1.setHeightForWidth(finishBtn->sizePolicy().hasHeightForWidth());
        finishBtn->setSizePolicy(sizePolicy1);
        finishBtn->setMaximumSize(QSize(20, 20));
        finishBtn->setIconSize(QSize(20, 20));
        stayBtn = new QPushButton(frame);
        stayBtn->setObjectName(QString::fromUtf8("stayBtn"));
        stayBtn->setGeometry(QRect(260, 10, 20, 20));
        sizePolicy1.setHeightForWidth(stayBtn->sizePolicy().hasHeightForWidth());
        stayBtn->setSizePolicy(sizePolicy1);
        stayBtn->setMaximumSize(QSize(20, 20));
        stayBtn->setIconSize(QSize(20, 20));
        drawMarkLineBtn = new QPushButton(frame);
        drawMarkLineBtn->setObjectName(QString::fromUtf8("drawMarkLineBtn"));
        drawMarkLineBtn->setGeometry(QRect(160, 10, 20, 20));
        drawMarkLineBtn->setMaximumSize(QSize(20, 20));
        drawMarkLineBtn->setIconSize(QSize(20, 20));
        drawMarkLineBtn->setCheckable(true);
        drawMarkLineBtn->setAutoExclusive(false);

        retranslateUi(ControlWidget);

        QMetaObject::connectSlotsByName(ControlWidget);
    } // setupUi

    void retranslateUi(QWidget *ControlWidget)
    {
        ControlWidget->setWindowTitle(QCoreApplication::translate("ControlWidget", "Form", nullptr));
#if QT_CONFIG(tooltip)
        returneditBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\346\222\244\351\224\200\346\223\215\344\275\234", nullptr));
#endif // QT_CONFIG(tooltip)
        returneditBtn->setText(QString());
#if QT_CONFIG(tooltip)
        drawLineBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\347\224\273\347\254\224", nullptr));
#endif // QT_CONFIG(tooltip)
        drawLineBtn->setText(QString());
#if QT_CONFIG(tooltip)
        arrowBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\347\224\273\347\256\255\345\244\264", nullptr));
#endif // QT_CONFIG(tooltip)
        arrowBtn->setText(QString());
#if QT_CONFIG(tooltip)
        textEditBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\346\267\273\345\212\240\346\226\207\345\255\227", nullptr));
#endif // QT_CONFIG(tooltip)
        textEditBtn->setText(QString());
#if QT_CONFIG(tooltip)
        rectangleBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\347\224\273\347\237\251\345\275\242", nullptr));
#endif // QT_CONFIG(tooltip)
        rectangleBtn->setText(QString());
#if QT_CONFIG(tooltip)
        drawRoundBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\347\224\273\345\234\206", nullptr));
#endif // QT_CONFIG(tooltip)
        drawRoundBtn->setText(QString());
#if QT_CONFIG(tooltip)
        saveBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\344\277\235\345\255\230\346\210\252\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
        saveBtn->setText(QString());
#if QT_CONFIG(tooltip)
        cancelBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\351\200\200\345\207\272\346\210\252\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
        cancelBtn->setText(QString());
#if QT_CONFIG(tooltip)
        finishBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\345\256\214\346\210\220\346\210\252\345\233\276", nullptr));
#endif // QT_CONFIG(tooltip)
        finishBtn->setText(QString());
#if QT_CONFIG(tooltip)
        stayBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\344\277\235\347\225\231\345\234\250\346\241\214\351\235\242\344\270\212", nullptr));
#endif // QT_CONFIG(tooltip)
        stayBtn->setText(QString());
#if QT_CONFIG(tooltip)
        drawMarkLineBtn->setToolTip(QCoreApplication::translate("ControlWidget", "\350\256\260\345\217\267\347\254\224", nullptr));
#endif // QT_CONFIG(tooltip)
        drawMarkLineBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ControlWidget: public Ui_ControlWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLWIDGET_H
