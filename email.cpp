#include "email.h"
#include "ui_email.h"
#include <QMessageBox>
Email::Email(QString host, int port, QString sender,QString password ,QString to, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Email)
{
  Email::host=host;
  Email::port=port;
  Email::sender=sender;
  Email::to=to;
  Email::password=password;
  ui->setupUi(this);
  if (to!="")
    ui->to_text->setText(to);
}

Email::Email(QString host, int port, QString sender,QString password ,QString to )
{
  Email::host=host;
  Email::port=port;
  Email::sender=sender;
  Email::to=to;

  Email::password=password;
}

bool Email::sendEmail()
{

  Smtp* smtp = new Smtp("anas.benbrahim@esprit.tn", "191JMT4743", host, port);
  smtp->sendMail("anas.benbrahim@esprit.tn", ui->to_text->text(),subject, ui->Big_text->toPlainText());
  return true;
}

Email::~Email()
{
  delete ui;
}

void Email::on_buttonBox_accepted()
{
  subject=ui->subject_text->text();
  text=ui->Big_text->toPlainText();
  if (ui->to_text->text().isEmpty())
    { QMessageBox::warning(this, "Warning", "Recipient address must not be empty");
    return;
    }
  if (sendEmail())
   QMessageBox::information(this, "Success","The Email Sent Successfully");
  else
     QMessageBox::warning(this, "Error", "An Unknown Error");
}
