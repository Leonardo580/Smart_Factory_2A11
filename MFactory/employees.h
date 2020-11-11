#ifndef EMPLOYEES_H
#define EMPLOYEES_H
#include <QVariant>
#include <QtSql/QSqlQuery>
#include <QString >
class Employees
{
  QString CIN, Full_Name, Address, Email ;
  unsigned int Age;
public:
  Employees();
  Employees(QString const & cin,QString const & name,QString const & address,QString const & email,unsigned int age): CIN(cin),
    Full_Name(name),Address(address), Email(email), Age(age){};

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

  bool add_employee();
  bool remove_employee(QString cin);
  bool remove_employee();
  bool update_employee();
  bool search_Employee(QString cin);

 // ~Employees();
};

#endif // EMPLOYEES_H
