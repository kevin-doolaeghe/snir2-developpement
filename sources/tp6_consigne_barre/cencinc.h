#ifndef CENCINC_H
#define CENCINC_H

#include "pifaceio.h"

class CEncInc : public PiFaceIO
{
public:
    CEncInc();
    unsigned char getConsigne();
    bool lit_Sens();
    bool lit_Rotation();

private:
    unsigned char consigne;
    bool cmc1;
    bool cmc2;
};

#endif // CENCINC_H
