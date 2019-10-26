#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString coinImg);
    int posX;//记录位置
    int posY;
    bool flag;//记录正反
    bool isWin=false;//记录是否胜利 -- 用于禁用按钮
    void changeFlag();//反转金币
    QTimer *timer1;
    QTimer *timer2;
    int min = 1;
    int max = 6;
    //是否正在执行动画标志
    bool isAnimation=false;
    //鼠标按下事件重写
    void mousePressEvent(QMouseEvent *e);

private:



signals:

public slots:
};

#endif // MYCOIN_H
