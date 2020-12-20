#ifndef POSTS_H
#define POSTS_H

#include <QString>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>
#include <QDebug>
class Posts
{
  QString  Job_Desc;
  double Salary, Benefits, Hours_worked;
  int id;
public:
  Posts();
  Posts(int id, QString Job_Desc, double Salary, double Benefits, double Hours_Worked);


  QString getJob_Desc() const;
  double getSalary() const;
  double getBenefits() const;
  double getHours_Worked() const;
  int getid() const;


  void setJob_Desc(QString job_dec);
  void setSalary(double salary);
  void setBenefits(double benefits);
  void setHours_Worked(double hours);
  void setid(int id);

  bool add_Posts();
  bool remove_Posts(int id);
  bool remove_Posts();
  bool update_Posts();
  bool search_post(int id);
  QSqlQueryModel * search(const QString& id);
  QSqlQueryModel * display_Posts();
};

#endif // POSTS_H
