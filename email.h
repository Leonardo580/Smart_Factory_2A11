#ifndef EMAIL_H
#define EMAIL_H

#include <QDialog>
#include "src/SmtpMime"
#include <QNetworkProxy>
namespace Ui {
  class Email;
}

class Email : public QDialog
{
  QString host, sender, to, subject, text, password;
  int port;
  Q_OBJECT

public:
  explicit Email(QString host, int port, QString sender,QString password ,QString to, QWidget *parent = nullptr);
  Email(QString host, int port ,QString sender,QString password ,QString to) ;
  bool sendEmail();
  ~Email();

private slots:
  void on_buttonBox_accepted();

private:
  Ui::Email *ui;
};

#endif // EMAIL_H
