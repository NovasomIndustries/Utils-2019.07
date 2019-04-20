HEADERS += \
    $$PWD/settingwidgets.h

SOURCES += \
    $$PWD/settingwidgets.cpp

INCLUDEPATH +=$$PWD topWidget
include(topWidget/topWidget.pri)

INCLUDEPATH +=$$PWD middleWidget
include(middleWidget/middleWidget.pri)

INCLUDEPATH +=$$PWD wpa_supplicant
include (wpa_supplicant/wpa_supplicant.pri)
