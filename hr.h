#ifndef HR_H
#define HR_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSqlQueryModel>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCore>
#include <QTcpSocket>
#include <QSslSocket>
#include <QNetworkProxy>
#include <QtMath>
#include "QSound"
#include "employees.h"
#include "posts.h"
#include "src/SmtpMime"
#include "arduino.h"
QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui { class HR; }
QT_END_NAMESPACE

class HR : public QMainWindow
{
  Q_OBJECT

public:
  HR(QWidget *parent = nullptr);
  void Stat();
  void animation_button(QPushButton* b);

  ~HR();
private slots:

  //void on_addnew_clicked();
  //void on_search_clicked();
  void arduino_output();


  //void on_AddEmployee_clicked();

  void on_DeleteEmployee_clicked();
  void display_Employee();

  void on_AddEmployeeButton_clicked();

  void on_UpdateEmployee_clicked();

  void on_Search_line_editingFinished();

  void on_tabWidget_tabBarClicked(int index=3);

  void on_tableView_2_activated(const QModelIndex &index);

  void on_pushButton_clicked();

  void on_comboBox_activated(int index);

  void on_DeletePosts_clicked();

  void on_pushButton_3_clicked();

  void on_tableViewPost_activated(const QModelIndex &index);

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_5_clicked();

  void on_actionLight_triggered();

  void on_actionDark_triggered();



private:
  void on_comboBox_2_activated(int index=0);
  Ui::HR *ui;
  QSqlQueryModel *m=new QSqlQueryModel;
  QSound *sound= new QSound(QString("://button1.wav"));
  Employees em;
  Posts po;
  Arduino ar;

};
#endif // HR_H