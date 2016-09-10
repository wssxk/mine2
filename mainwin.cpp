/*
 * mainwin.h的实现
 */


#include "mainwin.h"

mainWin::mainWin(QWidget * parent) : QWidget(parent)
{

    blockNum = 5;
    mineNum = 5;

    mf = new mineField(blockNum, mineNum);
    ib = new infoBox(blockNum, mineNum);
    //qhl = new QHBoxLayout;
    qgl = new QGridLayout;
    rw = new resultWin(this);
    connect(rw, SIGNAL(sendRestart()), this, SLOT(getRestart()));

    connect(mf, SIGNAL(sendSigned(int)), ib, SLOT(setSignedNum(int)));
    aw = new askWin(blockNum, mineNum, this);
    aw->setModal(Qt::ApplicationModal);
    connect(aw, SIGNAL(valueChanged(int, int)), this, SLOT(getValueChanged(int, int)));

    connect(mf, SIGNAL(sendResult(int)), rw, SLOT(setResult(int)));
    connect(mf, SIGNAL(sendResult(int)), this, SLOT(stopTimer(int)));
    connect(mf, SIGNAL(sendResult(int)), ib, SLOT(setGameState(int)));

    qgl->addWidget(mf, 1, 1);
    qgl->addWidget(ib, 1, 2);

    connect(ib, SIGNAL(sendRestart()), this, SLOT(getRestart()));
    connect(this, SIGNAL(refreshTime(int)), ib, SLOT(refreshTime(int)));

    this->setLayout(qgl);
    this->setFixedSize(this->sizeHint());
    this->setWindowTitle("Mine");
    this->startTimer(500);

    emit refreshTime(1);
}


void mainWin::getRestart()
{
    /*
    aw = new askWin(blockNum, mineNum, this);
    aw->setModal(Qt::ApplicationModal);
    connect(aw, SIGNAL(valueChanged(int, int)), this, SLOT(getValueChanged(int, int)));
    */
    aw->show();
}


void mainWin::getValueChanged(int bn, int mn)
{
    blockNum = bn;
    mineNum = mn;
    delete mf;
    mf = new mineField(blockNum, mineNum);

    connect(mf, SIGNAL(sendResult(int)), rw, SLOT(setResult(int)));
    connect(mf, SIGNAL(sendSigned(int)), ib, SLOT(setSignedNum(int)));
    connect(mf, SIGNAL(sendResult(int)), this, SLOT(stopTimer(int)));
    connect(mf, SIGNAL(sendResult(int)), ib, SLOT(setGameState(int)));
    qgl->addWidget(mf, 1, 1);

    mf->show();
    ib->setValue(bn, mn);
    ib->setGameState(-1);
    emit refreshTime(1);

    this->setFixedSize(this->sizeHint());

}


void mainWin::timerEvent(QTimerEvent *event)
{
    emit refreshTime(-1);

}

void mainWin::stopTimer(int state)
{
    emit refreshTime(0);

}


