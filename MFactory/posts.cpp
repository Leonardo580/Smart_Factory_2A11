#include "posts.h"

Posts::Posts()
{

}

Posts::Posts(int id, QString CIN, QString Job_Desc, double Salary, double Benefits, double Hours_Worked)
{
  Posts::id=id;
  Posts::CIN=CIN;
  Posts::Job_Desc=Job_Desc;
  Posts::Salary=Salary;
  Posts::Benefits=Benefits;
  Posts::Hours_worked=Hours_Worked;

}

QString Posts::getCIN() const
{
  return CIN;
}

QString Posts::getJob_Desc() const
{
  return Job_Desc;
}

double Posts::getSalary() const
{
  return Salary;
}

double Posts::getBenefits() const
{
  return Benefits;
}

double Posts::getHours_Worked() const
{
  return Hours_worked;
}

int Posts::getid() const
{
  return id;
}

void Posts::setCIN(QString cin)
{
  CIN=cin;
}

void Posts::setJob_Desc(QString job_dec)
{
  Job_Desc=job_dec;
}

void Posts::setBenefits(double benefits)
{
  Benefits=benefits;
}

void Posts::setHours_Worked(double hours)
{
  Hours_worked=hours;
}

void Posts::setid(int id)
{
  Posts::id=id;
}


void Posts::setSalary(double salary)
{
  Salary=salary;
}
bool Posts::add_Posts()
{
  QSqlQuery query;
  /*QString ID=QString::number(id);
  QString sal=QString::number(Salary);
  QString ben=QString::number(Benefits);
  QString Hour=QString::number(Hours_worked);*/
  query.prepare("INSERT INTO Posts(id, CIN,  Job_Desc,Salary, Benefits, Hours_Worked) values "
                "(:id, :CIN, :Job_Desc, :Salary, :Benefits, :Hours_Worked)");
  query.bindValue(":id",QVariant(id));
  query.bindValue(":CIN",QVariant(CIN));
  query.bindValue(":Job_Desc",QVariant(Job_Desc));
  query.bindValue(":Salary",QVariant(Salary));
  query.bindValue(":Benefits",QVariant(Benefits));
  query.bindValue(":Hours_Worked",QVariant(Hours_worked));
  return query.exec();
}

bool Posts::remove_Posts(int id)
{
  QSqlQuery query;
  query.prepare("Delete from Posts where id=:id ");
  query.bindValue(":id",QVariant(id));
  return query.exec();
}

bool Posts::remove_Posts()
{
  QSqlQuery query;
  query.prepare("Delete from Posts where id=:id ");
  query.bindValue(":id",QVariant(Posts::id));
  return query.exec();
}

bool Posts::update_Posts()
{
  QSqlQuery query;
  query.prepare("Update Posts set  id=:id, CIN=:CIN,  Job_Desc=:Job_Desc, Salary=:Salary, Benefits=:Benefits, "
                "Hours_Worked=:Hours_Worked where id=:id");
  query.bindValue(":id",QVariant(id));
  query.bindValue(":CIN",QVariant(CIN));
  query.bindValue(":Job_Desc",QVariant(Job_Desc));
  query.bindValue(":Salary",QVariant(Salary));
  query.bindValue(":Benefits",QVariant(Benefits));
  query.bindValue(":Hours_Worked",QVariant(Hours_worked));
  return query.exec();

}
