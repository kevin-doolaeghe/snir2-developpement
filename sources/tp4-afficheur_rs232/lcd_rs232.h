#ifndef LCD_RS232_H
#define LCD_RS232_H

#include <QIODevice>
#include <QMessageBox>
#include <unistd.h>
#include "src/qextserialport.h"

class LCD_RS232
{
public:
    LCD_RS232();
    ~LCD_RS232();
    void efface_LCD();
    void active_RE();
    void desactive_RE();
    void aff_car(char car);
    void aff_texte(QString texte);
    void position_curseur(int x, int y);
    void defini_car(char code, char *dessin);
    void active_curseur();
    void desactive_curseur();
    void defile(int vitesse);
    void open(char *com, int baudrate);
    void close();
    bool isOpen();
    QextSerialPort *portSerie;
private:
    char codeErreur;
    int ack;
    char trame[16][4];
    int curX;
    int curY;
};

#endif // LCD_RS232_H
