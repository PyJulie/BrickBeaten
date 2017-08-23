#ifndef CONTROL_H
#define CONTROL_H

#include "ball.h"
#include "slider.h"
#include "brick.h"
#include <vector>

#define BRICK_MAX 40
#define ROUND_MAX 2

using std::vector;

class Ball;
class Slider;
class Brick;




class Control
{
public:
    enum DIR{Up, Down, Left, Right};
    Control();
    void setIsStart(bool flag);
    void setIsFail(bool flag);
    void setBallAngle();
    bool getIsStart();
    void reSet();//还原游戏开始状态
    void setRound(int n);
    int getRound();
    int getLeftBrickSize();
    void GameStart();
   // void setVector(vector<QRect> &vec);
    void setBall(Ball* &ba);
    void setSlider(Slider* &sli);
    void setBrick(Brick** &bri);

    int moveBall();   //移动球 0移动成功 1失败 2继续
    void moveSlider(DIR dir);

    void showBall();
    void showSlider();
    void showBrick();

    void hideBall();
    void hideSlider();
    void hideBrick();
    int hasReduce;
private:
    int checkBall(QPoint beg, QPoint en, int &angl);   //碰撞检测, 左上 右下 与x轴左起的角度 小球所在的长方形

    bool checkSlider(QPoint beg, QPoint en);
    void modifyBrick(int num, int *x, int *y);//修改出场的砖块
private:
    bool isStart; //游戏开始 true 开始， false 没有
    bool isFail;
    vector<Brick*> briSize_vec;//砖块的尺寸容器
    Ball* ball;
    Slider* slider;
    Brick** brick;
    int brick_num;  //出现的砖块数量
    int round; //回合数



};


#endif // CONTROL_H
