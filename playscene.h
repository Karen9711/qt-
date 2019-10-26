#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QPainter>
#include<QMenuBar>
#include<QTimer>
#include<QLabel>
#include"mybutton.h"
#include"mycoin.h"
#include"dataconfig.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level);
    //重写绘图事件
    void paintEvent(QPaintEvent *event) override;
    void flipCoin(MyCoin *coin);
    void initGameArray(DataConfig &conf);
    bool isSuccessful();
    void showGameArray();
private:
    //记录当前关卡号
    int m_level;
    //维护游戏二维数组
    int gameArray[4][4];
    //存放金币按钮的数组
    MyCoin *coinBtn[4][4];
signals:
    void playSceneBack();

public slots:
};

#endif // PLAYSCENE_H
