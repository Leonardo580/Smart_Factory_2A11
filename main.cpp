#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowIcon(QIcon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\logo.JPG"));
  w.setFont(QFont("Agency FB"));
  w.show();

  return a.exec();
}
