#include "login.h"
#include "ui_login.h"
#include "login_juge.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>
#include "smtp.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->login_id->setPlaceholderText("Entrer votre id");
    ui->login_pass->setPlaceholderText("Entrer votre mot de passe");

    ui->signup_id->setPlaceholderText("Entrer votre id");
    ui->signup_pass->setPlaceholderText("Entrer un mot de passe");
    ui->signup_mail->setPlaceholderText("Entrer votre mail");

    ui->r_mail->setPlaceholderText("Entrer votre mail de récupération");

    ui->login_id->setValidator(new QIntValidator(100, 999999, this));
    ui->signup_id->setValidator(new QIntValidator(100, 999999, this));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
         //le slot update_label suite à la reception du signal readyRead (reception des données).

}

Login::~Login()
{
    delete ui;
}

void Login::on_b_inscrire_clicked()
{
    int id=ui->signup_id->text().toInt();
    QString password=ui->signup_pass->text();
    QString mail=ui->signup_mail->text();
Login_juge L(id, password, mail);

bool test=L.ajouter();
if(test)
{
ui->statut1->setText("Ajout effectué");
ui->signup_id->clear();
ui->signup_pass->clear();
ui->signup_mail->clear();
}
else
ui->statut1->setText("Ajout non effectué");
}

void Login::on_b_connexion_clicked()
{
    M= new MainWindow(this);
    M->show();
   /* QString id=ui->login_id->text();
    QString  password=ui->login_pass->text();
    QSqlQuery qry;
    if(qry.exec("select * from juge where id='"+id +"' and password='"+password+"'")) {
       int count=0;
        while (qry.next()){
               count++;
           }
        if(count==1){
            ui->statut->setText("Connexion effectuée...");
            M= new MainWindow(this);
            M->show();
            ui->login_id->clear();
            ui->login_pass->clear();
        }
        else{
            ui->statut->setText("Connexion non non effectuée\nEntrer votre mail puis\nclique sur cette serrure =>");}
}*/
            }


void Login::on_b_recuperation_clicked()
{
    QString pass;
    QString id=ui->login_id->text();
    QString  mail=ui->r_mail->text();
    QSqlQuery qry;
    if(qry.exec("select DISTINCT(password) from juge where id='"+id +"' and mail='"+mail+"'")) {
       int count=0;
        while (qry.next()){
               count++;
               pass=qry.value(0).toString();
           }
        if(count==1) {
            ui->statut->setText("Le mot de passe a été\nenvoyer à votre mail");
            Smtp* smtp = new Smtp("guesmi.aymen@esprit.tn","211JMT42072001","smtp.gmail.com",465);
                  connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
                  smtp->sendMail("guesmi.aymen@esprit.tn", ui->r_mail->text(), ui->objet_recup_cle->text(),pass);//titre
                    QMessageBox::information(nullptr, QObject::tr(" OK"),
                                        QObject::tr("mail sent Successfuly.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);
}
        else{
            ui->statut->setText("Mail ou ID incorrecte\nLa récupération non effectuer");}
}}
void Login::update_label()
{

    data=A.read_from_arduino();
    QByteArray text=QByteArray::fromHex(data);
    QSqlQuery qry;
    serialb +=QString::fromStdString(data.toStdString());


    if( qry.exec("select * from juge where RFID like '"+serialb+"%'") )
    {
           int count=0;
           while(qry.next())
                { count++;}
                     if(count==1)
                     {
                 M=new MainWindow(this);
                     M->show();

                 }
                     }
                     else
                     {
                        // QMessageBox::warning(this,"error","can't log in check informations");
        QMessageBox::warning(this,"error","error");
                     }

}
