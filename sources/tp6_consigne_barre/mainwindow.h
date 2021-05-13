#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "classthreadconsigne.h"

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
    void on_pushButton_quitter_clicked();

    void on_pushButton_demarrer_clicked();

private:
    Ui::MainWindow *ui;
    ClassThreadConsigne *threadEncodeur;
};

#endif // MAINWINDOW_H
