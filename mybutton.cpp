#include "mybutton.h"

MyButton::MyButton(double size,QString normalImg,QString pressImg)
{
    //保存初始时和按下后的图片路径
    normalImgPath = normalImg;
    pressImgPath = pressImg;
    m_size = size;
    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    //如果路径错误
    if(!ret)
    {
        QString str = QString("%1 图片加载失败").arg(normalImgPath);
        qDebug()<<str<<endl;
        return;
    }

    //设置按钮大小
    this->setFixedSize(pix.width()*size,pix.height()*size);

    //设置不规则图片格式
    //利用css
    //
    this->setStyleSheet("QPushButton{border:0;background-color:transparent}");

    //设置图片
    this->setIcon(pix);

    //设置图片的大小
    this->setIconSize(QSize(pix.width()*size,pix.height()*size));
}

void MyButton::zoomUp()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyButton::zoomDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();
}

void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret)//如果图片加载失败
        {
            qDebug()<<"图片加载失败"<<endl;
            return;
        }
        this->setFixedSize(pix.width()*m_size,pix.height()*m_size);
        this->setStyleSheet("QPushButton{border:0;background-color:transparent}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*m_size,pix.height()*m_size));
    }
    QPushButton::mousePressEvent(e);
}

void MyButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(pressImgPath != "")
    {
        QPixmap pix;
        bool ret = pix.load(normalImgPath);
        if(!ret)//如果图片加载失败
        {
            qDebug()<<"图片加载失败"<<endl;
            return;
        }
        this->setFixedSize(pix.width()*m_size,pix.height()*m_size);
        this->setStyleSheet("QPushButton{border:0;background-color:transparent}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*m_size,pix.height()*m_size));
    }
    QPushButton::mouseReleaseEvent(e);
}
