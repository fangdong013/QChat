#-------------------------------------------------
#
# Project created by QtCreator 2017-10-19T16:04:15
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QClient
TEMPLATE = app


SOURCES += main.cpp\
        qclient.cpp \
    signin.cpp \
    message.cpp \
    tcpsocketmsg.cpp

HEADERS  += qclient.h \
    signin.h \
    message.h \
    tcpsocketmsg.h

FORMS    += qclient.ui \
    signin.ui