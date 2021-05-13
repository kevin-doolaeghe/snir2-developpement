#ifndef USB_I2C_H
#define USB_I2C_H

#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include <unistd.h>

class Usb_I2c : public QSerialPort //La classe Usb_I2c hérite de la classe QSerialPort
{
public:
    Usb_I2c(char *com);
    ~Usb_I2c();
    bool ecrit_I2C_SGL(unsigned char add, unsigned char val);
    bool ecrit_I2C_AD1(unsigned char add, unsigned char reg, unsigned char nboctet, unsigned char *val);
    bool lit_I2C_SGL(unsigned char add);
    bool lit_I2C_AD1(unsigned char add, unsigned char reg, unsigned char nboctet);
    unsigned char donnee_Recu();
    int getAck();

private:
    unsigned char data_recu[80];
    int ack;
};

#endif // USB_I2C_H
