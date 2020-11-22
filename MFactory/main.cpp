#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.autoFillBackground();
  w.setWindowIcon(QIcon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\logo.JPG"));
  w.setFont(QFont("Agency FB"));

 QFile file("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Style1.qss");
 file.open(QFile::Text|QFile::ReadOnly);
 QTextStream txt(&file);
 a.setStyleSheet(txt.readAll());
 file.close();
  w.show();

  return a.exec();
}
