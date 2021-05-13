#ifndef P8055_H
#define P8055_H

#include <QLibrary>
// #include <QCoreApplication>
// #include <QtCore>
#include <QMessageBox>
#include <QApplication>
#include <QDir>

        typedef long (*OpenDevice)(long CardAddress);
        typedef void (*CloseDevice)(void);
        typedef void (*SetDigitalChannel)(long Channel);
        typedef void (*ClearDigitalChannel)(long Channel);
        typedef void (*WriteAllDigital)(long Data);
        typedef long (*ReadAllDigital)(void);
        typedef long (*ReadDigitalChannel)(long Channel);
        typedef void (*SetAnalogChannel)(long Channel);
        typedef void (*ClearAnalogChannel)(long Channel);
        typedef void (*OutputAnalogChannel)(long Channel, long Data);

class P8055
{
    private:
        OpenDevice opendevice;
        CloseDevice closedevice;
        SetDigitalChannel setdigitalchannel;
        ClearDigitalChannel cleardigitalchannel;
        WriteAllDigital writealldigital;
        ReadAllDigital readalldigital;
        ReadDigitalChannel readdigitalchannel;
        SetAnalogChannel setanalogchannel;
        ClearAnalogChannel clearanalogchannel;
        OutputAnalogChannel outputanalogchannel;

        int ncarte;
        char vals;
        char vale;
        QLibrary lib;

public:
        P8055(int addcarte);
        ~P8055();
        char P8055_present();
        void setbit(char val);
        void clearbit(char val);
        void val_output(unsigned char val);
        char get_output( ) ;
        char get_input();
        bool get_bitinput(char val);
        void set_DAC1_5V();
        void Clear_DAC1_0V();
        void Cna(char voie, unsigned char data);

};

#endif // P8055_H
