#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include<QPainter>
#include<QMenuBar>
#include<QTimer>
#include<QLabel>
#include"mybutton.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level);
    void paintEvent(QPaintEvent *event) override;
private:
    int m_level;
signals:
    void playSceneBack();

public slots:
};

#endif // PLAYSCENE_H
