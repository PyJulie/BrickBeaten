#include "control.h"
#include <cmath>
#define len 5
#define pai 3.14
#define page_width 300
#define page_height 400
#define SPEED 1.5


Control::Control()
{
    hasReduce = 0;
    isStart = false;
    isFail = false;

    round = 0;
}

void Control::setIsStart(bool flag){
    isStart = flag;
}

void Control::setIsFail(bool flag){
    isFail = flag;
}

void Control::setBallAngle(){
    ball->angle = ball->angle+1;
    if(ball->angle > 170)
        ball->angle = 0;

}

bool Control::getIsStart(){
    return isStart;
}

void Control::reSet(){
    isStart = false;
    isFail = false;

    ball->begin = QPoint(145, 375);
    ball->end = QPoint(ball->begin.x()+ball->width, ball->begin.y()+ball->length);
    ball->size = QRect(ball->begin, ball->end);
    ball->angle = 45;
    ball->label->move(ball->begin);

    slider->begin = QPoint(130, 390);
    slider->end = QPoint(slider->begin.x()+ball->width, slider->begin.y()+ball->length);
    slider->size = QRect(slider->begin, slider->end);
    slider->label->move(slider->begin);

}

int Control::getLeftBrickSize(){
    return briSize_vec.size();
}

void Control::setRound(int n){
    round = n;
}

int Control::getRound(){
    return round;
}

void Control::GameStart(){
    int num[ROUND_MAX] = {2, 21};
    int brick_posX[2][21] = {{100, 150},
                             {0, 50, 100, 150, 200, 250,
                             25, 75, 125, 175, 225,
                             50, 100, 150, 200,
                             75, 125, 175,
                             100, 150,
                             125
                            }};
    int brick_posY[2][21] = {{20, 20},
                             {0, 0, 0, 0, 0, 0,
                              20, 20, 20, 20, 20,
                              40, 40, 40, 40,
                              60, 60, 60,
                              80, 80,
                              100}};

    modifyBrick(num[round], brick_posX[round], brick_posY[round]);

}


void Control::setBall(Ball* &ba){
    ball = ba;
}

void Control::setSlider(Slider* &sli){
    slider = sli;
}

void Control::setBrick(Brick** &bri){
    brick = bri;
}

int Control::moveBall(){
    double dt = ball->angle / 180.0 * pai;

    int dx = SPEED * len * cos(dt);
    int dy = SPEED * len * sin(dt);

    QPoint beg = QPoint(ball->begin.x()-dx, ball->begin.y()-dy);
    QPoint en = QPoint(ball->end.x()-dx, ball->end.y()-dy);
    //int temAngle = ball->angle;

    int state = checkBall(beg, en, ball->angle);
    if(state == 1){  //0 撞墙，1 继续前进 ，2 游戏结束，3 下一回合 4撞砖
        ball->begin = beg;
        ball->end = en;
        ball->size = QRect(ball->begin, ball->end);

        ball->label->move(ball->begin);

    }else if(state == 0){
        moveBall();
    }else if(state == 2)
        return 1;
    else if(state == 3){
        ++round;
        return 2;
    }
    return 0;
}

