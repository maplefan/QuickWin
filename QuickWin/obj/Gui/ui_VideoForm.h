/********************************************************************************
** Form generated from reading UI file 'VideoForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOFORM_H
#define UI_VIDEOFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "Widget/ShowVideoWidget.h"
#include "Widget/VideoSlider.h"

QT_BEGIN_NAMESPACE

class Ui_VideoForm
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_container;
    QStackedWidget *stackedWidget;
    QWidget *page_open;
    QVBoxLayout *verticalLayout_6;
    QWidget *widget_showopen;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_open;
    QSpacerItem *horizontalSpacer_2;
    QWidget *page_audio;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QWidget *page_video;
    QVBoxLayout *verticalLayout_8;
    ShowVideoWidget *widget_videoPlayer;
    QWidget *widget_controller;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_open;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_play;
    QPushButton *pushButton_pause;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_stop;
    QSpacerItem *horizontalSpacer_6;
    VideoSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout;
    QLabel *label_currenttime;
    QLabel *label_2;
    QLabel *label_totaltime;
    QPushButton *pushButton_volume;
    QSlider *horizontalSlider_volume;
    QLabel *label_volume;

    void setupUi(QWidget *VideoForm)
    {
        if (VideoForm->objectName().isEmpty())
            VideoForm->setObjectName(QString::fromUtf8("VideoForm"));
        VideoForm->resize(1060, 695);
        verticalLayout = new QVBoxLayout(VideoForm);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_container = new QWidget(VideoForm);
        widget_container->setObjectName(QString::fromUtf8("widget_container"));
        widget_container->setStyleSheet(QString::fromUtf8("QWidget#widget_container\n"
"{\n"
"	background-color: rgb(22, 22, 22);\n"
"}\n"
""));
        stackedWidget = new QStackedWidget(widget_container);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(80, 40, 931, 381));
        page_open = new QWidget();
        page_open->setObjectName(QString::fromUtf8("page_open"));
        verticalLayout_6 = new QVBoxLayout(page_open);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_showopen = new QWidget(page_open);
        widget_showopen->setObjectName(QString::fromUtf8("widget_showopen"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_showopen->sizePolicy().hasHeightForWidth());
        widget_showopen->setSizePolicy(sizePolicy);
        widget_showopen->setStyleSheet(QString::fromUtf8("QWidget#widget_showopen\n"
"{\n"
"	\n"
"	background-color: rgba(60, 65, 68,100);\n"
"}"));
        verticalLayout_5 = new QVBoxLayout(widget_showopen);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        toolButton_open = new QToolButton(widget_showopen);
        toolButton_open->setObjectName(QString::fromUtf8("toolButton_open"));
        toolButton_open->setMinimumSize(QSize(160, 50));
        toolButton_open->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(toolButton_open);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_3);


        verticalLayout_6->addWidget(widget_showopen);

        stackedWidget->addWidget(page_open);
        page_audio = new QWidget();
        page_audio->setObjectName(QString::fromUtf8("page_audio"));
        verticalLayout_2 = new QVBoxLayout(page_audio);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(page_audio);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("image: url(:/images/audio.png);"));

        verticalLayout_2->addWidget(label);

        stackedWidget->addWidget(page_audio);
        page_video = new QWidget();
        page_video->setObjectName(QString::fromUtf8("page_video"));
        verticalLayout_8 = new QVBoxLayout(page_video);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        widget_videoPlayer = new ShowVideoWidget(page_video);
        widget_videoPlayer->setObjectName(QString::fromUtf8("widget_videoPlayer"));
        widget_videoPlayer->setEnabled(true);
        sizePolicy.setHeightForWidth(widget_videoPlayer->sizePolicy().hasHeightForWidth());
        widget_videoPlayer->setSizePolicy(sizePolicy);
        widget_videoPlayer->setMouseTracking(true);
        widget_videoPlayer->setStyleSheet(QString::fromUtf8("QWidget#widget_videoPlayer\n"
"{\n"
"	background-color: rgb(255, 55, 195);\n"
"}"));

        verticalLayout_8->addWidget(widget_videoPlayer);

        stackedWidget->addWidget(page_video);
        widget_controller = new QWidget(widget_container);
        widget_controller->setObjectName(QString::fromUtf8("widget_controller"));
        widget_controller->setGeometry(QRect(70, 480, 971, 60));
        widget_controller->setStyleSheet(QString::fromUtf8("QWidget#widget_controller\n"
"{\n"
"	background-color: rgba(60, 65, 68,160);\n"
"}"));
        verticalLayout_7 = new QVBoxLayout(widget_controller);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, -1, 0, -1);
        pushButton_open = new QPushButton(widget_controller);
        pushButton_open->setObjectName(QString::fromUtf8("pushButton_open"));
        pushButton_open->setMinimumSize(QSize(36, 36));
        pushButton_open->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_open->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"image: url(:/images/open_normal.png);\n"
"border-radius:0px; \n"
"} \n"
"QPushButton:hover{ \n"
"image: url(:/images/open_focus.png);\n"
"border-radius:0px; \n"
"} \n"
"QPushButton:pressed{ \n"
"image: url(:/images/open_normal.png);\n"
"border-radius:0px; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton_open);

        horizontalSpacer_3 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pushButton_play = new QPushButton(widget_controller);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        pushButton_play->setMinimumSize(QSize(36, 36));
        pushButton_play->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_play->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"image: url(:/images/start_normal.png);\n"
"border-radius:0px; \n"
"}  \n"
"QPushButton:hover{ \n"
"image: url(:/images/start_focus.png);\n"
"border-radius:0px; \n"
"} \n"
"QPushButton:pressed{ \n"
"image: url(:/images/start_normal.png);\n"
"border-radius:0px; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton_play);

        pushButton_pause = new QPushButton(widget_controller);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));
        pushButton_pause->setMinimumSize(QSize(36, 36));
        pushButton_pause->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_pause->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"image: url(:/images/pause_normal.png);\n"
"border-radius:0px; \n"
"} \n"
"QPushButton:hover{ \n"
"image: url(:/images/pause_focus.png);\n"
"border-radius:0px; \n"
"} \n"
"QPushButton:pressed{ \n"
"image: url(:/images/pause_normal.png);\n"
"border-radius:0px; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton_pause);

        horizontalSpacer_5 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        pushButton_stop = new QPushButton(widget_controller);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));
        pushButton_stop->setMinimumSize(QSize(36, 36));
        pushButton_stop->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_stop->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"image: url(:/images/stop_normal.png);\n"
"border-radius:0px; \n"
"}  \n"
"QPushButton:hover{ \n"
"image: url(:/images/stop_focus.png);\n"
"border-radius:0px; \n"
"} \n"
"QPushButton:pressed{ \n"
"image: url(:/images/stop_normal.png);\n"
"border-radius:0px; \n"
"}\n"
""));

        horizontalLayout_2->addWidget(pushButton_stop);

        horizontalSpacer_6 = new QSpacerItem(6, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        horizontalSlider = new VideoSlider(widget_controller);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setCursor(QCursor(Qt::PointingHandCursor));
        horizontalSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 0px solid #bbb;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background-color: #ff9900;\n"
"border-bottom-left-radius: 2px; \n"
"border-top-left-radius: 2px; \n"
"\n"
"border-radius: 2px; \n"
"margin-top:5px;\n"
"margin-bottom:5px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background-color: rgba(228, 228, 228, 50);v\n"
"border: 0px solid #777;\n"
"border-radius: 2px;\n"
"margin-top:5px;\n"
"margin-bottom:5px;\n"
"}\n"
"/*\n"
"QSlider::handle:horizontal {\n"
"background: rgb(255,153,102); \n"
"border: 1px solid rgb(255,153,102); \n"
"width: 14px;\n"
"height:10px;\n"
"border-radius: 7px;\n"
"margin-top:2px;\n"
"margin-bottom:2px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: rgb(255,128,6); \n"
"border: 1px solid rgba(102,102,102,102);\n"
"border-radius: 7px;\n"
"}*/\n"
"\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #bbb;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
""
                        "border-color: #999;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
