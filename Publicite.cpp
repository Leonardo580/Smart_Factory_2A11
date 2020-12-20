#include"Publicite.h"
#include <QApplication>
#include <QString>
#include <QSqlQueryModel>
#include<QSqlQuery>
#include <QDebug>
#include "QMessageBox"

Publicite :: Publicite()
{

         cin=0;
         prix=0;
         duree=0;
         type="";
         chaine="";
         nom="";
}

Publicite :: Publicite(int cin ,QString nom,float prix,int duree, QString type,  QString chaine)
{

   this->cin=cin;
    this->prix=prix;
    this->duree=duree;
    this->type=type;
    this->chaine=chaine;
    this->nom=nom;
}

bool Publicite :: ajouterPublicite(){

    QSqlQuery query;
    QString cin_st = QString::number(cin);
    QString prix_st = QString:: number(prix,'g',4);
    QString duree_st = QString:: number(duree);

          query.prepare("INSERT INTO Publicite (identifiant,nom, prix,duree,type,chaine) "
                        "VALUES (:cin,:nom, :prix,:duree,:type,:chaine)");
          query.bindValue(":cin", cin_st);
          query.bindValue(":nom", nom);
          query.bindValue(":prix", prix_st);
          query.bindValue(":duree", duree_st);
          query.bindValue(":type", type);
          query.bindValue(":chaine", chaine);

          return query.exec();


}
QSqlQueryModel* Publicite:: getAllPublicite()
{
    QSqlQueryModel* model= new QSqlQueryModel();

         model->setQuery("SELECT * FROM Publicite");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("NomPublicite"));

    return model;
}


bool Publicite::supprimerPublicite(int cin)
 {
     QSqlQuery q;
     q.prepare("DELETE from Publicite where identifiant=:cin");
     q.bindValue(":cin",cin);
     q.exec();
     if(q.exec())
     {
         qDebug()<<"Publicitaire supprimer";
         QMessageBox::information(nullptr, QObject::tr("supprimer un publicitaire"),
                                  QObject::tr(" publicitaire supprimé.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return true;
     }
     else
         {
         qDebug()<<"Publicitaire blcin";
         QMessageBox::information(nullptr, QObject::tr("supprimer un publicitaire"),
                                  QObject::tr(" publicitaire blcin.\n"
                                              "Click to cancel."), QMessageBox::Cancel);
         return false;
     }

 }

bool Publicite::modifierPublicite(int cin)
{
    QString cin_st = QString::number(cin);
    QString prix_st = QString:: number(prix,'g',4);
    QString duree_st = QString:: number(duree);
    QSqlQuery q;
    q.prepare("UPDATE Publicite  SET nom =:nom ,prix =:prix, duree =:duree, type =:type, chaine =:chaine where (identifiant=:cin)");

    q.bindValue(":cin",cin_st);
    q.bindValue(":nom", this->nom);
    q.bindValue(":chaine", this->chaine);
    q.bindValue(":type", this->type);
    q.bindValue(":prix", prix_st);
    q.bindValue(":duree", duree_st);
q.exec();
if(q.exec())
    return true;
return false ;

}





QSqlQueryModel * Publicite::chercherPublicite(int cin)
{
    QSqlQuery q;
    q.prepare("SELECT * from Publicite where identifiant=:cin");
    q.bindValue(":cin",cin);
    q.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(q);
    return model;

}
QSqlQueryModel * Publicite::chercherPublicitenom( QString nom)
{
    QSqlQuery q;
    q.prepare("SELECT * from Publicite where nom=:nom");
    q.bindValue(":nom",nom);
    q.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(q);
    return model;
}
QSqlQueryModel * Publicite::chercherPublicitetype( QString type)
{
    QSqlQuery q;
    q.prepare("SELECT * from Publicite where type=:type");
    q.bindValue(":type",type);
    q.exec();
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(q);
    return model;
}
Publicite Publicite::getPublicite(int cin)

 {
     Publicite *p = new Publicite();
    QSqlQuery q;
     q.prepare("SELECT * from Publicite where cin=:cin");
     q.bindValue(":cin",cin);
     q.exec();
     qDebug()<<cin;
     while (q.next()) {
         qDebug()<<q.value(1).toString();
         setcin(cin);
         setnom(q.value(3).toString());
         setprix(q.value(2).toInt());
         setduree(q.value(5).toInt());
         settype(q.value(1).toString());
         setchaine(q.value(4).toString());
         }
 return *p;
}
 QSqlQueryModel *Publicite::getAllPublicitecin()
 {
     QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT *  FROM  Publicite ORDER BY  idetifiant");
     return model;

 }
 QSqlQueryModel *Publicite::getAllPublicitecin_2()
 {
     QSqlQueryModel *model = new QSqlQueryModel();
     model->setQuery("SELECT *  FROM  Publicite ORDER BY  idetifiant DESC");
     return model;

 }
QSqlQueryModel *Publicite ::getAllPublicitenom()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  nom ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPublicitenom_2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  nom DESC");
    return model;

}
QSqlQueryModel *Publicite ::getAllPubliciteprix()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  prix ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPubliciteprix_2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  prix DESC ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPublicitetype()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  type ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPublicitetype_2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  type DESC ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPublicitechaine()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  chaine ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPublicitechaine_2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  chaine DESC");
    return model;

}


QSqlQueryModel *Publicite ::getAllPubliciteduree()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  duree ");
    return model;

}
QSqlQueryModel *Publicite ::getAllPubliciteduree_2()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT *  FROM  Publicite ORDER BY  duree DESC");
    return model;
}
