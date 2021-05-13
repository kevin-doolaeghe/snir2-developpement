#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    afficheur = new LCD8055(0); //Instanciation de la classe LCD8055 dans afficheur
}

MainWindow::~MainWindow()
{
    delete ui;
    delete afficheur;
}

void MainWindow::on_pushButton_afficher_clicked()
{
    QString str; //QString pour récupérer la chaîne
    char ligne[17]; //Tableau de caractères pour la méthode

    afficheur->clear_aff(); //Effacement de l'écran

    str = ui->lineEdit_ligne1->text(); //Récupération du texte de la ligne 1
    strcpy(ligne, str.toStdString().c_str()); //Conversion et copie de la chaîne dans le tableau de caractères

    afficheur->aff_texte(ligne); //Affichage

    afficheur->pos_curseur(1, 0); //Positionnement du curseur à la deuxième ligne

    //Idem que ci-dessus mais pour la deuxième ligne
    str = ui->lineEdit_ligne2->text();
    strcpy(ligne, str.toStdString().c_str());

    afficheur->aff_texte(ligne);
}

void MainWindow::on_pushButton_init_clicked()
{
    afficheur->init_LCD(); //Initialisation
}

void MainWindow::on_pushButton_A_clicked()
{
    afficheur->aff_car('A'); //Affichage
}

void MainWindow::on_pushButton_clear_clicked()
{
    afficheur->clear_aff(); //Effacement de l'écran
}

void MainWindow::on_pushButton_bonjour_clicked()
{
    afficheur->aff_texte("bonjour"); //Affichage
}

void MainWindow::on_pushButton_validCurs_clicked()
{
    bool ligne = false;
    int colonne = 0;

    if(ui->checkBox_ligne->isChecked()) ligne = 1;
    colonne = ui->checkBox_ligne->text().toInt() - 1;

    afficheur->pos_curseur(ligne, colonne); //Déplacement du curseur
}
