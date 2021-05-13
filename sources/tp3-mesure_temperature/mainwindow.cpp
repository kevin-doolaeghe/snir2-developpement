#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    temp = new DS1620_P8055(0); //Carte Velleman et sonde de température
    timer = new QTimer();
    graph = new Chart(ui->widgetGraph); //Graphique

    graph->setTitle("Température en fonction du temps");
    graph->setTraceName("Température");

    nbTempVal = 0; //Initialisation

    connect(timer, SIGNAL(timeout()), this, SLOT(majAutoTemp())); //Appel de la méthode majAutoTemp() dès que le timer renvoie un timeout
}

MainWindow::~MainWindow()
{
    delete ui;
    delete temp;
    delete timer;
    delete graph;
}

void MainWindow::on_pushButton_lance_clicked()
{
    temp->lance_conv(); //Lancer de la conversion
}

void MainWindow::on_pushButton_stop_clicked()
{
    temp->stop_conv(); //Stopper la conversion
}

void MainWindow::on_pushButton_lire_temp_clicked()
{
    majTemp();
    /*
     * Lire la température
     * Afficher la température
     * Aficher le graphique
     */
}

void MainWindow::majAutoTemp()
{ //Mise à jour automatique de la température
    temp->lance_conv(); //Lancer la conversion
    Sleep(1200); //Pause de 1,5 sec

    temp->stop_conv(); //Stopper la conversion
    Sleep(1200);

    majTemp(); //Mise à jour de la température
}

void MainWindow::majTemp()
{
    short tp_9bits = temp->lect_temp(); /*
                                         * Lecture de la température et stockage sur 16 bits
                                         * LSB -> demi
                                         * b1 à b8 -> donnée
                                         * b9 à MSB -> Inutile
                                         */

    char temperature = (char) tp_9bits >> 1; //Récupération de la température sur 8 bits en entier
    float tempFloat = temperature; //Pour graphique

    //Test de demi
    bool demi = false;
    if(tp_9bits & 1) demi = true;

    //Graphique
    if(demi) tempFloat += 0.5;
    graph->addValue(tempFloat);

    nbTempVal++; //Num. valeur

    //Affichage
    graph->update(); //MàJ graphique

    ui->label_nbVal->setText("Valeur n°" + QString::number(nbTempVal));

    if(demi) ui->label_temp->setText(QString::number(temperature) + ".5 °C");
    else ui->label_temp->setText(QString::number(temperature) + " °C");
}

void MainWindow::on_pushButton_toggleAutoVal_clicked()
{
    if(timer->isActive())
    { //Activation MàJ auto.
        timer->stop(); //Stoppe le timer
        ui->pushButton_toggleAutoVal->setText("Valeurs auto. : Off"); //Changement du texte
    }
    else
    { //Désactivation MàJ auto.
        timer->start(8000); //Met en marche le timer toutes les 8 secondes
        ui->pushButton_toggleAutoVal->setText("Valeurs auto. : On");
    }
}
