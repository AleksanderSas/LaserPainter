#include "mainpanel.h"
#include "bezierdesigner.h"
#include <QApplication>

int main(int argc, char *argv[])
{
     QApplication a(argc, argv);
     MainPanel w;

     w.show();

     return a.exec();
}
