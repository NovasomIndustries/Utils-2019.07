INCLUDEPATH +=$$PWD topWidget
include(topWidget/topWidget.pri)

INCLUDEPATH +=$$PWD middleWidget
include(middleWidget/middleWidget.pri)

INCLUDEPATH +=$$PWD bottomWidget
include(bottomWidget/bottomWidget.pri)

INCLUDEPATH +=$$PWD player
include(player/player.pri)

HEADERS += \
    $$PWD/videowidgets.h

SOURCES += \
    $$PWD/videowidgets.cpp


