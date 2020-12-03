#ifndef PUBLICITE_H
#define PUBLICITE_H

#include <QDialog>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>



class Publicite
{

private:

    int cin;// id cin
    float prix;  // le prix de la publicité
    int duree; // duree de publicité
    QString type;   //type de publicité
    QString chaine; // nom du chaine
    QString nom; // nom du pub
public:

   Publicite (int cin ,QString nom,float prix,int duree, QString type,  QString chaine);

   Publicite();

    int getcin(){return cin;}
    float getprix(){return prix;}
    int getduree(){return duree;}
    QString gettype(){return type;}
    QString getchaine(){return chaine;}
    QString getnom(){return nom;}

    void setcin(int cin){this->cin=cin;}
    void setprix(float prix){this->prix=prix;}
    void setduree(int duree){this->duree=duree;}
    void settype(QString type){this->type=type;}
    void setchaine(QString chaine){this->chaine=chaine;}
    void setnom(QString nom){this->nom=nom;}

    Publicite getPublicite(int cin);

    bool modifierPublicite(int cin);
    bool ajouterPublicite();
    QSqlQueryModel* chercherPublicite(int cin);
    QSqlQueryModel* chercherPublicitenom(QString nom);
    QSqlQueryModel* chercherPublicitetype(QString type);
    bool supprimerPublicite(int);



    QSqlQueryModel* getAllPublicite();

    QSqlQueryModel* getAllPublicitecin();
    QSqlQueryModel* getAllPublicitecin_2();

    QSqlQueryModel* getAllPublicitenom();
    QSqlQueryModel* getAllPublicitenom_2();

    QSqlQueryModel* getAllPubliciteprix();
    QSqlQueryModel* getAllPubliciteprix_2();

    QSqlQueryModel* getAllPubliciteduree();
    QSqlQueryModel* getAllPubliciteduree_2();

    QSqlQueryModel* getAllPublicitetype();
    QSqlQueryModel* getAllPublicitetype_2();

    QSqlQueryModel* getAllPublicitechaine();
    QSqlQueryModel* getAllPublicitechaine_2();
};


#endif // PUBLICITE_H
