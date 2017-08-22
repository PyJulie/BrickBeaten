#include "page.h"
#include "ui_page.h"

#include <QPalette>
#include <QPainter>
#include <QColor>
#include <vector>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <windows.h>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <fstream>
#include <string>
#include <iostream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QFont>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
using std::vector;

Page::Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page)
{
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "sqlite1");
    db.setDatabaseName(".//qtDb.db");
    if(!db.open())
    {
       qDebug() << "无法建立数据库连接";

    }

    QSqlQuery query(db);


    //创建数据库表

    bool success=query.exec("create table rank1(name varchar primary key,score int)");
    if(success)
    {
        qDebug() << QObject::tr("数据库表创建成功！\n");
    }
    else
    {
        qDebug() << QObject::tr("数据库表创建失败！\n");
    }
    resize(300, 400);

    this->setAutoFillBackground(true);  //设置背景颜色
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(0, 0, 0));
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/start.jpg")));
    this->setPalette(palette);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeDo()));
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(timeStart()));
    connect(ui->menuButton, SIGNAL(clicked(bool)), this, SLOT(reSet()));
    connect(ui->nextButton, SIGNAL(clicked(bool)), this, SLOT(timeContinue()));
    connect(ui->rankButton,SIGNAL(clicked(bool)),this,SLOT(rankPage()));
    connect(ui->exitButton,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
}

Page::~Page()
{
    delete ui;
}



void Page::timeDo(){
    int state = control.moveBall();

    if(state == 1){ //没接住球
        timeEnd();
    }else if(state == 2){
        if(control.getRound() != ROUND_MAX)
            nextRound();
        else
            success();

    }
    //ui->label->setText(QString::number(ball->getAngle()));
}

void Page::rankPage(){
    ui->rankButton->hide();
    ui->startButton->hide();
    ui->exitButton->hide();
    ui->menuButton->show();
    ui->label_2->show();

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/rank.png")));
    this->setPalette(palette);
    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);

    std::string result;

    int ord = 0;
    query.exec("select * from rank1 order by score desc");
    while(query.next()){
        ord++;
        std::string temp=(QString::number(ord,10).toStdString()+"      "+query.value(0).toString().toStdString()+"        "+query.value(1).toString().toStdString()+"\n");
        result+=temp;
        qDebug()<<QString::fromStdString(result);
        qDebug()<<query.value(0)<<" "<<query.value(1)<<"\n";
    }
    QFont font ("Microsoft YaHei", 15, 50);
    ui->label_2->setFont(font);
    ui->label_2->setText(QString::fromStdString(result));

}

void Page::sqlSave(QString name,int score){

    QSqlDatabase db = QSqlDatabase::database("sqlite1"); //建立数据库连接
    QSqlQuery query(db);
    if(!db.open()){
        qDebug()<<"meidakai";
    }

    query.prepare("insert into rank1 values(:name,:score)");
    QSqlRecord rec = query.record();
    int no = rec.count();

    query.bindValue(":name",name.toStdString().c_str());
    query.bindValue(":score",score);
    bool success = query.exec();
    if(success){
        qDebug()<<"chengong";
    }
    else{
        qDebug()<<query.lastError();
    }
}

void Page::timeStart(){

    ui->startButton->hide();//按钮隐藏
    ui->exitButton->hide();
    ui->rankButton->hide();
    ui->rankButton->setEnabled(false);
    control.GameStart();
    control.showBall();//场景切换
    control.showSlider();
    control.showBrick();
    //control.setIsStart(true);//游戏开始

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/beijing.png")));
    this->setPalette(palette);

    this->setFocusPolicy(Qt::StrongFocus); //获得焦点
}

void Page::timeEnd(){
    timer->stop();

    control.hideBall();//场景切换
    control.hideSlider();
    control.hideBrick();

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/end.png")));
    this->setPalette(palette);

    ui->menuButton->show();
    ui->rankButton->setEnabled(true);
    saveRecord();
}

void Page::saveRecord(){
    int reduceNo;

    reduceNo = control.hasReduce;

    QDialog *temp_dialog = new QDialog(this);
    QLabel *label = new QLabel(temp_dialog);
    label->setText("大侠，你的分数："+QString::number(reduceNo,10)+",请留下您的姓名保存记录：");
    QLineEdit *line_edit = new QLineEdit(temp_dialog);
    QPushButton *ok_button = new QPushButton("保存",temp_dialog);
    QPushButton *cancel_button = new QPushButton("取消",temp_dialog);
    QVBoxLayout *layout= new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(line_edit);
    layout->addWidget(ok_button);
    layout->addWidget(cancel_button);
    temp_dialog->setLayout(layout);
    ////按钮事件
    connect(ok_button, SIGNAL(clicked()), temp_dialog, SLOT(accept()));
    connect(cancel_button, SIGNAL(clicked()), temp_dialog, SLOT(reject()));
    if(temp_dialog->exec() == QDialog::Accepted){
        sqlSave(line_edit->text(),reduceNo);
        return;

    }
    if(temp_dialog->exec() == QDialog::Rejected){
        return;
    }
}

void Page::reSet(){
    ui->menuButton->hide();
    ui->nextButton->hide();
    ui->rankButton->show();
    ui->startButton->show();
    ui->exitButton->show();
    ui->label_2->hide();
    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/start.jpg")));
    this->setPalette(palette);

    control.reSet();
    control.setRound(0);
}

void Page::timeContinue(){//继续游戏
    ui->menuButton->hide();
    ui->nextButton->hide();

    control.reSet();

    control.GameStart();
    control.showBall();//场景切换
    control.showSlider();
    control.showBrick();

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/beijing.png")));
    this->setPalette(palette);

    this->setFocusPolicy(Qt::StrongFocus); //获得焦点


}

void Page::nextRound(){
    timer->stop();

    control.hideBall();//场景切换
    control.hideSlider();
    control.hideBrick();

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/next.png")));
    this->setPalette(palette);

    ui->nextButton->show();
    ui->menuButton->show();
}

void Page::success(){
    timer->stop();

    control.hideBall();//场景切换
    control.hideSlider();
    control.hideBrick();

    QPalette palette;//切换背景图片
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/sucai/success.png")));
    this->setPalette(palette);

    ui->menuButton->show();
}

void Page::keyPressEvent(QKeyEvent *event){
        switch(event->key()){
            case Qt::Key_Left:
                control.moveSlider(Control::Left);
                break;
            case Qt::Key_Right:
                control.moveSlider(Control::Right);
                break;
            case Qt::Key_Space:
                timer->start(20);
                control.setIsStart(true);
                break;
\
    }
}

