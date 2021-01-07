#include "notification.h"

notification::notification()
{

}

void notification::Alerte_Ajout_Ent(int id,int i)
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    //notifyIcon->setIcon(QIcon("C:/Users/Desktop/projet/icon.png"));
    notifyIcon->show();
    if (i==0)
    {
        notifyIcon->showMessage("Entreprise","On peut pas ajouter cette Entreprise",QSystemTrayIcon::Warning,1500);
    }
    else if (i==1)
    {
        notifyIcon->showMessage("Entreprise","Une nouvelle Entreprise avec un Matricule "+QString::number(id)+" a été ajoutée",QSystemTrayIcon::Information,1500);
    }
}


void notification::Alerte_Modifier_Ent(int id, int i){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    //notifyIcon->setIcon(QIcon("C:/Users/Desktop/projet/icon.png"));
    notifyIcon->show();
    if (i==0)
    {
        notifyIcon->showMessage("Entreprise","Erreur!",QSystemTrayIcon::Warning,1500);
    }
    else if (i==1)
    {
        notifyIcon->showMessage("Entreprise","L'Entreprise avec un matricule "+QString::number(id)+" a été modifiée",QSystemTrayIcon::Information,1500);
    }
}

void notification::Alerte_Supprimer_Ent(int id, int i){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    //notifyIcon->setIcon(QIcon("C:/Users/Desktop/projet/icon.png"));
    notifyIcon->show();
    if (i==0)
    {
        notifyIcon->showMessage("Entreprise","Cette Entreprise n'existe pas",QSystemTrayIcon::Warning,1500);
    }
    else if (i==1)
    {
        notifyIcon->showMessage("Entreprise","L'Entreprise avec un matricule "+QString::number(id)+" a été supprimée",QSystemTrayIcon::Information,1500);
    }
}



void notification::Alerte_Ajout_cont(int id,int i)
{
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    //notifyIcon->setIcon(QIcon("C:/Users/Desktop/projet/icon.png"));
    notifyIcon->show();
    if (i==0)
    {
        notifyIcon->showMessage("Contrat","On peut pas ajouter ce contrat",QSystemTrayIcon::Warning,1500);
    }
    else if (i==1)
    {
        notifyIcon->showMessage("Contrat","Un nouveau contrat avec un numero "+QString::number(id)+" a été ajouté",QSystemTrayIcon::Information,1500);
    }
}


void notification::Alerte_Modifier_cont(int id, int i){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    //notifyIcon->setIcon(QIcon("C:/Users/Desktop/projet/icon.png"));
    notifyIcon->show();
    if (i==0)
    {
        notifyIcon->showMessage("Contrat","Erreur!",QSystemTrayIcon::Warning,1500);
    }
    else if (i==1)
    {
        notifyIcon->showMessage("Contrat","Le contrat numero "+QString::number(id)+" a été modifié",QSystemTrayIcon::Information,1500);
    }
}

void notification::Alerte_Supprimer_cont(int id, int i){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    //notifyIcon->setIcon(QIcon("C:/Users/Desktop/projet/icon.png"));
    notifyIcon->show();
    if (i==0)
    {
        notifyIcon->showMessage("Contrat","Erreur!",QSystemTrayIcon::Warning,1500);
    }
    else if (i==1)
    {
        notifyIcon->showMessage("Contrat","Le contrat numero "+QString::number(id)+" a été supprimé",QSystemTrayIcon::Information,1500);
    }
}
