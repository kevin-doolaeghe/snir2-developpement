#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Création du thread avec le label comme paramètre pour modifier l'affichage
    threadEncodeur = new ClassThreadConsigne(ui->label_consigne);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete threadEncodeur; //Destruction du thread
}

void MainWindow::on_pushButton_quitter_clicked()
{
    this->close(); //Ferme le programme
}

void MainWindow::on_pushButton_demarrer_clicked()
{
    if(ui->pushButton_demarrer->text() == "Démarrer")
    { //Démarrage de la lecture
        threadEncodeur->lanceThread(); //Démarrage du thread de lecture
        ui->pushButton_demarrer->setText("Arrêter"); //Changement du texte
    }
    else
    { //Arrêt de la lecture
        threadEncodeur->stopThread(); //Arrêt du thread de lecture
        ui->pushButton_demarrer->setText("Démarrer"); //Changement du texte
    }
}
