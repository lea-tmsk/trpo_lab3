QT       += core gui
QT += sql
QT += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app.cpp \
    chartsview.cpp \
    datareader.cpp \
    filesview.cpp \
    main.cpp \
    mainwindow.cpp \
    settings.cpp \
    topbuttons.cpp

HEADERS += \
    app.h \
    chartsview.h \
    datareader.h \
    filesview.h \
    ioc.h \
    mainwindow.h \
    settings.h \
    topbuttons.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
