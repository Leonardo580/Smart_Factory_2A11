#ifndef MAINWINDOW_H
#define MAINWINDOW_H
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
QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  void Stat();
  void animation_button(QPushButton* b);
  ~MainWindow();

private slots:

  //void on_addnew_clicked();
  void on_search_clicked();



  //void on_AddEmployee_clicked();

  void on_DeleteEmployee_clicked();
  void display_Employee();

  void on_AddEmployeeButton_clicked();

  void on_DeleteEmployee_button_clicked();

  void on_DeleteEmployee_button_2_clicked();

  void on_AddEmployee_clicked();

  void on_UpdateEmployee_clicked();

  void on_Search_line_editingFinished();

  void on_tabWidget_tabBarClicked(int index);

  void on_tableView_2_activated(const QModelIndex &index);

  void on_pushButton_clicked();

  void on_comboBox_activated(int index);

private:
  Ui::MainWindow *ui;
  QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");
  QSqlQueryModel *m=new QSqlQueryModel;
  QSound *sound= new QSound(QString("://button1.wav"));
  Employees em;
  Posts po;
};
#endif // MAINWINDOW_H
