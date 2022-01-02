#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef STICKYNOTE_H
#define STICKYNOTE_H

#include <QMainWindow>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class StickyNote; }
QT_END_NAMESPACE

class StickyNote : public QMainWindow
{
    Q_OBJECT

public:
    StickyNote(QWidget *parent = nullptr);
    ~StickyNote();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::StickyNote *ui;
    int padding;                    //边距
    bool moveEnable;                //可移动
    bool resizeEnable;              //可拉伸
    QWidget *widget;                //无边框窗体

    bool pressed;                   //鼠标按下
    bool pressedLeft;               //鼠标按下左侧
    bool pressedRight;              //鼠标按下右侧
    bool pressedTop;                //鼠标按下上侧
    bool pressedBottom;             //鼠标按下下侧
    bool pressedLeftTop;            //鼠标按下左上侧
    bool pressedRightTop;           //鼠标按下右上侧
    bool pressedLeftBottom;         //鼠标按下左下侧
    bool pressedRightBottom;        //鼠标按下右下侧

    int rectX, rectY, rectW, rectH; //窗体坐标+宽高
    QPoint lastPos;                 //鼠标按下处坐标

    QRect rectLeft;                 //左侧区域
    QRect rectRight;                //右侧区域
    QRect rectTop;                  //上侧区域
    QRect rectBottom;               //下侧区域
    QRect rectLeftTop;              //左上侧区域
    QRect rectRightTop;             //右上侧区域
    QRect rectLeftBottom;           //左下侧区域
    QRect rectRightBottom;          //右下侧区域

    QIcon iconAddBtn;
    QIcon iconTopBtn;
    QIcon iconEditUnlockBtn;
    QIcon iconEditLockBtn;
    QIcon iconShrinkBtn;
    QIcon iconExpandBtn;
    QIcon iconSettingBtn;
    QIcon iconDeleteBtn;
    bool  isTop;
    bool  isEdit;
    bool  isMin;


public Q_SLOTS:
    //设置边距
    void setPadding(int padding);
    //设置是否可拖动+拉伸
    void setMoveEnable(bool moveEnable);
    void setResizeEnable(bool resizeEnable);

    //设置要无边框的窗体
    void setWidget(QWidget *widget);

private slots:
    void on_addBtn_clicked();
    void on_topBtn_clicked();
    void on_editBtn_clicked();
    void on_minBtn_clicked();
    void on_settingBtn_clicked();
    void on_deleteBtn_clicked();
};
#endif // STICKYNOTE_H
