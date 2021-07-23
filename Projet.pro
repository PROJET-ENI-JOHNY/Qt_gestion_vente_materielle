#-------------------------------------------------
#
# Project created by QtCreator 2017-12-05T09:14:28
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet
TEMPLATE = app


SOURCES += main.cpp\
    fichier.cpp \
    client.cpp \
    conversion.cpp \
    materiele.cpp \
    achat.cpp \
    affaire.cpp \
    recherchedate.cpp \
    mainwindow.cpp \
    commande.cpp \
    facture.cpp

HEADERS  += \
    fichier.h \
    client.h \
    conversion.h \
    materiele.h \
    achat.h \
    affaire.h \
    recherchedate.h \
    mainwindow.h \
    commande.h \
    facture.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    image.qrc

DISTFILES +=
