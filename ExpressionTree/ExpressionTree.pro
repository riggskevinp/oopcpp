QT += core gui widgets

include(gtest_dependency.pri)



CONFIG += c++11 #console
CONFIG -= app_bundle
CONFIG += thread
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    expressiontreenode.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    expressiontreenode.h \
    mainwindow.h \
    test_expressiontree.h

FORMS += \
    mainwindow.ui

# install
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
