#ifndef AVOCAT_H
#define AVOCAT_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>
#include<QDateTime>
#include<QTimer>
class Avocat
{
public:
    Avocat();
    Avocat(QString,QString,QString,QString);
    QString getnumtel();
    QString getnom();
    QString getprenom();
    QString gettype();

    void setnum(QString);
    void setnom(QString);
    void setprenom(QString);
    void settype(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel* recherche(QString num_tel);
    QSqlQueryModel * trier();
    QSqlQueryModel * stat();
    QString pdf(QString);

private:
QString num_tel,nom,prenom,type;
};

#endif // AVOCAT_H
