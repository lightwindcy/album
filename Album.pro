#-------------------------------------------------
#
# Project created by QtCreator 2023-03-24T16:53:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Album
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    wizard.cpp \
    prosetpage.cpp \
    confirmpage.cpp \
    protree.cpp \
    protreewidget.cpp \
    protreeitem.cpp \
    protreethread.cpp \
    removeprodialog.cpp \
    openprothread.cpp \
    picshow.cpp \
    picbutton.cpp \
    slideshowdlg.cpp \
    picstatebtn.cpp \
    picanimation.cpp \
    prelistwid.cpp \
    prelistitem.cpp

HEADERS += \
        mainwindow.h \
    wizard.h \
    prosetpage.h \
    confirmpage.h \
    protree.h \
    protreewidget.h \
    protreeitem.h \
    const.h \
    protreethread.h \
    removeprodialog.h \
    openprothread.h \
    picshow.h \
    picbutton.h \
    slideshowdlg.h \
    picstatebtn.h \
    picanimation.h \
    prelistwid.h \
    prelistitem.h

FORMS += \
        mainwindow.ui \
    wizard.ui \
    prosetpage.ui \
    confirmpage.ui \
    protree.ui \
    removeprodialog.ui \
    picshow.ui \
    slideshowdlg.ui

RESOURCES += \
    res.qrc

RC_ICONS ="icon/bulm.ico"
