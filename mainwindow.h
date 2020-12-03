#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Publicite.h"
#include"Promo.h"
#include "QMediaPlayer"
#include "QMediaPlaylist"

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     void click();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();


    void on_pr_ajouter_clicked();

    void on_pr_supprimer_clicked();



    void on_tri_1_activated(const QString &arg1);



    void on_pushButton_clicked();



    void on_cher_cin_cursorPositionChanged(int arg1, int arg2);

    void on_cher_cin_2_cursorPositionChanged(int arg1, int arg2);


private:
    Ui::MainWindow *ui;
    Publicite pub;
    Promo pr;
    QMediaPlaylist* music1;
    QMediaPlayer* music;
};

#endif // MAINWINDOW_H
