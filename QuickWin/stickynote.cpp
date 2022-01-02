#include "stickynote.h"
#include "ui_stickynote.h"
#include <QDebug>
StickyNote::StickyNote(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StickyNote)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/tray.ico"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->ui->textEdit->setMinimumSize(250 , 55);
    this->ui->textEdit->setMaximumSize(800-30 , 800-45);
    this->ui->textEdit->setGeometry( 15 , 45 , this->ui->textEdit->width() , this->ui->textEdit->height() - 20);
    padding = 8;
    moveEnable = true;
    resizeEnable = true;
    widget = 0;
    isTop = true;
    isEdit = true;
    isMin = false;
    pressed = false;
    pressedLeft = false;
    pressedRight = false;
    pressedTop = false;
    pressedBottom = false;
    pressedLeftTop = false;
    pressedRightTop = false;
    pressedLeftBottom = false;
    pressedRightBottom = false;

    //如果父类是窗体则直接设置
    if (parent->isWidgetType()) {
        setWidget((QWidget *)parent);
    }

    //设置无边框
    this->setWindowFlags(Qt::FramelessWindowHint);

    this->ui->textEdit->setStyleSheet(
    //设置滚动条
    "QScrollBar:vertical"
    "{"
    "background:#F0F8FF;"
    "}"
     );

    this->ui->lineEdit->setStyleSheet("QLineEdit{border-width:0;border-style:outset;background:#F0F8FF}");
    this->ui->lineEdit->setAlignment(Qt::AlignHCenter);
    this->ui->titleLabel->setAlignment(Qt::AlignHCenter);
    //设置字体和颜色
    QFont font = QFont("Microsoft YaHei",16,2);
    this->ui->textEdit->setFont(font);
    this->ui->textEdit->setTextColor(Qt::black);
    this->ui->lineEdit->setFont(font);
    this->ui->titleLabel->setFont(font);

    //设置编辑框背景颜色
    QPalette palEdit = ui->textEdit->palette();
    palEdit.setBrush(QPalette::Base, QColor(240 , 248 , 255));
    this->ui->textEdit->setPalette(palEdit);

    QPalette palTitle = ui->lineEdit->palette();
    palTitle.setBrush(QPalette::Base, QColor(240 , 248 , 255));
    this->ui->lineEdit->setPalette(palTitle);

    iconAddBtn = QIcon(":images/addBtn.png");
    iconTopBtn = QIcon(":images/topBtn.png");
    iconEditUnlockBtn = QIcon(":images/unlockBtn.png");
    iconEditLockBtn = QIcon(":images/lockBtn.png");
    iconShrinkBtn = QIcon(":images/shrinkBtn.png");
    iconExpandBtn = QIcon(":images/expandBtn.png");
    iconSettingBtn = QIcon(":images/settingBtn.png");
    iconDeleteBtn = QIcon(":images/deleteBtn.png");

    this->ui->addBtn->setIcon(iconAddBtn);
    this->ui->topBtn->setIcon(iconTopBtn);
    this->ui->editBtn->setIcon(iconEditUnlockBtn);
    this->ui->minBtn->setIcon(iconShrinkBtn);
    this->ui->settingBtn->setIcon(iconSettingBtn);
    this->ui->deleteBtn->setIcon(iconDeleteBtn);

    this->ui->addBtn->setFlat(true);
    this->ui->topBtn->setFlat(true);
    this->ui->editBtn->setFlat(true);
    this->ui->minBtn->setFlat(true);
    this->ui->settingBtn->setFlat(true);
    this->ui->deleteBtn->setFlat(true);

    this->ui->addBtn->setIconSize(QSize(36,36));
    this->ui->topBtn->setIconSize(QSize(36,36));
    this->ui->editBtn->setIconSize(QSize(36,36));
    this->ui->minBtn->setIconSize(QSize(36,36));
    this->ui->settingBtn->setIconSize(QSize(36,36));
    this->ui->deleteBtn->setIconSize(QSize(36,36));

    this->ui->titleLabel->installEventFilter(this);
    this->ui->lineEdit->installEventFilter(this);
}

StickyNote::~StickyNote()
{
    delete ui;
}

