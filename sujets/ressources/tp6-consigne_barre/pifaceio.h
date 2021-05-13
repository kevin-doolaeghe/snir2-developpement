#ifndef PIFACEIO_H
#define PIFACEIO_H

#include "piface.h"

class PiFaceIO
{
public:
    void clearBitPiFace(unsigned char pin);
    bool readBitPiFace(unsigned char pin);
    void setBitPiFace(unsigned char pin);
    void writePiFace(unsigned char val);
    PiFaceIO();
    ~PiFaceIO();
};

#endif // PIFACEIO_H
