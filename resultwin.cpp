#include <QPainter>
#include <QFont>
#include "resultwin.h"
#include "global.h"

resultWin::resultWin(QWidget *parent):QDialog(parent)
{
    result = -1;

    dis = new QLabel;
    ok = new QPushButton;
    restart = new QPushButton;
    qhl = new QHBoxLayout;
   // qgl = new QGridLayout;
    qvl = new QVBoxLayout;
    font = new QFont;

    font->setPixelSize(global::unit_ext);
    dis->setFont(*font);
    dis->setAlignment(Qt::AlignHCenter);

    dis->setFixedSize(5 * global::unit_ext, 1.5 * global::unit_ext);
    ok->setText("&Ok");
    restart->setText("&Restart");

    connect(ok, SIGNAL(clicked()), this, SLOT(close()));
    connect(restart, SIGNAL(clicked()), this, SIGNAL(sendRestart()));
    connect(restart, SIGNAL(clicked()), this, SLOT(close()));

    qhl->addWidget(ok);
    qhl->addWidget(restart);

    qvl->addWidget(dis);
    qvl->addLayout(qhl);

    this->setLayout(qvl);

    this->setWindowTitle("Result");
    this->setFixedSize(this->sizeHint());
    this->setModal(Qt::ApplicationModal);

    //setResult(result);

}


void resultWin::setResult(int r)
{
    result = r;
    if(result == 0)
    {
        dis->setStyleSheet("color:red;");
        dis->setText("Game over!");
    }
    else if(result == 1)
    {
        dis->setStyleSheet("color:green;");
        dis->setText("You Win!");
    }
    else
    {
        dis->setText("Nothing");
    }


    this->show();

}

/*
void resultWin::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    QFont font;
    font.setPixelSize(global::unit_ext);
    painter.setFont(font);


    if(result == 0)
    {
        painter.setPen(Qt::red);
        painter.drawText(this->rect(), Qt::AlignVCenter, "Game\nover!");
    }
    else if(result == 1)
    {
        painter.setPen(Qt::yellow);
        painter.drawText(this->rect(), Qt::AlignCenter, "You win!");
    }
    else
    {
        painter.setPen(Qt::black);
        painter.drawText(this->rect(), Qt::AlignCenter, "Nothing");
    }


}

*/
