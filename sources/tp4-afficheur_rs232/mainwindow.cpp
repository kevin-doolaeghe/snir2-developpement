#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    aff_lcd = new LCD_RS232();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete aff_lcd; //Supprime l'objet instancié au pointeur
}

void MainWindow::on_pushButton_desactive_re_clicked()
{
    if(isRE) //Si le rétro-éclairage est activé
    {
        aff_lcd->desactive_RE(); //Désactive le RE
        isRE = false; //Rétro-éclairage désactivé
        ui->pushButton_desactive_re->setText("Activer RE"); //Change le texte du bouton
    }
    else //Sinon
    { //Inverse
        aff_lcd->active_RE();
        isRE = true;
        ui->pushButton_desactive_re->setText("Désactiver RE");
    }
}

void MainWindow::on_pushButton_envoyer_a_clicked()
{
    aff_lcd->aff_car('A'); //Affiche 'a'
}

void MainWindow::on_comboBox_port_currentIndexChanged(int index)
{
    //Trouve le port
    char num = (char) index + 48;
    char com[5] = {'C', 'O', 'M', num};

    if(aff_lcd->isOpen()) //Si connecté
        aff_lcd->close(); //Déconnexion

    //Connexion
    aff_lcd->open(com, 115200); //"COM4", 115200);

    if(aff_lcd->isOpen()) //Si l'afficheur est connecté
    {
        //Active tous les boutons
        ui->pushButton_active_cur->setEnabled(true);
        ui->pushButton_afficher_date->setEnabled(true);
        ui->pushButton_afficher_heure->setEnabled(true);
        ui->pushButton_afficher_texte->setEnabled(true);
        ui->pushButton_defiler->setEnabled(true);
        ui->pushButton_desactive_re->setEnabled(true);
        ui->pushButton_effacer_lcd->setEnabled(true);
        ui->pushButton_envoyer_a->setEnabled(true);
        ui->pushButton_pos_cur->setEnabled(true);
        ui->pushButton_car_spe->setEnabled(true);

        //Active le curseur
        aff_lcd->active_curseur();
        isCur = true;

        //Désactive le rétro-éclairage
        aff_lcd->desactive_RE();
        isRE = false;

        //Vitesse minimale
        vitesse = 1;
    }
    else
    {
        //Désactive tous les boutons
        ui->pushButton_active_cur->setEnabled(false);
        ui->pushButton_afficher_date->setEnabled(false);
        ui->pushButton_afficher_heure->setEnabled(false);
        ui->pushButton_afficher_texte->setEnabled(false);
        ui->pushButton_defiler->setEnabled(false);
        ui->pushButton_desactive_re->setEnabled(false);
        ui->pushButton_effacer_lcd->setEnabled(false);
        ui->pushButton_envoyer_a->setEnabled(false);
        ui->pushButton_pos_cur->setEnabled(false);
        ui->pushButton_car_spe->setEnabled(false);
    }
}

void MainWindow::on_pushButton_active_cur_clicked()
{
    if(isCur) //Si le curseur est affiché
    {
        aff_lcd->desactive_curseur(); //Désactive le curseur
        isCur = false; //Curseur désactivé
        ui->pushButton_active_cur->setText("Activer curseur"); //Change le texte du bouton
    }
    else //Sinon
    { //Inverse
        aff_lcd->active_curseur();
        isCur = true;
        ui->pushButton_active_cur->setText("Désactiver curseur");
    }
}

void MainWindow::on_pushButton_afficher_texte_clicked()
{
    aff_lcd->aff_texte(ui->lineEdit_texte->text()); //Affiche le texte
}

void MainWindow::on_pushButton_effacer_lcd_clicked()
{
    aff_lcd->efface_LCD(); //Efface l'écran
}

void MainWindow::on_pushButton_pos_cur_clicked()
{
    aff_lcd->position_curseur(ui->lineEdit_X->text().toInt(), ui->lineEdit_Y->text().toInt());
}

void MainWindow::on_pushButton_afficher_date_clicked()
{
    aff_lcd->position_curseur(0, 1);

    aff_lcd->aff_texte(QDateTime::currentDateTime().toString("dd/MM/yy")); //Affiche la date
}

void MainWindow::on_pushButton_afficher_heure_clicked()
{
    aff_lcd->position_curseur(8, 1);

    aff_lcd->aff_texte(QDateTime::currentDateTime().toString("hh:mm:ss")); //Affiche l'heure
}

void MainWindow::on_pushButton_defiler_clicked()
{
    aff_lcd->defile(vitesse); //Fait défiler l'écran
}

void MainWindow::on_horizontalScrollBar_defiler_valueChanged(int value)
{
    vitesse = value * 10; //met à jour la vitesse de défilement
}

void MainWindow::on_pushButton_car_spe_clicked()
{
    CaracSpe car(aff_lcd); //Ouvre une fenêtre de dialogue
    car.exec();
}
