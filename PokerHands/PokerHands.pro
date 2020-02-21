QT       += core gui widgets

include(gtest_dependency.pri)


QT += widgets
CONFIG += c++11 #console
CONFIG -= app_bundle
CONFIG += thread
DEFINES += QT_DEPRECATED_WARNINGS

win32{
LIBS += -L$$PWD/../../libconfig/Release -llibconfig++
}

SOURCES += \
    card.cpp \
    main.cpp \
    mainwindow.cpp \
    pokerhand.cpp

HEADERS += \
    card.h \
    mainwindow.h \
    pokerhand.h \
	test_poker.h

FORMS += \
    mainwindow.ui

# install
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
