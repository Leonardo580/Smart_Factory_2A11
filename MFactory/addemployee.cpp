#include "addemployee.h"
#include "ui_addemployee.h"
#include <QMessageBox>
#include "employees.h"
#include <QValidator>
#include <QRegExp>
AddEmployee::AddEmployee(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddEmployee)
{
  ui->setupUi(this);
  ui->CIN_Employee_text->setMaxLength(8);
  ui->CIN_Employee_text->setValidator(new QRegExpValidator(QRegExp("[0-9]*")));
  ui->Age_Employee_text->setMaxLength(3);
  ui->Age_Employee_text->setValidator(new QRegExpValidator(QRegExp("\\w")));
  ui->Name_Employee_text->setValidator(new QRegExpValidator(QRegExp("\\w")));
  ui->Address_Employee_text->setValidator(new QRegExpValidator(QRegExp("\\w|\\b")));
  ui->Email_Employee_text->setValidator(new QRegExpValidator(QRegExp("^[\\w-\\.]+@([\\w-]+\\.)+[\\w-]{2,4}$")));
}

AddEmployee::~AddEmployee()
{
  delete ui;
}

void AddEmployee::on_AddEmployeeButton_clicked()
{
  //sound->play();
  Employees e;

  e.setCin(ui->CIN_Employee_text->text());
  e.setFull_Name(ui->Name_Employee_text->text());
  e.setAge(ui->Age_Employee_text->text().toUInt());
  e.setAddress(ui->Address_Employee_text->text());
  e.setEmail(ui->Email_Employee_text->text());

  if (e.search_Employee(ui->CIN_Employee_text->text())){
  if (e.add_employee()){
      QMessageBox::information(this, "Add Employee", "The employee added successfully", QMessageBox::Ok);
    }
  else{
   // QMessageBox::warning(this, "Warning", "An unknow error",QMessageBox::Ok);
for (int i=0;i<3;i++);
    }
    }
  else {
      if (e.update_employee()){
          QMessageBox::information(this, "update Employee", "The Employee info is successfully changed", QMessageBox::Ok);
        }
      else
        for (int i=0;i<3;i++);
       // QMessageBox::warning(this, "Warning", "An unknow error",QMessageBox::Ok);
    }
}

void AddEmployee::on_AddEmployeeButton_2_clicked()
{
    close();
}
