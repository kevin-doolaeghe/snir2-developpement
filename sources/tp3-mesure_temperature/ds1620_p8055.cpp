#include "ds1620_p8055.h"

DS1620_P8055::DS1620_P8055(int addcarte) : P8055(addcarte)
{
    setbit(2); //Horloge à 1
    clearbit(3); //RàZ à 0
}

DS1620_P8055::~DS1620_P8055()
{

}

void DS1620_P8055::lance_conv()
{
    //EEh
    setbit(3); //RàZ à 1
    clearbit(2); //Horloge à 0
    protocol(0xee);
    setbit(2); //Horloge à 1
    clearbit(3); //RàZ à 0
}

void DS1620_P8055::stop_conv()
{
    //22h
    setbit(3);
    clearbit(2);
    protocol(0x22);
    setbit(2);
    clearbit(3);
}

short DS1620_P8055::lect_temp()
{
    //AAh
    setbit(3);
    clearbit(2);
    protocol(0xaa);

    //Récupération de la température
    bool bit;
    short temp = 0;
    for(int i = 0; i < 9; i++) {
        clock(); //Coup d'horloge
        Sleep(200); //Délai de mise à jour de la valeur en mémoire
        bit = get_bitinput(1); //Réception des bits
        temp |= bit << i; //Mise à jour de la température
    }

    setbit(2);
    clearbit(3);
    return temp;
}

void DS1620_P8055::clock()
{
    setbit(2); //Horloge à 1
    clearbit(2); //Horloge à 0
}

void DS1620_P8055::protocol(char val)
{
    bool bit;
    for(int i = 0; i < 8; i++) {
        bit = val & (1 << i);
        if(bit) setbit(1); //Si bit à 1, envoie 1
        else clearbit(1); //Sinon envoie 0
        clock();
    }
}
