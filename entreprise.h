#ifndef ENTREPRISE_H
#define ENTREPRISE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QVariant>
#include"contrat.h"

class entreprise
{
    int matricule;
    QString nom;
    QString location;
    QString email;


    contrat tmpcontrat;
public:
    entreprise();
    entreprise(int,QString,QString,QString);
    ~entreprise();
    int getMatricule();
    void setMatricule(int);
    QString getNom();
    void setNom(QString);
    QString getLocation();
    void setLocation(QString);
    QString getEmail();
    void setEmail(QString);

    bool ajouter();
    bool modifier(int);
    QSqlQueryModel* afficher();
    bool supprimer(int);
    entreprise getEntreprise(int);

    QStringList getListEntreprise();

};

#endif // ENTREPRISE_H
