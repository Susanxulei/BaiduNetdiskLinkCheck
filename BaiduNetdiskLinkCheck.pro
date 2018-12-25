#-------------------------------------------------
#
# Project created by QtCreator 2018-12-24T22:59:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaiduNetdiskLinkCheck
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
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
    dialog.cpp \
    CurlWrapper/src/NetworkWrapper.cpp \

HEADERS += \
        mainwindow.h \
    dialog.h \
    CurlWrapper/include/curl/curl.h \
    CurlWrapper/include/curl/curlver.h \
    CurlWrapper/include/curl/easy.h \
    CurlWrapper/include/curl/mprintf.h \
    CurlWrapper/include/curl/multi.h \
    CurlWrapper/include/curl/stdcheaders.h \
    CurlWrapper/include/curl/system.h \
    CurlWrapper/include/curl/typecheck-gcc.h \
    CurlWrapper/include/NetworkWrapper.h \
    json.hpp

FORMS += \
        mainwindow.ui \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



LIBS+=E:/QT/BaiduNetdiskLinkCheck/lib/libcurldll.a

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/lib