int Control::checkBall(QPoint beg, QPoint en, int &angl){

    bool inc;//true 增加 ，false 减少 increase

    if(beg.x() < 0 || beg.y() < 0 || en.x() > page_width || en.y() > page_height){
        if(angl >= 0 && angl < 90){ //第一方向
            if(beg.x() < 0)     //左
                inc = true;
            else if(beg.y() < 0)     //上
                inc = false;

        }else if(angl >= 90 && angl < 180){ //第二方向
            if(beg.y() < 0)      //上
                inc = true;
            else if(en.x() > page_width)  //右
                inc = false;

        }else if(angl >= 180 && angl < 270){
            if(en.x() > page_width)  //右
                inc = true;
            else if(en.y() > page_height){
                if(!ball->size.intersects((slider->size))){  //如果接到了，游戏继续，方向改变
                    return 2;
                }else
                    inc = false;
            }

        }else if(angl >= 270 && angl <360){
            if(en.y() > page_height)
                if(!ball->size.intersects((slider->size))){  //如果接到了，游戏继续，方向改变
                    return 2;//没接到 游戏结束
                }else
                    inc = true;
            else if(beg.x() < 0)
                inc = false;
        }

        if(inc)
            angl = (angl + 90) % 360;
        else
            angl = (angl - 90) % 360;

        if(angl < 0)
            angl += 360;

        return 0;//碰到墙
    }

    //砖块的碰撞判断
    for(vector<Brick*>::iterator it = briSize_vec.begin(); it != briSize_vec.end(); ){
        if(ball->size.intersects((*it)->size)){

            QRect interRect = ball->size.intersected((*it)->size);
            int left = interRect.x();
            int up = interRect.y();
            int right = left+interRect.width();
            int down = up+interRect.height();

            if(angl >= 0 && angl < 90){ //第一方向
                if(down == ((*it)->size.y()+(*it)->size.height()))     //下
                    inc = false;
                else     //上
                    inc = true;

            }else if(angl >= 90 && angl < 180){ //第二方向
                if(down == ((*it)->size.y()+(*it)->size.height()))      //下
                    inc = true;
                else  //左
                    inc = false;

            }else if(angl >= 180 && angl < 270){
                if(up == (*it)->size.y())  //上
                    inc = false;
                else
                    inc = true;


            }else if(angl >= 270 && angl <360){
                if(up == (*it)->size.y())
                    inc = true;
                else
                    inc = false;
            }

            if(inc)
                angl = (angl + 90) % 360;
            else
                angl = (angl - 90) % 360;

            if(angl < 0)
                angl += 360;

            (*it)->label->hide();
            it = briSize_vec.erase(it);//清除掉砖块
            hasReduce++;
            if(briSize_vec.empty())//砖块打完
                return 3;
            return 0;//或砖块
        }else
            ++it;
    }


    return 1;//没碰到，球前进

}


void Control::moveSlider(DIR dir){
    QPoint tem_beg, tem_end;
    switch(dir){
        case Left:{
            tem_beg = QPoint(slider->begin.x()-20, slider->begin.y());
            tem_end = QPoint(slider->end.x()-20, slider->end.y());
            if(!checkSlider(tem_beg, tem_end)){
                slider->begin = tem_beg;
                slider->end = tem_end;
            }else{
                slider->begin = QPoint(0, slider->begin.y());
                slider->end = QPoint(40, slider->end.y());
            }

            break;
            }
        case Right:{
            tem_beg = QPoint(slider->begin.x()+20, slider->begin.y());
            tem_end = QPoint(slider->end.x()+20, slider->end.y());
            if(!checkSlider(tem_beg, tem_end)){
                slider->begin = tem_beg;
                slider->end = tem_end;
            }else{
                slider->begin = QPoint(page_width-40, slider->begin.y());
                slider->end = QPoint(page_width, slider->end.y());
            }
            break;
        }
    }
    slider->size = QRect(slider->begin, slider->end);
    slider->label->move(slider->begin);
    if(!isStart){
        ball->begin.setX(slider->begin.x()+15);
        ball->end.setX(ball->begin.x()+15);
        ball->size = QRect(ball->begin, ball->end);

        ball->label->move(ball->begin);
    }
}

 bool Control::checkSlider(QPoint beg, QPoint en){
     if(beg.x() < 0)
         return true;
     else if(en.x() > page_width)
         return true;

     return false;
 }

 void Control::modifyBrick(int num, int *x, int *y){
    brick_num = num;
    briSize_vec.clear();

    for(int ix = 0; ix != brick_num; ++ix){
        brick[ix]->setBrickPos(x[ix], y[ix]);
        briSize_vec.push_back(brick[ix]);//将砖块size(QRect)收集起来，做与砖块的碰撞判断使用
    }
 }


 void Control::showBall(){
     ball->label->show();
 }

 void Control::showSlider(){
     slider->label->show();
 }

 void Control::showBrick(){
     for(int i = 0; i != brick_num; ++i)
         brick[i]->label->show();
 }

 void Control::hideBall(){
     ball->label->hide();
 }

 void Control::hideSlider(){
     slider->label->hide();
 }

 void Control::hideBrick(){
     for(int i = 0; i != brick_num; ++i)
         brick[i]->label->hide();
 }
