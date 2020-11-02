#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stat.h"
#include "addemployee.h"
#include "search.h"
#include <QLabel>
#include <QList>
#include <QLayout>
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{

  ui->setupUi(this);

  QAction **ico=new  QAction*[4];
  for (int i=0;i<4;i++){
      ico[i]=new QAction;
    }
  ico[0]->setIcon(QIcon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\plus.png"));
  ico[1]->setIcon(QIcon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\minus.png"));
  ico[2]->setIcon(QIcon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\edit.png"));
  ico[3]->setIcon(QIcon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\search.png"));
  ico[0]->setToolTip(QString("Add new employee"));
  for (int i=0;i<4;i++){
      ui->toolBar->addAction(ico[i]);
    }
  ui->tabWidget->heightForWidth(1280);
  connect(ico[0], &QAction::triggered,qApp,[=](){
      if (ui->tabWidget->currentIndex()==0) on_addnew_clicked();});
  connect(ico[1],&QAction::triggered,qApp,[&](){ui->Employees->raise();});
  connect(ico[2],&QAction::triggered,qApp,[&](){on_addnew_clicked();});
  connect(ico[3],&QAction::triggered,qApp,[&](){on_search_clicked();});

}



MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Stat s;
    s.exec();
}

void MainWindow::on_addnew_clicked()
{
  AddEmployee e;
  e.exec();
}

void MainWindow::on_search_clicked()
{
  Search s;
  s.exec();
}
