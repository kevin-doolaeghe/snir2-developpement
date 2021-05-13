#include "usb_i2c.h"

Usb_I2c::Usb_I2c(char *com)
{ //Configuration de la liaison série et ouverture
    setPortName(com); //Port COM
    setBaudRate(QSerialPort::Baud19200); //19200 bauds
    setFlowControl(QSerialPort::NoFlowControl); //Pas de contrôle de flux
    setDataBits(QSerialPort::Data8); //8 bits de donnée
    setParity(QSerialPort::NoParity); //Pas de bit de parité
    setStopBits(QSerialPort::TwoStop); //2 bits de stop

    open(QIODevice::ReadWrite); //Ouverture en mode lecture/écriture

    if(this->isOpen())
    { //Si la liaison est ouverte
        QMessageBox::information(0, "Statut de la liaison", "Liaison série ouverte correctement", QMessageBox::Ok, 0); //Message de signalement
        ack = 0; //Ok
    }
    else
    { //Sinon
        QMessageBox::information(0, "Statut de la liaison", "Erreur dans l'ouverture de la liaison série", QMessageBox::Warning, 0);
        ack = -1; //Erreur
    }
}

Usb_I2c::~Usb_I2c()
{
    close(); //Fermeture de la communication
}

bool Usb_I2c::ecrit_I2C_SGL(unsigned char add, unsigned char val)
{ //Ecrit un registre
    bool reponse = false; //Par défaut : erreur
    const char trame[4] = {0x53, (char) add, (char) val, 0}; //Trame modifiant un registre

    int nbEnvoi = writeData(trame, 3); //Ecrit les 3 premiers octets de la trame ci-dessus

    if(nbEnvoi == 3) reponse = true; //Si la liaison a bien tout envoyer sinon réponse par défaut
    return reponse; //Retour du statut de la communication
}

bool Usb_I2c::ecrit_I2C_AD1(unsigned char add, unsigned char reg, unsigned char nboctet, unsigned char *val)
{ //Ecrit plusieurs registres
    bool reponse = false; //Par défaut : erreur
    char trame[260] = {0x55, (char) add, (char) reg, (char) nboctet}; //Trame modifiant nboctet registres

    for(int i = 0; i < nboctet; i++)
    { //Ajoute à la trame les données pour les registres
        trame[i + 4] = val[i]; //i + 4 car il y a 4 octets avant les données
    }

    int nbEnvoi = writeData(trame, 4 + nboctet); //Envoi de la trame

    if(nbEnvoi == nboctet + 4) reponse = true; //Si la liaison a bien tout envoyer sinon réponse par défaut
    return reponse; //Retour du statut de la communication
}

bool Usb_I2c::lit_I2C_SGL(unsigned char add)
{ //Lit un registre
    bool reponse = false; //Par défaut : erreur
    add |= 1; //Mode lecture
    char trame[3] = {0x53, (char) add, 0}; //Trame pour lire le registre add

    int nbEnvoi = this->writeData(trame, 2); //Envoi la demande de lecture

    usleep(700); //Attend que la donnée arrive

    int nbRecu = this->readData((char *) data_recu, 1); //Récupère la donnée

    if(nbEnvoi == 2 && nbRecu == 1) reponse = true; //Si tout a bien été envoyé et reçu
    return reponse;
}

bool Usb_I2c::lit_I2C_AD1(unsigned char add, unsigned char reg, unsigned char nboctet)
{ //Lit nboctet registres
    bool reponse = false; //Par défaut : erreur
    add |= 1; //Mode lecture
    char trame[5] = {0x55, (char) add, (char) reg, (char) nboctet, 0}; //Trame pour lire nboctet registres

    int nbEnvoi = this->writeData(trame, 4); //Envoi la demande de lecture

    usleep(700); //Attend que les données arrivent

    int nbRecu = this->readData((char *) data_recu, nboctet); //Récupère les données

    if(nbEnvoi == 4 && nbRecu == nboctet) reponse = true; //Si tout a bien été envoyé et reçu
    return reponse;
}

unsigned char Usb_I2c::donnee_Recu()
{
    return data_recu[0]; //Retourne le premier octet de data_recu
}

int Usb_I2c::getAck()
{
    return ack; //Retourne le statut de la liaison
}

