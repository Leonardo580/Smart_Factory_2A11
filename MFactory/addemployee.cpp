#include "addemployee.h"
#include "ui_addemployee.h"

AddEmployee::AddEmployee(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AddEmployee)
{
  ui->setupUi(this);
}

AddEmployee::~AddEmployee()
{
  delete ui;
}
