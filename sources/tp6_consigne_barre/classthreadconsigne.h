#ifndef CLASSTHREADCONSIGNE_H
#define CLASSTHREADCONSIGNE_H

#include <QLabel>
#include "classThread.h"
#include "cencinc.h"

class ClassThreadConsigne : public ClassThread
{
public:
    ClassThreadConsigne(QLabel *label_consigne);
    void traitementThread();

private:
    CEncInc encodeur;
    QLabel *label_consigne;
};

#endif // CLASSTHREADCONSIGNE_H
