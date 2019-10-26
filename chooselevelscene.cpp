#include "chooselevelscene.h"
#include<QTimer>
#include<QLabel>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //初始化
    this->setWindowTitle(QString::fromLocal8Bit("金币翻转"));//设置title
    this->setWindowIcon(QIcon(":/pics/goldCoin1.png"));//设置title icon
    this->setFixedSize(480,870);//设置固定大小 -- 这里的大小可以设定成宏变量或者常量值

    //设置菜单栏等
    QMenuBar *menu = menuBar();
    this->setMenuBar(menu);
    //创建开始菜单项
    QMenu *startMenu = menu->addMenu(QString::fromLocal8Bit("开始"));
    //创建开始菜单项的下拉菜单选项
    QAction *quitAction = startMenu->addAction(QString::fromLocal8Bit("退出"));
    //设置退出action 的trigger动作 -- 退出窗口
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });
//    初始化游戏场景指针
    playScene = NULL; //因为每次新点击一个游戏场景创建新的窗口

    //添加返回按钮
    MyButton *backBtn = new MyButton(0.8,":/pics/backBtn2.png",":/pics/backBtn.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击返回按钮返回主界面
    connect(backBtn,&MyButton::clicked,this,[=](){
//       qDebug()<<QString::fromLocal8Bit("返回")<<endl;
        //发送自定义信号
        //避免切换太快延时发射
        QTimer::singleShot(200,this,[=](){
            emit chooseSceneBack();//在主场景中捕获
        });
    });

    //设置选择关卡按钮
    for(int i=0;i<20;i++)
    {
        int row = i/4;
        int column = i-row*4;
        MyButton *levelBtn = new MyButton(0.5,":/pics/levelIcon.png");
        connect(levelBtn,&MyButton::clicked,[=](){
            //进入具体的游戏场景
            //传入游戏的等级
            playScene = new PlayScene(i);
            this->hide();
            playScene->setGeometry(this->geometry());
            playScene->show();
            connect(playScene,&PlayScene::playSceneBack,[=](){
//                设置选择场景关卡的位置

                this->setGeometry(playScene->geometry());
                playScene->close();
                delete playScene;
                playScene = NULL;
                this->show();
            });
        });
        //监听游戏场景发出的信号

        levelBtn->setParent(this);
        levelBtn->move((this->width()-levelBtn->width()*4)/2+column*100,this->height()*0.2+row*100);
        //使用标签来显示关卡数字
        QLabel *label = new QLabel(this);
        label->setFixedSize(levelBtn->width(),levelBtn->height());
        label->setText(QString::number(i+1));//数字--QString
        label->setAlignment(Qt::AlignCenter);
        label->move((this->width()-levelBtn->width()*4)/2+column*100,this->height()*0.2+row*100);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}


//重写paintEvent
void ChooseLevelScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/pics/background.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,480,870,pix);
    //绘制标题
    pix.load(":/pics/title.png");
    painter.drawPixmap(0,0,pix);
}
