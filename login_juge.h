#ifndef LOGIN_JUGE_H
#define LOGIN_JUGE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Login_juge
{
public:
    Login_juge();
    Login_juge(int,QString,QString);
    int getid();
    QString getpassword();
    QString getmail();
    void setid(int);
    void setpassword(QString);
    void setmail(QString);
    bool ajouter();

private:
    int id;
    QString password,mail;
};

#endif // LOGIN_JUGE_H
