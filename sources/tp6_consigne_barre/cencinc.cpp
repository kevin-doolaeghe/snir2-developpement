#include "cencinc.h"

CEncInc::CEncInc() : PiFaceIO()
{
    consigne = 127; //Initialise la consigne à 127
}

unsigned char CEncInc::getConsigne()
{
    return consigne; //Retourne la consigne
}

bool CEncInc::lit_Sens()
{
    return cmc2;
}

bool CEncInc::lit_Rotation() //Regarde si il y a
{
    bool retour = 0; //N'a pas lu par défaut
    bool entree1 = readBitPiFace(1); //Lit l'état de l'entrée 1

    if(entree1 == 1 && cmc1 == 0) //Si front montant
    {
        cmc2 = readBitPiFace(2); //Lit l'état de l'entrée 2

        if(cmc2) //Si consigne incrémentée
        {
            if(consigne < 255) //Si consigne pas au maximum
                consigne++; //Incrémentation
        }
        else //Si consigne décrémentée
        {
            if(consigne > 0) //Si consigne pas au minimum
                consigne--; //Décrémentation
        }

        retour = 1; //A correctement lu
    }

    cmc1 = entree1; //Mise à jour de l'état de l'entrée
    return retour; //Retourne si la lecture s'est correctement déroulée
}
