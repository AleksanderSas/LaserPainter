#include "mainwindow.h"
#include "mainpanel.h"
#include "bezierdesigner.h"
#include <QApplication>
#include <QtGui/QLabel>

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    QLabel *lable=new QLabel (&w);
    QString str = "Hello World";
    lable->setText(str);
    lable->setAlignment(Qt::AlignCenter);
    w.show();

    return a.exec();*/


     QApplication a(argc, argv);
     MainPanel w;

     w.show();

     return a.exec();
}
