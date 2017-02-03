#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QElapsedTimer>
#include <QFile>

#include <vector>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "argon2/argon2.h"

#include "data.h"


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

    void clearEverything();
    void hashButton_clicked();

private:
    Ui::MainWindow *ui;

    QThread hashingThread;
    QElapsedTimer authTimer;

    void setParameters();

    argon2_type TYPE;
    quint32 T_COST;
    quint32 M_COST;
    quint32 THREADS;
    quint32 HASHLEN;

    Data data;

};

#endif // MAINWINDOW_H
