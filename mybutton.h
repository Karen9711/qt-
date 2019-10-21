#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>
#include<QDebug>
#include<QPropertyAnimation>
#include<QMouseEvent>
class MyButton : public QPushButton
{
    Q_OBJECT
private:
    QString normalImgPath;
    QString pressImgPath;
    double m_size;
public:
//    explicit MyButton(QWidget *parent = nullptr);
    MyButton(double size,QString normalImg,QString pressImg="");
    //向上跳跃
    void zoomUp();
    //向下跳跃
    void zoomDown();
    //捕获鼠标事件进行按钮图片切换的效果
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

signals:

public slots:
};

#endif // MYBUTTON_H
