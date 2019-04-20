HEADERS += \
    $$PWD/musicwidgets.h \
    $$PWD/topwidgets.h

SOURCES += \
    $$PWD/musicwidgets.cpp \
    $$PWD/topwidgets.cpp

INCLUDEPATH +=$$PWD player
include(player/player.pri)

INCLUDEPATH +=$$PWD bottomWidget
include(bottomWidget/bottomWidget.pri)

INCLUDEPATH +=$$PWD middleWidget
include(middleWidget/middleWidget.pri)

