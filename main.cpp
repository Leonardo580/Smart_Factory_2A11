#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/images/126042835_198489595235184_1959348384574746721_n.jpg"));
    w.show();
    return a.exec();
}
