/*
 * 程序运行的起点，在这里调用扫雷的起点
 */



#include <QApplication>
#include <QWidget>

#include "global.h"
//#include "mine.h"
//#include "minefield.h"
#include "mainwin.h"
//#include "infobox.h"
//#include "askwin.h"
//#include "resultwin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //定义全局变量中尺寸的相对参考大小
    QWidget *init_tmp = new QWidget();
    global::unit_ext = (init_tmp->size()).width() / 16;
    delete init_tmp;

//    mineField mf;
//    mf.show();


//	mainWin mw;
//	mw.show();

//    infoBox ib;
//    ib.show();

//    askWin aw(20, 7);
//    aw.show();

    //启动主窗口
    mainWin mw;
    mw.show();

    //resultWin rw;
    //rw.show();

    return app.exec();
}