bool StickyNote::eventFilter(QObject *watched, QEvent *event)
{
    if (widget != 0 && watched == widget) {
        if (event->type() == QEvent::Resize) {
            //重新计算八个描点的区域,描点区域的作用还有就是计算鼠标坐标是否在某一个区域内
            int width = widget->width();
            int height = widget->height();

            //左侧描点区域
            rectLeft = QRect(0, padding, padding, height - padding * 2);
            //上侧描点区域
            rectTop = QRect(padding, 0, width - padding * 2, padding);
            //右侧描点区域
            rectRight = QRect(width - padding, padding, padding, height - padding * 2);
            //下侧描点区域
            rectBottom = QRect(padding, height - padding, width - padding * 2, padding);

            //左上角描点区域
            rectLeftTop = QRect(0, 0, padding, padding);
            //右上角描点区域
            rectRightTop = QRect(width - padding, 0, padding, padding);
            //左下角描点区域
            rectLeftBottom = QRect(0, height - padding, padding, padding);
            //右下角描点区域
            rectRightBottom = QRect(width - padding, height - padding, padding, padding);
        } else if (event->type() == QEvent::HoverMove) {
            //设置对应鼠标形状,这个必须放在这里而不是下面,因为可以在鼠标没有按下的时候识别
            if(isEdit){
                return false;
            }
            QHoverEvent *hoverEvent = (QHoverEvent *)event;
            QPoint point = hoverEvent->pos();
            if (resizeEnable) {
                if (rectLeft.contains(point)) {
                    widget->setCursor(Qt::SizeHorCursor);
                } else if (rectRight.contains(point)) {
                    widget->setCursor(Qt::SizeHorCursor);
                } else if (rectTop.contains(point)) {
                    widget->setCursor(Qt::SizeVerCursor);
                } else if (rectBottom.contains(point)) {
                    widget->setCursor(Qt::SizeVerCursor);
                } else if (rectLeftTop.contains(point)) {
                    widget->setCursor(Qt::SizeFDiagCursor);
                } else if (rectRightTop.contains(point)) {
                    widget->setCursor(Qt::SizeBDiagCursor);
                } else if (rectLeftBottom.contains(point)) {
                    widget->setCursor(Qt::SizeBDiagCursor);
                } else if (rectRightBottom.contains(point)) {
                    widget->setCursor(Qt::SizeFDiagCursor);
                } else {
                    widget->setCursor(Qt::ArrowCursor);
                }
            }

            //根据当前鼠标位置,计算XY轴移动了多少
            int offsetX = point.x() - lastPos.x();
            int offsetY = point.y() - lastPos.y();

            //根据按下处的位置判断是否是移动控件还是拉伸控件
            if (moveEnable) {
                if (pressed) {
                    widget->move(widget->x() + offsetX, widget->y() + offsetY);
                }
            }

            if (resizeEnable) {
                if (pressedLeft) {
                    int resizeW = widget->width() - offsetX;
                    if (widget->minimumWidth() <= resizeW) {
                        widget->setGeometry(widget->x() + offsetX, rectY, resizeW, rectH);
                        this->ui->textEdit->setGeometry(15,45, resizeW - 30  , rectH - 65 - 20);
                        this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                        this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                        this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                        int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                        int minBtnLeft = this->ui->minBtn->x();
                        if(minBtnLeft - 5 >= editBtnRight)
                        {
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        }
                        else{
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        }
                    }
                } else if (pressedRight) {
                    widget->setGeometry(rectX, rectY, rectW + offsetX, rectH);
                    this->ui->textEdit->setGeometry(15,45, rectW + offsetX - 30 , rectH - 65 - 20 );
                    this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                    this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                    this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                    int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                    int minBtnLeft = this->ui->minBtn->x();
                    if(minBtnLeft - 5 >= editBtnRight)
                    {
                        this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                    }
                    else{
                        this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                    }
                } else if (pressedTop) {
                    int resizeH = widget->height() - offsetY;
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(rectX, widget->y() + offsetY, rectW, resizeH);
                        this->ui->textEdit->setGeometry(15,45, rectW - 30 , resizeH - 65 - 20 );
                    }
                } else if (pressedBottom) {
                    widget->setGeometry(rectX, rectY, rectW, rectH + offsetY);
                    this->ui->textEdit->setGeometry(15,45, rectW - 30 , rectH + offsetY - 65 - 20 );
                } else if (pressedLeftTop) {
                    int resizeW = widget->width() - offsetX;
                    int resizeH = widget->height() - offsetY;
                    if (widget->minimumWidth() <= resizeW) {
                        widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
                        this->ui->textEdit->setGeometry(15,45, resizeW , resizeH - 65 - 20 );
                        this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                        this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                        this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                        int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                        int minBtnLeft = this->ui->minBtn->x();
                        if(minBtnLeft - 5 >= editBtnRight)
                        {
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        }
                        else{
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        }
                    }
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
                        this->ui->textEdit->setGeometry(15,45, resizeW - 30 , resizeH - 65 - 20);
                        this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                        this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                        this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                        int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                        int minBtnLeft = this->ui->minBtn->x();
                        if(minBtnLeft - 5 >= editBtnRight)
                        {
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        }
                        else{
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        }
                    }
                } else if (pressedRightTop) {
                    int resizeW = rectW + offsetX;
                    int resizeH = widget->height() - offsetY;
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(widget->x(), widget->y() + offsetY, resizeW, resizeH);
                        this->ui->textEdit->setGeometry(15,45, resizeW - 30 , resizeH - 65 - 20 );
                        this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                        this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                        this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                        int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                        int minBtnLeft = this->ui->minBtn->x();
                        if(minBtnLeft - 5 >= editBtnRight)
                        {
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        }
                        else{
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        }
                    }
                } else if (pressedLeftBottom) {
                    int resizeW = widget->width() - offsetX;
                    int resizeH = rectH + offsetY;
                    if (widget->minimumWidth() <= resizeW) {
                        widget->setGeometry(widget->x() + offsetX, widget->y(), resizeW, resizeH);
                        this->ui->textEdit->setGeometry(15,45, resizeW - 30 , resizeH - 65 - 20 );
                        this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                        this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                        this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                        int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                        int minBtnLeft = this->ui->minBtn->x();
                        if(minBtnLeft - 5 >= editBtnRight)
                        {
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        }
                        else{
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        }
                    }
                    if (widget->minimumHeight() <= resizeH) {
                        widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
                        this->ui->textEdit->setGeometry(15,45, resizeW - 30 , resizeH - 65 - 20 );
                        this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                        this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                        this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                        int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                        int minBtnLeft = this->ui->minBtn->x();
                        if(minBtnLeft - 5 >= editBtnRight)
                        {
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        }
                        else{
                            this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                            this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        }
                    }
                } else if (pressedRightBottom) {
                    int resizeW = rectW + offsetX;
                    int resizeH = rectH + offsetY;
                    widget->setGeometry(widget->x(), widget->y(), resizeW, resizeH);
                    this->ui->textEdit->setGeometry(15,45, resizeW - 30 , resizeH - 65 - 20 );
                    this->ui->minBtn->setGeometry(widget->width() - 3*41 , 3 , 36 , 36);
                    this->ui->settingBtn->setGeometry(widget->width() - 2*41 , 3 , 36 , 36);
                    this->ui->deleteBtn->setGeometry(widget->width() - 1*41 , 3 , 36 , 36);
                    int editBtnRight = this->ui->editBtn->x() + this->ui->editBtn->width();
                    int minBtnLeft = this->ui->minBtn->x();
                    if(minBtnLeft - 5 >= editBtnRight)
                    {
                        this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                        this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , minBtnLeft - editBtnRight - 10 , 36);
                    }
                    else{
                        this->ui->lineEdit->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                        this->ui->titleLabel->setGeometry(editBtnRight + 5 , 3 , 0 , 36);
                    }
                }
            }
        } else if (event->type() == QEvent::MouseButtonPress) {
            //记住当前控件坐标和宽高以及鼠标按下的坐标
            QMouseEvent *mouseEvent = (QMouseEvent *)event;
            rectX = widget->x();
            rectY = widget->y();
            rectW = widget->width();
            rectH = widget->height();
            lastPos = mouseEvent->pos();

            //判断按下的手柄的区域位置
            if (rectLeft.contains(lastPos)) {
                pressedLeft = true;
            } else if (rectRight.contains(lastPos)) {
                pressedRight = true;
            } else if (rectTop.contains(lastPos)) {
                pressedTop = true;
            } else if (rectBottom.contains(lastPos)) {
                pressedBottom = true;
            } else if (rectLeftTop.contains(lastPos)) {
                pressedLeftTop = true;
            } else if (rectRightTop.contains(lastPos)) {
                pressedRightTop = true;
            } else if (rectLeftBottom.contains(lastPos)) {
                pressedLeftBottom = true;
            } else if (rectRightBottom.contains(lastPos)) {
                pressedRightBottom = true;
            } else {
                pressed = true;
            }
        } else if (event->type() == QEvent::MouseMove) {
            //改成用HoverMove识别
        } else if (event->type() == QEvent::MouseButtonRelease) {
            //恢复所有
            pressed = false;
            pressedLeft = false;
            pressedRight = false;
            pressedTop = false;
            pressedBottom = false;
            pressedLeftTop = false;
            pressedRightTop = false;
            pressedLeftBottom = false;
            pressedRightBottom = false;
            widget->setCursor(Qt::ArrowCursor);
        }
    }
    else if( watched == this->ui->titleLabel )
    {
        if (event->type() == QEvent::MouseButtonDblClick)
        {
            this->ui->lineEdit->setText(this->ui->titleLabel->text());
            this->ui->lineEdit->setVisible(true);
            this->ui->titleLabel->setVisible(false);
            this->ui->lineEdit->setFocus();
        }
    }
    else if( watched == this->ui->lineEdit )
    {
        if (event->type() == QEvent::KeyPress)
        {
             QKeyEvent* keyevt = static_cast<QKeyEvent*>(event);
             if ((keyevt->key() == Qt::Key_Return) ||
               (keyevt->key() == Qt::Key_Escape) ||
               (keyevt->key() == Qt::Key_Enter))   // Qt::Key_Return是大键盘的回车键 Qt::Key_Enter是小键盘的回车键
               {
                   this->ui->titleLabel->setText(this->ui->lineEdit->text());
               }
        }
        else if (event->type() == QEvent::FocusOut)
        {
              this->ui->titleLabel->setText(this->ui->lineEdit->text());
              this->ui->lineEdit->setVisible(false);
              this->ui->titleLabel->setVisible(true);
        }
    }

    return QObject::eventFilter(watched, event);
}

