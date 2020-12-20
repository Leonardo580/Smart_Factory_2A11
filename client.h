#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>

class Client


{ private:

    QString nom,prenom,adresse,date_naissance,numero,CIN;
public:
    Client();
     Client(QString,QString,QString,QString,QString,QString);
    void SetCIN(QString val){CIN=val;}
    QString GetCIN() {return CIN;}
    QString Getnom() { return nom; }
            void Setnom(QString val) { nom = val; }
            QString Getprenom() { return prenom; }
            void Setprenom(QString val) { prenom = val; }
            QString Getadresse() { return adresse; }
            void Setadresse(QString val) { adresse = val; }
            QString Getdate_naissance() { return date_naissance; }
            void Setdate_naissance(QString val) { date_naissance = val; }
            void Setnumero(QString val){numero=val;}
            QString Getnumero(){return numero;}
            bool ajouter();
            QSqlQueryModel*afficher();
            bool supprimer(QString);
            QSqlQueryModel *rechercher_3(QString CIN,QString adresse,QString date_naissance);
            QSqlQueryModel * tri_CIN();
             QSqlQueryModel * tri_numero();
              QSqlQueryModel * tri_adresse();
               QSqlQueryModel * tri_nom();
                QSqlQueryModel * tri_prenom();
                QSqlQueryModel * recherche_CIN(const QString &);
                  bool  recherche_CIN2(const QString &);


};

#endif // CLIENT_H