"border: 1px solid #aaa;\n"
"border-radius: 2px;\n"
"}\n"
""));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setValue(0);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_currenttime = new QLabel(widget_controller);
        label_currenttime->setObjectName(QString::fromUtf8("label_currenttime"));
        label_currenttime->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:16px;\n"
"}\n"
""));

        horizontalLayout->addWidget(label_currenttime);

        label_2 = new QLabel(widget_controller);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:16px;\n"
"}\n"
""));

        horizontalLayout->addWidget(label_2);

        label_totaltime = new QLabel(widget_controller);
        label_totaltime->setObjectName(QString::fromUtf8("label_totaltime"));
        label_totaltime->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"font-family:\"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"font-size:16px;\n"
"}\n"
""));

        horizontalLayout->addWidget(label_totaltime);


        horizontalLayout_2->addLayout(horizontalLayout);

        pushButton_volume = new QPushButton(widget_controller);
        pushButton_volume->setObjectName(QString::fromUtf8("pushButton_volume"));
        pushButton_volume->setMinimumSize(QSize(36, 36));
        pushButton_volume->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_volume->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"image: url(:/images/volume_normal.png);\n"
"border-radius:0px; \n"
"padding:5px;\n"
"}  \n"
"QPushButton:hover{ \n"
"image: url(:/images/stop_focus.png);\n"
"border-radius:0px; \n"
"padding:3px;\n"
"} \n"
"QPushButton:!checked{ \n"
"image: url(:/images/volume_normal.png);\n"
"} \n"
"QPushButton:checked{ \n"
"image: url(:/images/volume_mute.png);\n"
"} \n"
"\n"
""));
        pushButton_volume->setCheckable(true);

        horizontalLayout_2->addWidget(pushButton_volume);

        horizontalSlider_volume = new QSlider(widget_controller);
        horizontalSlider_volume->setObjectName(QString::fromUtf8("horizontalSlider_volume"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalSlider_volume->sizePolicy().hasHeightForWidth());
        horizontalSlider_volume->setSizePolicy(sizePolicy1);
        horizontalSlider_volume->setMaximumSize(QSize(150, 16777215));
        horizontalSlider_volume->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 0px solid #bbb;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: rgb(235,97,0);\n"
"border-radius: 0px;\n"
"margin-top:8px;\n"
"margin-bottom:8px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: rgb(255,255, 255);\n"
"border: 0px solid #777;\n"
"border-radius: 2px;\n"
"margin-top:8px;\n"
"margin-bottom:8px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"background: rgb(255,153,102); \n"
"border: 1px solid rgb(255,153,102); \n"
"width: 8px;\n"
"height:8px;\n"
"border-radius: 2px;\n"
"margin-top:6px;\n"
"margin-bottom:6px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: rgb(255,128,6); \n"
"border: 1px solid rgba(102,102,102,102);\n"
"border-radius: 7px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: #bbb;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: #eee;\n"
"border-color: #999;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:disabled {\n"
"background: #eee;\n"
""
                        "border: 1px solid #aaa;\n"
"border-radius: 4px;\n"
"}\n"
"\n"
""));
        horizontalSlider_volume->setMaximum(100);
        horizontalSlider_volume->setSingleStep(0);
        horizontalSlider_volume->setPageStep(0);
        horizontalSlider_volume->setValue(100);
        horizontalSlider_volume->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_volume);

        label_volume = new QLabel(widget_controller);
        label_volume->setObjectName(QString::fromUtf8("label_volume"));
        label_volume->setMinimumSize(QSize(20, 0));
        label_volume->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-radius:0px;\n"
"	color: #F0F0F0;\n"
"	background-color:rgba(0,0,0,0);\n"
"	border-style:none;\n"
"font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"}\n"
""));
        label_volume->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_volume);


        verticalLayout_7->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(widget_container);


        retranslateUi(VideoForm);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VideoForm);
    } // setupUi

    void retranslateUi(QWidget *VideoForm)
    {
        VideoForm->setWindowTitle(QCoreApplication::translate("VideoForm", "Form", nullptr));
        toolButton_open->setText(QCoreApplication::translate("VideoForm", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        label->setText(QString());
        pushButton_open->setText(QString());
        pushButton_play->setText(QString());
        pushButton_pause->setText(QString());
        pushButton_stop->setText(QString());
        label_currenttime->setText(QCoreApplication::translate("VideoForm", "00:00:00", nullptr));
        label_2->setText(QCoreApplication::translate("VideoForm", "/", nullptr));
        label_totaltime->setText(QCoreApplication::translate("VideoForm", "00:00:00", nullptr));
        pushButton_volume->setText(QString());
        label_volume->setText(QCoreApplication::translate("VideoForm", "100", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VideoForm: public Ui_VideoForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOFORM_H
