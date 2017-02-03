#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <QTime>
#include <QDebug>
#include <QElapsedTimer>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->argon2TypeComboBox->addItem("Argon2i");
    ui->argon2TypeComboBox->addItem("Argon2d");
    ui->argon2TypeComboBox->addItem("Argon2id");
    ui->argon2TypeComboBox->setCurrentIndex(0);

    ui->mCostComboBox->addItem("1 MB");
    ui->mCostComboBox->addItem("2 MB");
    ui->mCostComboBox->addItem("4 MB");
    ui->mCostComboBox->addItem("8 MB");
    ui->mCostComboBox->addItem("16 MB");
    ui->mCostComboBox->addItem("32 MB");
    ui->mCostComboBox->addItem("64 MB");
    ui->mCostComboBox->addItem("128 MB");
    ui->mCostComboBox->addItem("256 MB");
    ui->mCostComboBox->addItem("512 MB");
    ui->mCostComboBox->addItem("1 GB");
    ui->mCostComboBox->addItem("2 GB");
    ui->mCostComboBox->addItem("4 GB");
    ui->mCostComboBox->addItem("8 GB");
    ui->mCostComboBox->setCurrentIndex(6);

    clearEverything();

    hashButton_clicked();

    connect(ui->hashButton,         SIGNAL(clicked()),                  this,   SLOT(hashButton_clicked()));

    connect(ui->pwdLineEdit,        SIGNAL(textEdited(QString)),        this,   SLOT(clearEverything()));
    connect(ui->saltLineEdit,       SIGNAL(textEdited(QString)),        this,   SLOT(clearEverything()));

    connect(ui->pwdLineEdit,        SIGNAL(textChanged(QString)),       this,   SLOT(clearEverything()));
    connect(ui->saltLineEdit,       SIGNAL(textChanged(QString)),       this,   SLOT(clearEverything()));
    connect(ui->argon2TypeComboBox, SIGNAL(currentIndexChanged(int)),   this,   SLOT(clearEverything()));
    connect(ui->tCostSpinBox,       SIGNAL(valueChanged(int)),          this,   SLOT(clearEverything()));
    connect(ui->mCostComboBox,      SIGNAL(currentIndexChanged(int)),   this,   SLOT(clearEverything()));
    connect(ui->parallelismSpinBox, SIGNAL(valueChanged(int)),          this,   SLOT(clearEverything()));
    connect(ui->hashLengthSpinBox,  SIGNAL(valueChanged(int)),          this,   SLOT(clearEverything()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::clearEverything()
{
    ui->pwdLengthLabel->setText(QStringLiteral("%1 bytes.").arg(ui->pwdLineEdit->text().length()));
    ui->saltLengthLabel->setText(QStringLiteral("%1 bytes.").arg(ui->saltLineEdit->text().length()));

    ui->hashLineEdit->clear();
    ui->hashStatusLabel->clear();
    ui->hashingTimeLabel->clear();

}

void MainWindow::hashButton_clicked()
{
    setParameters();

    QString user_pass = ui->pwdLineEdit->text();
    QString user_salt = ui->saltLineEdit->text();

    quint32 pwdlen = user_pass.length();
    quint8 pwd[pwdlen];
    memcpy( pwd,user_pass.toLatin1().data(), pwdlen);

    quint32 saltlen = (quint8)user_salt.length();
    quint8 salt[saltlen];
    memcpy( salt, user_salt.toLatin1().data(), saltlen);

    quint8 output[HASHLEN];

    quint32 t_cost = T_COST;            // n-pass computation
    quint32 m_cost = (1<<M_COST);      // 4 mebibytes memory usage
    quint32 parallelism = THREADS;       // number of threads and lanes

    QElapsedTimer timer;
    timer.start();

    //const size_t encodedlen = 256;
    //char* encoded = new char[encodedlen];

    // high-level API
    int rc = argon2_hash(t_cost, m_cost, parallelism, pwd, pwdlen, salt, saltlen, output, HASHLEN, NULL, 0, TYPE, ARGON2_VERSION_NUMBER);


    //int rx = argon2i_hash_encoded(t_cost, m_cost, parallelism, pwd, pwdlen, salt, saltlen, HASHLEN, encoded,encodedlen); qDebug() << __LINE__<< encoded;
    //for( int i=0; i<HASHLEN; ++i ) printf( "%02x", output[i] ); printf( "\n" );

    QString status = "";
    QString user_hash = "";

    if(ARGON2_OK != rc) {
        status = QStringLiteral("<font color=\"red\">Error: %1.</font>").arg(argon2_error_message(rc));
    }
    else {
        for (uint i = 0; i < HASHLEN; i++) user_hash += QString("%1").arg(output[i], 2, 16, QChar('0'));
        status = QString("<font color=green>OK</font>");
    }

    int time = timer.elapsed();
    timer.invalidate();

    ui->hashLineEdit->setText(user_hash);
    ui->hashStatusLabel->setText(status);
    ui->hashingTimeLabel->setText(QString("%1 seconds.").arg(QString::number(time / 1000.0, 'g' ,5)));
}

void MainWindow::setParameters()
{
    if (ui->argon2TypeComboBox->currentIndex() == 0)
        TYPE = Argon2_i;
    else if (ui->argon2TypeComboBox->currentIndex() == 1)
        TYPE = Argon2_d;
    else
        TYPE = Argon2_id;

    T_COST = ui->tCostSpinBox->value();    // default: 2-pass over memory
    M_COST = ui->mCostComboBox->currentIndex() + 10;    // 2^M_COST KB of memory
    THREADS = ui->parallelismSpinBox->value();    // 4 - parallelism
    HASHLEN = ui->hashLengthSpinBox->value();       // output length

    data.setPassword(ui->pwdLineEdit->text());
    data.setHash(ui->hashLineEdit->text());
    data.setTYPE(TYPE);
    data.setT_COST(T_COST);
    data.setM_COST(M_COST);
    data.setTHREADS(THREADS);
    data.setHASHLEN(HASHLEN);
}


