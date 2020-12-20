#include"Promo.h"

#include <QApplication>
#include <QString>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDebug>
#include "QMessageBox"

Promo :: Promo()
{

        cin=0;
        pourcentage=0;
        nom="";
       dateDebut=dateDebut.currentDate();
       dateFin=dateFin.currentDate();

}

Promo :: Promo (int cin ,int pourcentage, QString nom,  QDate dateDebut, QDate dateFin)
{

   this->cin=cin;
    this->pourcentage=pourcentage;

    this->nom=nom;
    this->dateDebut=dateDebut;
    this->dateFin=dateFin;
}

bool Promo :: ajouterpromo(){

    QSqlQuery query;
    QString cin_st = QString::number(cin);
    QString pourcentage_st = QString:: number(pourcentage);


          query.prepare("INSERT INTO Promo (cin, pourcentage,nom,dateDebut,dateFin) "
                        "VALUES (:cin,:pourcentage, :nom,:dateDebut,:dateFin)");
          query.bindValue(":cin", cin_st);
          query.bindValue(":pourcentage", pourcentage_st);
          query.bindValue(":nom", nom);
          query.bindValue(":dateDebut", dateDebut);
          query.bindValue(":dateFin", dateFin);

          return query.exec();
}

QSqlQueryModel* Promo:: getAllpromo()
{
    QSqlQueryModel* model= new QSqlQueryModel();

         model->setQuery("SELECT * FROM Promo");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Pourcentage"));

    return model;
}

bool Promo::supprimerpromo(int cin)
 {
     QSqlQuery q;
     q.prepare("DELETE from Promo where cin=:cin");
     q.bindValue(":cin",cin);
     q.exec();
     if(q.exec())
     {
         qDebug()<<"promotion supprimer";
         QMessageBox::information(nullptr, QObject::tr("promotion un publicitaire"),
                                  QObject::tr(" promotion supprimé.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return true;
     }
     else
         {
         qDebug()<<"Promotion blcin";
         QMessageBox::information(nullptr, QObject::tr("supprimer une promotion"),
                                  QObject::tr(" promotion blcin.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return false;
     }

 }
bool Promo::modifierpromo(int cin)
{
    QString cin_st = QString::number(cin);
    QString pourcentage_st = QString:: number(pourcentage);
    QDate dtDebut= this->dateDebut;
    QDate dtFin=this->dateFin;

    QSqlQuery q;
    q.prepare("UPDATE Promo  SET cin =:cin ,pourcentage =:pourcentage,nom =:nom, Date_Debut =:date_Debut, date_Fin =:date_Fin where (cin=:cin)");

    q.bindValue(":cin",cin_st);
    q.bindValue(":pourcentage", pourcentage_st);
    q.bindValue(":nom",this->nom);
    q.bindValue(":date_Debut",dtDebut);
    q.bindValue(":date_Fin",dtFin);


q.exec();
if(q.exec())
    return true;
return false ;

}


QSqlQueryModel * Promo::chercherPromopourcentage(int pourcentage)
{
    QSqlQuery q;
    q.prepare("SELECT * from Promo where pourcentage=:pourcentage");
    q.bindValue(":pourcentage",pourcentage);
    q.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(q);
    return model;
}
QSqlQueryModel * Promo::chercherPromonom( QString nom)
{
    QSqlQuery q;
    q.prepare("SELECT * from Promo where nom=:nom");
    q.bindValue(":nom",nom);
    q.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(q);
    return model;
}
