#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "smtp.h"
login::login(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::login)
{
  ui->setupUi(this);


  db.setDatabaseName(QString("Source_Projet2A"));
  db.setUserName("Anas");
  db.setPassword("esprit20");
  if(!db.open()) {
    QMessageBox::warning(this, tr("MFactory"), tr("Unable to open database"), QMessageBox::Ok);
    }
  else {
  ui->label_7->setText("Status: Connected");
    }
  verif=0;
}

bool login::log()
{
  QSqlQuery query;
  query.prepare("select * from employees where (email=? and cin=?);");
  query.addBindValue(QVariant(ui->USER_text->text()));
  query.addBindValue(QVariant(ui->Password_text->text()));
  query.exec();
  query.first(); 
  return query.value(0).toString()!="";
}

login::~login()
{

  delete ui;
}

void login::on_DeleteEmployee_button_2_clicked()
{
 if (log())
   {this->hide();
    db.close();
    MainWindow *w=new MainWindow;
    w->show();
   }
 else {
     QMessageBox::information(this,"error","user name or password is invalid");
     verif++;
   }
 if(verif==4)
 {
     Smtp* smtp = new Smtp("anas.benbrahim@esprit.tn", "191JMT4743", "smtp.gmail.com", 465);

     connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));



     smtp->sendMail("anas.benbrahim@esprit.tn","mohamedamine.mehrez@esprit.tn","alert","Quelqu'un veut entrer a ton application");
     verif=0;
 }

}

