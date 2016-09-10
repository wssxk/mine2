/*
 * minefield.h的实现文件
 */


#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "minefield.h"

mineField::mineField(int BN, int MN, QWidget *parent) : QWidget(parent)
{
	//这里注意不要混淆局部变量和类的成员变量
    clickedBlock = 0;
    blockNum = BN;
    mineNum = MN;
//	std::cout << blockNum << std::endl;
    srand(time(NULL));
    //地雷位置
    int* minePos = new int[mineNum];

    int tmp;
    int exist_tmp = 0;
/*
    for(int t = 0; t < mineNum; t ++)
        minePos[t] = -1;
 */
   //产生随机位置
   for(int t = 0; t < mineNum; t ++)
    {
        tmp = rand() % (blockNum * blockNum);
        //检验位置是否存在
        for(int t2 = 0; t2 < t; t2 ++)
            if(tmp == minePos[t2])
            {
                exist_tmp = 1;
                break;
            }
        if(exist_tmp == 1)
        {
            t --;
            exist_tmp = 0;
            continue;
        }

        minePos[t] = tmp;
       // exist_tmp = 0;

    }

   //int count_tmp = 0;
   //产生地雷
    for(int i = 1; i <= blockNum; i ++)
        for(int t = 1; t <= blockNum; t ++)
        {
            mf[i - 1][t - 1] = new mine;
            qgl.addWidget(mf[i - 1][t - 1], i, t);
            connect(mf[i - 1][t - 1], SIGNAL(touchMine()), this, SLOT(touchMine()));

			connect(mf[i - 1][t - 1], SIGNAL(checkAro(int, int)), this, SLOT(checkAro(int, int)));
            connect(mf[i - 1][t - 1], SIGNAL(sendClicked()), this, SLOT(getClicked()));
            connect(mf[i - 1][t - 1], SIGNAL(sendSigned(int)), this, SIGNAL(sendSigned(int)));

            mf[i - 1][t - 1]->setPos(i - 1, t - 1);
        }
    //设置区块为地雷
    for(int t = 0; t < mineNum; t ++)
    {
        int count = 0;
        for(int i1 = 0; i1 < blockNum; i1 ++)
            for(int i2 = 0; i2 < blockNum; i2 ++)
            {
                if(count == minePos[t])
                {
                    mf[i1][i2]->setMine(1);
                    i1 = blockNum;
                    break;
                }

                count ++;
            }
    }

    qgl.setSpacing(1);
    this->setLayout(&qgl);
//	std::cout << blockNum << std::endl;

	//touchMine();

    this->setFixedSize(this->sizeHint());




}


mineField::~mineField()
{
	for(int i = 0; i < blockNum; i ++)
			for(int t = 0; t < blockNum; t ++)
			{
				delete mf[i][t];
			}
//	QWidget::~QWidget();
}


void mineField::touchMine()
{

//    std::cout << this->blockNum << std::endl;
    for(int t = 0; t < blockNum; t ++)
        for(int i = 0; i < blockNum; i ++)
        {
//			std::cout << t << " " << i << std::endl; 
            mf[t][i]->showMine();
        }

    emit sendResult(0);
    //std::cout << "TTTTTTTT" << std::endl;
	
}

void mineField::checkAro(int x, int y)
{
	int count = 0;

    //遍历周围的格
	if(x - 1 >= 0 && y - 1 >= 0)
			count += mf[x - 1][y - 1]->checkMine();
    //std::cout << count << " 1 OO" << std::endl;
	if(x - 1 >= 0)
			count += mf[x - 1][y]->checkMine();
    //std::cout << count << " 2 OO" << std::endl;
	if(x - 1 >= 0 && y + 1 < blockNum)
			count += mf[x - 1][y + 1]->checkMine();
    //std::cout << count << " 3 OO" << std::endl;
	if(y + 1 < blockNum)
			count += mf[x][y + 1]->checkMine();
    //std::cout << count << " 4 OO" << std::endl;
	if(x + 1 < blockNum && y + 1 < blockNum)
			count += mf[x + 1][y + 1]->checkMine();
    //std::cout << count << " 5 OO" << std::endl;
	if(x + 1 < blockNum)
			count += mf[x + 1][y]->checkMine();
    //std::cout << count << " 6 OO" << std::endl;
	if(x + 1 < blockNum && y - 1 >= 0)
			count += mf[x + 1][y - 1]->checkMine();
    //std::cout << count << " 7 OO" << std::endl;
	if(y - 1 >= 0)
			count += mf[x][y - 1]->checkMine();

    //std::cout << count << " 8 OO" << std::endl;

	mf[x][y]->setAroNum(count);


	if(count != 0) return;

    //点击周围的格

	if(x - 1 >= 0 && y - 1 >= 0)
			mf[x - 1][y - 1]->clicked();
//	std::cout << count << " 1 OO" << std::endl; 
	if(x - 1 >= 0)
			mf[x - 1][y]->clicked();
//	std::cout << count << " 2 OO" << std::endl; 
	if(x - 1 >= 0 && y + 1 < blockNum)
			mf[x - 1][y + 1]->clicked();
//	std::cout << count << " 3 OO" << std::endl; 
	if(y + 1 < blockNum)
			mf[x][y + 1]->clicked();
//	std::cout << count << " 4 OO" << std::endl; 
	if(x + 1 < blockNum && y + 1 < blockNum)
			mf[x + 1][y + 1]->clicked();
//	std::cout << count << " 5 OO" << std::endl; 
	if(x + 1 < blockNum)
			mf[x + 1][y]->clicked();
//	std::cout << count << " 6 OO" << std::endl; 
	if(x + 1 < blockNum && y - 1 >= 0)
			mf[x + 1][y - 1]->clicked();
//	std::cout << count << " 7 OO" << std::endl; 
	if(y - 1 >= 0)
			mf[x][y - 1]->clicked();

//	std::cout << count << " 8 OO" << std::endl; 



	
}


void mineField::getClicked()
{
    clickedBlock ++;
    if(blockNum * blockNum - clickedBlock == mineNum)
    {
        for(int t1 = 0; t1 < blockNum; t1 ++)
            for(int t2 = 0; t2 < blockNum; t2 ++)
            {
                if(mf[t1][t2]->checkMine() == 1)
                {
                    mf[t1][t2]->showMine();
                }
            }
        std::cout << clickedBlock << std::endl;
        emit sendResult(1);
    }



}
