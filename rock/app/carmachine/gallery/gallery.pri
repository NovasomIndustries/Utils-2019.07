HEADERS += \
    $$PWD/gallerywidgets.h \
    $$PWD/gallerytopwidgets.h

SOURCES += \
    $$PWD/gallerywidgets.cpp \
    $$PWD/gallerytopwidgets.cpp

INCLUDEPATH +=$$PWD middleWidget
include(middleWidget/middleWidget.pri)

