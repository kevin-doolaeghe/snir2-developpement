#include "classthreadconsigne.h"

ClassThreadConsigne::ClassThreadConsigne(QLabel *label_consigne) : ClassThread()
{
    this->label_consigne = label_consigne;
}

void ClassThreadConsigne::traitementThread()
{
    while(drapeauThread) //Tant que le thread n'est pas arrêté (drapeauThread à true)
    {
        if(encodeur.lit_Rotation())
        { //Si lecture effectuée correctement
            //Mise à jour de la valeur de la consigne affichée
            label_consigne->setText("Consigne : " + QString::number(encodeur.getConsigne()));
        }
    }
}
