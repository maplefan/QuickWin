#include "snappit.h"
#include <QFileDialog>
#include <QScreen>
#include <QMouseEvent>
#include <QBitmap>
#include <QComboBox>
#include "QTranslator"
#include <qt_windows.h>

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#define SHOWWINDOWTOP \
::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);\
::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);\
this->show();\
this->activateWindow();


snappit::snappit(QWidget *parent)
    : QWidget(), m_translator(nullptr)
{
    ui.setupUi(this);
    connect(ui.pushButton_open,     &QPushButton::clicked, this, &snappit::openImage);
    connect(ui.pushButton_shortcut, &QPushButton::clicked, this, &snappit::screenShotCut);
}

snappit::~snappit()
{
	for(int i = 0; i < _arr_imgView.size(); i++)
	{
		ImageView *imgView = _arr_imgView[i];
		if(imgView != NULL)
		{
			imgView->close();
			delete imgView;
			imgView = NULL;
		}
	}
}

void snappit::openImage()
{
	QString img_path = QFileDialog::getOpenFileName(this, tr("Choose Image"), _file_path, "Image files (*.bmp *.jpg *.png);;All files (*.*)");
	if(!img_path.isEmpty())
	{
		QFileInfo file(img_path);
		_file_path = file.absolutePath();
		ImageView *imgView = new ImageView();
		imgView->setImage(img_path);
		imgView->show();
		_arr_imgView.push_back(imgView);
	}
}

void snappit::screenShotCut()
{
	QScreen *screen = QGuiApplication::primaryScreen();
	QPixmap fullPixmap = screen->grabWindow(0);
    ScreenView *screenView = new ScreenView();
    screenView->setBackGroundPixmap(fullPixmap);  //传递全屏背景图片
    screenView->show();
}

void snappit::hideEvent(QHideEvent *event)
{
	{
        this->hide();
		event->ignore();
	}
}

void snappit::closeEvent(QCloseEvent *event)
{
	{
        this->hide(); //隐藏窗口
        event->ignore(); //忽略事件
	}
}
