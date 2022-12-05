#include "avocat.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
Avocat::Avocat()
{
num_tel="";
nom="";
prenom="";
type="";
}

Avocat::Avocat(QString num_tel,QString nom,QString prenom,QString type)
{
    this->num_tel=num_tel; this->nom=nom; this->prenom=prenom;this->type=type;
}
QString Avocat:: getnumtel(){return num_tel;}
QString Avocat::getnom(){return nom;}
QString Avocat::getprenom(){return prenom;}
QString Avocat::gettype(){return type;}
void Avocat::setnum(QString num_tel){this->num_tel=num_tel;}
void Avocat::setnom(QString nom){this->nom=nom;}
void Avocat::setprenom(QString prenom){this->prenom=prenom;}
void Avocat::settype(QString type){this->type=type;}
bool Avocat::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO Avocat (num_tel,nom,prenom,type,datee)"
               "VALUES (:num_tel, :nom, :prenom,:type,:datee)");
query.bindValue(":num_tel",num_tel);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":type",type);
return query.exec();
}

bool Avocat::supprimer(QString)
{
    QSqlQuery query;
    query.prepare("Delete from Avocat where num_tel=:num_tel");
    query.bindValue(":num_tel",num_tel);
    return query.exec();
}

QSqlQueryModel* Avocat::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM Avocat");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_tel"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
return model;
}

bool Avocat::modifier()
{
QSqlQuery query;

query.prepare("UPDATE AVOCAT SET nom=:nom,prenom=:prenom,type=:type where num_tel=:num_tel");
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":type",type);
query.bindValue(":num_tel",num_tel);

return query.exec();
}

QSqlQueryModel* Avocat::recherche(QString num_tel)
{
QSqlQuery query;
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT * FROM Avocat where num_tel='"+num_tel+"'");
query.bindValue(":num_tel",num_tel);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_tel"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
return model;
}

QSqlQueryModel * Avocat::trier()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from Avocat order by num_tel asc;");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("num_tel"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("type"));
return model;
}

QString Avocat::pdf(QString num_tel)
{
    QSqlQuery query;
    QString a="";
    query.prepare("select * from Avocat where num_tel= :num_tel");
    query.bindValue(":num_tel",num_tel);
    if(query.exec())
    {
        while (query.next())
        {
            QString num_tel= query.value(0).toString();
            QString nom= query.value(1).toString();
            QString prenom= query.value(2).toString();
            QString type= query.value(3).toString();
            a="num_tel= "+num_tel+"\nnom= "+nom+"\nprenom= "+prenom+"\ntype= "+type;
        }
    }
    return a;
}






