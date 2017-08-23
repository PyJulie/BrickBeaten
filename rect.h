#ifndef RECT_H
#define RECT_H

#include <QPoint>
#include <QLabel>
#include <QRect>

class rect
{
    friend class Control;
public:
    rect();
    ~rect();
protected:
    QPoint begin; //左上角坐标
    QPoint end;   //右下角坐标
    QLabel *label;
    QRect size;   //球的区域
    int width;
    int length;
};

#endif // RECT_H
