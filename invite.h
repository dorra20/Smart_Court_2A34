#ifndef INVITE_H
#define INVITE_H

#include <QString>
#include <QSqlQueryModel>
class Invite
{
public:
    Invite();
    Invite(int,QString,QString,int,QString,QString);
    int getcin();
    QString getnom();
    QString getprenom();
    int getnum();
    QString getemail();
    QString getsexe();
    void setcin(int);
    void setnom(QString);
    void setprenom(QString);
    void setnum(int);
    void setemail(QString);
    void setsexe(QString);
    bool ajouter();
    bool supprimer(int);
    bool modifier();
    void notif(QString,QString);
    QSqlQueryModel* afficher();
    QSqlQueryModel * Recherche(QString);
    QSqlQueryModel * stat();
    QSqlQueryModel * trier();
private:
    int cin,num;
    QString nom,prenom,email,sexe;
};

#endif // INVITE_H
