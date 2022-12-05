#include <QMessageBox>
#include <QIntValidator>
#include <QFileDialog>
#include <QTextStream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "juge.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //////////////////////////////////// arduino
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_ard()));
    //////////////////////////////////////////////////////////////////// login
    ui->login_id->setPlaceholderText("Entrer votre id");
    ui->login_pass->setPlaceholderText("Entrer votre mot de passe");

    ui->signup_id->setPlaceholderText("Entrer votre id");
    ui->signup_pass->setPlaceholderText("Entrer un mot de passe");
    ui->signup_mail->setPlaceholderText("Entrer votre mail");

    ui->r_mail->setPlaceholderText("Entrer votre mail de récupération");

    ui->login_id->setValidator(new QIntValidator(100, 999999, this));
    ui->signup_id->setValidator(new QIntValidator(100, 999999, this));

    ////////////////////////////////////////////////////// aymen
    ui->stackedWidget->setCurrentIndex(0);
    ui->l_id->setPlaceholderText("Entrer votre id");
    ui->l_nom->setPlaceholderText("Entrer votre nom");
    ui->l_prenom->setPlaceholderText("Entrer votre prenom");
    ui->l_id_supp->setPlaceholderText("Entrer id a supprimer");
    ui->juge_idd->setPlaceholderText("Entrer id a modifier");
    ui->juge_m_id->setPlaceholderText("Entrer le nouveau id");
    ui->juge_m_nom->setPlaceholderText("Entrer le nouveau nom");
    ui->juge_m_prenom->setPlaceholderText("Entrer le nouveau prenom");
    ui->id_print_juge->setPlaceholderText("Entrer l'id a imprimer");

    ui->l_id->setValidator(new QIntValidator(100, 999999, this)); //999999 =6 chiffres a inserrer
    ui->l_id_supp->setValidator(new QIntValidator(100, 999999, this));
    ui->juge_idd->setValidator(new QIntValidator(100, 999999, this));
    ui->juge_m_id->setValidator(new QIntValidator(100, 999999, this));
    ui->id_print_juge->setValidator(new QIntValidator(100, 999999, this));
    ui->tab_juge->setModel(J.afficher());


    //////////////////////////////////////// lina
    ui->le_cin->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_invite->setModel(I.afficher());


         ////////////////////////////////////////////////////////////////// dorra
          ui->tab_affaire->setModel(Aff.afficher());
         ui->archiveView->setModel(Aff.afficherArchive());
         ui->comboBoxSupp->setModel(Aff.afficher());
          ui->comboBoxM->setModel(Aff.afficher());
     ////////////////////////////////////////////////////////////// bechir

          QDateTime date=QDateTime::currentDateTime() ;
          ui->dateTimeEdit->setDateTime(date);
          ui->tab->setModel(aud.afficher());

//////////////////////////////////// yaine
          ui->le_num_tel->setValidator(new QIntValidator(0, 99999999, this));
          ui->tab_avocats->setModel(av.afficher());

/////////////////////////////////////////////
}

MainWindow::~MainWindow()
{
    delete ui;
}

/////////////////////////////////////////////////////////////////////// login

void MainWindow::on_b_inscrire_clicked()
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

void MainWindow::on_b_connexion_clicked()
{
    QString id=ui->login_id->text();
    QString  password=ui->login_pass->text();
    QSqlQuery qry;
    if(qry.exec("select * from juge where id='"+id +"' and password='"+password+"'")) {
       int count=0;
        while (qry.next()){
               count++;
           }
        if(count==1){
            ui->statut->setText("Connexion effectuée...");
            ui->stackedWidget->setCurrentIndex(2);
            ui->login_id->clear();
            ui->login_pass->clear();
        }
        else{
            ui->statut->setText("Connexion non non effectuée\nEntrer votre mail puis\nclique sur cette serrure =>");}
}}


void MainWindow::on_b_recuperation_clicked()
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
void MainWindow::update_label()
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
                 ui->stackedWidget->setCurrentIndex(2);

                 }
                     }
                     else
                     {
                        // QMessageBox::warning(this,"error","can't log in check informations");
        QMessageBox::warning(this,"error","error");
                     }

}

