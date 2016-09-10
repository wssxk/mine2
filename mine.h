/*
 * 单个格
 */

#ifndef MINE_H
#define MINE_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
//#include "global.h"
//extern int unit;

class mine : public QWidget
{
    Q_OBJECT
private:
    //在雷场的位置
	int xPos;
	int yPos;
    //格的尺寸
    int len;
    //是否是雷
    int isMine;
    //是否激活
    int isEnable;
    //是否已被标记
    int isSigned;
    //游戏是否已结束
    int isFinished;
    //是否已设置周围的雷数
    int isSetAroNum;
//  int isShowMine;
    //格的颜色
    Qt::GlobalColor color;
    //周围雷数
	int aroNum;
    //雷，旗的图片
    QPixmap* mine_ico;
    QPixmap* flag_ico;

public:
    //构造函数
    mine(QWidget *parent = 0);
    //设置雷
    void setMine(int m = 1);
    //设置是否激活
    void setEnable(int m = 1);
    //展示所有的雷
    void showMine();
    //设置位置
	void setPos(int x, int y);
    //设置周围雷数
	void setAroNum(int t);
    //检查是否是雷
	int checkMine();
   // void writeText(QString str);


protected:
    //绘制格
    void paintEvent(QPaintEvent *event);
    //各种鼠标事件
    void mouseMoveEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public slots:
    //格被左击
    void clicked();
    //右键释放
    void getRightRelease();

signals:
    //点到雷的信号
    void touchMine();
    //获取周围雷数
	void checkAro(int x, int y);
    //发送有格被点击的信号，用于判断游戏结果
    void sendClicked();
    //发送雷的标记信号
    void sendSigned(int state);
};
#endif
