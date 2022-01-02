#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef IVIEW_H
#define IVIEW_H
class IView {
public:    virtual void setMouseOver(const int) =0;
};
#endif // IVIEW_H
