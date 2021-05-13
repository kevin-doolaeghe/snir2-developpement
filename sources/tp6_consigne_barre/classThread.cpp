#include "classThread.h"

ClassThread::ClassThread()
{
}

void ClassThread::lanceThread()
{
    this->drapeauThread = true;
    initThread();
}

void ClassThread::stopThread()
{
    this->drapeauThread = false;
}

pthread_t *ClassThread::initThread()
{
    if ( !pthread_create(&(this->threadApplication), NULL, ClassThread::demareThread, static_cast<void *>(this)))
        return &(this->threadApplication);
    else
        return 0;
}

void *ClassThread::demareThread(void *threadApp)
{
    static_cast<ClassThread *>(threadApp)->traitementThread();
    pthread_exit(0);
}

void ClassThread::traitementThread()
{
    while (drapeauThread)
    {
        cout << "Traitement Thread ..." << endl;
    }
}
