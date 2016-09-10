/*
 * mine.h的实现文件
 */


#include <QPainter>
#include <QPen>
#include <QBrush>
#include <iostream>
#include <QFont>
#include "mine.h"
#include "global.h"

mine::mine(QWidget *parent) : QWidget(parent)
{
	aroNum = 0;

    isMine = 0;
    isEnable = 1;
    isSigned = 0;
    isFinished = 0;
    isSetAroNum = 0;

    mine_ico = new QPixmap(":/mine.ico");
    flag_ico = new QPixmap(":/flag.ico");
//    isShowMine = 0;
    len = global::unit_ext * 1.5;
    this->setFixedSize(len, len);
    color = Qt::darkGray;
    this->setMouseTracking(true);




}

void mine::paintEvent(QPaintEvent *event)
{

//	xPos = yPos = -1;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
//    painter.drawRect(this->rect());
    painter.setBrush(color);
    painter.drawRoundedRect(this->rect(), 5, 5);
/*
    painter.setPen(Qt::black);

    QFont font;
    font.setPixelSize(global::unit_ext);
    painter.setFont(font);

    painter.drawText(this->rect(), Qt::AlignCenter, QObject::tr("9"));
*/
    if(isMine == 1 && isEnable == 0 && (isSigned == 0 || isFinished == 1))
    {

        painter.drawPixmap(this->rect(), *mine_ico);
        /*
        painter.setPen(Qt::black);
        QFont font;
        font.setPixelSize(len);
        painter.setFont(font);
        painter.drawText(this->rect(), Qt::AlignCenter, "T");
    */

    }
    else if(isMine == 0 && isEnable == 0 && isSigned == 0)
    {
		if(aroNum == 0) return;
        painter.setPen(Qt::black);
        QFont font;
        font.setPixelSize(len);
        painter.setFont(font);
		char str[2];
		sprintf(str, "%d", aroNum);
        painter.drawText(this->rect(),  Qt::AlignCenter, str);
    }
    else if(isSigned == 1)
    {
        painter.drawPixmap(this->rect(), *flag_ico);

    }

}

void mine::mouseMoveEvent(QMouseEvent *event)
{
   if(isEnable == 0 || isFinished == 1) return;
    color = Qt::gray;
    this->repaint();

}

void mine::enterEvent(QEvent *event)
{
    if(isEnable == 0 || isFinished == 1) return;
    color = Qt::gray;
    this->repaint();

}

void mine::leaveEvent(QEvent *event)
{
    if(isEnable == 0 || isFinished == 1) return;
    color = Qt::darkGray;
    this->repaint();

}


void mine::mousePressEvent(QMouseEvent *event)
{
    if(isEnable == 0 || isFinished == 1) return;
    //color = Qt::black;
    this->repaint();

}

void mine::mouseReleaseEvent(QMouseEvent *event)
{
    if(isFinished == 1) return;

    if(event->button() == Qt::RightButton)
    {
        getRightRelease();
        return;
    }
    if(isEnable == 0) return;
    //color = Qt::lightGray;
    //this->repaint();
    clicked();

}

void mine::setMine(int m)
{
    isMine = m;
}

void mine::setEnable(int m)
{
    isEnable = m;

}

void mine::clicked()
{
    if(isEnable == 0 && isSigned == 0) return;
    emit sendClicked();
    isFinished = 1;
    if(isMine == 1)
    {
        color = Qt::red;
		isEnable = 0;
		repaint();
        //std::cout << "I" << std::endl;
        emit touchMine();

    }
    else if(isMine == 0)
    {
        color = Qt::lightGray;
		isEnable = 0;
        if(isSigned == 1)
            emit sendSigned(0);
        isSigned = 0;

		repaint();
        std::cout << "I" << std::endl;
		emit checkAro(xPos, yPos);
    }

}

/*
void mine::writeText(QString str)
{
    QPainter painter(this);
    QFont font;

    painter.setPen(Qt::black);
    font.setPixelSize(len);
    painter.setFont(font);

    painter.drawText(this->rect(), Qt::AlignCenter, str);

}
*/


void mine::showMine()
{
    if(isEnable == 0 && isSigned == 0) return;
    isFinished = 1;
    if(isMine == 0)
	{
		isEnable = 0;
		color = Qt::darkGray;

//		repaint();
		return;
	}
    color = Qt::darkGray;
    isEnable = 0;
    isFinished = 1;
    repaint();
    std::cout << "T" << std::endl;
}


void mine::setPos(int x, int y)
{
	xPos = x;
	yPos = y;
}

void mine::setAroNum(int t)
{
    //isSetAroNum = 1;
	aroNum = t;
	repaint();
}

int mine::checkMine()
{

	return isMine;
}


void mine::getRightRelease()
{
    if(isEnable == 0 && isSigned == 0)
        return;
    if(isSigned == 0)
    {
        isSigned = 1;
        isEnable = 0;
        emit sendSigned(1);
    }
    else if(isSigned == 1)
    {
        isSigned = 0;
        isEnable = 1;
        emit sendSigned(0);
    }
    color = Qt::darkGray;
    repaint();

}
