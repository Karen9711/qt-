#include "playscene.h"
#include"dataconfig.h"
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
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            gameArray[i][j] =  conf.mData[m_level][i][j];
        }
    }

    //创建金币的背景图片
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
            coin->posX = i;
            coin->posY = j;
            coin->flag = gameArray[i][j];
            coin->setParent(this);
            coin->move((this->width()-cell->width()*4)/2+j*77,this->height()*0.3+i*77);
            connect(coin,&QPushButton::clicked,this,[=](){
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j]==1 ? 0 : 1;//同步二维数组得数据

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



