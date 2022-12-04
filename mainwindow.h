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


//////////////////////////////////// lina
#include "arduino.h"
#include "invite.h"
#include "smtp.h"

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

    void update_ard();

    void on_pushButton_porte_clicked();

    void on_pushButton_stat_lina_clicked();
    ///////////////////////////////////////////////////////////////
private:
    Ui::MainWindow *ui;
    Juge J;
    Arduino A ;
    Invite I;
    Smtp * S;
};

#endif // MAINWINDOW_H
