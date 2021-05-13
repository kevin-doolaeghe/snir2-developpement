#include "pifaceio.h"

PiFaceIO::PiFaceIO()
{
    PifaceOpenSpiPort();
}
//-------------------------------------------------------------------------
PiFaceIO::~PiFaceIO()
{
   PifaceCloseSpiPort();

}


void PiFaceIO::writePiFace(unsigned char val)
{
    piface_outputs = val;
    piface_set_outputs();

}

void PiFaceIO::setBitPiFace(unsigned char pin)
{
    piface_outputs |= 1<<pin;
    piface_set_outputs();
}

void PiFaceIO::clearBitPiFace(unsigned char pin)
{
    piface_outputs &= ~(1<<pin);
    piface_set_outputs();
}

bool PiFaceIO::readBitPiFace(unsigned char pin)
{
    bool etat = false;
    piface_read_inputs();
    if (piface_inputs & (1<<pin))
        etat = 1;
    return etat ;
}
