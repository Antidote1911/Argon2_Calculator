#ifndef DATA_H
#define DATA_H

// Class that keeps shared data (shared between mainclass and cracker)

#include <QObject>
#include "argon2/argon2.h"
class Data : public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = 0);

    static QString getPassword();
    static void setPassword(const QString &value);

    static QString getHash();
    static void setHash(const QString &value);

    static argon2_type getTYPE();
    static void setTYPE(const argon2_type &value);

    static quint32 getT_COST();
    static void setT_COST(const quint32 &value);

    static quint32 getM_COST();
    static void setM_COST(const quint32 &value);

    static quint32 getTHREADS();
    static void setTHREADS(const quint32 &value);

    static quint32 getHASHLEN();
    static void setHASHLEN(const quint32 &value);

signals:

public slots:

private:
    static QString password;
    static QString hash;
    static argon2_type TYPE;
    static quint32 T_COST;
    static quint32 M_COST;
    static quint32 THREADS;
    static quint32 HASHLEN;

};

#endif // DATA_H
