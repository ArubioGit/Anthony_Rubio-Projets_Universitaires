TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

LIBS+=`sdl-config --libs` -lSDL_image -lSDL_ttf

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra
SOURCES += \
    level.cpp \
    monster.cpp \
    menu.cpp \
    image.cpp \
    main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    monster.h \
    image.h \
    menu.h

