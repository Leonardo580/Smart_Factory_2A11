#include "employees.h"

Employees::Employees()
{
  CIN=Full_Name=Address=Email="";
  Age=0;
}

QString Employees::getCin() const
{
  return CIN;
}

QString Employees::getFull_Name() const{
  return Full_Name;
}

QString Employees::getAddress() const
{
  return Address;
}

QString Employees::getEmail() const
{
  return Email;
}

unsigned int Employees::getAge() const
{
  return Age;
}

void Employees::setCin(const QString cin)
{
  CIN=cin;
}

void Employees::setFull_Name(const QString name)
{
  Full_Name=name;
}

void Employees::setAddress(const QString address)
{
  Address=address;
}

void Employees::setEmail(const QString email)
{
  Email=email;
}

void Employees::setAge(unsigned int age)
{
  Age=age;
}

bool Employees::add_employee()
{
  QSqlQuery query;
  QString age=QString::number(getAge());
  query.prepare("INSERT INTO Employees(CIN, Full_Name,Age,  Address, Email) values "
                "(:CIN, :Full_Name,:Age,  :Address, :Email);");
  query.bindValue(":CIN",QVariant(CIN));
  query.bindValue(":Full_Name",QVariant(Full_Name));
  query.bindValue(":Age",QVariant(age));
  query.bindValue(":Address",QVariant(Address));
  query.bindValue(":Email",QVariant(Email));
  return query.exec();

}

bool Employees::remove_employee(QString cin)
{
  QSqlQuery query;
  query.prepare("Delete from Employees where (CIN=:cin); ");
  query.bindValue(":cin",QVariant(cin));
  return query.exec();
}

bool Employees::remove_employee()
{
  QSqlQuery query;
  query.prepare("Delete from Employees where (CIN=:cin);");
  query.bindValue(":cin",QVariant(CIN));
  return query.exec();
}

bool Employees::update_employee()
{
  QSqlQuery query;
  QString age=QString::number(getAge());
  query.prepare("Update Employees set Full_Name=:Full_Name, Age=:Age, Address=:Address, Email=:Email where (CIN=:CIN);");
  query.bindValue(":Full_Name",QVariant(Full_Name));
  query.bindValue(":Age",QVariant(age));
  query.bindValue(":Address",QVariant(Address));
  query.bindValue(":Email",QVariant(Email));
  query.bindValue(":CIN",QVariant(CIN));
  return query.exec();

}

bool Employees::search_Employee(QString cin)
{
  QSqlQuery query;
  query.prepare("select * from Employees where (CIN=:cin);");
  query.bindValue(":cin", QVariant(cin));
  query.exec();
  query.first();
  return query.value(0).toString()==cin;

}


QSqlQueryModel * Employees::display_Employee()
{
  QSqlQueryModel *query=new QSqlQueryModel();
  query->setQuery("Select * from Employees");
  query->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
  query->setHeaderData(1,Qt::Horizontal,"Full Name");
  query->setHeaderData(2,Qt::Horizontal,"Age");
  query->setHeaderData(3,Qt::Horizontal,"Address");
  query->setHeaderData(4,Qt::Horizontal,"Email");
  return query;

}

QSqlQueryModel *Employees::sort_employees(int index)
{
  QSqlQueryModel *model = new QSqlQueryModel;
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
  model->setHeaderData(1,Qt::Horizontal,"Full Name");
  model->setHeaderData(2,Qt::Horizontal,"Age");
  model->setHeaderData(3,Qt::Horizontal,"Address");
  model->setHeaderData(4,Qt::Horizontal,"Email");

    switch (index) {
      case 0:
        model=display_Employee();
        break;
      case 1:
         model->setQuery("select * from Employees order by CIN ASC;");
        break;
      case 2:
         model->setQuery("select * from Employees order by Full_Name ASC;");
        break;
      case 3:
         model->setQuery("select * from Employees order by Age ASC;");
        break;
      }
    return model;

}

void Employees::SendEmail(class Email e)
{
  e.show();
  e.exec();
}