//////////////////////////////// aymen
void MainWindow::on_pushButton_clicked()
{
    bool test_r, test=false;
        int idd=ui->l_id->text().toInt();
        QString nom=ui->l_nom->text();
        QString prenom=ui->l_prenom->text();
        QString poste=ui->l_poste->currentText();
        test_r=J.recherche(idd);
        if(test_r==false)
        {
            test=J.ajouter(idd,nom,prenom,poste);
        }

    if(test)
    {
    QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Ajout effectué\n""click cancel to exit."),QMessageBox::Cancel);
    ui->tab_juge->setModel(J.afficher());
    }
    else
    QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Ajout non effectué\n""click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_b_supp_clicked()
{
  bool test=false, test_r;
  int id=(ui->l_id_supp->text().toInt());
  test_r=J.recherche(id);
  if (test_r==false)
  {
      test=J.supprimer(id);
  }

  QMessageBox msgBox;
  if(test)
{
      msgBox.setText("Suppression avec succes");
      ui->tab_juge->setModel(J.afficher());
      ui->l_id_supp->clear();
}
  else
      msgBox.setText("Echec du Suppression");

  msgBox.exec();
}

void MainWindow::on_b_maj_clicked()
{
    bool test_r, test=false;
    int idd=ui->juge_idd->text().toInt();
    int m_id=ui->juge_m_id->text().toInt();
    QString m_nom=ui->juge_m_nom->text();
    QString m_prenom=ui->juge_m_prenom->text();
    QString m_poste=ui->juge_m_poste->currentText();
    test_r=J.recherche(idd);
    if(test_r==false)
    {
        test=J.maj(idd,m_id,m_nom,m_prenom,m_poste);
    }

if(test)
{
QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("Modification effectué\n""click cancel to exit."),QMessageBox::Cancel);
ui->tab_juge->setModel(J.afficher());
}
else
QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("Modification non effectué\n""click cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_bt_imprimer_juge_clicked()
{
    int id=ui->id_print_juge->text().toInt(); //importer id qui a ete ecrit
    QString z=J.pdf(id);
    ui->pdf_juge->setText(z);
    QPrinter printer;
        printer.setPrinterName("Juge");
        printer.setPageSize(QPrinter::A4);
        QPrintDialog dialog(&printer,this); //ouvrir la page de l'impression
        if (dialog.exec()== QDialog::Rejected)
        return;
        ui->pdf_juge->print(&printer); //quoi imprimer
}

void MainWindow::on_tri1_clicked()
{
    ui->tab_juge->setModel(J.tri1());
}
void MainWindow::on_tri2_clicked()
{
    ui->tab_juge->setModel(J.tri2());
}
void MainWindow::on_tri3_clicked()
{
    ui->tab_juge->setModel(J.tri3());
}
void MainWindow::on_tri4_clicked()
{
    ui->tab_juge->setModel(J.tri4());
}
void MainWindow::on_tri5_clicked()
{
    ui->tab_juge->setModel(J.tri5());
}

void MainWindow::on_b_recherhcer_clicked()
{
    ui->tab_juge->setModel(J.recherche_juge(ui->lineEdit_Recherche->text()));
}


void MainWindow::on_actionstat_triggered()
{

}

void MainWindow::on_stats_clicked()
{
    QSqlQuery q1,q2,q3,q4,q5;
        qreal tot=0,c1=0,c2=0,c3=0,c4=0;
        q1.prepare("Select * from juge");
        if(q1.exec())
        {
            while (q1.next())// combien de juges
            {
                tot++;
            }
        }
        q2.prepare("Select * from juge where poste ='Juge aux affaires familiales'");
        if(q2.exec())
        {
            while (q2.next())
            {
                c1++;
            }
        }
        q3.prepare("Select * from juge where poste ='Juge de l_instruction'");
        if(q3.exec())
        {
            while (q3.next())
            {
                c2++;
            }
        }
        q4.prepare("Select * from juge where poste ='Juge des enfants'");
        if(q4.exec())
        {
            while (q4.next())
            {
                c3++;
            }
        }
        q5.prepare("Select * from juge where poste ='Juge de l_execution'");
        if(q5.exec())
        {
            while (q5.next())
            {
                c4++;
            }
        }
        c1=c1/tot;
        c2=c2/tot;
        c3=c3/tot;
        c4=c4/tot;

        QPieSeries *series = new QPieSeries();
                series->append("Juge aux affaires familiales",c1);
                series->append("Juge de l'instruction",c2);
                series->append("Juge des enfants",c3);
                series->append("Juge de l'execution",c4);
                QPieSlice *slice0 = series->slices().at(0);
                slice0->setExploded();
                slice0->setLabelVisible();
                slice0->setPen(QPen(Qt::darkGray, 2));
                slice0->setBrush(Qt::gray);
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setExploded();
                slice1->setLabelVisible();
                slice1->setPen(QPen(Qt::darkRed, 2));
                slice1->setBrush(Qt::red);
                QPieSlice *slice2 = series->slices().at(2);
                slice2->setExploded();
                slice2->setLabelVisible();
                slice2->setPen(QPen(Qt::darkYellow, 2));
                slice2->setBrush(Qt::yellow);
                QPieSlice *slice3 = series->slices().at(3);
                slice3->setExploded();
                slice3->setLabelVisible();
                slice3->setPen(QPen(Qt::darkGreen, 2));
                slice3->setBrush(Qt::green);
                QChart *chart = new QChart();
                chart->addSeries(series);
                chart->setTitle("Juge par poste");
                chart->setAnimationOptions(QChart::AllAnimations);
                chart->legend()->hide();
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
                QGridLayout *layout = new QGridLayout();
                layout->addWidget(chartView);
                ui->statistiques->setLayout(layout);
}

////////////////////////////////////////////////////////////////////////////// lina




void MainWindow::on_bouton_ajouter_clicked()
    {
        int cin=ui->le_cin->text().toInt();
        QString nom=ui->le_nom->text();
        QString prenom=ui->le_prenom->text();
        int num=ui->le_num->text().toInt();
        QString email=ui->le_email->text();
        QString sexe=ui->comboBox_sexe->currentText();
        Invite I(cin,nom,prenom,num,email,sexe);
        bool test=I.ajouter();
        if(test)
            {
            I.notif("gestion des invites","invite ajouté");
                QMessageBox::information(this,"edit","invité ajouté avec succes");
                ui->tab_invite->setModel(I.afficher());
            }
        else
            {
                QMessageBox::warning(this,"error","error");
            }

}

void MainWindow::on_pb_supprimer_clicked()
{
    Invite I;
    I.setcin(ui->cin_supp->text().toInt());
    bool test=I.supprimer(I.getcin());
    if(test)
    {
        I.notif("gestion des invites","invite supprimé");
        QMessageBox::information(this,"edit","service deleted successfuly");
        ui->tab_invite->setModel(I.afficher());
    }
    else { QMessageBox::warning(this,"error","error");}
}

void MainWindow::on_pushButton_7_clicked()
{
   int cin=ui->cin_up->text().toInt();
   QString nom=ui->nom_up->text();
   QString prenom=ui->prenom_up->text();
   int num=ui->num_up->text().toInt();
   QString email=ui->email_up->text();
   QString sexe=ui->comboBox_sexeup->currentText();


  Invite I (cin,nom,prenom,num,email,sexe);
  bool test=I.modifier();
  QMessageBox msgBox;
  if(test)
  {
      I.notif("gestion des invites","invite modifié");
      msgBox.setText("modifier avec succes");
      ui->tab_invite->setModel(I.afficher());
      msgBox.exec();
  }
  else
  {
      msgBox.setText("echec de modification");
      msgBox.exec();

}
}



void MainWindow::on_pb_pdf_clicked()
{
    QSqlDatabase db;
        QTableView tab_invite;
        QSqlQueryModel * Modal=new  QSqlQueryModel();

        QSqlQuery query ;
         query.prepare("SELECT * FROM Invite ");
         query.exec();
         Modal->setQuery(query);
        tab_invite.setModel(Modal);



         db.close();


         QString strStream;
         QTextStream out(&strStream);

         const int rowCount = tab_invite.model()->rowCount();
         const int columnCount =  tab_invite.model()->columnCount();


         const QString strTitle ="Document";


         out <<  "<html>\n"
             "<head>\n"
                 "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             <<  QString("<title>%1</title>\n").arg(strTitle)
             <<  "</head>\n"
             "<body bgcolor=#ffffff link=#5000A0>\n"
            << QString("<h3 style=\" font-size: 32px; font-family: Arial, Helvetica, sans-serif; color: #FF9933; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des Event")
            <<"<br>"
             <<"<table border=1 cellspacing=0 cellpadding=2>\n";

         out << "<thead><tr bgcolor=#f0f0f0>";
         for (int column = 0; column < columnCount; column++)
             if (!tab_invite.isColumnHidden(column))
                 out << QString("<th>%1</th>").arg(tab_invite.model()->headerData(column, Qt::Horizontal).toString());
         out << "</tr></thead>\n";

         for (int row = 0; row < rowCount; row++) {
             out << "<tr>";
             for (int column = 0; column < columnCount; column++) {
                 if (!tab_invite.isColumnHidden(column)) {
                     QString data = tab_invite.model()->data(tab_invite.model()->index(row, column)).toString().simplified();
                     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                 }
             }
             out << "</tr>\n";
         }
         out <<  "</table>\n"
                 "<br><br>"
                 //<< QString("<p><img src=":/img/aze.png"; width="200"; height="200";\">%1</p>\n")
                 <<"<br>"
                 <<"<table border=1 cellspacing=0 cellpadding=2>\n";


             out << "<thead><tr bgcolor=#f0f0f0>";

                 out <<  "</table>\n"

             "</body>\n"
             "</html>\n";

         QTextDocument *document = new QTextDocument();
         document->setHtml(strStream);

         QPrinter printer;
         QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
         if (dialog->exec() == QDialog::Accepted) {

             QLabel lab;
              QPixmap pixmap(":/img/aze.png");
             lab.setPixmap(pixmap);
             QPainter painter(&lab);
             //QPrinter printer(QPrinter::PrinterResolution);

             //pixmap.load("aze.png");
             //painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
             //painter.drawPixmap(10,10,50,50, pixmap);

             document->print(&printer);
         }

         printer.setOutputFormat(QPrinter::PdfFormat);
         printer.setPaperSize(QPrinter::A4);
         printer.setOutputFileName("/tmp/commandes.pdf");
         printer.setPageMargins(QMarginsF(15, 15, 15, 15));



         delete document;
}

void MainWindow::on_pb_afficher_clicked()
{
    ui->tab_invite->setModel(I.afficher());
}

void MainWindow::on_pb_trier_clicked()
{
    QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select * from invite ORDER BY cin ASC");
        ui->tab_invite->setModel(model);
}


void MainWindow::on_line_rech_textChanged(const QString &arg1)
{
    ui->tab_invite->setModel(I.Recherche(arg1));
}



void MainWindow::on_pushButton_excel_clicked()
{
    {
        QTableView *table;
               table = ui->tab_invite;

               QString filters("CSV files (.csv);;All files (.*)");
               QString defaultFilter("CSV files (*.csv)");
               QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);
               QFile file(fileName + ".csv");

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                   QTextStream data(&file);
                   QStringList strList;
                   for (int i = 0; i < model->columnCount(); i++) {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(",") << "\n";
                   for (int i = 0; i < model->rowCount(); i++) {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++) {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(",") + "\n";
                   }
                   file.close();
                   QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
               }
    }
}

void MainWindow::on_pushButton_envoyer_mail_l_clicked()
{
    S = new Smtp("firas.eljary@esprit.tn" , "espritmain47", "smtp.gmail.com",465);
    connect(S, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));



    S->sendMail("lina",ui->lineEdit_adress_l->text(),ui->lineEdit_sujet_l->text(),ui->plainTextEdit_msg_l->toPlainText());

    QMessageBox::information(nullptr, QObject::tr("SENT"),
                             QObject::tr("Email envoyé avec succes.\n"
                                         ), QMessageBox::Cancel);
    I.notif("gestion des invites","mail envoyé");
}

