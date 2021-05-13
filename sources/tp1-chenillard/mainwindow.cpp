#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chenillard = new Chenillard_p8055(0);
    connect(chenillard->timer,SIGNAL(timeout()),this,SLOT(declencheTimerChenillard()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete chenillard;
}

void MainWindow::on_pushButton_lance_clicked()
{
    unsigned char octet = 0;
    if(ui->checkBox_1->isChecked()) octet |= 128;
    if(ui->checkBox_2->isChecked()) octet |= 64;
    if(ui->checkBox_3->isChecked()) octet |= 32;
    if(ui->checkBox_4->isChecked()) octet |= 16;
    if(ui->checkBox_5->isChecked()) octet |= 8;
    if(ui->checkBox_6->isChecked()) octet |= 4;
    if(ui->checkBox_7->isChecked()) octet |= 2;
    if(ui->checkBox_8->isChecked()) octet |= 1;
    octet = -octet;

    chenillard->lance(octet);
}

void MainWindow::on_pushButton_stop_clicked()
{
    chenillard->stop();
}

void MainWindow::on_horizontalSlider_valueChanged(int vitesse)
{
    chenillard->vitesse(vitesse);
}

void MainWindow::declencheTimerChenillard()
{
    chenillard->fonction_Timer();
}

void MainWindow::on_pushButton_sens_clicked()
{
    chenillard->sens();
}
