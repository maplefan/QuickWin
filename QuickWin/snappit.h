#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef SNAPPIT_H
#define SNAPPIT_H

#include <QWidget>
#include "ui_snappit.h"
#include "imageview.h"
#include "screenview.h"
#include <QSystemTrayIcon>
#include "QMenu"

class snappit : public QWidget
{
    Q_OBJECT

public:
    snappit(QWidget *parent = 0);
	~snappit();

public:
	void openImage();
	void screenShotCut();
	void switchLanguage(const QString &text);

protected:
    void hideEvent(QHideEvent *event)     Q_DECL_OVERRIDE;
    void closeEvent(QCloseEvent *event)	  Q_DECL_OVERRIDE;

private:
    Ui::snappit ui;
	std::vector<ImageView *> _arr_imgView;
	QString _file_path;
	QAction *m_prefer;
	QAction *m_quit;
    QTranslator *m_translator;
};

#endif // SNAPPIT_H
