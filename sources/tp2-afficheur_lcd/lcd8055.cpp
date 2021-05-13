#include "lcd8055.h"

LCD8055::LCD8055(int addcarte) : P8055(addcarte)
{
    init_LCD(); //Initialisation dans le constructeur
}

LCD8055::~LCD8055()
{

}

void LCD8055::init_LCD()
{
    //Initialisation
    this->val_output(0x03);
    valid_E();
    Sleep(4);

    this->val_output(0x03);
    valid_E();

    this->val_output(0x03);
    valid_E();

    this->val_output(0x02);
    valid_E();
    //Fin d'initialisation

    envoie_Octet(0x28, false); //Mode 4 bits sur 2 lignes

    envoie_Octet(0x0F, false); //Allumer écran, afficheur curseur et faire clignoter

    clear_aff(); //Effacer l'écran

    //-----------------
    curPos = 0; //Initialisation
    //-----------------
}

void LCD8055::aff_car(char val)
{
    envoie_Octet(val, true); //Afficher val
}

void LCD8055::clear_aff()
{
    envoie_Octet(0x01, false); //Effacer l'écran

    //-----------------
    curPos = 0; //Réinitialisation de la position
    //-----------------
}

void LCD8055::aff_texte(char *val)
{
    while(*val != 0) //Envoie toute la chaîne à aff_car pour afficher
    {
        aff_car(*val);
        val++;
    }
}

void LCD8055::pos_curseur(bool ligne, int colonne)
{
    char addr = 0; //Addresse dans RAM
    if(ligne) addr = addr | 0x40; //Si ligne 2
    addr += colonne; //Assignation de la colonne

    addr = addr | 0x80; //Pour dire que l'on veut modifier l'adresse dans la RAM
    envoie_Octet(addr, false); //Envoie de la commande

    //-----------------
    if(ligne) curPos = 0x40; //Si ligne 2
    else curPos = 0; //Si ligne 1
    curPos += colonne;
    //-----------------
}

void LCD8055::valid_E()
{
    setbit(6); //Broche 6 à 1
    clearbit(6); //Broche 6 à 0
    //Pour donner impulsion
}

void LCD8055::envoie_Octet(char octet, bool rs)
{
    //-----------------
    if(rs) //Si affichage
    {
        if(curPos == 0x0F) //Si fin première ligne
        {
            curPos = 0x40; //Ligne 2
            pos_curseur(1, 0); //Positionnement du curseur
        }
        if(curPos == 0x48) //Si fin deuxième ligne
        {
            curPos = 0; //Ligne 1
            pos_curseur(0, 0); //Positionnement du curseur
        }

        curPos++; //Incrémentation si affichage
    }
    //-----------------

    char val;

    //MSB
    val = octet >> 4; //Récupération des 4 bits MSB
    val = val & 0x0F;
    if(rs) //Si affichage
    {
        val = val | 0x10; //RS = 1
    }
    this ->val_output(val); //Envoie
    valid_E(); //Validation

    //Idem qu'au dessus mais pour LSB
    val = octet & 0x0F; //Récupération des 4 bits LSB
    if(rs)
    {
        val = val | 0x10;
    }
    this ->val_output(val);
    valid_E();
}
