#ifndef LCD8055_H
#define LCD8055_H

#include "p8055.h"
#include <windows.h>

class LCD8055 : public P8055
{
public:
    LCD8055(int addcarte);
    ~LCD8055();
    void init_LCD();
    void aff_car(char val);
    void clear_aff();
    void aff_texte(char *val);
    void pos_curseur(bool ligne, int colonne);
private:
    void valid_E();
    void envoie_Octet(char octet, bool rs);

    //-----------------
    int curPos; //Pour gérer le débordement des caractères sur l'écran
    //-----------------
};

#endif // LCD8055_H
