#include "invite.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSystemTrayIcon>


Invite::Invite()
{
cin=0; nom=""; prenom=""; num=0; email=""; sexe="";
}


Invite::Invite(int cin,QString nom,QString prenom,int num,QString email,QString sexe)
{
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->num=num;
    this->email=email;
    this->sexe=sexe;
}

void Invite::notif(QString t, QString b){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

     // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
      notifyIcon->show();
      notifyIcon->showMessage(t,b,QSystemTrayIcon::Information,15000);
}


int Invite::getcin(){return cin;}
QString Invite::getnom(){return nom;}
QString Invite::getprenom(){return prenom;}
int Invite::getnum(){return num;}
QString Invite::getemail(){return email;}
QString Invite::getsexe(){return sexe;}
void Invite::setcin(int cin){this->cin=cin;}
void Invite::setnom(QString nom){this->nom=nom;}
void Invite::setprenom(QString prenom){this->prenom=prenom;}
void Invite::setnum(int num){this->num=num;}
void Invite::setemail(QString email){this->email=email;}
void Invite::setsexe(QString sexe){this->sexe=sexe;}



bool Invite::ajouter()
{
    QSqlQuery query;
    QString cin_string= QString::number(cin);
          query.prepare("INSERT INTO invite (cin,nom,prenom,num,email,sexe) "
                        "VALUES (:cin, :nom, :prenom, :num, :email, :sexe)");
          query.bindValue(":cin",cin_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":num", num);
          query.bindValue(":email", email);
          query.bindValue(":sexe",sexe);
          return query.exec();
}


QSqlQueryModel* Invite::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT *  FROM invite");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    return model;
}


bool Invite::supprimer(int cin)
    {
        QSqlQuery query;
        QString cin_string=QString::number(cin);
        query.prepare("delete from Invite where cin=:cin");
        query.bindValue(":cin",cin);
        return query.exec();
    }


bool Invite::modifier()
{
   QSqlQuery query;
   QString cin_string=QString::number(cin);
   QString num_string=QString::number(num);

    query.prepare("UPDATE invite SET  nom= :nom, prenom= :prenom, num= :num, email= :email, sexe= :sexe");

            query.addBindValue(nom);
            query.addBindValue(prenom);
            query.addBindValue(num);
            query.addBindValue(email);
            query.addBindValue(sexe);
    return query.exec();
}


QSqlQueryModel * Invite::Recherche(QString rech)
{
   QSqlQuery query;

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Invite "
                    " where ( cin LIKE ""'%"+rech+"%' OR nom LIKE '%"+rech+"%' OR num LIKE '%"+rech+"%' )");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));

    return model;



}
QSqlQueryModel * Invite::trier()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from invite order by cin;");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));

return model;

}





