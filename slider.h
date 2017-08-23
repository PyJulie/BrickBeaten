#ifndef SLIDER_H
#define SLIDER_H
#include "rect.h"
class Slider : public rect
{
public:
    Slider(int posX, int posY, QWidget* parent); //传的是左上角的坐标
    ~Slider();
};

#endif // SLIDER_H
