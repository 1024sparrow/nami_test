QT += core widgets
#QT += qml declarative

CONFIG += c++11

SOURCES += \
    main.cpp \
    gameplay.cpp \
    irotor.cpp \
    rotorlcd.cpp \
    rotorlcdstupid.cpp \
    rotorlcdqml.cpp \
    demologics.cpp

HEADERS += \
    gameplay.h \
    irotor.h \
    rotorlcd.h \
    rotorlcdstupid.h \
    rotorlcdqml.h \
    demologics.h

RESOURCES += \
    res.qrc
#    res_qml_dial.qrc
