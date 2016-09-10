/*
 * askwin.h的实现文件
 */

#include "askwin.h"

askWin::askWin(int bn, int mn, QWidget *parent) : QDialog(parent)
{

    qgl = new QGridLayout;
    qhl = new QHBoxLayout;
    qvl = new QVBoxLayout;

    blockNum = bn;
    mineNum = mn;

    blockInfo.setText("blockNum");
    mineInfo.setText("mineNum");

    blockSlider.setOrientation(Qt::Horizontal);
    mineSlider.setOrientation(Qt::Horizontal);

    ok.setText("&Ok");
    cancle.setText("&Cancle");

    connect(&blockSlider, SIGNAL(valueChanged(int)), &blockSpin, SLOT(setValue(int)));
    connect(&blockSpin, SIGNAL(valueChanged(int)), &blockSlider, SLOT(setValue(int)));
    connect(&mineSlider, SIGNAL(valueChanged(int)), &mineSpin, SLOT(setValue(int)));
    connect(&mineSpin, SIGNAL(valueChanged(int)), &mineSlider, SLOT(setValue(int)));
    connect(&blockSlider, SIGNAL(valueChanged(int)), this, SLOT(setMineMax(int)));

    connect(&cancle, SIGNAL(clicked()), this, SLOT(close()));
    connect(&ok, SIGNAL(clicked()), this, SLOT(getOk()));
    connect(&ok, SIGNAL(clicked()), this, SLOT(close()));


    blockSlider.setRange(1, 20);
    blockSlider.setValue(blockNum);

    mineSlider.setValue(mineNum);


    qgl->addWidget(&blockInfo, 1, 1);
    qgl->addWidget(&blockSlider, 1, 2);
    qgl->addWidget(&blockSpin, 1 ,3);

    qgl->addWidget(&mineInfo, 2, 1);
    qgl->addWidget(&mineSlider, 2, 2);
    qgl->addWidget(&mineSpin, 2, 3);

 //   qgl->addWidget(&ok, 3, 2);
 //   qgl->addWidget(&cancle, 3, 3);

    qhl->addWidget(&ok);
    qhl->addWidget(&cancle);

    qvl->addLayout(qgl);
    qvl->addLayout(qhl);

    this->setLayout(qvl);

    this->setFixedSize(this->sizeHint());
    this->setWindowTitle("Restart");


}


askWin::~askWin()
{
    delete qgl;
    delete qhl;
    delete qvl;

}


void askWin::setMineMax(int t)
{
    mineSlider.setRange(0, t * t - 1);
    mineSpin.setRange(0, t * t - 1);
}



void askWin::getOk()
{
    emit valueChanged(blockSlider.value(), mineSlider.value());

}
