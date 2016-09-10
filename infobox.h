/*
 * 显示信息的控件
 */



#ifndef INFOBOX_H
#define INFOBOX_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QTime>

class infoBox : public QWidget
{
    Q_OBJECT

private:
    //格数
    int blockNum;
    //雷数
    int mineNum;
    //已标记的雷数
    int signedNum;
    //计时器状态
    int timeState;

    //计时器的开始时间
    QTime startTime;

    //显示信息的各种标签
    QLabel blockInfo;
    QLabel blockInfoNum;

    QLabel mineInfo;
    QLabel mineInfoNum;

    QLabel signedInfo;
    QLabel signedInfoNum;

    //重新开始游戏的按钮
    QPushButton restart;
    //布局管理
    QGridLayout qgl;

    //标签
    QLabel timeInfo;
    QLabel timeInfoNum;

    //标签
    QLabel gameStateInfo;
    QLabel gameStateNum;


public:
    //构造函数
    infoBox(int bn = 5, int mn = 5, QWidget *parent = 0);

    //设置格数和雷数信息
    void setValue(int bn, int mn);

    //int getSecond();


signals:
    //发送重新开始游戏的信号
    void sendRestart();

public slots:
    //设置已标记的雷数
    void setSignedNum(int state);
    //刷新计时器
    void refreshTime(int state);
    //设置游戏状态
    void setGameState(int state);

};

#endif // INFOBOX_H
