#include "lcd_rs232.h"

LCD_RS232::LCD_RS232()
{
    portSerie = new QextSerialPort(); //Instantiation de l'objet QextSerialPort
}

LCD_RS232::~LCD_RS232()
{
    delete portSerie;
}

void LCD_RS232::efface_LCD()
{ //Efface l'écran
    char data[3] = {0x1b, 0x43, 0}; //Trame
    portSerie->writeData(data, 2); //Ecrit 2 octets de la trame

    //Coordonnées du curseur
    curX = 0; //Curseur x à 0
    curY = 0; //Curseur y à 0

    //Texte de l'afficheur vide
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            trame[j][i] = 0;
        }
    }
}

void LCD_RS232::active_RE()
{ //Active le RE
    char data[3] = {0x1b, 0x42, 0};
    portSerie->writeData(data, 2);
}

void LCD_RS232::desactive_RE()
{ //Désactive le RE
    char data[3] = {0x1b, 0x62, 0};
    portSerie->writeData(data, 2);
}

void LCD_RS232::aff_car(char car)
{
    portSerie->writeData(&car, 1); //Affiche le caractère

    trame[curX][curY] = car; //Ajoute le caractère à la trame

    curX++; //Incrémente la pos. x

    if(curX > 15) //Si sort de la ligne
    {
        curX -= 16; //Reset la ligne
        switch (curY) { //Teste de la ligne
        case 0:
            curY = 1; //Ligne 0 -> passe à la ligne 1
            break;
        case 1:
            curY = 0; //Inverse
            break;
        }

        position_curseur(curX, curY); //Déplace le curseur
    }
}

void LCD_RS232::aff_texte(QString texte)
{
    const char *chaine = texte.toStdString().c_str(); //Texte de QString vers char*

    for(int i = 0; i < texte.length(); i++)
    {
        aff_car(chaine[i]); //Affiche les caractères
    }
}

void LCD_RS232::position_curseur(int x, int y)
{
    if(x < 0 || x > 15) x = 0; //Test des valeurs de x & y
    if(y < 0 || y > 3) y = 0;

    char data[5] = {0x1b, 0x4c, (char) x, (char) y, 0}; //Fabrication de la trame
    portSerie->writeData(data, 4); //Envoi

    curX = x; //Maj de x & y
    curY = y;
}

void LCD_RS232::defini_car(char code, char *dessin)
{ //Définit le caractère 0x8
    //Fabrication de la trame selon la doc. -> 11 octets
    char data[12] = {0x1b, 0x44, code, dessin[0], dessin[1], dessin[2], dessin[3], dessin[4], dessin[5], dessin[6], dessin[7], 0};
    portSerie->writeData(data, 11);
}

void LCD_RS232::active_curseur()
{ //Active le curseur
    char data[3] = {0x1b, 0x53, 0};
    portSerie->writeData(data, 2);
}

void LCD_RS232::desactive_curseur()
{ //Désactive le curseur
    char data[3] = {0x1b, 0x73, 0};
    portSerie->writeData(data, 2);
}

void LCD_RS232::defile(int vitesse)
{
    for(int nbCar = 0; nbCar < 16; nbCar++) //16 affichages
    {
        efface_LCD();

        for(int colonne = 0; colonne < nbCar + 1; colonne++) //Détermine le nombre de colonne(s) à afficher
        {
            for(int ligne = 0; ligne < 4; ligne++) //4 lignes
            {
                position_curseur(15 - colonne, ligne); //Déplacement du curseur
                aff_car(trame[colonne + nbCar][ligne]); //Affiche le caractère de la trame voulu
            }
        }

        usleep(vitesse); //Endort le thread pendant vitesse ms
    }

    position_curseur(0, 0); //Reset le curseur
}

void LCD_RS232::open(char *com, int baudrate)
{ //Initialisation
    portSerie->setPortName(com); //Port COM
    portSerie->setQueryMode(QextSerialPort::Polling); //Asynchrone
    portSerie->setBaudRate((BaudRateType) baudrate); //Baud rate
    portSerie->setDataBits(DataBitsType::DATA_8); //Nombre de bits de données
    portSerie->setParity(ParityType::PAR_NONE); //Parité
    portSerie->setStopBits(StopBitsType::STOP_1); //Nombre de bits de stop
    portSerie->setFlowControl(FlowType::FLOW_OFF); //Contrôle de flux
    portSerie->setTimeout(500); //Timeout en ms

    portSerie->open(QIODevice::ReadWrite); //Ecriture seule

    if(portSerie->isOpen()) { //Boîte de dialogue
        QMessageBox::information(0, "Statut", "Ok", QMessageBox::Ok, 0);
    } else {
        QMessageBox::information(0, "Statut", "Erreur", QMessageBox::Ok, 0);
    }

    efface_LCD();
}

void LCD_RS232::close()
{ //Fermeture
    portSerie->close();
}

bool LCD_RS232::isOpen()
{ //Renvoie si le port est ouvert
    return portSerie->isOpen();
}
