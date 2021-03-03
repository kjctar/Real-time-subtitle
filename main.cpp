#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);

     MainWindow w;




    //w.setWindowFlags(Qt::FramelessWindowHint);  // 无边框+无状态栏图标
    //w.setAttribute(Qt::WA_TranslucentBackground);  // 透明

    w.setWindowOpacity(0.7);



    w.show();
    return a.exec();
}
