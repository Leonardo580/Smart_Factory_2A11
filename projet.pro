QT       += core gui
QT +=sql
QT +=charts
QT       +=printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG +=console
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    commande.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    client.h \
    commande.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    moh.qrc

DISTFILES += \
    images/4.png \
    images/5.png \
    images/istockphoto-507065413-170667a.jpg \
    img/1.png \
    img/2.png \
    img/3.png
