TEMPLATE = app

TARGET = Harmonograph

INCLUDEPATH += .
INCLUDEPATH += src/headers
INCLUDEPATH += libs

QT += widgets

LIBS+=-lglut

HEADERS += resource.h \
           libs/* \
           src/headers/*

FORMS += src/ui/*

SOURCES += src/cpp/*

RESOURCES = HarmonographApp.qrc
