/*
 * 询问重新开始游戏时的数据窗口
 */

#ifndef ASKWIN_H
#define ASKWIN_H

#include <QDialog>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class askWin : public QDialog
{

    Q_OBJECT
private:

    //格数
    int blockNum;
    //雷数
    int mineNum;

    //各种标签
    QLabel blockInfo;
    QLabel mineInfo;

    //调节控件
    QSlider blockSlider;
    QSlider mineSlider;

    //调节控件
    QSpinBox blockSpin;
    QSpinBox mineSpin;

    //按钮
    QPushButton ok;
    QPushButton cancle;

    //布局管理
    QGridLayout* qgl;
    QHBoxLayout* qhl;
    QVBoxLayout* qvl;

public:
    //构造函数
    askWin(int bn = 5, int mn = 5, QWidget *parent = 0);
    //析构函数
    ~askWin();

public slots:
    //调节控件之间的联系
    void setMineMax(int);
    //获取确认信息
    void getOk();

signals:
    //发送确认结果数据的信号
    void valueChanged(int bn, int mn);


};

#endif // ASKWIN_H
