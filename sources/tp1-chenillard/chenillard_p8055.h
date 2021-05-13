#ifndef CHENILLARD_P8055_H
#define CHENILLARD_P8055_H

#include <QTimer>

#include "p8055.h"

class Chenillard_p8055 : public P8055
{
public:
    Chenillard_p8055(int addcarte);
    ~Chenillard_p8055();
    void fonction_Timer();
    void lance(int vals = 1, int vit = 100, bool nbs = 1);
    void vitesse(int vit);
    void sens();
    void stop();

    unsigned char valSortie;
    bool nbSens;
    int nbVitesse;
    QTimer *timer;
};

#endif // CHENILLARD_P8055_H
