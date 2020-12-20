#include "commande.h"

commande::commande()
{
    CINC="";
        adresse="";
            prix=0;
            quantite=0;
            type="";
            date_paiment="";
            prixunitaire=0;
}
commande::commande(QString CINC,QString type,QString adresse,QString date_paiment,int quantite,float prixunitaire,float prix)
{  this->prixunitaire=prixunitaire;
   this->CINC=CINC;
    this->type=type;
    this->prix=prix;
        this->quantite=quantite;
    this->adresse=adresse;
    this->date_paiment=date_paiment;}
bool commande::ajouter()
{ QSqlQuery query;
    QString res=QString::number(quantite);
    QString res2=QString::number(prixunitaire);
    QString res3=QString::number(prix);
    query.prepare("insert into commande(CINC,type,adresse,date_paiment,quantite,prixunitaire,prix)""values(:CINC,:type,:adresse,:date_paiment,:quantite,:prixunitaire,:prix)");
            query.bindValue(":CINC",CINC);
            query.bindValue(":type",type);
             query.bindValue(":adresse",adresse);
             query.bindValue(":date_paiment",date_paiment);
             query.bindValue(":quantite",res);
            query.bindValue(":prix",res3);
              query.bindValue(":prixunitaire",res2);


    return query.exec();

}
QSqlQueryModel* commande::afficher()
{QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from commande");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CINC"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("type"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("date_paiment"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("quantite"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("prixunitaire"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("prix"));
    return(model);

}
bool commande::supprimer(QString CINC)
{QSqlQuery query;
    query.prepare("Delete from commande where CINC= :CINC");
    query.bindValue(":CINC",CINC);
    return query.exec();

}
