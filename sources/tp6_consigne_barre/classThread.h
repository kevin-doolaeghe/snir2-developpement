#ifndef CLASSTHREAD_H
#define CLASSTHREAD_H
#include <pthread.h>
#include <iostream>
using namespace std;

class ClassThread
{
public:
    bool drapeauThread;
    pthread_t threadApplication;

    ClassThread();
    void lanceThread();
    void stopThread();
    pthread_t* initThread();
    static void* demareThread(void* threadApp);
    virtual void traitementThread()=0;
};

#endif // CLASSTHREAD_H
