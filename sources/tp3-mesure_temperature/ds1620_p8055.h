#ifndef DS1620_P8055_H
#define DS1620_P8055_H

#include <p8055.h>
#include <windows.h>

class DS1620_P8055 : public P8055
{
public:
    DS1620_P8055(int addcarte);
    ~DS1620_P8055();
    void lance_conv();
    void stop_conv();
    short lect_temp();
private:
    void clock();
    void protocol(char val);
};

#endif // DS1620_P8055_H
