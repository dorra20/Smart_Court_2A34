#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"invite.h"
#include "smtp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void affichage();

private slots:
    void on_bouton_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pushButton_7_clicked();

    void on_pb_pdf_clicked();

    void on_pb_trier_clicked();

    void on_line_rech_textChanged(const QString &arg1);

    void on_pb_afficher_clicked();

    void on_pushButton_excel_clicked();

    void on_pushButton_clicked();

    void on_pushButton_envoyer_mail_l_clicked();

private:
    Ui::MainWindow *ui;
    Invite I;
    Smtp * S;
};
#endif // MAINWINDOW_H
