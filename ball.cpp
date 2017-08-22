#include "ball.h"

Ball::Ball(int posX, int posY, QWidget* parent){
    width = 15;
    length = 15;
    begin = QPoint(posX, posY);  //左上角
    end = QPoint(posX+width, posY+length);  //右下角
    size = QRect(begin, end);  //球的大小矩形
    angle = 45;      //初始角度


    label = new QLabel("球", parent);
    label->resize(width, length);  //球重设
    label->move(posX, posY);
    label->setPixmap(QPixmap(":/sucai/ball.png"));
    label->hide();

}

Ball::~Ball(){
    delete label;
}

int Ball::getAngle(){
    return angle;
}

