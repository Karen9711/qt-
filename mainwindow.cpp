#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"mybutton.h"
#include<QTimer>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始画首页面窗口
    this->setWindowTitle(QString::fromLocal8Bit("金币翻转"));//设置title
    this->setWindowIcon(QIcon(":/pics/goldCoin1.png"));//设置title icon
    this->setFixedSize(480,870);//设置固定大小

    //初始化选择关卡窗口
    this->chooseLevelScene = new ChooseLevelScene; //此时就创建是由于选择关卡窗口的可复用，可以有长时间的存在周期

    //监听第二个场景发出的信号
    connect(chooseLevelScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        //延时返回
        chooseLevelScene->hide();
        this->show();
    });
    //点击开始-》退出 退出游戏
    connect(ui->actionquit,&QAction::triggered,this,[=](){
       this->close();
    });

    //开始按钮的创建
    MyButton *startBtn = new MyButton(0.6,":/pics/startIcon.png");
    startBtn->setParent(this);
    //将开始按钮放置到主界面中
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);
    //制作点击按钮时的弹跳效果
    connect(startBtn,&QPushButton::clicked,this,[=](){
        startBtn->zoomDown();
        startBtn->zoomUp();
//        qDebug()<<"push button"<<endl; //test

        //进入第二个场景

        //要进行延时 -- 按钮动画可以播放且场景切换比较复合用户期待
        QTimer::singleShot(350,this,[=](){
           //将自身窗口隐藏
            this->hide();
            //显示选择关卡窗口
            chooseLevelScene->show();
        });
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pics/background.jpg");
    //设置背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //设置标题图片
    pix.load(":/pics/title.png");
    painter.drawPixmap(-20,0,pix);


}
