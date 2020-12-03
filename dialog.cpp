#include "dialog.h"
#include "ui_dialog.h"
#include "mailing/SmtpMime"
#include <QMessageBox>
#include <QApplication>
#include "mainwindow.h"
#include "Promo.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_envoyeymail_clicked()
{
    MainWindow w;
    w.click();
        SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);




                    smtp.setUser("aziz.farjallah@esprit.tn");
                    smtp.setPassword("191JMT3394");



            MimeMessage message;

            message.setSender(new EmailAddress("aziz.farjallah@esprit.tn", "Aziz Farjallah"));
            message.addRecipient(new EmailAddress(ui->le_mail->text(), "Recipient's name"));
            message.setSubject(ui->le_object->text());



            MimeText text;

            text.setText(ui->le_msgmail->toPlainText());



            message.addPart(&text);

            smtp.connectToHost();
            smtp.login();
            if (smtp.sendMail(message)){
               QMessageBox::information(this, "OK", "email envoyé");
            }
            else{
               QMessageBox::critical(this, "Erreur","email non envoyé");
            }
            smtp.quit();
}
