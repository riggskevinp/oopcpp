QT += core gui widgets

include(gtest_dependency.pri)



CONFIG += c++11 #console
CONFIG -= app_bundle
CONFIG += thread
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    elevator.cpp \
    elevatorsimulation.cpp \
    elevatorutils.cpp \
    floor.cpp \
    main.cpp \
    mainwindow.cpp \
    passenger.cpp

HEADERS += \
    direction.h \
    elevator.h \
    elevatorsimulation.h \
    elevatorutils.h \
    floor.h \
    mainwindow.h \
    passenger.h \
    tst_elevatorsim.h

FORMS += \
    mainwindow.ui

# install
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
