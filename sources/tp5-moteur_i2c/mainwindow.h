#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usb_i2c.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_comboBox_port_currentIndexChanged(int index);

    void on_comboBox_moteur_currentIndexChanged(int index);

    void on_pushButton_demarrer_clicked();

    void on_pushButton_sens_clicked();

    void on_horizontalScrollBar_vitesse_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    Usb_I2c *moteur; //Pointeur du moteur (liaison série)
    unsigned char vitesse; //Contient la vitesse du moteur
    bool sens; //Sens de rotation
    bool moteurSelec; //Moteur gauche ou droit
};

#endif // MAINWINDOW_H
