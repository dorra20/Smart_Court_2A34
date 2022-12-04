#include "juge.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>

Juge::Juge()
{
    id=0; nom="";prenom="";poste="";
}
Juge::Juge(int id,QString nom,QString prenom,QString poste)
{this->id=id; this->nom=nom; this->prenom=prenom; this->poste=poste;}
int Juge::getid(){return id;}
int getid();
QString Juge::getnom(){return nom;}
QString Juge::getprenom(){return prenom;}
QString Juge::getposte(){return poste;}

void Juge::setid(int id){this->id=id;}
void Juge::setnom(QString nom){this->nom=nom;}
void Juge::setprenom(QString prenom){this->prenom=prenom;}
void Juge::setposte(QString poste){this->poste=poste;}

bool Juge::ajouter(int idd,QString nom,QString prenom,QString poste)
{
    QSqlQuery query;
    QString id_string= QString::number(idd);
    //QString id= QString::number(id); //on doit saisir comme string et le id est int (nombre fonction qui convertir int à une chaine)
    query.prepare("update juge set ID= :idd ,NOM= :nom ,PRENOM= :prenom ,POSTE= :poste where ID= :idd ");
    query.bindValue(":id", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":poste", poste);
    query.bindValue(":idd", id_string);
    return query.exec(); //retourn true or false(ajout avec succe = true snn false)
}
bool Juge::recherche(int r_id)
{
    QSqlQuery query;
    QString id_string= QString::number(r_id); //on doit saisir comme string et le id est int (nombre fonction qui convertir int à une chaine)
    query.prepare("INSERT INTO juge (id, nom, prenom, poste) "
              "VALUES (:r_id, :nom, :prenom, :poste)");
    query.bindValue(":r_id", id_string);
    query.bindValue(":nom", "");
    query.bindValue(":prenom", "");
    query.bindValue(":poste", "");
    bool test=query.exec(); //retourn true or false(ajout avec succe = true snn false)
    if (test==true)
    {
        supprimer(r_id);
    }
    return test;

}
bool Juge::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("Delete from juge where id=:id");
    query.bindValue(":id",id_string);
    return query.exec();
}

QSqlQueryModel* Juge::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("select id,nom,prenom,poste,mail from juge");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("Identifiant"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Poste"));
return model;
}

bool Juge::maj(int idd,int m_id,QString m_nom,QString m_prenom,QString m_poste)
{
    QSqlQuery query;
    QString idd_string= QString::number(idd);
    QString m_id_string= QString::number(m_id); //on doit saisir comme string et le id est int (nombre fonction qui convertir int à une chaine)
    query.prepare("update juge set ID= :m_id ,NOM= :m_nom ,PRENOM= :m_prenom ,POSTE= :m_poste where ID= :idd ");
    query.bindValue(":m_id", m_id_string);
    query.bindValue(":m_nom", m_nom);
    query.bindValue(":m_prenom", m_prenom);
    query.bindValue(":m_poste", m_poste);
    query.bindValue(":idd", idd_string);
    return query.exec(); //retourn true or false(ajout avec succe = true snn false)
}

QString Juge::pdf(int id)
{
    QSqlQuery query; //lier la bd avec qt
    QString a="";
    query.prepare("select * from juge where id= :id"); //code sql
    query.bindValue(":id", id); //entrer la variable dans sql
    if(query.exec()) //execution sql(prepare)
    {
        while (query.next()) //etat apres l'execution
        {
            QString pdf_id= query.value(0).toString();
            QString nom= query.value(1).toString();
            QString prenom= query.value(2).toString();
            QString poste= query.value(3).toString();
            a="id= "+pdf_id+"\nnom= "+nom+"\nprenom= "+prenom+"\nposte ="+poste;
        }
    }
    return a;
}

QSqlQueryModel * Juge::tri1()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM juge ORDER BY id");
        return model;
}

QSqlQueryModel * Juge::tri2()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM juge ORDER BY nom");
        return model;
}
QSqlQueryModel * Juge::tri3()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM juge ORDER BY prenom");
        return model;
}
QSqlQueryModel * Juge::tri4()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM juge ORDER BY poste");
        return model;
}
QSqlQueryModel * Juge::tri5()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM juge ORDER BY mail");
        return model;
}
QSqlQueryModel * Juge::recherche_juge(QString search)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString qry="select * from juge where id like '%"+search+"%' or nom like '%"+search+"%' or prenom like '%"+search+"%' or poste like '%"+search+"%' or mail like '%"+search+"%' ";
    qDebug()<<qry;
    model->setQuery(qry);
    return model;
}