void MainWindow::update_ard()
{
//data="";
QByteRef a=A.read_from_arduino()[0];

if (a == '0')
    {
     ui->label_porte->setText("salle fermee");
    }
    else
    {
       ui->label_porte->setText("salle ouverte");
    }
}

void MainWindow::on_pushButton_porte_clicked()
{
    A.write_to_arduino("fermer la porte");
}

void MainWindow::on_pushButton_stat_lina_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("SELECT sexe FROM invite WHERE sexe = 'Homme' ");
            float homme=model->rowCount();
            model->setQuery("SELECT sexe FROM invite WHERE sexe = 'Femme' ");
            float femme=model->rowCount();
            float total=homme+femme;

            QPieSeries *series = new QPieSeries();
            series->append("Hommes",homme);
            series->append("Femmes",femme);



            if (homme!=0)
            {
                // Add label and define brush for 1st slice
                QPieSlice *slice1 = series->slices().at(0);
                //slice1->setExploded();
                slice1->setLabel("Hommes "+QString("%1%").arg(100*slice1->percentage(),3,'f',1));
                slice1->setLabelVisible();
                slice1->setBrush(QColor(Qt::cyan));

            }
            if(femme!=0)
            {
                // Add labels to rest of slices
                QPieSlice *slice2 = series->slices().at(1);
                //slice1->setExploded();
                slice2->setLabel("Femmes "+QString("%1%").arg(100*slice2->percentage(),3,'f',1));
                slice2->setLabelVisible();
                slice2->setBrush(QColor(Qt::red));
            }

            // Create the chart widget
            QChart *chart = new QChart();
            // Add data to chart with title and hide legend
            chart->addSeries(series);
            chart->setTitle(" Totale "+ QString::number(total));

            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chart->legend()->hide();
            chartView->show();
}
//////////////////////////////////////////
////
///dorra

