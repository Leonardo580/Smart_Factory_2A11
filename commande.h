#ifndef COMMANDE_H
#define COMMANDE_H
#include "client.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class commande
{
private:

    QString adresse,date_paiment,CINC,type;
    float prix,prixunitaire;
    int quantite;
public:
    commande();
      commande(QString,QString,QString,QString,int,float,float);
    void SetCIN(QString val){CINC=val;}
    QString GetCIN() {return CINC;}
    float Getprix() { return prix; }
            void Setprix(float val) { prix= val; }
            float Getprixunitaire() { return prixunitaire; }
                    void Setprixunitaire(float val) { prixunitaire= val; }
            QString Gettype() { return type; }
            void Settype(QString val) { type = val; }
            QString Getadresse() { return adresse; }
            void Setadresse(QString val) { adresse = val; }
            QString Getdate_paiment() { return date_paiment; }
            void Setdate_paiment(QString val) { date_paiment = val; }
            void Setquantite(int val){quantite=val;}
            int Getquantite(){return quantite;}
            bool ajouter();
            QSqlQueryModel*afficher();
            bool supprimer(QString);
};

#endif // COMMANDE_H
