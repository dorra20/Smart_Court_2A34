#include "affaire.h"
#include"mainwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QtDebug>
#include <QObject>

Affaire::Affaire()
{
id=0 ;
date ="";
type="";
etat="";
}

Affaire::Affaire(int id,QString date,QString type,QString etat){
    this->id=id;
    this->date=date;
    this->type=type;
    this->etat=etat;}

int Affaire::getid(){return this-> id;}
QString Affaire:: getdate(){return this -> date;}
QString Affaire::gettype(){return this -> type;}
QString Affaire:: getetat(){return this ->etat;}
void Affaire::setid(int id){this->id=id;}
void Affaire::setdate(QString date){this->date=date;}
void Affaire::settype(QString type){this->type=type;}
void Affaire ::setetat(QString etat){this->etat=etat;}
// ajouter



bool Affaire::rechercheArchive()
{
    QSqlQueryModel *  model=new QSqlQueryModel();
    model->setQuery("select * from affarchive");
    int n = model->rowCount();
    for (int i = 0 ; i<n ; i ++ )
    {
        if (model->data(model->index(i,0)).toInt() == id )
        {
            return false ;
        }

    }
    return true ;
}
bool Affaire::ajouter(){

    //bool test=false;
   // return test;
    QSqlQuery query;

    QString id_string= QString ::number(id);

          query.prepare("INSERT INTO affaire (ID,DATEE,TYPE,ETAT) "
                        "VALUES (:id, :date, :type,:etat)");
          query.bindValue(":id", id_string);
          query.bindValue(":date", date);
          query.bindValue(":type", type);
          query.bindValue(":etat", etat);
         return query.exec();
}
bool Affaire::ajouterarchive(){


    QSqlQuery query;

    QString id_string= QString ::number(id);

          query.prepare("INSERT INTO affarchive (ID,DATEE,TYPE,ETAT) "
                        "VALUES (:id, :date, :type,:etat)");
          query.bindValue(":id", id_string);
          query.bindValue(":date", date);
          query.bindValue(":type", type);
          query.bindValue(":etat", etat);
         return query.exec();
}

//supprimer**********
bool Affaire::supprimer(int id){
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from affaire where id= :id");
    query.bindValue(":id",res);
    return query.exec();
}

bool Affaire::supprimerArchive(int id){
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from affarchive where id= :id");
    query.bindValue(":id",res);
    return query.exec();
}

QSqlQueryModel* Affaire::afficher()
{QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery ("select * from affaire");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));


    return model;

}
void Affaire::classer(int id,QString c )
{
    /*data=a.read_from_arduino();
    QByteArray text=QByteArray::fromHex(data);
    serialBuffer +=QString::fromStdString(data.toStdString());
     QSqlQuery query;
     query.prepare("UPDATE affaire SET archive where id=:id");
     query.bindValue(":id",id);
   if( query.exec())
   {
      while (query.next())
      {
          if(serialBuffer=="1"){
          query.value(3).toString()="classé";}
          else if (serialBuffer=="0"){
          query.value(3).toString()="non classé";}
          }
      }*/
    QSqlQuery query;
          query.prepare("UPDATE affaire SET etat='"+c+"' WHERE id=:id") ;
          query.bindValue(":id", id);
          query.exec();
   }

QSqlQueryModel* Affaire::afficherArchive()
{QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery ("select * from affarchive ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("etat"));
    return model;

}

bool Affaire::modifier(int id)
{

QSqlQuery query;

QString id_string= QString::number(id);

query.prepare("Update affaire set type=:type,datee=:date,etat=:etat where id=:id_string");

query.bindValue(":id_string",id_string);
query.bindValue(":date",date);
query.bindValue(":type",type);
query.bindValue(":etat",etat);

return    query.exec();
}

QSqlQueryModel* Affaire::recherche(QString test)
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery ("select * from affaire where  ( ID LIKE '%"+test+"%' OR type LIKE '%"+test+"%' OR etat LIKE '%"+test+"%' )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));


    return model;
}
QSqlQueryModel* Affaire::affichertri()
{

    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery ("select * from affaire order by ID");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("ETAT"));


    return model;

}



