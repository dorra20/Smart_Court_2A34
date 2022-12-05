#ifndef AFFAIRE_H
#define AFFAIRE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "arduino.h"

class Affaire
{
private:
    int id;
    QString date,type,etat;
    //QByteArray data;
    //arduino a;
    //QString serialBuffer;
    int archive;
public:
    Affaire();
    Affaire(int,QString,QString,QString);
    int getid();
    QString getdate();
    QString gettype();
    QString getetat();
    void setid(int);
    void setdate(QString);
    void settype(QString);
    void setetat(QString);


    bool rechercheArchive();
    bool ajouterarchive();
    bool ajouter();//la méthode ajouter a un accés au val des attribus de cette classe
    bool supprimer(int id);
    bool supprimerArchive(int id);
    QSqlQueryModel* afficher();
    QSqlQueryModel* recherche(QString test);
    QSqlQueryModel* afficherArchive();
    bool modifier(int);
    QSqlQueryModel* affichertri();
    void classer(int,QString);
};
#endif // AFFAIRE_H
