#ifndef CONTRAT_H
#define CONTRAT_H
#include<QDate>
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QVariant>

class contrat
{
    int num_contrat;
    QDate date_signature;
    int periode;
    double montant;
    int matricule_ent;
public:
    contrat();
    contrat(int,QDate,int,double,int);

    int getNumContrat();
    void setNumContrat(int num_contrat);
    QDate getDate_Signature();
    void setDate_Signature(QDate date_signature);
    int getPeriode();
    void setPeriode(int periode);
    double getMontant();
    void setMontant(double montant);
    int getMatriculeEnt();
    void setMatriculeEnt(int matricule_ent);

    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    QSqlQueryModel *afficher();
    contrat getContrat(int);
    QSqlQueryModel *recherche(QString);

};

#endif // CONTRAT_H
