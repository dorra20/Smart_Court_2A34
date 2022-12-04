#ifndef JUGE_H
#define JUGE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Juge
{
public:
    Juge();
    Juge(int,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getposte();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setposte(QString);
    bool ajouter(int,QString,QString,QString);
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool recherche(int);
    bool maj(int,int,QString,QString,QString);
    QString pdf(int);
    //QSqlQueryModel* Find_juge();
    QSqlQueryModel* recherche_juge(QString search);
    QSqlQueryModel * tri1();
    QSqlQueryModel * tri2();
    QSqlQueryModel * tri3();
    QSqlQueryModel * tri4();
    QSqlQueryModel * tri5();
private:
    int id;
    QString nom,prenom,poste;
};

#endif // JUGE_H
