/*
 * infobox.h的实现
 */


#include <iostream>
#include <QSizePolicy>

#include "infobox.h"

infoBox::infoBox(int bn, int mn, QWidget *parent) : QWidget(parent)
{
    blockNum = bn;
    mineNum = mn;
    signedNum = 0;
    timeState = 0;

    startTime = QTime::currentTime();

    char str[5];

    sprintf(str, "%d (%dx%d)", blockNum * blockNum, blockNum, blockNum);
    blockInfo.setText("blockNum: ");
    blockInfoNum.setText(str);

    sprintf(str, "%d", mineNum);
    mineInfo.setText("mineNum: ");
    mineInfoNum.setText(str);

    sprintf(str, "%d", signedNum);
    signedInfo.setText("signedNum: ");
    signedInfoNum.setText(str);

    timeInfo.setText("time(s): ");
    timeInfoNum.setNum(0);

    gameStateInfo.setText("state: ");
    gameStateNum.setStyleSheet("color:blue;");
    gameStateNum.setText("Playing...");

    restart.setText("&Restart");

    qgl.addWidget(&timeInfo, 1, 1);
    qgl.addWidget(&timeInfoNum, 1, 2);
    qgl.addWidget(&blockInfo, 2, 1);
    qgl.addWidget(&blockInfoNum, 2, 2);
    qgl.addWidget(&mineInfo, 3, 1);
    qgl.addWidget(&mineInfoNum, 3, 2);
    qgl.addWidget(&signedInfo, 4, 1);
    qgl.addWidget(&signedInfoNum, 4, 2);
    qgl.addWidget(&gameStateInfo, 5, 1);
    qgl.addWidget(&gameStateNum, 5, 2);
    qgl.addWidget(&restart, 6, 2);

    connect(&restart, SIGNAL(clicked()), this, SIGNAL(sendRestart()));

    this->setLayout(&qgl);

//    this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    this->setFixedSize(this->sizeHint());

}


void infoBox::setValue(int bn, int mn)
{
    blockNum = bn;
    mineNum = mn;
    signedNum = 0;

    char str[5];

    sprintf(str, "%d (%dx%d)", blockNum * blockNum, blockNum, blockNum);
    //blockInfo.setText("blockNum: ");
    blockInfoNum.setText(str);

    sprintf(str, "%d", mineNum);
    //mineInfo.setText("mineNum: ");
    mineInfoNum.setText(str);

    sprintf(str, "%d", signedNum);
    //signedInfo.setText("signedNum: ");
    signedInfoNum.setText(str);



}


void infoBox::setSignedNum(int state)
{
    //state 1：添加标记， 2：减去标记
    if(state == 1) signedNum ++;
    else signedNum --;

    char str[5];
    sprintf(str, "%d", signedNum);
    //signedInfo.setText("signedNum: ");
    signedInfoNum.setText(str);


}


/*
void infoBox::getSecond()
{


}

*/

void infoBox::refreshTime(int state)
{
    //state 1：重新计时， 0：结束计时， -1：正常刷新

    if(state == -1 && timeState == 0) return;

    if(state == 0)
    {
        timeState = 0;
        return;

    }

    if(state == 1)
    {
        startTime = QTime::currentTime();
        timeState = 1;
    }

    QTime current = QTime::currentTime();
    int second = current.hour() * 3600 + current.minute() * 60 + current.second()
            - startTime.hour() * 3600 - startTime.minute() * 60 - startTime.second();

    timeInfoNum.setNum(second);

}


void infoBox::setGameState(int state)
{
    //state 1：赢， 0：输， -1：正在游戏
    if(state == 0)
    {
        gameStateNum.setStyleSheet("color:red;");
        gameStateNum.setText("You faild!");
        return;
    }
    else if(state == 1)
    {
        gameStateNum.setStyleSheet("color:green;");
        gameStateNum.setText("You Win!");
        return;
    }
    else if(state == -1)
    {
        gameStateNum.setStyleSheet("color:blue");
        gameStateNum.setText("Playing...");
        return;
    }

}
