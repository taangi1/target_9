#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Target 9 Game");

    w.setWindowFlags(w.windowFlags() | Qt::Window | Qt::WindowStaysOnTopHint);

    w.show();
    return a.exec();
}
