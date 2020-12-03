#ifndef PROMO_H
#define PROMO_H


#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Promo
{

private:

    int cin;// id
    int pourcentage;  // pourcentage

      QString nom; // nom promo
    QDate dateDebut; // dateDebut
    QDate dateFin; // dateDebut


public:

   Promo (int cin ,int pourcentage, QString nom,  QDate dateDebut, QDate dateFin);
   Promo();

   int getcin(){return cin ;}
   int getpourcentage(){return pourcentage ;}

    QString getnom(){return nom ;}
    QDate getdateDebut(){return dateDebut ;}
    QDate getdateFin(){return dateFin ;}

    void setcin(int cin){this->cin=cin;}
    void setpourcentage(int pourcentage){this->pourcentage=pourcentage;}

    void setnom(QString nom){this->nom=nom;}
    void setdateDebut(QDate dateDebut){this->dateDebut=dateDebut;}
    void setdateFin(QDate dateFin){this->dateFin=dateFin;}



    Promo getpromo(int cin);

    bool ajouterpromo();

    bool supprimerpromo(int cin);
    bool modifierpromo(int cin);

    QSqlQueryModel* chercherPromopourcentage(int pourcentage);
    QSqlQueryModel* chercherPromonom(QString nom);


    QSqlQueryModel* getAllpromocin();
    QSqlQueryModel* getAllpromo();


};

#endif // PROMO_H

