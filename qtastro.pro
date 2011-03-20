TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .
QT += opengl
HEADERS += graphwidget.h \
 mainwindow.h \
 graphsettings.h \
 graphobject.h \
 graphinspector.h \
 drawerwidget.h \
 drawersettings.h \
 mover.h \
 motion/controllerwidget.h \
 model/modelobject.h \
 globals.h \
 motion/motiongenerator.h
FORMS += ui/mainwindow.ui \
 ui/graphsettings.ui \
 ui/graphinspector.ui \
 ui/drawersettings.ui \
 ui/controllerwidget.ui \
 ui/circlemotiongenerator.ui
SOURCES += graphwidget.cpp \
 main.cpp \
 mainwindow.cpp \
 graphsettings.cpp \
 graphobject.cpp \
 graphinspector.cpp \
 drawerwidget.cpp \
 drawersettings.cpp \
 mover.cpp \
 model/modelobject.cpp \
 motion/controllerwidget.cpp \
 motion/motiongenerator.cpp
CONFIG += release warn_on
