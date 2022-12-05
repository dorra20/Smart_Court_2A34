#ifndef AUDIANCE_H
#define AUDIANCE_H

#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDateTimeEdit>
#include <QMainWindow>
#include "mainwindow.h"
#include "ui_mainwindow.h"
class Audiance
{
public:
    Audiance();
    Audiance(QString,QDateTime,QString,QString);
    QString getNUM();
    QDateTime getDate();
    QString getHeure();
    QString getgenre();


    //QDateTime currentDateTime();
    void setNum(QString num);
    void setHeure(QString heure);


    void setDate(QDateTime date);
    void setgenre(QString genre);
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool update(QString ID);
    bool supprimer(QString ID);
   // bool chercherParCin()  ;
    int verificationID() ;
    QSqlQueryModel * trieid();
     QSqlQueryModel * trienom();
     QSqlQueryModel * triehorloge();


    QSqlQueryModel* Trier(QString critere) ;
    void  rechercher(Ui::MainWindow *ui) ;


private :
    QString num,heure,genre ;

    QDateTime date ;//=QDateTime::currentDateTime() ;
};

#endif // AUDIANCE_H
