#include "playscene.h"

PlayScene::PlayScene(int level)
{
    //保留本官关卡
    m_level = level;

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
            emit playSceneBack();//在选择关卡场景中中捕获
        });
    });

    //添加显示当前关卡
    QLabel *label = new QLabel(this);
    QString levelStr = QString("Level:%1").arg(m_level+1);
    QFont font;
    font.setPointSize(20);
    label->setFont(font);
    label->setText(levelStr);
    label->setGeometry(QRect(30,this->height()-50,160,50));

    //初始化当前游戏数组
    DataConfig conf;
    initGameArray(conf);

    //加载获胜图片
    QLabel *winLabel = new QLabel(this);
    QPixmap tmpPix;
    tmpPix.load("://pics/win.png");
    winLabel->setPixmap(tmpPix);
    winLabel->setFixedSize(tmpPix.width(),tmpPix.height());
    winLabel->move((this->width()-tmpPix.width())*0.5,-winLabel->height());

    //创建游戏区域
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //QLabel 显示背景图片
            QLabel *cell = new QLabel(this);
            cell->setGeometry(0,0,75,75);
            cell->setPixmap(QPixmap(":/pics/cellBackground.png"));
            cell->move((this->width()-cell->width()*4)/2+j*77,this->height()*0.3+i*77);

            //显示初始页面得金币 或银币
            QString coinName;
            if(gameArray[i][j]==0){
                //为0 -- 显示银币
                coinName = ":/pics/coin006.png";
            }
            else{
                //为1 -- 显示金币
                coinName = ":/pics/coin001.png";
            }
            MyCoin *coin = new MyCoin(coinName);
            //将金币放进金币二维数组中
            coinBtn[i][j] = coin;
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];
            coin->setParent(this);
            coin->move((this->width()-cell->width()*4)/2+j*77,this->height()*0.3+i*77);
            connect(coin,&QPushButton::clicked,this,[=](){
                //先禁用所有的按钮
                //禁用按钮
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<4;j++)
                    {
                        coinBtn[i][j]->isWin=true;
                    }
                }

                //翻转当前硬币
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j]==1 ? 0 : 1;//同步二维数组得数据
                //延时翻动周围的硬币
                QTimer::singleShot(200,this,[=](){
                    flipCoin(coin);
                    //翻转完所有的硬币后再解禁
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            coinBtn[i][j]->isWin=false;
                        }
                    }
                    //判断成功
                    bool result = isSuccessful();
                    if(result)
                    {
                        //禁用按钮
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        //弹出胜利的图片
                        QPropertyAnimation *animation = new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(800);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+winLabel->height()+100,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });
            });
        }

    }
}

void PlayScene::paintEvent(QPaintEvent *event)
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


 void PlayScene::flipCoin(MyCoin *coin)
 {

     //检测翻动右侧硬币
     //延时翻转 --
     //如果使用延时QTimer::singleshot会导致判断成功的时候出现问题
     //解决 -- 把成功检测放入延时中
     //延时写到函数外
     if(coin->posY+1<=3)
     {
         coinBtn[coin->posX][coin->posY+1]->changeFlag();
         gameArray[coin->posX][coin->posY+1] =  (gameArray[coin->posX][coin->posY+1]==1)?0:1 ;
     }
     //检测翻动左侧硬币
     if(coin->posY-1>=0)
     {
         coinBtn[coin->posX][coin->posY-1]->changeFlag();
         gameArray[coin->posX][coin->posY-1] = gameArray[coin->posX][coin->posY-1]==1?0:1;
     }
     //检测翻动下面的硬币
     if(coin->posX+1<=3)
     {
         coinBtn[coin->posX+1][coin->posY]->changeFlag();
         gameArray[coin->posX+1][coin->posY] = gameArray[coin->posX+1][coin->posY]==1 ? 0 : 1;
     }
     //检测翻动上面的硬币
     if(coin->posX-1>=0)
     {
         coinBtn[coin->posX-1][coin->posY]->changeFlag();
         gameArray[coin->posX-1][coin->posY] = gameArray[coin->posX-1][coin->posY]==1 ? 0 : 1;
     }
 }


void PlayScene::initGameArray(DataConfig &conf)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            gameArray[i][j] =  conf.mData[m_level][i][j];
        }
    }
}

bool PlayScene::isSuccessful()
{
    bool flag = true;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(coinBtn[i][j]->flag==false)
            {
                flag = false;
                break;
            }
        }
    }
    return flag;
}

void PlayScene::showGameArray()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            qDebug()<<coinBtn[i][j]->flag;

        }
        qDebug()<<endl;
    }
}
