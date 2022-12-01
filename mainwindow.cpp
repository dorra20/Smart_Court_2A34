#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"invite.h"
#include<QMessageBox>
#include<QIntValidator>
#include <QObject>
#include<QSqlQuery>
#include<QTextStream>
#include<QTextDocument>
#include<QPainter>
#include<QPrinter>
#include<QPrintDialog>
#include<QFileDialog>
#include <QtCharts/QtCharts>
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->le_cin->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_invite->setModel(I.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


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
      ui->tab_invite->setModel(I.afficher());}
  else
  {msgBox.setText("echec de modification");
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


void MainWindow::on_pushButton_clicked()
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
