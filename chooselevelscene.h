#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include<QPainter>
#include<QPaintEvent>
#include<QMenuBar>
#include<QPixmap>
#include"mybutton.h"
#include"playscene.h"
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;

private:
    //维护游戏场景的指针
    PlayScene *playScene;
signals:
    void chooseSceneBack();

public slots:
};

#endif // CHOOSELEVELSCENE_H
