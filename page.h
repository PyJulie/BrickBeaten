#ifndef PAGE_H
#define PAGE_H

#include <QWidget>
#include "ball.h"
#include "control.h"
#include <QTimer>
#include "slider.h"
#include <QKeyEvent>
#include <vector>
#include "brick.h"
#include <qlcdnumber.h>
#include <QtMultimedia/QMediaPlayer>

using std::vector;



namespace Ui {
class Page;
}

class Page : public QWidget
{
    Q_OBJECT

public:
    explicit Page(QWidget *parent = 0);
    ~Page();
    void nextRound();//下一局
    void success();//游戏通关
    void sqlSave(QString name,int score);
protected:
    void keyPressEvent(QKeyEvent *event);

    //void paintEvent(QPaintEvent *event);
private slots:
    void timeDo();  //游戏执行
    void timeStart(); //游戏开始
    void timeEnd();   //结束，game over
    void reSet();  //还原回游戏开始画面
    void timeContinue(); //下一关
    void saveRecord();
    void rankPage();

private:
    Ui::Page *ui;

    QTimer *timer;
    Ball *ball;
    Slider *slider;
    Brick** brick; //很多砖块
    Control control;

    QMediaPlayer *player;
    //vector<QRect> rect_vec;  //存障碍物
};

#endif // PAGE_H
