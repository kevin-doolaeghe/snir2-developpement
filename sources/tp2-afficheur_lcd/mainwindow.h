#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include "lcd8055.h"

using namespace std;

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
    void on_pushButton_afficher_clicked();

    void on_pushButton_init_clicked();

    void on_pushButton_A_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_bonjour_clicked();

    void on_pushButton_validCurs_clicked();

private:
    Ui::MainWindow *ui;
    LCD8055 *afficheur; //Pointeur de classe LCD8055
};

#endif // MAINWINDOW_H
