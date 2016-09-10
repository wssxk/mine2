/*
 * 雷场
 */


#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QWidget>
#include <QGridLayout>
#include "mine.h"
class mineField : public QWidget
{
    Q_OBJECT
private:
    //格数
    int blockNum;
    //雷数
    int mineNum;
    //已点开的格数
    int clickedBlock;
    //雷场中的格
    mine* mf[20][20];
    //布局管理
    QGridLayout qgl;
public:
    //构造函数
    mineField(int BN = 5, int MN = 5, QWidget *parent = 0);
    //析构函数
    ~mineField();
 //   void gameOver(int state);

public slots:
    //点到雷
    void touchMine();
    //检查某格周围的雷数
	void checkAro(int x, int y);
    //有格被点开
    void getClicked();


signals:
    //发送游戏结果
    void sendResult(int result);
    //发送标记状态
    void sendSigned(int state);

};


#endif // MINEFIELD_H
