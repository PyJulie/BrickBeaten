# 简易打砖块游戏
## 核心功能及设计介绍
### 1.control类
  负责所有逻辑部分的管理，包括最基本的界面变换（游戏开始、游戏结束、下一关卡等）、所有控件的初始化（初始位置、状态等）、小球的移动处理、小球与墙的碰撞、小球与砖块的碰撞、小球与托盘的碰撞的一些处理。
  小球移动在控制类中的处理方法：</br>
  <div align="center">
![image](https://github.com/PyJulie/ImageUsed/blob/master/BrickBeaten/1.jpg)
  </div>
  </br>垂直方向的移动距离=速度*sin(angle);
  水平方向的移动距离=速度*cos(angle);
  再结合小球移动前的位置,即可判断小球移动后的位置，再利用paintEvent()进行重绘。
  小球在碰撞中的处理方法：</br>
  <div align="center>
![image](https://github.com/PyJulie/ImageUsed/blob/master/BrickBeaten/2.jpg)
  </div>
   </br>由于在Qt中，所有的控件都有自己的一个绝对位置，这个位置是相比于界面左上角为起点而言的。假设小球的位置为(x,y)，半径为r，再加上利用angle来确定小球是移动的方向，若向右移，只需判断(x+r,y)与(x,y-r)与砖块下方和左方坐标的大小即可，反之亦然。总的来说，就是根据小球的坐标来判断接下来是否会发生碰撞，而获取角度则可减少次碰撞计算。
### 2. Rect类
  所有可移动的控件（砖块、小球、滑块）的父类，其包括最基本的位置信息：左上角及右下角的坐标（可用来判断碰撞），长宽。由于需要在Control类中操控，因此被设为其友元类。
### 3.Ball、Slider、Brick类
  小球类，继承于Rect类，除了父类继承下来的成员变量及函数，还有发射的角度，默认为45°。滑块类，继承于Rect类。砖块类，继承于Rect类。
### 4.Page类
  界面类，整合所有类，具体功能包括界面的切换，数据库的操作，整体美工的设计。
  界面切换的处理方法：
```C++
    ui->setupUi(this);
    ui->menuButton->hide();//隐藏返回菜单按钮
    ui->nextButton->hide();
    ui->label_2->hide();

    ball = new Ball(145, 375, this);  //球生成
    slider = new Slider(130, 390, this); //滑块生成
    brick = new Brick*[BRICK_MAX];
    player = new QMediaPlayer(this);
    QMediaPlaylist *qpl = new QMediaPlaylist();
    qpl->addMedia(QUrl::fromLocalFile("./1.mp3"));
    player->setPlaylist(qpl);
    player->play();
    for(size_t ix= 0; ix != BRICK_MAX; ++ix){ //所有砖块初始化
        brick[ix] = new Brick(this);
    }


    control.setBall(ball);
    control.setSlider(slider);
    control.setBrick(brick);
```
  首先在构造函数里就初始化好所有的控件，包括按钮，以及游戏中的砖块等，然后根据不同的界面需求选择隐藏哪些控件。
  再例如游戏结束时，直接切换背景图片，然后显示相应的按钮：
```C++
    timer->stop();

    control.hideBall();//场景切换
    control.hideSlider();
    control.hideBrick();

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/end.png")));
    this->setPalette(palette);

    ui->menuButton->show();
    ui->rankButton->setEnabled(true);
```
