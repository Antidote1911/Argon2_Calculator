#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T13:55:55
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Argon2_Calculator
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    data.cpp \
    argon2/blake2/blake2b.c \
    argon2/argon2.c \
    argon2/core.c \
    argon2/encoding.c \
    argon2/ref.c \
    argon2/thread.c

HEADERS  += mainwindow.h \
    data.h \
    argon2/blake2/blake2-impl.h \
    argon2/blake2/blake2.h \
    argon2/blake2/blamka-round-opt.h \
    argon2/blake2/blamka-round-ref.h \
    argon2/argon2.h \
    argon2/core.h \
    argon2/encoding.h \
    argon2/ref.h \
    argon2/thread.h \
    argon2/argon2.h

FORMS    += mainwindow.ui

#unix:!macx: LIBS += -largon2

