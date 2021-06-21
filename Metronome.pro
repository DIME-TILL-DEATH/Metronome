QT += quick
QT += multimedia

CONFIG += c++11

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/musicalbarmodel.h \
    include/musicaltypes.h \
    include/metronome.h \
    include/metronomepreset.h \
    include/musicalnote.h \
    include/musicalpatternmodel.h \
    include/soundengine.h \
    include/timersengine.h

SOURCES += \
        main.cpp \
        src/metronome.cpp \
        src/metronomepreset.cpp \
        src/musicalbarmodel.cpp \
        src/musicalnote.cpp \
        src/musicalpatternmodel.cpp \
        src/soundengine.cpp \
        src/timersengine.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD/qml
QML2_IMPORT_PATH += $$PWD/qml

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



