#include "brick.h"


Brick::Brick(QWidget *parent){
    width = 50;
    length = 20;
    label = new QLabel(" ****** ", parent);
    label->resize(width, length);
    label->setPixmap(QPixmap(":/sucai/brick.png"));
    label->hide();

}


Brick::~Brick(){
    delete label;
}

void Brick::setBrickPos(int posX, int posY){
    begin = QPoint(posX, posY);
    end = QPoint(posX+width, posY+length);
    size = QRect(begin, end);

    label->move(posX, posY);

}
