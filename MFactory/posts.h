#ifndef POSTS_H
#define POSTS_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
class Posts
{
  QString CIN, Job_Desc;
  double Salary, Benefits, Hours_worked;
  int id;
public:
  Posts();
  Posts(int id, QString CIN, QString Job_Desc, double Salary, double Benefits, double Hours_Worked);

  QString getCIN() const;
  QString getJob_Desc() const;
  double getSalary() const;
  double getBenefits() const;
  double getHours_Worked() const;
  int getid() const;

  void setCIN(QString cin);
  void setJob_Desc(QString job_dec);
  void setSalary(double salary);
  void setBenefits(double benefits);
  void setHours_Worked(double hours);
  void setid(int id);

  bool add_Posts();
  bool remove_Posts(int id);
  bool remove_Posts();
  bool update_Posts();
};

#endif // POSTS_H
