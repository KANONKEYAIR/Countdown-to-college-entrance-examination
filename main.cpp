#include "mainwindow.h"
#include <QApplication>
#include <QScreen>
#include <QRect>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QScreen *screen = QGuiApplication::primaryScreen ();
    QRect screenRect =  screen->availableVirtualGeometry();
    int dWidth = screenRect.width();
    w.move(dWidth- w.width(),0);
    w.show();

    return a.exec();
}
