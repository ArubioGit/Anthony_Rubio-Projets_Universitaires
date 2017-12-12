TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11 -pedantic -Wall -Wextra

LIBS += -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

SOURCES += main.cpp \
    Action.cpp \
    Application.cpp \
    Button.cpp \
    Case.cpp \
    Character.cpp \
    Game.cpp \
    Level.cpp \
    Process.cpp \
    Case_Dock.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Action.h \
    Application.h \
    Button.h \
    Case.h \
    Character.h \
    Game.h \
    Level.h \
    Process.h \
    Case_Dock.h

