#ifndef CARACSPE_H
#define CARACSPE_H

#include <QDialog>
#include "lcd_rs232.h"

namespace Ui {
class CaracSpe;
}

class CaracSpe : public QDialog
{
    Q_OBJECT

public:
    explicit CaracSpe(LCD_RS232 *aff_lcd, QWidget *parent = 0);
    ~CaracSpe();

private slots:

    void on_pushButton_reset_clicked();

    void on_pushButton_creer_car_clicked();

    void on_pushButton_aff_car_clicked();

private:
    Ui::CaracSpe *ui;
    LCD_RS232 *aff_lcd;
    bool checked[40];
    char car[8];
};

#endif // CARACSPE_H
