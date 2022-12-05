
#include<QtDebug>
#include<QObject>
#include<QSqlQuery>
#include "ui_mainwindow.h"
#include <QDateTime>
#include<QDateTimeEdit>
#include "mainwindow.h"



Audiance::Audiance()
{
num="" ;heure="";genre="";
}

Audiance::Audiance(QString num,QDateTime date,QString heure,QString genre)
{
    this->num=num;
    this->heure=heure;
    this->date=date ;
    this->genre=genre;
    //QDateTime::currentDateTime();  }
}
QString Audiance::getNUM(){return num;}
QString Audiance::getHeure(){return heure ;}

QDateTime Audiance::getDate() {return date ;}
QString Audiance::getgenre() {return genre ;}

void Audiance::setNum(QString num){this->num=num;}
void Audiance::setHeure(QString heure){this->heure=heure;}

void Audiance::setDate(QDateTime date) {this->date=date;}
void Audiance::setgenre(QString genre) {this->genre=genre;}

 bool Audiance :: ajouter()
 {
     QSqlQuery query;

     query.prepare("INSERT INTO AUDIANCE (NUM,DATE_AD,HEURE,genre) "
                   "VALUES (:num,:date,:heure,:genre)");

     query.bindValue(":num", num);
     query.bindValue(":date",date);
     query.bindValue(":heure",heure);
     query.bindValue(":genre",genre);


     //query.exec();
     return query.exec();

}


QSqlQueryModel* Audiance :: afficher()
{
         QSqlQueryModel *model = new QSqlQueryModel;
         model->setQuery("SELECT * from AUDIANCE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_AD"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE"));

 return model;
}
bool Audiance::supprimer(QString num)
{


    QSqlQuery query;

       query.prepare("Delete from AUDIANCE where NUM=:num");
       query.bindValue(0, num);
       query.exec();

       return query.exec();
}

bool Audiance::update(QString ID)
{
QString res= (ID);


QSqlQuery query;
query.prepare("Update AUDIANCE set NUM = :ID , DATE_AD = :date , HEURE = :heure   where NUM = :ID ");
query.bindValue(":ID", res);
query.bindValue(":date",date );
query.bindValue(":heure",heure );

//query.exec();
return    query.exec();


}



void Audiance::rechercher(Ui::MainWindow *ui)
{
    QSqlQuery q;
        QSqlQueryModel *modal=new QSqlQueryModel();
        QString mot =ui->lineEdit_recherche->text();
        q.prepare("select * from AUDIANCE where (NUM LIKE '%"+mot+"%' or HEURE LIKE '%"+mot+"%' )");

        q.exec() ;
        modal->setQuery(q);
        ui->tab->setModel(modal);

}
QSqlQueryModel *Audiance:: trieid()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from AUDIANCE order by NUM " );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_AD"));

    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE"));

 return model;

}
QSqlQueryModel *Audiance:: triehorloge()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select *from AUDIANCE order by DATE_AD " );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE_AD"));

    model->setHeaderData(2, Qt::Horizontal, QObject::tr("HEURE"));
  return model;

}

