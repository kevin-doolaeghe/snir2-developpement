#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vitesse = 0; //Vitesse
    sens = 0; //Sens inverse
    moteurSelec = 0; //Moteur droit
}

MainWindow::~MainWindow()
{
    delete ui;

    moteur->close(); //Fermeture de la liaison série
    delete moteur; //Suppression de l'objet du pointeur moteur
}

void MainWindow::on_comboBox_port_currentIndexChanged(int index)
{
    if(moteur->getAck() != -1) //Si liaison ouverte
    { //Fermeture de la liaison
        moteur->close(); //Fermeture
    }

    QString com = "COM" + QString::number(index + 1); //Choix du port

    moteur = new Usb_I2c((char *) com.toStdString().c_str()); //Instanciation de l'objet Usb_I2c au pointeur moteur

    if(moteur->getAck() != -1) //Si la connexion a réussi
    {
        ui->comboBox_moteur->setEnabled(true); //Active la le choix du moteur
        ui->pushButton_demarrer->setEnabled(true); //Active le démarrage du moteur
        ui->pushButton_sens->setEnabled(true); //Active le changement du sens
        ui->horizontalScrollBar_vitesse->setEnabled(true); //Active le changement de la vitesse

        //Initialise le moteur
        unsigned char data[4] = {1, 0, 0, 200}; //Mode 1 : -127 à 128, vitesse des moteurs gauche et droit à 0, accélération à 200 (12.8ms)
        moteur->ecrit_I2C_AD1(0xb0, 0, 4, data); //Ecrit les 4 premiers registres avec les données.
    }
}

void MainWindow::on_comboBox_moteur_currentIndexChanged(int index)
{
    if(index == 1) //Si on choisit le moteur gauche
    {
        moteurSelec = 1; //Moteur gauche
    }
    else //Si on choisis le moteur droit
    {
        moteurSelec = 0; //Moteur droit
    }
}

void MainWindow::on_pushButton_demarrer_clicked()
{
    if(ui->pushButton_demarrer->text() == "Démarrer moteur")
    { //Si démarrage demandé
        if(moteurSelec == 0 && sens == 0)
        { //Si le moteur sélectionné est le droit et que le sens est horaire
            unsigned char data = vitesse; //Vitesse dans le sens horaire
            moteur->ecrit_I2C_AD1(0xb0, 1, 1, &data); //Change la vitesse du moteur droit dans le sens horaire
        }

        if(moteurSelec == 0 && sens == 1)
        { //Si le moteur sélectionné est le droit et que le sens est inverse
            unsigned char data = -vitesse; //Vitesse dans le sens inverse
            moteur->ecrit_I2C_AD1(0xb0, 1, 1, &data); //Change la vitesse du moteur droit dans le sens inverse
        }

        if(moteurSelec == 1 && sens == 0)
        { //Si le moteur sélectionné est le gauche et que le sens est horaire
            unsigned char data = vitesse; //Vitesse dans le sens horaire
            moteur->ecrit_I2C_AD1(0xb0, 2, 1, &data); //Change la vitesse du moteur droit dans le sens horaire
        }

        if(moteurSelec == 1 && sens == 1)
        { //Si le moteur sélectionné est le gauche et que le sens est inverse
            unsigned char data = -vitesse; //Vitesse dans le sens inverse
            moteur->ecrit_I2C_AD1(0xb0, 2, 1, &data); //Change la vitesse du moteur droit dans le sens inverse
        }

        ui->pushButton_demarrer->setText("Arrêter moteur"); //Changement de l'affichage

        ui->comboBox_moteur->setEnabled(false); //Désactive le changement du moteur
        ui->pushButton_sens->setEnabled(false); //Désactive le changement du sens
    }
    else
    { //Si arrêt demandé
        if(moteurSelec == 0)
        { //Si moteur droit
            unsigned char data[1] = {0}; //Vitesse à 0
            moteur->ecrit_I2C_AD1(0xb0, 1, 1, data); //Arrêt du moteur droit
        }
        else
        { //Si moteur gauche
            unsigned char data[1] = {0}; //Vitesse à 0
            moteur->ecrit_I2C_AD1(0xb0, 2, 1, data); //Arrêt du moteur gauche
        }

        ui->pushButton_demarrer->setText("Démarrer moteur"); //Changement de l'affichage

        ui->comboBox_moteur->setEnabled(true); //Active le changement du moteur
        ui->pushButton_sens->setEnabled(true); //Active le changement du sens
    }
}

void MainWindow::on_pushButton_sens_clicked()
{ //Change le sens de rotation du moteur après l'arrêt
    if(sens == 0)
    {
        sens = 1; //Horaire
        ui->pushButton_sens->setText("Sens inverse");
    }
    else
    {
        sens = 0; //Inverse
        ui->pushButton_sens->setText("Sens horaire");
    }
}

void MainWindow::on_horizontalScrollBar_vitesse_valueChanged(int value)
{
    vitesse = (unsigned char) value; //Valeur entre 0 et 127 compris

    on_pushButton_demarrer_clicked(); //Mise à jour
    on_pushButton_demarrer_clicked(); //Retour à l'état de base

    double pourcentage = (double) vitesse / 1.27; //Calcul de la vitesse (écart par rapport à la vitesse max.)
    ui->label_vitesse->setText("Vitesse : " + QString::number(pourcentage) + "%"); //Mise à jour de l'affichage de la vitesse
}
