#ifndef BALL_H
#define BALL_H
#include "rect.h"
class Ball : public rect
{
public:
    Ball(int posX, int posY, QWidget* parent);
    ~Ball();
    int getAngle();
    int angle;
};

#endif // BALL_H
