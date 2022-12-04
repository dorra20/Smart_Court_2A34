#ifndef LOGIN_H
#define LOGIN_H
#include <QPrinter>
#include <QPrintDialog>
#include <QMainWindow>
#include "login_juge.h"
#include "juge.h"
#include "mainwindow.h"
#include "arduino.h"
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_b_connexion_clicked();

    void on_b_inscrire_clicked();

    void on_b_recuperation_clicked();

    void update_label();

private:
    Ui::Login *ui;
    Login_juge L;
    MainWindow *M;
    Arduino A;
QByteArray data;
QString serialb;
};

#endif // LOGIN_H
