#include "data.h"

QString Data::password;
QString Data::hash;
argon2_type Data::TYPE;
quint32 Data::T_COST;
quint32 Data::M_COST;
quint32 Data::THREADS;
quint32 Data::HASHLEN;

Data::Data(QObject *parent) :
    QObject(parent)
{

}
QString Data::getPassword()
{
    return password;
}

void Data::setPassword(const QString &value)
{
    password = value;
}
QString Data::getHash()
{
    return hash;
}

void Data::setHash(const QString &value)
{
    hash = value;
}
argon2_type Data::getTYPE()
{
    return TYPE;
}

void Data::setTYPE(const argon2_type &value)
{
    TYPE = value;
}
quint32 Data::getT_COST()
{
    return T_COST;
}

void Data::setT_COST(const quint32 &value)
{
    T_COST = value;
}
quint32 Data::getM_COST()
{
    return M_COST;
}

void Data::setM_COST(const quint32 &value)
{
    M_COST = value;
}
quint32 Data::getTHREADS()
{
    return THREADS;
}

void Data::setTHREADS(const quint32 &value)
{
    THREADS = value;
}
quint32 Data::getHASHLEN()
{
    return HASHLEN;
}

void Data::setHASHLEN(const quint32 &value)
{
    HASHLEN = value;
}







