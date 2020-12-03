QT       += core gui charts
QT       += sql
QT       += serialport
QT       += multimedia
QT       += core network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = SMTPEmail

# Build as an application
TEMPLATE = app
#TEMPLATE = lib
#DEFINES += SMTP_BUILD
#win32:CONFIG += dll
#CONFIG +=
CONFIG += c++11
CONFIG +=console
CONFIG -=app_bundle
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addemployee.cpp \
    email.cpp \
    employees.cpp \
    main.cpp \
    mainwindow.cpp \
    posts.cpp \
    search.cpp

HEADERS += \
    addemployee.h \
    email.h \
    employees.h \
    mainwindow.h \
    posts.h \
    search.h

FORMS += \
    addemployee.ui \
    email.ui \
    mainwindow.ui \
    search.ui

    # Location of SMTP Library
    SMTP_LIBRARY_LOCATION ="C:\Users\Anas\OneDrive\Workload\Project 2\build-MFactory-Desktop_Qt_5_9_9_MinGW_32bit-Debug"
    win32:CONFIG(release, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/ -lSMTPEmail
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$SMTP_LIBRARY_LOCATION/debug/ -lSMTPEmail
    else:unix: LIBS += -L$$SMTP_LIBRARY_LOCATION -lSMTPEmail

    INCLUDEPATH += $$SMTP_LIBRARY_LOCATION
    DEPENDPATH += $$SMTP_LIBRARY_LOCATION

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../../../../Desktop/Project.Pas/qt_test/Emoji.qrc \
    Resources.qrc

SUBDIRS += \
    SMTPEmail.pro \
    SMTPEmail.pro
