#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"Publicite.h"
#include"dialog.h"
#include<QMessageBox>
#include <QDoubleValidator>
#include <QDebug>
#include<QDesktopServices>
#include<QSystemTrayIcon>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include<QSound>
#include<QSqlError>
#include "QMediaPlayer"
#include<QtPrintSupport/QPrintDialog>
#include<QPrinter>

#include <QCoreApplication>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


      ui->tab_pub->setModel(pub.getAllPublicite());
       ui->tab_pub_2->setModel(pub.getAllPublicite());
       ui->tab_promo->setModel(pr.getAllpromo());
        ui->tab_promo_2->setModel(pr.getAllpromo());
       music1 =new QMediaPlaylist();
      music1->addMedia(QUrl("qrc:/music.mp3"));
       music1->setPlaybackMode(QMediaPlaylist::Loop);
       music = new QMediaPlayer();
       music->setPlaylist(music1);
       music->setVolume(1);
       music->play();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete music;

}
void MainWindow::click()
{

    QMediaPlayer * music =new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Click2.mp3"));
    music->play();
}

void MainWindow::on_pb_ajouter_clicked()
{

    int cin=ui->le_cin->text().toInt();
    float prix  = ui->le_prix->value();

    int duree = ui->le_duree->text().toInt();
    QString type= ui->le_type->currentText();
    QString chaine = ui->le_chaine->text();
    QString nom= ui->le_nom->text();


  Publicite pub(cin,nom,prix,duree,type,chaine);




  if ((cin!=0)&&(prix!=0)&&(duree!=0)&&(type!="Select")&&(chaine!="")&&(nom!=""))
  {

   bool test = pub.ajouterPublicite();
    if(test)

    {
       click();
       QMessageBox::information(nullptr,("Ajout Publicitaire"),("publicitaire ajouté"));
       ui->tab_pub->setModel(pub.getAllPublicite());
    }
    else
     {
       QMessageBox::warning(nullptr,("Ajout Publicitaire"),("Publicitaire non ajouté"));
     }
   }

   else QMessageBox::warning(nullptr,("Ajout Publicitaire"),("pas de données"));

}
void MainWindow::on_pb_supprimer_clicked()
{
    Publicite*q=new Publicite();
       q->supprimerPublicite(ui->le_cin_supp->text().toInt());
 ui->tab_pub->setModel(pub.getAllPublicite());
}



