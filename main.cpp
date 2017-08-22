#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/sucai/2.gif"));

    splash->show();
    for(int i=0;i<1000;i++)
     {
         splash->repaint();
     }
    MainWindow w;
    w.show();

    return a.exec();
}
