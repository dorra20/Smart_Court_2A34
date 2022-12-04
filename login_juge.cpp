#include "login_juge.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>

Login_juge::Login_juge()
{
    id=0; password=""; mail="";
}
Login_juge::Login_juge(int id,QString password,QString mail)
{this->id=id; this->password=password; this->mail=mail;}
int Login_juge::getid(){return id;}
int getid_signup();
QString Login_juge::getpassword(){return password;}
QString Login_juge::getmail(){return mail;}

void Login_juge::setid(int id){this->id=id;}
void Login_juge::setpassword(QString password){this->password=password;}
void Login_juge::setmail(QString mail){this->mail=mail;}

bool Login_juge::ajouter()
{
    QSqlQuery query;
    QString id_string= QString::number(id); //on doit saisir comme string et le id est int (nombre fonction qui convertir int à une chaine)
    query.prepare("INSERT INTO juge (id, password, mail) "
              "VALUES (:id, :password, :mail)");
    query.bindValue(":id", id_string);
    query.bindValue(":password", password);
    query.bindValue(":mail", mail);
    return query.exec(); //retourn true or false(ajout avec succe = true snn false)
}