void MainWindow::on_pb_modifier_clicked()
{
    //QSound bts("C:/Users/Desktop/interface_pub/sound.wav");
       // bts.play();

    int cin= ui->cin_mod->text().toInt();
    QString nom= ui->nom_mod->text();
    float prix= ui->prix_mod->text().toFloat();
    int duree=ui->duree_mod->text().toInt();
    QString type = ui->type_mod->currentText();
    QString chaine = ui->chaine_mod->text();

    Publicite *p=new Publicite( cin,nom,prix,duree,type,chaine);
    bool test= p->modifierPublicite(cin);



  if(test)
  {
     ui->tab_pub->setModel(pub.getAllPublicite());//refresh
     ui->tab_pub_2->setModel(pub.getAllPublicite());//refresh
QMessageBox::information(nullptr, QObject::tr("Modifier un Publicitaire"),
                  QObject::tr("Publicitaire Modifié.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
ui->cin_mod->clear();
ui->nom_mod->clear();
ui->prix_mod->clear();
ui->duree_mod->clear();
ui->type_mod->clear();
ui->chaine_mod->clear();
}
  else
      QMessageBox::critical(nullptr, QObject::tr("Modifier un Publicitaire"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::on_pr_ajouter_clicked()
{
    int cin=ui->le_cinn->text().toInt();
    int pourcentage= ui->le_pourcentage->text().toInt();

  QString nom=ui->le_nompr->text();
QString dtDebut = ui->le_dateDebut->text();
QDate dateDebut= QDate :: fromString(dtDebut,"dd/mm/yyyy");
 QString dtFin= ui->le_dateFin->text();
 QDate dateFin= QDate :: fromString(dtFin,"dd/mm/yyyy");


Promo pr(cin,pourcentage,nom,dateDebut,dateFin);


 pr.ajouterpromo();
 ui->tab_promo->setModel(pr.getAllpromo());
}

void MainWindow::on_pr_supprimer_clicked()
{
    Promo*q=new Promo();
       q->supprimerpromo(ui->le_cinn_supp->text().toInt());
 ui->tab_promo->setModel(pr.getAllpromo());
}



void MainWindow::on_tri_1_activated(const QString &arg1)
{

 if (arg1=="Cin")
 {
  if (ui->radioButton_7->isChecked())
  {
       ui->tab_tri->setModel(pub.getAllPublicitecin());
      click();
  }
  if (ui->radioButton_8->isChecked())
  {
       ui->tab_tri->setModel(pub.getAllPublicitecin_2());
      click();
  }
 }

 else if (arg1=="Nom")
 {
  if (ui->radioButton_7->isChecked())
  {
       ui->tab_tri->setModel(pub.getAllPublicitenom());
      click();
  }
  if (ui->radioButton_8->isChecked())
  {
       ui->tab_tri->setModel(pub.getAllPublicitenom_2());
      click();
  }
 }

  else if (arg1=="Duree")
  {
   if (ui->radioButton_7->isChecked())
   {
        ui->tab_tri->setModel(pub.getAllPubliciteduree());
       click();
   }
   if (ui->radioButton_8->isChecked())
   {
        ui->tab_tri->setModel(pub.getAllPubliciteduree_2());
       click();
   }
  }
 else if (arg1=="Prix")
 {
  if (ui->radioButton_7->isChecked())
  {
       ui->tab_tri->setModel(pub.getAllPubliciteprix());
      click();
  }
  if (ui->radioButton_8->isChecked())
  {
       ui->tab_tri->setModel(pub.getAllPubliciteprix_2());
      click();
  }
 }

 else if (arg1=="Type")
  {
   if (ui->radioButton_7->isChecked())
   {
        ui->tab_tri->setModel(pub.getAllPublicitetype());
       click();
   }
   if (ui->radioButton_8->isChecked())
   {
        ui->tab_tri->setModel(pub.getAllPublicitetype_2());
       click();
   }
  }
 else if (arg1=="Chaine")
   {
    if (ui->radioButton_7->isChecked())
    {
         ui->tab_tri->setModel(pub.getAllPublicitechaine());
        click();
    }
    if (ui->radioButton_8->isChecked())
    {
         ui->tab_tri->setModel(pub.getAllPublicitechaine_2());
        click();
    }
}

}




void MainWindow::on_pushButton_clicked()
{
    click();
    Dialog d;
    d.exec();

}



void MainWindow::on_cher_cin_cursorPositionChanged(int arg1, int arg2)
{
    if (ui->radioButton_4->isChecked())
    {
        int cin = ui->cher_cin->text().toInt();


             ui->tab_pub_2->setModel(pub.chercherPublicite(cin));
        click();
    }

   if (ui->radioButton_5->isChecked())
    {
       QString nom = ui->cher_cin->text();


            ui->tab_pub_2->setModel(pub.chercherPublicitenom(nom));
       click();
    }

     if (ui->radioButton_6->isChecked())
    {
         QString type = ui->cher_cin->text();


              ui->tab_pub_2->setModel(pub.chercherPublicitetype(type));
         click();
    }

}

void MainWindow::on_cher_cin_2_cursorPositionChanged(int arg1, int arg2)
{


   if (ui->radioButton_10->isChecked())
    {
       QString nom = ui->cher_cin_2->text();


            ui->tab_promo_2->setModel(pr.chercherPromonom(nom));
       click();
    }

     if (ui->radioButton_13->isChecked())
    {
         int pourcentage = ui->cher_cin_2->text().toInt();


              ui->tab_promo_2->setModel(pr.chercherPromopourcentage(pourcentage));
         click();
    }
}



