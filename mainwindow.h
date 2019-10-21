#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QPainter>
#include"chooselevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //重写绘图事件函数绘制背景图
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    //维护一个选择关卡场景的指针
    ChooseLevelScene *chooseLevelScene;

};
#endif // MAINWINDOW_H
