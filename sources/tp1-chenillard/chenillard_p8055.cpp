#include "chenillard_p8055.h"

Chenillard_p8055::Chenillard_p8055(int addcarte)
                :P8055(addcarte)
{
    valSortie = 0;
    nbSens = false;
    timer = new QTimer();
}

Chenillard_p8055::~Chenillard_p8055()
{
    delete timer;
}

void Chenillard_p8055::fonction_Timer()
{
    unsigned char val = valSortie;

    if(nbSens)
    {
        val = val & 1;
        valSortie = valSortie >> 1;
        valSortie |= val << 7;
    } else
    {
        val = val & 0x80;
        valSortie = valSortie << 1;
        valSortie |= val >> 7;
    }

    if(this->P8055_present() != -1) this->val_output(valSortie);
}

void Chenillard_p8055::lance(int vals, int vit, bool nbs)
{
    valSortie = vals;
    nbVitesse = vit;
    nbSens = nbs;

    timer->start(nbVitesse);
}

void Chenillard_p8055::vitesse(int vit)
{
    nbVitesse = vit * 100;
}

void Chenillard_p8055::sens()
{
    nbSens = !nbSens;
}

void Chenillard_p8055::stop()
{
    timer->stop();
}
