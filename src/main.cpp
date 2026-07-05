#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    int width=800;
    int height=600;
    MainWindow w(width, height);
    w.show();
    return a.exec();
}
