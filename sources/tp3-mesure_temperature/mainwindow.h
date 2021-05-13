#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "ds1620_p8055.h"
#include "chart.h"

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
    void on_pushButton_lance_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_lire_temp_clicked();

    void on_pushButton_toggleAutoVal_clicked();

    void majAutoTemp();

private:
    void majTemp();
    Ui::MainWindow *ui;
    DS1620_P8055 *temp;
    QTimer *timer;
    Chart *graph;
    int nbTempVal;
};

#endif // MAINWINDOW_H
