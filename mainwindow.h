#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPrinter>
#include <QPrintDialog>
#include <QMainWindow>

#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlQuery>
#include <QApplication>
#include <QtCharts/QLegend>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "juge.h"
#include "affaire.h"

//////////////////////////////////////// login
#include <QPrinter>
#include <QPrintDialog>
#include "login_juge.h"
#include "juge.h"
#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>


//////////////////////////////////// lina
#include "arduino.h"
#include "invite.h"
#include "smtp.h"

/////////////////////////////////////// bechir
#include <QMainWindow>
#include<QSqlTableModel>
#include<QTableView>
#include "audiance.h"
#include <QTimer>
#include <QWidget>
#include <QGroupBox>
#include <QSystemTrayIcon>
#include <QToolTip>
#include <QMenu>
#include <QDialog>
#include <QtQuick/QQuickWindow>
#include <QtQuick/QQuickRenderControl>
#include <QtQml/QQmlComponent>
#include <QtQuickControls2/QtQuickControls2>
#include <QFileDialog>
#include <QFileInfo>
#include <exportexcelobject.h>
#include <QtPrintSupport/QPrinterInfo>
#include <QPrinter>
/////////////
///
///
#include "avocat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    ///////////////////////////////////////////// login

    void on_b_connexion_clicked();

    void on_b_inscrire_clicked();

    void on_b_recuperation_clicked();

    void update_label();

    //////////////////////////
    void on_pushButton_clicked();

    void on_b_supp_clicked();

    void on_b_maj_clicked();

    void on_bt_imprimer_juge_clicked();

    void on_tri1_clicked();

    void on_tri2_clicked();

    void on_b_recherhcer_clicked();

    void on_tri3_clicked();

    void on_tri4_clicked();

    void on_tri5_clicked();

    void on_actionstat_triggered();

    void on_stats_clicked();
    //////////////////////////////////////////////////////////// lina

    void on_bouton_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_7_clicked();

    void on_pb_pdf_clicked();

    void on_pb_trier_clicked();

    void on_line_rech_textChanged(const QString &arg1);

    void on_pb_afficher_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_envoyer_mail_l_clicked();

    void update_ard();

    void on_pushButton_porte_clicked();

    void on_pushButton_stat_lina_clicked();
    /////////////////////////////////////////////////////////////// dorra

    void on_pb_ajouter_clicked();

    void on_pb_modifier_clicked();

    //void on_pushButton_clicked();

    void on_Push_stat_do_clicked();

    void makePlot();

    void on_pushButton_archiverd_clicked();

    void on_pushButton_desarchiver_do_clicked();

    void on_pushButton_envoyer_d_clicked();

    void on_lineEdit_recherche_d_textChanged(const QString &arg1);

    void on_PDF_clicked();

    void update_label_dorra();

    void on_pb_supprimer_d_clicked();

    void on_pushButton_tri_d_clicked();

    //////////////////////////////////////////////////////// bechir audience
    void on_Valider_clicked();

    void on_Update_clicked();

    void on_tab_activated(const QModelIndex &index);

    void on_Update_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_search_bechir_clicked();
   /////////////////////////
    void on_pushButton_menu_juges_clicked();

    void on_pushButton_menu_invites_clicked();

    void on_pushButton_men_audience_clicked();

    void on_pushButton_menu_last_clicked();

    void on_pushButton_menu_affaires_clicked();

    void on_pushButton_deco_clicked();

    //////////////////////////
    ///
    void on_pb_ajouter_2_clicked();

    void on_pb_supprimer_2_clicked();

    void on_linecomboBox_activated(int index);

    void on_pb_modifier_2_clicked();

    void on_pb_rechercher_clicked();

    void on_pb_stat_clicked();

    void on_pb_pdf_2_clicked();

private:
    Ui::MainWindow *ui;
    Juge J;
    Login_juge L;
    Arduino A ;
    Invite I;
    Smtp * S;
    Affaire Aff;
    Smtp* smtp;
    QByteArray data;
    QString serialb;
    Audiance aud ;
    Avocat av;
};

#endif // MAINWINDOW_H
