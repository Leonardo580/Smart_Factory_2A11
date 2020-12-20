#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include <QVariant>
#include <QtSql/QSqlQuery>
#include <QString >
#include <QSqlQueryModel>
#include <QDebug>
#include "email.h"
class Employees
{
  QString CIN, Full_Name, Address, Email ;
  unsigned int Age, id;
public:
  Employees();
  Employees(QString const & cin,QString const & name,QString const & address,QString const & email,unsigned int age, unsigned int Id)
    : CIN(cin),Full_Name(name),Address(address), Email(email), Age(age), id(Id){};

  QString getCin() const;
  QString getFull_Name() const;
  QString getAddress() const;
  QString getEmail() const;
  unsigned int getAge() const;

  void setCin(QString const cin) ;
  void setFull_Name(QString const name);
  void setAddress(QString const address) ;
  void setEmail(QString const email) ;
  void setAge(unsigned int age);
  void setId(unsigned int i);

  bool add_employee();
  bool remove_employee(QString cin);
  bool remove_employee();
  bool update_employee();
  bool search_Employee(QString cin);
  QSqlQueryModel * display_Employee() ;
  QSqlQueryModel* sort_employees(int index);
  void SendEmail(class Email e);
  ~Employees(){};
};

#endif // EMPLOYEES_H
