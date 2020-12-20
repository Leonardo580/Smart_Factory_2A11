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
  SmtpClient smtp(host, port , SmtpClient::SslConnection);
  smtp.setUser(sender);
  smtp.setPassword(password);
  //smtp.getSocket()->setProxy(QNetworkProxy::NoProxy);
 //smtp.setAuthMethod(SmtpClient::AuthLogin);
  MimeMessage message;
  EmailAddress send (sender,sender.section('@',0, 0));

  message.setSender(&send);
  if (to.isEmpty()) to=ui->to_text->text();
  EmailAddress to2(to, to.section('@', 0, 0));
  message.addRecipient(&to2);
  message.setSubject(subject);
  MimeText text;
  text.setText(Email::text);
  message.addPart(&text);
  if(!smtp.connectToHost()){
      qDebug() << "failed to connect to the host\n";
      return false;
    }
  if (!smtp.login()){
      qDebug()<< "failed to login\n";
      return false;
    }
  if (!smtp.sendMail(message)){
      qDebug() << "failed to send message\n";
      return false;
    }
  smtp.quit();
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
