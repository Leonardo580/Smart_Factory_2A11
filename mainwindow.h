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
#include <QLabel>
#include <QList>
#include <QLayout>
#include <QPushButton>
#include <QPrinter>
#include <QFileDialog>
#include <QSystemTrayIcon>
#include <QTextDocument>
#include <QFontDialog>
#include <QTranslator>
#include <QNetworkConfigurationManager>
#include <QRadioButton>
#include<QtPrintSupport/QPrinter>
#include<QPdfWriter>
#include <QPainter>
#include<QFileDialog>
#include<QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include<QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include <QMessageBox>
#include<QUrl>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include <QPrintDialog>
#include <QVideoWidget>
#include "QMediaPlayer"
#include "QMediaPlaylist"
#include "email.h"
#include "QSound"
#include "employees.h"
#include "posts.h"
#include "src/SmtpMime"
#include "arduino.h"
#include "Publicite.h"
#include"Promo.h"
#include "login.h"
#include"entreprise.h"
#include"notification.h"
#include"contrat.h"
#include "client.h"
#include "commande.h"
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
   void click();
  ~MainWindow();
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





  void on_pushButton_6_clicked();

  void on_actionChoose_font_triggered();

  void on_pushButton_7_clicked();

  ProvideContextMenu( const QPoint &);

  void avgPosts();
  void sumPosts();


 // void on_actionFalse_Alarm_triggered();

  void on_HR_clicked();

  void on_actionReturn_to_main_triggered();


  void on_pb_ajouter_clicked();

      void on_pb_supprimer_clicked();

      void on_pb_modifier_clicked();


      void on_pr_ajouter_clicked();

      void on_pr_supprimer_clicked();



      void on_tri_1_activated(const QString &arg1);
      void on_cher_cin_cursorPositionChanged(int arg1, int arg2);

          void on_cher_cin_2_cursorPositionChanged(int arg1, int arg2);

          void on_aziz_clicked();


          void on_pushButton_9_clicked();

          void on_pushButton_10_clicked();

          void on_ajouter_ent_clicked();

          void on_modifier_ent_clicked();

          void on_supprimer_ent_clicked();

          void on_matricule_ent_textChanged(const QString &arg1);

          void on_tabWidget_currentChanged(int index);

          void on_ajouter_contrat_clicked();

          void on_supprimer_contrat_clicked();

          void on_num_contrat_textChanged(const QString &arg1);

          void on_modifier_contrat_clicked();

          void on_recherche_contrat_textChanged(const QString &arg1);

          void on_pdf_contrat_clicked();


          void on_anas_clicked();



          void on_ajouterclient_clicked();

              void on_modifierclient_clicked();

              void on_supprimerclient_clicked();

              void on_pushButton_imp_clicked();

              void on_pushButton_RC_clicked();

              void on_ajoutercommande_clicked();

              void on_modifiercommande_clicked();

              void on_supprimercommande_clicked();

              void on_tabstats_tabBarClicked(int index);

              void on_comboBoxclient_activated(const QString &arg1);





          void on_HR_2_clicked();

private:
  void on_comboBox_2_activated(int index=0);
   Ui::MainWindow *ui;
   QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");
   QSqlQueryModel *m=new QSqlQueryModel;
   QSound *sound= new QSound(QString(":/new/prefix1/Resources/button1.wav"));
   QMediaPlayer *mu= new QMediaPlayer();
   Employees em;
   Posts po;
   Arduino ar;
   Publicite pub;
   Promo pr;
   QMediaPlaylist* music1;
   QMediaPlayer* music;
   entreprise tmpentreprise;
   contrat tmpcontrat;
   notification n;
   QMediaPlayer * bulletsound;
   commande com;
   Client ctmp;
};
#endif // MAINWINDOW_H
