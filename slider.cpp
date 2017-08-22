#include "slider.h"

Slider::Slider(int posX, int posY, QWidget* parent){
    width=40;
    length=10;

    begin = QPoint(posX, posY);  //左上角
    end = QPoint(posX+width, posY+length);  //右下角

    size = QRect(begin, end);  //slider的大小矩形


    label = new QLabel("sf", parent);
    label->resize(width, length);  //球重设
    label->move(posX, posY);
    label->setPixmap(QPixmap(":/sucai/slider.png"));
    label->hide();

}

Slider::~Slider(){
    delete label;
}
