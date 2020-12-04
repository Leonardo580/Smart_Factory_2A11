#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtSql/QSqlDatabase>
#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include "client.h"
#include "commande.h"
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <iostream>

#include <QMessageBox>

#include  <QDebug>

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

#include<QtSql/QSqlQuery>

#include<QVariant>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_pushButton_clicked();

    void on_supprimerchantier_clicked();



    void on_modifierchantier_clicked();

    void on_pushButton_2_clicked();

    void on_supprimerchantier_2_clicked();

    void on_modifierchantier_2_clicked();

    void on_pushButton_5_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_pushButton_4_clicked();

private:
    commande com;
    Client ctmp;
    Ui::MainWindow *ui;

    QSqlDatabase db= QSqlDatabase::addDatabase("QODBC");

};
#endif // MAINWINDOW_H