void MainWindow::update_label_dorra()
{


    /*int row =ui->tab_affaire->selectionModel()->currentIndex().row();
             int code=ui->tab_affaire->model()->index(row,0).data().toInt();

          //   A.classer(code);
         //    ui->tab_affaire->setModel(A.afficher());
             data=a.read_from_arduino();
             QByteArray text=QByteArray::fromHex(data);
             serialBuffer +=QString::fromStdString(data.toStdString());
              QSqlQuery query;
              QString t,t1;
              t="classé";
              t1="non classé";

            if( query.exec())
            {
               while (query.next())
               {
                   if(serialBuffer=="1"){
                       qDebug()<<"working";
                       query.prepare("UPDATE affaire SET etat='"+t+"' where id=:id");
                       query.bindValue(":id",code);}
                   else if (serialBuffer=="0"){
                       query.prepare("UPDATE affaire SET etat='"+t1+"' where id=:id");
                       query.bindValue(":id",code);}
                   }
               }*/




    data=A.read_from_arduino();// 1 ou 2 selon
    if (data == "1"){
        int row =ui->tab_affaire->selectionModel()->currentIndex().row();
                 int code=ui->tab_affaire->model()->index(row,0).data().toInt();// récupurer le code id du dossier

                 Aff.classer(code,"classe");
                  ui->tab_affaire->setModel(Aff.afficher());
    }

    else if (data == "2"){
        int row =ui->tab_affaire->selectionModel()->currentIndex().row();
                 int code=ui->tab_affaire->model()->index(row,0).data().toInt();

                 Aff.classer(code,"non classe");
         ui->tab_affaire->setModel(Aff.afficher());


}}
void MainWindow::on_pb_ajouter_clicked()
    {
        int id =ui->ln_id->text().toInt();//convertir to int
        QString date=ui->date->text();// récuprer la valeur par l'utilisteur
        QString type=ui->ln_type->text();
        QString etat=ui->comboBox_etatd->currentText();

        Affaire Aff(id,date,type,etat);
        bool testarchive = Aff.rechercheArchive();
        if (testarchive){
        bool test=Aff.ajouter();
        if (test){
         ui->tab_affaire->setModel(Aff.afficher());

                 QMessageBox::information(nullptr, QObject::tr("ok"),
                 QObject::tr("ajout effectué\n""Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBoxM->setModel(Aff.afficher());
        ui->comboBoxSupp->setModel(Aff.afficher());
        ui->ln_type->clear();
        //ui->ln_etat->clear();
     //ui->dateEditA->clear();
         ui->ln_id->clear();



}
  else{
     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                 QObject::tr("ajout non effectué\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
        }
        }

       else {
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("element existant dans l'archive\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

}









void MainWindow::on_pb_modifier_clicked()
{
    int id=ui->comboBoxM->currentText().toInt();

    QString type=ui->ln_typeM->text();
    QString date=ui->date->text();
    QString etat=ui->comboBox_etatd_mod->currentText();


      Affaire Am(id,date,type,etat); //int NumAff,QString type,QString dateinscrit,QString etataf,QString object

    bool test=Am.modifier(id);

          if(test)
        {
              //ui->comboBoxM->setModel(Am.afficher());
              ui->tab_affaire->setModel(Am.afficher());
              //ui->comboBox_2->setModel(Am.afficher());

        QMessageBox::information(nullptr, QObject::tr("modifier une affaire"),
                          QObject::tr("affaire modifiée.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
             //ui->comboBox->setModel(Am.afficher());

       // ui->comboBoxM->setModel(Am.afficher());
        ui->ln_typeM->clear();
        //ui->ln_etatM->clear();

        }
          else  QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                                       QObject::tr("ERREUR.\n"
                                                   "Click Cancel to exit."), QMessageBox::Cancel);

}



void MainWindow::makePlot()
{
    QSqlQuery q;
    QVector<double> stat(5);
    stat[0]=0;
    stat[1]=0;

    q.prepare("SELECT type FROM affaire WHERE etat='traite'");
    q.exec();
    while (q.next())
    {
        stat[0]++;

    }
    q.prepare("SELECT type FROM affaire WHERE etat='en cours'");
    q.exec();
    while (q.next())
    {
        stat[1]++;

    }
    // prepare data:
    QVector<double> x3(5), y3(20);
    for (int i=0; i<x3.size(); ++i)
    {
      x3[i] = i+1;

    }
    for (int i=0; i<y3.size(); ++i)
    {
      y3[i] = i+1;

    }

    QCPBars *bars1 = new QCPBars(ui->customplot->xAxis, ui->customplot->yAxis);
    bars1->setWidth(2/(double)x3.size());
    bars1->setData(x3, stat);//////////////////////////////////////////fonction statistiques
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(100, 0, 6, 170));
    ui->customplot->replot();

    // move bars above graphs and grid below bars:
    ui->customplot->addLayer("abovemain", ui->customplot->layer("main"), QCustomPlot::limAbove);
    ui->customplot->addLayer("belowmain", ui->customplot->layer("main"), QCustomPlot::limBelow);
    ui->customplot->xAxis->grid()->setLayer("belowmain");
    ui->customplot->yAxis->grid()->setLayer("belowmain");

    // set some pens, brushes and backgrounds:
    QVector<double> Ticks;
    Ticks<<1<<2<<3<<4<<5<<6<<7;////
    QVector<QString> labels;
    labels<<"traité"<<"en cours";////////////////////////////////////////
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(Ticks,labels);
    ui->customplot->xAxis->setTicker(textTicker);
    ui->customplot->xAxis->setSubTicks(false);
    ui->customplot->xAxis->setTickLength(0,4);
    ui->customplot->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setTickPen(QPen(Qt::transparent, 1));
    ui->customplot->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->customplot->xAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customplot->yAxis->setSubTickPen(QPen(Qt::transparent, 1));
    ui->customplot->xAxis->setTickLabelColor(Qt::white);
    ui->customplot->yAxis->setTickLabelColor(Qt::white);
    ui->customplot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->customplot->xAxis->grid()->setSubGridVisible(true);
    ui->customplot->yAxis->grid()->setSubGridVisible(true);
    ui->customplot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    ui->customplot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->customplot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(200, 50, 80));
    plotGradient.setColorAt(1, QColor(100, 20, 50));
    ui->customplot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(10, 50, 200));//
    axisRectGradient.setColorAt(1, QColor(0, 0, 200));
    ui->customplot->axisRect()->setBackground(axisRectGradient);

    ui->customplot->rescaleAxes();
    ui->customplot->xAxis->setRange(0, 7);
    ui->customplot->yAxis->setRange(0, 10);


}

void MainWindow::on_Push_stat_do_clicked()
{
    ui->customplot->clearPlottables();
    MainWindow::makePlot();
    MainWindow::makePlot();

}

void MainWindow::on_pushButton_archiverd_clicked()
{
    int id =ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(ui->tab_affaire->currentIndex().row(),0)).toInt();
    QString etat = ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(ui->tab_affaire->currentIndex().row(),3)).toString();
    QString date = ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(ui->tab_affaire->currentIndex().row(),1)).toString();
    QString type = ui->tab_affaire->model()->data(ui->tab_affaire->model()->index(ui->tab_affaire->currentIndex().row(),2)).toString();
    Affaire Aff(id ,date , type , etat) ;
    if(etat=="traite"){
    bool test = Aff.ajouterarchive();//ajouter dans le tableau archive
    bool test1 = Aff.supprimer(id);//suppression normale de notre tableau
    if((test)&&(test1))
    {
        //refresh

        ui->tab_affaire->setModel(Aff.afficher());
         ui->archiveView->setModel(Aff.afficherArchive());//mise à jour pour les deux affichages tableau archive view

        QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("archivé avec succes\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBoxM->setModel(Aff.afficher());
        ui->comboBoxSupp->setModel(Aff.afficher());


     }
              else
                  QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("error lors de l'archivage\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("not ok"),
                    QObject::tr("error:dossier an cours\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_pushButton_desarchiver_do_clicked()
{
    int id =ui->archiveView->model()->data(ui->archiveView->model()->index(ui->archiveView->currentIndex().row(),0)).toInt();
    QString etat = ui->archiveView->model()->data(ui->archiveView->model()->index(ui->archiveView->currentIndex().row(),3)).toString();
    QString date = ui->archiveView->model()->data(ui->archiveView->model()->index(ui->archiveView->currentIndex().row(),1)).toString();
    QString type = ui->archiveView->model()->data(ui->archiveView->model()->index(ui->archiveView->currentIndex().row(),2)).toString();
    Affaire A(id ,date , type , etat ) ;
    bool test = A.ajouter();//ajout retour de l'élément supprimé
    bool test1 = A.supprimerArchive(id);//supprimer de l'archive
    if((test)&&(test1))
    {
        //refresh

        ui->tab_affaire->setModel(A.afficher());
         ui->archiveView->setModel(A.afficherArchive());

        QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("desarchivé avec succes\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBoxM->setModel(A.afficher());
        ui->comboBoxSupp->setModel(A.afficher());


     }
              else
                  QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("error lors de desarchivage\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);


}



void MainWindow::on_pushButton_envoyer_d_clicked()
{
    {
        smtp = new Smtp("smartcourt2A34@gmail" , "smartcourt2A34", "smtp.gmail.com",465);//créer un constructeur paramétré
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));// des fonctions implimentés dans cette classe

        QString msg=ui->plainTextEdit_contenu_d->toPlainText();

        smtp->sendMail("dorra_test",ui->lineEdit_adress_d->text(),ui->lineEdit_objet_d->text(),msg);

        QMessageBox::information(nullptr, QObject::tr("SENT"),
                                 QObject::tr("Email Sent Successfully.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_lineEdit_recherche_d_textChanged(const QString &arg1)
{
    ui->tab_affaire->setModel(Aff.recherche(arg1));
}

void MainWindow::on_PDF_clicked()
{
        QPdfWriter pdf("C:/Users/Alpha/Desktop/test.pdf");
                QPainter painter(&pdf);
                int i = 4000;
                painter.setPen(Qt::blue);
                painter.setFont(QFont("Arial", 30));
                painter.drawText(3300,1200,"Liste Des affairess");
                painter.setPen(Qt::black);
                painter.setFont(QFont("Arial", 50));
                painter.drawRect(1500,200,7300,2600);
                painter.drawRect(0,3000,9600,500);
                painter.setFont(QFont("Arial", 9));
                painter.drawText(1300,3300,"ID");
                painter.drawText(2600,3300,"TYPE");
                painter.drawText(3900,3300,"DATE");
                painter.drawText(5200,3300,"ETAT");






                QSqlQuery query;
                query.prepare("select * from AFFAIRE");
                query.exec();
                while (query.next())
                {
                    painter.drawText(1300,i,query.value(0).toString());
                    painter.drawText(2600,i,query.value(1).toString());
                    painter.drawText(3900,i,query.value(2).toString());
                    painter.drawText(5200,i,query.value(3).toString());





                    i = i +500;
                }

                int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                if (reponse == QMessageBox::Yes)
                {
                    QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/firas/Desktop/test.pdf"));

                    painter.end();
                }
                if (reponse == QMessageBox::No)
                {
                    painter.end();

}
}



void MainWindow::on_pb_supprimer_d_clicked()
{
    int id=ui->comboBoxSupp->currentText().toInt();


    bool test=Aff.supprimer(id);
    if(test)
    {
        //refresh

        ui->tab_affaire->setModel(Aff.afficher());

        QMessageBox::information(nullptr, QObject::tr("ok"),
                              QObject::tr("suppression effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        ui->comboBoxM->setModel(Aff.afficher());
        ui->comboBoxSupp->setModel(Aff.afficher());


     }
              else
                  QMessageBox::critical(nullptr, QObject::tr("not ok"),
                              QObject::tr("suppression non effectué\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_tri_d_clicked()
{
    ui->tab_affaire->setModel(Aff.affichertri());
}
////////////////////////////////////////////////////////////////////////////// bechir
void MainWindow::on_Valider_clicked()
{

    QString Num=ui->lineEdit_id->text();
    QDateTime date=ui->dateTimeEdit->dateTime();

     QString heure=ui->lineEdit_heure->text();
     QString genre=ui->c_genre->currentText();



    Audiance aud(Num,date,heure,genre);
   bool test=aud.ajouter();
   QMessageBox msgBox;
   if(test)
   {
      msgBox.setText("ajouter avec succés");
   ui->tab->setModel(aud.afficher());
   }
   else {
       msgBox.setText("echec d'ajout");
   msgBox.exec();
}

}

void MainWindow::on_Update_clicked()
{
  QString Num=ui->lineEdit_id->text();
  QString heure=ui->lineEdit_heure->text();


         QDateTime date=ui->dateTimeEdit->dateTime();
         QString genre=ui->c_genre->currentText();
    Audiance aud(Num,date,heure,genre);
         bool test=aud.update(Num);
         if(test)
       {
            ui->tab->setModel(aud.afficher());

       QMessageBox::information(nullptr, QObject::tr("modifier un audiance"),
                         QObject::tr("audiance modifié.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);




       }
         else
             QMessageBox::critical(nullptr, QObject::tr("modifier un audiance"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

            ui->tab->setModel(aud.afficher());

}


void MainWindow::on_tab_activated(const QModelIndex &index)
{

    QSqlQuery query;

    QString val=ui->tab->model()->data(index).toString();
      query.prepare("Select * from AUDIANCE where NUM=:num");

      query.bindValue(":num",val);


      if(query.exec())
         {
             while(query.next())
             {

                 ui->lineEdit_id->setText(query.value(0).toString());
                 ui->dateTimeEdit->setDateTime(query.value(1).toDateTime());
                 ui->lineEdit_heure->setText(query.value(2).toString());

             }

}
}

void MainWindow::on_Update_2_clicked()
{



    Audiance aud ;
        aud.setNum(ui->le_id_sup->text());
        bool test=aud.supprimer(aud.getNUM());
        QMessageBox msgBox;
        if(test)
        {
             ui->tab->setModel(aud.afficher());
            msgBox.setText("suppression avec succés");
        }
        else{
            msgBox.setText("echeck de suppression");
        msgBox.exec();
}
}



void MainWindow::on_pushButton_2_clicked()
{
    ui->tab->setModel(aud.trieid());
}



void MainWindow::on_pushButton_4_clicked()
{
     ui->tab->setModel(aud.triehorloge());
}



void MainWindow::on_pushButton_6_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),

                                                          tr("Excel Files (*.xls)"));

          if (fileName.isEmpty())

              return;



          ExportExcelObject obj(fileName, "mydata", ui->tab);


          //colums to export

          obj.addField(0, "NUM", "char(20)");

          obj.addField(1, "HEURE", "char(20)");

          int retVal = obj.export2Excel();

          if( retVal > 0)

          {

              QMessageBox::information(this, tr("Done"),

                                       QString(tr("%1 records exported!")).arg(retVal)

                                       );

          }
}



void MainWindow::on_pushButton_3_clicked()
{
    QString strStream;
                QTextStream out(&strStream);

                const int rowCount = ui->tab->model()->rowCount();
                const int columnCount = ui->tab->model()->columnCount();
                QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                out <<"<html>\n"
                      "<head>\n"
                       "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                    << "<title> LISTE DES AUDIANCES <title>\n "
                    << "</head>\n"
                    "<body bgcolor=#ffffff link=#5000A0>\n"
                    "<h1 style=\"text-align: center;\"><strong> ***LISTE DES AUDIANCES *** "+TT+"</strong></h1>"
                    "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                      "</br> </br>";
                // headers
                out << "<thead><tr bgcolor=#d6e5ff>";
                for (int column = 0; column < columnCount; column++)
                    if (!ui->tab->isColumnHidden(column))
                        out << QString("<th>%1</th>").arg(ui->tab->model()->headerData(column, Qt::Horizontal).toString());
                out << "</tr></thead>\n";

                // data table
                for (int row = 0; row < rowCount; row++) {
                    out << "<tr>";
                    for (int column = 0; column < columnCount; column++) {
                        if (!ui->tab->isColumnHidden(column)) {
                            QString data =ui->tab->model()->data(ui->tab->model()->index(row, column)).toString().simplified();
                            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                        }
                    }
                    out << "</tr>\n";
                }
                out <<  "</table>\n"
                    "</body>\n"
                    "</html>\n";

                QTextDocument *document = new QTextDocument();
                document->setHtml(strStream);

                QPrinter printer;

                QPrintDialog *test = new QPrintDialog(&printer, NULL);
                if (test->exec() == QDialog::Accepted) {
                    document->print(&printer);
                }

                delete document;

}

void MainWindow::on_pushButton_5_clicked()
{
    QSqlQuery q1,q2,q3;
            qreal tot=0,c1=0,c2=0;
            q1.prepare("Select * from AUDIANCE");
            if(q1.exec())
            {
                while (q1.next())
                {
                    tot++;
                }
            }
            q2.prepare("Select * from AUDIANCE where genre ='Homme'");
            if(q2.exec())
            {
                while (q2.next())
                {
                    c1++;
                }
            }
            q3.prepare("Select * from AUDIANCE where genre ='Femme'");
            if(q3.exec())
            {
                while (q3.next())
                {
                    c2++;
                }
            }

            c1=c1/tot;
            c2=c2/tot;


            QPieSeries *series = new QPieSeries();
                    series->append("Homme",c1);
                    series->append("Femme",c2);

                    QPieSlice *slice0 = series->slices().at(0);
                    slice0->setExploded();
                    slice0->setLabelVisible();
                    slice0->setPen(QPen(Qt::darkGray, 2));
                    slice0->setBrush(Qt::gray);
                    QPieSlice *slice1 = series->slices().at(1);
                    slice1->setExploded();
                    slice1->setLabelVisible();
                    slice1->setPen(QPen(Qt::darkRed, 2));
                    slice1->setBrush(Qt::red);

                    QChart *chart = new QChart();
                    chart->addSeries(series);
                    chart->setTitle("les genres");
                    chart->setAnimationOptions(QChart::AllAnimations);
                    chart->legend()->hide();
                    QChartView *chartView = new QChartView(chart);
                    chartView->setRenderHint(QPainter::Antialiasing);
                    QGridLayout *layout = new QGridLayout();
                    layout->addWidget(chartView);
                    ui->statistiques_2->setLayout(layout);
}

void MainWindow::on_pushButton_search_bechir_clicked()
{
    /*QString id=ui->lineEdit_recherche->text();
    ui->tab->setModel(ent.rechercher());*/
    class Audiance aud ;

    ui->tab->setModel(aud.afficher());


           aud.rechercher(ui);

}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_menu_juges_clicked()
{
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_menu_invites_clicked()
{
    bool nom;
    bool mp;
    QString Nom;
    QString mdp;
    QMessageBox msgBox;
    QInputDialog* i = new QInputDialog(this);

    do{
     Nom = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Nom d'utilisateur:"), QLineEdit::Normal,
                                           "", &nom);
      mdp = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Mot de passe :"), QLineEdit::Normal,
                                           "", &mp);
      if ((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()))
      {
          msgBox.setText("Veuillez saisir le nom d'utilsateur et le mot de passe !");
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.exec();
      }
    }while((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()));
      if (nom && mp)
      {
      if (Nom == "invites" && mdp == "admin")
      {
          msgBox.setText("Connecté !");
          msgBox.setIcon(QMessageBox::Information);
          msgBox.exec();
        ui->stackedWidget->setCurrentIndex(3);
      }
      else
      {

         msgBox.setText("Nom d'utilsateur ou mot de passe erroné !");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
      }
      }


}

void MainWindow::on_pushButton_men_audience_clicked()
{
    bool nom;
    bool mp;
    QString Nom;
    QString mdp;
    QMessageBox msgBox;
    QInputDialog* i = new QInputDialog(this);

    do{
     Nom = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Nom d'utilisateur:"), QLineEdit::Normal,
                                           "", &nom);
      mdp = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Mot de passe :"), QLineEdit::Normal,
                                           "", &mp);
      if ((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()))
      {
          msgBox.setText("Veuillez saisir le nom d'utilsateur et le mot de passe !");
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.exec();
      }
    }while((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()));
      if (nom && mp)
      {
      if (Nom == "audiences" && mdp == "admin")
      {
          msgBox.setText("Connecté !");
          msgBox.setIcon(QMessageBox::Information);
          msgBox.exec();
        ui->stackedWidget->setCurrentIndex(5);
      }
      else
      {

         msgBox.setText("Nom d'utilsateur ou mot de passe erroné !");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
      }
      }
}

void MainWindow::on_pushButton_menu_last_clicked()
{
    bool nom;
    bool mp;
    QString Nom;
    QString mdp;
    QMessageBox msgBox;
    QInputDialog* i = new QInputDialog(this);

    do{
     Nom = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Nom d'utilisateur:"), QLineEdit::Normal,
                                           "", &nom);
      mdp = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Mot de passe :"), QLineEdit::Normal,
                                           "", &mp);
      if ((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()))
      {
          msgBox.setText("Veuillez saisir le nom d'utilsateur et le mot de passe !");
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.exec();
      }
    }while((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()));
      if (nom && mp)
      {
      if (Nom == "avocat" && mdp == "admin")
      {
          msgBox.setText("Connecté !");
          msgBox.setIcon(QMessageBox::Information);
          msgBox.exec();
        ui->stackedWidget->setCurrentIndex(6);
      }
      else
      {

         msgBox.setText("Nom d'utilsateur ou mot de passe erroné !");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
      }
      }
}

void MainWindow::on_pushButton_menu_affaires_clicked()
{
    bool nom;
    bool mp;
    QString Nom;
    QString mdp;
    QMessageBox msgBox;
    QInputDialog* i = new QInputDialog(this);

    do{
     Nom = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Nom d'utilisateur:"), QLineEdit::Normal,
                                           "", &nom);
      mdp = i->getText(this, tr("QInputDialog::getText()"),
                                           tr("Mot de passe :"), QLineEdit::Normal,
                                           "", &mp);
      if ((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()))
      {
          msgBox.setText("Veuillez saisir le nom d'utilsateur et le mot de passe !");
          msgBox.setIcon(QMessageBox::Critical);
          msgBox.exec();
      }
    }while((nom && mp) && (Nom.isEmpty() || mdp.isEmpty()));
      if (nom && mp)
      {
      if (Nom == "affaire" && mdp == "admin")
      {
          msgBox.setText("Connecté !");
          msgBox.setIcon(QMessageBox::Information);
          msgBox.exec();
        ui->stackedWidget->setCurrentIndex(4);
      }
      else
      {

         msgBox.setText("Nom d'utilsateur ou mot de passe erroné !");
         msgBox.setIcon(QMessageBox::Critical);
         msgBox.exec();
      }
      }
}

void MainWindow::on_pushButton_deco_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


////////////////////////////////////////
///
void MainWindow::on_pb_ajouter_2_clicked()
{
    QString num_tel=ui->le_num_tel->text();
    QString nom=ui->le_nom_2->text();
    QString prenom=ui->le_prenom_2->text();
    QString type=ui->le_type->currentText();
    Avocat a(num_tel,nom,prenom,type);
    bool test = a.ajouter();
        if (test)
        {
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("Ajout effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
        ui->tab_avocats->setModel(a.afficher());
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                     QObject::tr("Ajout non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_pb_supprimer_2_clicked()
{
    Avocat a1; a1.setnum(ui->le_num_tel_supp->text());
    bool test=a1.supprimer(a1.getnumtel());
    if (test)
    {
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("suppression effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
      ui->tab_avocats->setModel(av.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("suppression non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_linecomboBox_activated(int index)
{
    QString val= ui->linecomboBox->currentText();
      ui->tab_avocats->setModel(av.trier());
}


void MainWindow::on_pb_modifier_2_clicked()
{
    QString num_tel=ui->num_up_2->text();
     QString nom=ui->nom_up_2->text();
     QString prenom=ui->prenom_up_2->text();
     QString type=ui->type_up->currentText();
     Avocat A(num_tel, nom, prenom,type);
     bool test=A.modifier();
     if (test)
     {
         QMessageBox::information(nullptr,QObject::tr("OK"),
                                  QObject::tr("modification effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
       ui->tab_avocats->setModel(A.afficher());
     }
     else
         QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                  QObject::tr("modification non effectué \n" "Click cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_pb_rechercher_clicked()
{
    QString num_tel=ui->le_num_tel_recherche->text();
     ui->tab_avocats_2->setModel(av.recherche(num_tel));
}


void MainWindow::on_pb_stat_clicked()
{
    QSqlQuery q1,q2,q3,q4,q5;
        qreal tot=0,c1=0,c2=0,c3=0,c4=0;
        q1.prepare("Select * from AVOCAT");
        if(q1.exec())
        {
            while (q1.next())
            {
                tot++;
            }
        }
        q2.prepare("Select * from AVOCAT where TYPE ='droit des personnes'");
        if(q2.exec())
        {
            while (q2.next())
            {
                c1++;
            }
        }
        q3.prepare("Select * from AVOCAT where TYPE ='droit immobilier'");
        if(q3.exec())
        {
            while (q3.next())
            {
                c2++;
            }
        }
        q4.prepare("Select * from AVOCAT where TYPE ='droit public'");
        if(q4.exec())
        {
            while (q4.next())
            {
                c3++;
            }
        }
        q5.prepare("Select * from AVOCAT where TYPE ='droit commercial'");
        if(q5.exec())
        {
                while (q5.next())
                {
                    c4++;
                }
            }
            c1=c1/tot;
            c2=c2/tot;
            c3=c3/tot;
            c4=c4/tot;

            QPieSeries *series = new QPieSeries();
                    series->append("droit des personnes",c1);
                    series->append("droit immobilier",c2);
                    series->append("droit public",c3);
                    series->append("droit commercial",c4);
                    QPieSlice *slice0 = series->slices().at(0);
                    slice0->setExploded();
                    slice0->setLabelVisible();
                    slice0->setPen(QPen(Qt::darkGray, 2));
                    slice0->setBrush(Qt::gray);
                    QPieSlice *slice1 = series->slices().at(1);
                    slice1->setExploded();
                    slice1->setLabelVisible();
                    slice1->setPen(QPen(Qt::darkRed, 2));
                    slice1->setBrush(Qt::red);
                    QPieSlice *slice2 = series->slices().at(2);
                    slice2->setExploded();
                    slice2->setLabelVisible();
                    slice2->setPen(QPen(Qt::darkYellow, 2));
                    slice2->setBrush(Qt::yellow);
                    QPieSlice *slice3 = series->slices().at(3);
                    slice3->setExploded();
                    slice3->setLabelVisible();
                    slice3->setPen(QPen(Qt::darkGreen, 2));
                    slice3->setBrush(Qt::green);
                    QChart *chart = new QChart();
                    chart->addSeries(series);
                    chart->setTitle("most types");
                                chart->setAnimationOptions(QChart::AllAnimations);
                                chart->legend()->hide();
                                QChartView *chartView = new QChartView(chart);
                                chartView->setRenderHint(QPainter::Antialiasing);
                                QGridLayout *layout = new QGridLayout();
                                layout->addWidget(chartView);
                                ui->stat->setLayout(layout);

}


void MainWindow::on_pb_pdf_2_clicked()
{
    QString num_tel=ui->num_tel_pdf->text();
       QString z=av.pdf(num_tel);
       ui->tab_avocats_3->setText(z);
       QPrinter printer;
           printer.setPrinterName("Avocat");
           printer.setPageSize(QPrinter::A4);
           QPrintDialog dialog(&printer,this);
           if (dialog.exec()== QDialog::Rejected)
           return;
           ui->tab_avocats_3->print(&printer);
}

