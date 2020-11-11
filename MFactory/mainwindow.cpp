#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stat.h"
#include "addemployee.h"
#include "search.h"
#include <QLabel>
#include <QList>
#include <QLayout>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{

  ui->setupUi(this);
  QPushButton *add= ui->AddEmployee;
  QPixmap add_image("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\plus.png");
  QIcon add_icon("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\plus.png");
  add->setIcon(add_icon);
  add->setIconSize(add->size());
  QIcon deletes("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\minus.png"),
      update("C:\\Users\\Anas\\OneDrive\\Workload\\Project 2\\Smart Factory\\MFactory\\Resources\\edit.png");
  ui->DeleteEmployee->setIcon(deletes);
  ui->UpdateEmployee->setIcon(update);
  ui->DeletePosts->setIcon(deletes);
  ui->AddPosts->setIcon(add_icon);
  ui->UpdatePosts->setIcon(update);

  ui->DeleteEmployee->setIconSize(ui->DeleteEmployee->size());
  ui->UpdateEmployee->setIconSize(ui->UpdateEmployee->size());
  ui->DeletePosts->setIconSize(ui->DeletePosts->size());
  ui->AddPosts->setIconSize(ui->AddPosts->size());
  ui->UpdatePosts->setIconSize(ui->UpdatePosts->size());




}



MainWindow::~MainWindow()
{
  db.close();
  delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Stat s;
    s.exec();
}



void MainWindow::on_search_clicked()
{
  Search s;
  s.exec();
}




/*void MainWindow::on_AddEmployee_clicked()
{
 // ui->tableEmployees->resizeColumnToContents(5);
  //ui->tableEmployees->sortItems(5,Qt::AscendingOrder);
  //ui->tableEmployees->insertRow(ui->tableEmployees->rowCount());
  //while (ui->tableWidget->isItemSelected(ui->tableWidget->currentItem()));
  QPushButton *a1=ui->AddEmployee, *a2=ui->DeleteEmployee, *a3=ui->UpdateEmployee;
  QRect r[]={a1->geometry(),a2->geometry(),a3->geometry()};

  if (ui->AddEmployee->isEnabled()){
    QPropertyAnimation *p1=new QPropertyAnimation(ui->AddEmployee,"geometry"),
        *p2= new QPropertyAnimation(ui->DeleteEmployee,"geometry"),*p3 =new QPropertyAnimation(ui->UpdateEmployee,"geometry");
    QParallelAnimationGroup *p = new QParallelAnimationGroup();
    p->addAnimation(p1);
    p->addAnimation(p2);
    p->addAnimation(p3);

    p1->setDuration(1500);
    p2->setDuration(1500);
    p3->setDuration(1500);


    p1->setStartValue(a1->geometry());
    p2->setStartValue(a2->geometry());
    p3->setStartValue(a3->geometry());

    ui->AddEmployee->setText("Add Employee");

    p1->setEndValue(QRect(a1->geometry().x(),a1->geometry().y(),100,a1->height()));
    p2->setEndValue(QRect(a2->geometry().x()+100,a2->geometry().y(),a2->width(),a2->height()));
    p3->setEndValue(QRect(a3->geometry().x()+100,a3->geometry().y(),a3->width(),a3->height()));
    p->start();
    }
  else {
    a1->setGeometry(r[0]);
    a2->setGeometry(r[1]);
    a3->setGeometry(r[2]);
    }

}*/

void MainWindow::on_DeleteEmployee_clicked()
{
  if (ui->tableEmployees->isEnabled())
    ui->tableEmployees->removeRow(ui->tableEmployees->currentRow());
}

void MainWindow::display_Employee()
{
  m->setQuery("Select * from Employees");
  ui->tableView->setModel(m);
}

void MainWindow::on_AddEmployeeButton_clicked()
{

  sound->play();
  Employees e;
  e.setCin(ui->CIN_Employee_text->toPlainText());
  e.setFull_Name(ui->Name_Employee_text->toPlainText());
  e.setAge(ui->Age_Employee_text->toPlainText().toUInt());
  e.setAddress(ui->Address_Employee_text->toPlainText());
  e.setEmail(ui->Email_Employee_text->toPlainText());

  if (e.search_Employee(ui->CIN_Employee_text->toPlainText())){
  if (e.add_employee()){
      QMessageBox::information(this, "Add Employee", "The employee added successfully", QMessageBox::Ok);
    }
  else
    QMessageBox::warning(this, "Warning", "An unknow error",QMessageBox::Ok);
    }
  else {
      if (e.update_employee()){
          QMessageBox::information(this, "update Employee", "The Employee info is successfully changed", QMessageBox::Ok);
        }
      else
        QMessageBox::warning(this, "Warning", "An unknow error",QMessageBox::Ok);
    }

}

void MainWindow::on_DeleteEmployee_button_clicked()
{
    Employees e;
    sound->play();
    e.setCin(ui->CIN_Del_Text->toPlainText());
    if (e.remove_employee()){
        QMessageBox::information(this, "Delete Employee", "The employee removed successfully", QMessageBox::Ok);
      }
    else
      QMessageBox::warning(this, "Warning", "the task failed successfully",QMessageBox::Ok);
}

void MainWindow::on_DeleteEmployee_button_2_clicked()
{
  db.setDatabaseName(QString("Source_Projet2A"));
  db.setUserName(ui->USER_text->toPlainText());
  db.setPassword(ui->Password_text->text());
  if(!db.open()) {
    qDebug() << QString("Unable to open database");
    QMessageBox::warning(this, tr("MFactory"), tr("Unable to open database"), QMessageBox::Ok);
    }
  else {
      QMessageBox::information(this,"Sucess","You gained access to the Database", QMessageBox::Ok);
  ui->label_7->setText("Status: Connected");
    }
}

