#include "mycoin.h"
#include<QPixmap>
#include<QMessageBox>
#include<QTimer>
MyCoin::MyCoin(QString coinImg)
{
    //初始化得是金币图片
    QPixmap pix;
    bool ret = pix.load(coinImg);
    if(!ret)
    {
        QString str = QString(QString::fromLocal8Bit("图片加载失败"));
        QMessageBox::critical(this,QString::fromLocal8Bit("加载失败"),str);
        return;
    }
    //如果图片加载成功
    //设置不规则按钮
    this->setFixedSize(QSize(75,75));
    this->setIcon(pix);
    this->setStyleSheet("QPushButton{border:0}");
    this->setIconSize(QSize(75,75));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
//做定时器得信号和槽连接
    //定时器1 -- 正 -- 反
    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString(":/pics/coin00%1.png").arg(min++);
        pix.load(str);
        this->setFixedSize(QSize(75,75));
        this->setIcon(pix);
        this->setStyleSheet("QPushButton{border:0}");
        this->setIconSize(QSize(75,75));
        //如果显示到最后一张图片停止定时器
        if(min>max)
        {
            min = 1;//重置最小值
            isAnimation = false;
            timer1->stop();//停止定时器
        }
    });
    //定时器2 -- 反 -- 正
    connect(timer2,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str = QString(":/pics/coin00%1.png").arg(max--);
        pix.load(str);
        this->setFixedSize(QSize(75,75));
        this->setIcon(pix);
        this->setStyleSheet("QPushButton{border:0}");
        this->setIconSize(QSize(75,75));
        //如果显示到最后一张图片停止定时器
        if(max<min)
        {
            max = 6;//重置最小值
            isAnimation = false;
            timer2->stop();//停止定时器
        }
    });
}

void MyCoin::changeFlag()
{
    if(this->flag)
    {
        isAnimation = true;
         flag = false;
        timer1->start(30);

    }
    else
    {
        isAnimation = true;
        flag = true;
        timer2->start(30);

    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation || this->isWin)
    {
        //正在做动画
        //或已经胜利
        return;
    }
    //否则交给父类做默认处理
    QPushButton::mousePressEvent(e);
}

