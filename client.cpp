#include "client.h"
Client::Client()
{   CIN="";
    adresse="";
        nom="";
        prenom="";
        numero="";
        date_naissance="";

}
Client::Client(QString CIN,QString nom,QString prenom,QString numero,QString adresse,QString date_naissance)
{
   this->CIN=CIN;
    this->nom=nom;
    this->prenom=prenom;
        this->numero=numero;
    this->adresse=adresse;
    this->date_naissance=date_naissance;
}
bool Client::ajouter()
{ QSqlQuery query;
    QString res= CIN;
    query.prepare("insert into Client(CIN,nom,prenom,adresse,numero,date_naissance)""values(:CIN,:nom,:prenom,:adresse,:numero,:date_naissance)");
            query.bindValue(":CIN",res);
            query.bindValue(":nom",nom);
            query.bindValue(":prenom",prenom);
              query.bindValue(":numero",numero);
            query.bindValue(":adresse",adresse);
            query.bindValue(":date_naissance",date_naissance);
    return query.exec();
}
QSqlQueryModel*Client::afficher()
{ QSqlQueryModel *model=new QSqlQueryModel();
   model->setQuery("select * from CLIENT");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("adresse"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("numero"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("date_naissance"));

return model;
}
bool Client::supprimer(QString CIN)
{QSqlQuery query;
    QString res=CIN;
    query.prepare("Delete from CLIENT where CIN= :CIN");
    query.bindValue(":CIN",res);
return query.exec();
}
QSqlQueryModel * Client::rechercher_3(QString CIN,QString adresse,QString numero)
{
    QMessageBox msgBox;
    QMessageBox msgBox1;

    QSqlQueryModel *model = new QSqlQueryModel;
    QSqlQuery query;
    int count=0;



    query.prepare("SELECT * FROM CLIENT WHERE CIN = ? and adresse= ?  and numero= ?");
    query.addBindValue(CIN);
    query.addBindValue(adresse);
    query.addBindValue(numero);



    if(query.exec() )

    {
while (query.next())
   { printf("éfretret");
   count ++;
}
if(count!=0)
   {
    msgBox.setText("Client existe");
    printf("1");
    msgBox.exec();
    model->setQuery(query);
}

else if (count==0)
{
    msgBox1.setText("Client n'existe pas");
       printf("0");
        msgBox1.exec();
        model=0;
}

    }





    return model;


}
