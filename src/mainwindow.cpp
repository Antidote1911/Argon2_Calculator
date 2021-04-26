#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QDebug>
#include <QElapsedTimer>

#include <derivator.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          m_ui(std::make_unique<Ui::MainWindow>()) {
    m_ui->setupUi(this);

    m_ui->argon2TypeComboBox->addItem("Argon2i");
    m_ui->argon2TypeComboBox->addItem("Argon2d");
    m_ui->argon2TypeComboBox->addItem("Argon2id");
    m_ui->argon2TypeComboBox->setCurrentIndex(0);

    m_ui->mCostComboBox->addItem("1 MB");
    m_ui->mCostComboBox->addItem("2 MB");
    m_ui->mCostComboBox->addItem("4 MB");
    m_ui->mCostComboBox->addItem("8 MB");
    m_ui->mCostComboBox->addItem("16 MB");
    m_ui->mCostComboBox->addItem("32 MB");
    m_ui->mCostComboBox->addItem("64 MB");
    m_ui->mCostComboBox->addItem("128 MB");
    m_ui->mCostComboBox->addItem("256 MB");
    m_ui->mCostComboBox->addItem("512 MB");
    m_ui->mCostComboBox->addItem("1 GB");
    m_ui->mCostComboBox->addItem("2 GB");
    m_ui->mCostComboBox->addItem("4 GB");
    m_ui->mCostComboBox->addItem("8 GB");
    m_ui->mCostComboBox->setCurrentIndex(6);

    clearEverything();

    hashButton_clicked();

    connect(m_ui->hashButton, SIGNAL(clicked()), this, SLOT(hashButton_clicked()));

    connect(m_ui->pwdLineEdit, SIGNAL(textEdited(QString)), this, SLOT(clearEverything()));
    connect(m_ui->saltLineEdit, SIGNAL(textEdited(QString)), this, SLOT(clearEverything()));

    connect(m_ui->pwdLineEdit, SIGNAL(textChanged(QString)), this, SLOT(clearEverything()));
    connect(m_ui->saltLineEdit, SIGNAL(textChanged(QString)), this, SLOT(clearEverything()));
    connect(m_ui->argon2TypeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(clearEverything()));
    connect(m_ui->tCostSpinBox, SIGNAL(valueChanged(int)), this, SLOT(clearEverything()));
    connect(m_ui->mCostComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(clearEverything()));
    connect(m_ui->parallelismSpinBox, SIGNAL(valueChanged(int)), this, SLOT(clearEverything()));
    connect(m_ui->hashLengthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(clearEverything()));
}

MainWindow::~MainWindow() = default;

void MainWindow::clearEverything() {
    m_ui->pwdLengthLabel->setText(QStringLiteral("%1 bytes.").arg(m_ui->pwdLineEdit->text().length()));
    m_ui->saltLengthLabel->setText(QStringLiteral("%1 bytes.").arg(m_ui->saltLineEdit->text().length()));

    m_ui->lineEdit_formated->clear();
    m_ui->lineEdit_hex->clear();
    m_ui->lineEdit_b69->clear();
    m_ui->hashStatusLabel->clear();
    m_ui->hashingTimeLabel->clear();
}

void MainWindow::hashButton_clicked() {
    setParameters();
    QString user_pass = m_ui->pwdLineEdit->text();
    QString user_salt = m_ui->saltLineEdit->text();

    quint32 t_cost = T_COST;        // n-pass computation
    quint32 m_cost = (1 << M_COST); // 4 mebibytes memory usage
    quint32 parallelism = THREADS;       // number of threads and lanes

    QElapsedTimer timer;
    timer.start();

    derivator engine;
    engine.setParams(TYPE,
                     user_pass.toStdString(),
                     user_salt.toStdString(),
                     m_cost,
                     t_cost,
                     parallelism,
                     HASHLEN);

    QString status;
    status = QString("<font color=green>OK</font>");

    auto time = static_cast<double>(timer.elapsed());
    timer.invalidate();

    m_ui->lineEdit_formated->setText(QString::fromStdString(engine.getFormatedHash()));
    m_ui->lineEdit_b69->setText(QString::fromStdString(engine.getB69Hash()));
    m_ui->lineEdit_hex->setText(QString::fromStdString(engine.getHexHash()));
    m_ui->hashStatusLabel->setText(status);
    m_ui->hashingTimeLabel->setText(QString("%1 seconds.").arg(QString::number(time / 1000.0, 'g', 5)));
}

void MainWindow::setParameters() {
    if (m_ui->argon2TypeComboBox->currentIndex() == 0)
        TYPE = "Argon2i";
    else if (m_ui->argon2TypeComboBox->currentIndex() == 1)
        TYPE = "Argon2d";
    else
        TYPE = "Argon2id";

    T_COST = m_ui->tCostSpinBox->value();              // default: 2-pass over memory
    M_COST = m_ui->mCostComboBox->currentIndex() + 10; // 2^M_COST KB of memory
    THREADS = m_ui->parallelismSpinBox->value();        // 4 - parallelism
    HASHLEN = m_ui->hashLengthSpinBox->value();         // output length
}