void StickyNote::setPadding(int padding)
{
    this->padding = padding;
}

void StickyNote::setMoveEnable(bool moveEnable)
{
    this->moveEnable = moveEnable;
}

void StickyNote::setResizeEnable(bool resizeEnable)
{
    this->resizeEnable = resizeEnable;
}

void StickyNote::setWidget(QWidget *widget)
{
    if (this->widget == 0) {
        this->widget = widget;
        //设置鼠标追踪为真
        this->widget->setMouseTracking(true);
        //绑定事件过滤器
        this->widget->installEventFilter(this);
        //设置悬停为真,必须设置这个,不然当父窗体里边还有子窗体全部遮挡了识别不到MouseMove,需要识别HoverMove
        this->widget->setAttribute(Qt::WA_Hover, true);
    }
}

void StickyNote::on_addBtn_clicked()
{
    QWidget *w = new QWidget;
    w->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    w->setMinimumSize(280, 45);
    w->setMaximumSize(800 , 800);
    w->resize(425, 425);
    //设置窗口背景颜色
    QPalette palWidget = w->palette();
    palWidget.setBrush(QPalette::Background, QColor(240 , 248 , 255));
    w->setPalette(palWidget);
    StickyNote *sn = new StickyNote(w);
    sn->setWidget(w);
    w->show();
    w->setGeometry(w->x()+20 , w->y()+20 , w->width() , w->height());
}

