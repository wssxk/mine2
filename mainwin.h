/*
 * 扫雷游戏的主窗口
 */

#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTimerEvent>

#include "minefield.h"
#include "infobox.h"
#include "askwin.h"
#include "resultwin.h"

class mainWin : public QWidget
{
    Q_OBJECT
private:
    //格数
    int blockNum;
    //雷数
    int mineNum;
    //雷场
    mineField *mf;
    //信息显示控件
    infoBox *ib;
    //结果显示控件
    resultWin* rw;

    //布局管理
    QGridLayout* qgl;
    //QHBoxLayout* qhl;

    //重新游戏的数据询问窗口
    askWin* aw;

public:
    //构造函数
    mainWin(QWidget * parent = 0);

public slots:
    //获取要求重新开始游戏的信号
    void getRestart();
    //获取重启游戏的确认数据
    void getValueChanged(int bn, int mn);
    //停止游戏计时
    void stopTimer(int state);

protected:
    //Qt计时器运行的程序
    void timerEvent(QTimerEvent* event);

signals:
    //刷新游戏计时的信号
    void refreshTime(int state);
};

#endif // MAINWIN_H
