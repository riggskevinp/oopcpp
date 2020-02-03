TARGET = statistics

TEMPLATE = app

QT += widgets
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

requires(qtConfig(tableview))

SOURCES += main.cpp \
           mainwindow.cpp \
           mymodel.cpp \
           statistics.cpp

HEADERS += mainwindow.h \
           mymodel.h \
           statistics.h

# install
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