void StickyNote::on_topBtn_clicked()
{
    if(isTop)
    {
        isTop = false;
        this->parentWidget()->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnBottomHint);
        this->parentWidget()->show();
        qDebug()<<"bottom"<<endl;
    }
    else{
        isTop = true;
        this->parentWidget()->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
        this->parentWidget()->show();
        qDebug()<<"top"<<endl;
    }
}

void StickyNote::on_editBtn_clicked()
{
    if(isEdit)
    {
        isEdit = false;
        this->ui->editBtn->setIcon(iconEditLockBtn);
        this->ui->textEdit->setReadOnly(true);
        this->ui->lineEdit->setReadOnly(true);
    }
    else{
        isEdit = true;
        this->ui->editBtn->setIcon(iconEditUnlockBtn);
        this->ui->textEdit->setReadOnly(false);
        this->ui->lineEdit->setReadOnly(false);
    }
}

void StickyNote::on_minBtn_clicked()
{
    if(isMin)
    {
        isMin = false;
        this->ui->minBtn->setIcon(iconShrinkBtn);
        this->parentWidget()->setGeometry(this->parentWidget()->x() , this->parentWidget()->y() , this->parentWidget()->width() , 425);
    }
    else{
        isMin = true;
        this->ui->minBtn->setIcon(iconExpandBtn);
        this->parentWidget()->setGeometry(this->parentWidget()->x() , this->parentWidget()->y() , this->parentWidget()->width() , 45);
    }
}

void StickyNote::on_settingBtn_clicked()
{

}

void StickyNote::on_deleteBtn_clicked()
{
    this->close();
    this->parentWidget()->close();
}
