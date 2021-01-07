#include "entreprise.h"

entreprise::entreprise()
{
    matricule=0;
}

entreprise::entreprise(int matricule,QString nom,QString location,QString email){
    this->matricule=matricule;
    this->nom=nom;
    this->location=location;
    this->email=email;
}

entreprise::~entreprise(){}

int entreprise::getMatricule(){
    return matricule;
}

void entreprise::setMatricule(int matricule){
    this->matricule=matricule;
}

QString entreprise::getNom(){
    return nom;
}

void entreprise::setNom(QString nom){
    this->nom=nom;
}

QString entreprise::getLocation(){
    return location;
}

void entreprise::setLocation(QString location){
    this->location=location;
}

QString entreprise::getEmail(){
    return email;
}

void entreprise::setEmail(QString email){
    this->email=email;
}

bool  entreprise::ajouter(){
    QSqlQuery query;
    query.prepare("insert into entreprise (matricule,nom,location,email) values (:matricule,:nom,:location,:email)");
    query.bindValue(":matricule",matricule);
    query.bindValue(":nom",nom);
    query.bindValue(":location",location);
    query.bindValue(":email",email);

    return query.exec();
}

bool entreprise::supprimer(int matricule){
    QSqlQuery q;
    q.prepare("select * from entreprise where matricule=:matricule");
    q.bindValue(":matricule",matricule);
    q.exec();
    int total=0;
    while(q.next()){
        total++;
    }
    if(total==1){
        QSqlQuery qu;
        qu.prepare("select * from contrat where matricule_ent=:matricule");
        qu.bindValue(":matricule",matricule);
        qu.exec();
        while(qu.next()){
            tmpcontrat.supprimer(qu.value(0).toInt());
        }

        QSqlQuery query;
        query.prepare("delete from entreprise where matricule=:matricule");
        query.bindValue(":matricule",matricule);

        return query.exec();
    }
    else{
        return false;
    }
}

bool entreprise::modifier(int matr){
    QSqlQuery query;
    query.prepare("update entreprise set matricule=:matricule,nom=:nom,location=:location,email=:email where matricule=:matr");
    query.bindValue(":matricule",matricule);
    query.bindValue(":nom",nom);
    query.bindValue(":location",location);
    query.bindValue(":email",email);
    query.bindValue(":matr",matr);

    return query.exec();
}

QSqlQueryModel* entreprise::afficher(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select* from entreprise");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("matricule"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("location"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("email"));

    return model;
}

entreprise entreprise::getEntreprise(int matr){
    QSqlQuery query;
    query.prepare("select * from entreprise where matricule=:matricule");
    query.bindValue(":matricule",matr);
    query.exec();
    entreprise e;
    while(query.next()){
        e.setMatricule(query.value(0).toInt());
        e.setNom(query.value(1).toString());
        e.setLocation(query.value(2).toString());
        e.setEmail(query.value(3).toString());
    }
    return e;
}

QStringList entreprise::getListEntreprise(){
    QStringList list;
    QSqlQuery query;
    query.prepare("select matricule from entreprise");
    query.exec();
    while(query.next()){
        list.append(QString::number(query.value(0).toInt()));
    }
    return list;
}
