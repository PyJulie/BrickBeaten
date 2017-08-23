#ifndef BRICK_H
#define BRICK_H
#include "rect.h"
class Brick : public rect
{
public:
    Brick(QWidget* parent);
    ~Brick();
    void setBrickPos(int posX, int posY);
};

#endif // BRICK_H
