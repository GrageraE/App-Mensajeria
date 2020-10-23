QT       += core gui websockets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminhistorial.cpp \
    cliente.cpp \
    main.cpp \
    mainwindow.cpp \
    ventanahistorial.cpp

HEADERS += \
    adminhistorial.h \
    cliente.h \
    mainwindow.h \
    serverDef.h \
    ventanahistorial.h

FORMS += \
    mainwindow.ui \
    ventanahistorial.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
