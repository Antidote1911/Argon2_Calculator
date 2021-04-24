#pragma once

#include <QMainWindow>
#include <QFile>
#include <vector>
#include <string>
#include <memory>
#include "3rdparty/argon2/include/argon2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void clearEverything();
    void hashButton_clicked();

private:
    const std::unique_ptr<Ui::MainWindow> m_ui;
    void setParameters();
    argon2_type TYPE{};
    quint32 T_COST{};
    quint32 M_COST{};
    quint32 THREADS{};
    quint32 HASHLEN{};
};

