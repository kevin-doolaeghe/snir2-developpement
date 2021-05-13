#include "caracspe.h"
#include "ui_caracspe.h"

CaracSpe::CaracSpe(LCD_RS232 *aff_lcd, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CaracSpe)
{
    ui->setupUi(this);

    this->aff_lcd = aff_lcd; //Pointe vers l'afficheur transmis

    for(int i = 0; i < 40; i++)
        checked[i] = false;

    //Initialise le caractère à 0
    for(int i = 0; i < 8; i++)
        car[i] = 0;
}

CaracSpe::~CaracSpe()
{
    delete ui;
}

void CaracSpe::on_pushButton_reset_clicked()
{ //Décoche les cases
    ui->checkBox_1->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);
    ui->checkBox_8->setChecked(false);
    ui->checkBox_9->setChecked(false);
    ui->checkBox_10->setChecked(false);
    ui->checkBox_11->setChecked(false);
    ui->checkBox_12->setChecked(false);
    ui->checkBox_13->setChecked(false);
    ui->checkBox_14->setChecked(false);
    ui->checkBox_15->setChecked(false);
    ui->checkBox_16->setChecked(false);
    ui->checkBox_17->setChecked(false);
    ui->checkBox_18->setChecked(false);
    ui->checkBox_19->setChecked(false);
    ui->checkBox_20->setChecked(false);
    ui->checkBox_21->setChecked(false);
    ui->checkBox_22->setChecked(false);
    ui->checkBox_23->setChecked(false);
    ui->checkBox_24->setChecked(false);
    ui->checkBox_25->setChecked(false);
    ui->checkBox_26->setChecked(false);
    ui->checkBox_27->setChecked(false);
    ui->checkBox_28->setChecked(false);
    ui->checkBox_29->setChecked(false);
    ui->checkBox_30->setChecked(false);
    ui->checkBox_31->setChecked(false);
    ui->checkBox_32->setChecked(false);
    ui->checkBox_33->setChecked(false);
    ui->checkBox_34->setChecked(false);
    ui->checkBox_35->setChecked(false);
    ui->checkBox_36->setChecked(false);
    ui->checkBox_37->setChecked(false);
    ui->checkBox_38->setChecked(false);
    ui->checkBox_39->setChecked(false);
    ui->checkBox_40->setChecked(false);

    //Reset
    for(int i = 0; i < 40; i++)
        checked[i] = false;

    for(int i = 0; i < 8; i++)
        car[i] = 0;
}

void CaracSpe::on_pushButton_creer_car_clicked()
{ //Teste si les cases sont cochées
    checked[0] = ui->checkBox_1->isChecked();
    checked[1] = ui->checkBox_2->isChecked();
    checked[2] = ui->checkBox_3->isChecked();
    checked[3] = ui->checkBox_4->isChecked();
    checked[4] = ui->checkBox_5->isChecked();
    checked[5] = ui->checkBox_6->isChecked();
    checked[6] = ui->checkBox_7->isChecked();
    checked[7] = ui->checkBox_8->isChecked();
    checked[8] = ui->checkBox_9->isChecked();
    checked[9] = ui->checkBox_10->isChecked();
    checked[10] = ui->checkBox_11->isChecked();
    checked[11] = ui->checkBox_12->isChecked();
    checked[12] = ui->checkBox_13->isChecked();
    checked[13] = ui->checkBox_14->isChecked();
    checked[14] = ui->checkBox_15->isChecked();
    checked[15] = ui->checkBox_16->isChecked();
    checked[16] = ui->checkBox_17->isChecked();
    checked[17] = ui->checkBox_18->isChecked();
    checked[18] = ui->checkBox_19->isChecked();
    checked[19] = ui->checkBox_20->isChecked();
    checked[20] = ui->checkBox_21->isChecked();
    checked[21] = ui->checkBox_22->isChecked();
    checked[22] = ui->checkBox_23->isChecked();
    checked[23] = ui->checkBox_24->isChecked();
    checked[24] = ui->checkBox_25->isChecked();
    checked[25] = ui->checkBox_26->isChecked();
    checked[26] = ui->checkBox_27->isChecked();
    checked[27] = ui->checkBox_28->isChecked();
    checked[28] = ui->checkBox_29->isChecked();
    checked[29] = ui->checkBox_30->isChecked();
    checked[30] = ui->checkBox_31->isChecked();
    checked[31] = ui->checkBox_32->isChecked();
    checked[32] = ui->checkBox_33->isChecked();
    checked[33] = ui->checkBox_34->isChecked();
    checked[34] = ui->checkBox_35->isChecked();
    checked[35] = ui->checkBox_36->isChecked();
    checked[36] = ui->checkBox_37->isChecked();
    checked[37] = ui->checkBox_38->isChecked();
    checked[38] = ui->checkBox_39->isChecked();
    checked[39] = ui->checkBox_40->isChecked();

    for(int i = 0; i < 5; i++) //Toutes les colonnes
    {
        for(int j = 0; j < 8; j++) //Toutes les lignes
        {
            car[j] |= checked[i + j * 5] << i; //Construis le caractère
        }
    }

    aff_lcd->defini_car(8, car); //Définit le caractère
}

void CaracSpe::on_pushButton_aff_car_clicked()
{
    aff_lcd->aff_car(8); //Affiche le caractère
}
