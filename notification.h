#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSystemTrayIcon>

class notification
{
public:
    notification();
    void Alerte_Ajout_Ent(int id, int i);
    void Alerte_Modifier_Ent(int id,int i);
    void Alerte_Supprimer_Ent(int id,int i);

    void Alerte_Ajout_cont(int id, int i);
    void Alerte_Modifier_cont(int id,int i);
    void Alerte_Supprimer_cont(int id,int i);
};

#endif // NOTIFICATION_H
