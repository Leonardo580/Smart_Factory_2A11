#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
 // MainWindow w;

  QMediaPlayer* player = new QMediaPlayer;
  QVideoWidget* vw = new QVideoWidget;

  player->setVideoOutput(vw);

  player->setMedia(QUrl::fromLocalFile("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Integration\\integ_3\\v.mp4"));

  vw->setGeometry(100,100,300,400);
  vw->show();
  login l;
  l.show();
 // w.show();
  return a.exec();
}
