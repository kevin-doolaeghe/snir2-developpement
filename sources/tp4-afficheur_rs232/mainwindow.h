#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QDialog>
#include "lcd_rs232.h"
#include "caracspe.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_desactive_re_clicked();

    void on_pushButton_envoyer_a_clicked();

    void on_comboBox_port_currentIndexChanged(int index);

    void on_pushButton_active_cur_clicked();

    void on_pushButton_afficher_texte_clicked();

    void on_pushButton_effacer_lcd_clicked();

    void on_pushButton_pos_cur_clicked();

    void on_pushButton_afficher_date_clicked();

    void on_pushButton_afficher_heure_clicked();

    void on_pushButton_defiler_clicked();

    void on_horizontalScrollBar_defiler_valueChanged(int value);

    void on_pushButton_car_spe_clicked();

private:
    Ui::MainWindow *ui;
    LCD_RS232 *aff_lcd;
    int vitesse;
    bool isCur;
    bool isRE;
};

#endif // MAINWINDOW_H
