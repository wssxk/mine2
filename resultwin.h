/*
 * 显示结果的窗口
 */

#ifndef RESULTWIN_H
#define RESULTWIN_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
//#include <QGridLayout>
#include <QVBoxLayout>
#include <QPaintEvent>
#include <QLabel>
#include <QFont>



class resultWin : public QDialog
{
    Q_OBJECT
private:
    //结果 1：赢， 0：输
    int result;
    //QWidget* dis;
    //显示结果的标签
    QLabel* dis;
    //按钮
    QPushButton* ok;
    QPushButton* restart;
    //布局管理
    QHBoxLayout* qhl;
    QVBoxLayout* qvl;
    //输出的字体
    QFont *font;

public:
    //构造函数
    resultWin(QWidget *parent = 0);

public slots:
    //设置结果
    void setResult(int r);

protected:
    //void paintEvent(QPaintEvent *event);

signals:
    //发送重新开始信号
    void sendRestart();
};

#endif // RESULTWIN_H
