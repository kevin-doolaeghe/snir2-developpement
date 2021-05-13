#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "chenillard_p8055.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Chenillard_p8055 *chenillard;

private slots:
    void on_pushButton_lance_clicked();

    void on_pushButton_stop_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void declencheTimerChenillard();

    void on_pushButton_sens_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
