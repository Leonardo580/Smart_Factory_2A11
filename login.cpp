#include "login.h"
#include "ui_login.h"
#include "hr.h"
login::login(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::login)
{
  ui->setupUi(this);


  /*db.setDatabaseName(QString("Source_Projet2A"));
  db.setUserName("Anas");
  db.setPassword("esprit20");
  if(!db.open()) {
    QMessageBox::warning(this, tr("MFactory"), tr("Unable to open database"), QMessageBox::Ok);
    }
  else {
  ui->label_7->setText("Status: Connected");
    }*/
}

bool login::log()
{
  QSqlQuery query;
  query.prepare("select * from employees where (email=?);");
  query.addBindValue(QVariant(ui->USER_text->text()));
  query.exec();
  query.first();
  return query.value(0)!="";
}

login::~login()
{
  //db.close();
  delete ui;
}

void login::on_DeleteEmployee_button_2_clicked()
{
 /*if (log)
 this->hide();*/
}

