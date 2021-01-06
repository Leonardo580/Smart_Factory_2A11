#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
namespace Ui {
  class login;
}

class login : public QMainWindow
{
  Q_OBJECT

public:
  explicit login(QWidget *parent = nullptr);
  bool log();
  ~login();

private slots:
  void on_DeleteEmployee_button_2_clicked();

private:
  //QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");
  Ui::login *ui;
};

#endif // LOGIN_H
