#include "contrat.h"

contrat::contrat()
{
    num_contrat=0;
    date_signature=QDate(2000,01,01);
    periode=0;
    montant=0;
    matricule_ent=0;
}
contrat::contrat(int num_contrat,QDate date_signature,int periode,double montant,int matricule_ent)
{
    this->num_contrat=num_contrat;
    this->date_signature=date_signature;
    this->periode=periode;
    this->montant=montant;
    this->matricule_ent=matricule_ent;
}

int contrat::getNumContrat(){
    return num_contrat;
}
void contrat::setNumContrat(int num_contrat){
    this->num_contrat=num_contrat;
}
QDate contrat::getDate_Signature(){
    return date_signature;
}
void contrat::setDate_Signature(QDate date_signature){
    this->date_signature=date_signature;
}
int contrat::getPeriode(){
    return periode;
}
void contrat::setPeriode(int periode){
    this->periode=periode;
}
double contrat::getMontant(){
    return montant;
}
void contrat::setMontant(double montant){
    this->montant=montant;
}
int contrat::getMatriculeEnt(){
    return matricule_ent;
}
void contrat::setMatriculeEnt(int matricule_ent){
    this->matricule_ent=matricule_ent;
}


bool contrat::ajouter(){
    QSqlQuery query;
    query.prepare("insert into contrat (num_contrat,date_signature,periode,montant,matricule_ent) values (:num_contrat,:date_signature,:periode,:montant,:matricule_ent)");
    query.bindValue(":num_contrat",num_contrat);
    query.bindValue(":date_signature",date_signature);
    query.bindValue(":periode",periode);
    query.bindValue(":montant",montant);
    query.bindValue(":matricule_ent",matricule_ent);

    return query.exec();

}
bool contrat::modifier(int num){
    QSqlQuery query;
    query.prepare("update contrat set num_contrat=:num_contrat,date_signature=:date_signature,periode=:periode,montant=:montant,matricule_ent=:matricule_ent where num_contrat=:num");
    query.bindValue(":num_contrat",num_contrat);
    query.bindValue(":date_signature",date_signature);
    query.bindValue(":periode",periode);
    query.bindValue(":montant",montant);
    query.bindValue(":matricule_ent",matricule_ent);
    query.bindValue(":num",num);

    return query.exec();
}

bool contrat::supprimer(int num){
    QSqlQuery q;
    q.prepare("select * from contrat where num_contrat=:num");
    q.bindValue(":num",num);
    q.exec();
    int total=0;
    while(q.next()){
        total++;
    }
    if(total==1){
        QSqlQuery query;
        query.prepare("delete from contrat where num_contrat=:num");
        query.bindValue(":num",num);

        return query.exec();
    }
    else{
        return false;
    }


}

QSqlQueryModel* contrat::afficher(){
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select num_contrat,date_signature,periode,montant,nom from contrat inner join entreprise on contrat.matricule_ent=entreprise.matricule");
   model->setHeaderData(0,Qt::Horizontal, QObject::tr("numero contrat"));
   model->setHeaderData(1,Qt::Horizontal, QObject::tr("date signature"));
   model->setHeaderData(2,Qt::Horizontal, QObject::tr("periode"));
   model->setHeaderData(3,Qt::Horizontal, QObject::tr("montant"));
   model->setHeaderData(4,Qt::Horizontal, QObject::tr("L'entreprise"));

   return model;
}


contrat contrat::getContrat(int num){
    QSqlQuery query;
    query.prepare("select * from contrat where num_contrat=:num");
    query.bindValue(":num",num);
    query.exec();
    contrat c;
    while(query.next()){
        c.setNumContrat(query.value(0).toInt());
        c.setDate_Signature(query.value(1).toDate());
        c.setPeriode(query.value(2).toInt());
        c.setMontant(query.value(3).toDouble());
        c.setMatriculeEnt(query.value(4).toInt());
    }
    return c;
}

QSqlQueryModel* contrat::recherche(QString str){
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select num_contrat,date_signature,periode,montant,nom from contrat inner join entreprise on contrat.matricule_ent=entreprise.matricule where nom like '"+str+"%' or montant like '"+str+"%' or num_contrat like '"+str+"%' or periode like '"+str+"%'");
   model->setHeaderData(0,Qt::Horizontal, QObject::tr("numero contrat"));
   model->setHeaderData(1,Qt::Horizontal, QObject::tr("date signature"));
   model->setHeaderData(2,Qt::Horizontal, QObject::tr("periode"));
   model->setHeaderData(3,Qt::Horizontal, QObject::tr("montant"));
   model->setHeaderData(4,Qt::Horizontal, QObject::tr("L'entreprise"));

   return model;
}
