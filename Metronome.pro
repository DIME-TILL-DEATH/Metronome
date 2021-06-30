QT += quick
QT += multimedia
QT += svg
QTPLUGIN += qsvg

CONFIG += c++11

INCLUDEPATH += $$PWD/include

HEADERS += \
    include/musicalbar.h \
    include/musicalpattern.h \
    include/musicaltypes.h \
    include/metronome.h \
    include/metronomepreset.h \
    include/musicalnote.h \
    include/musicalpatternmodel.h \
    include/patterneditor.h \
    include/soundengine.h \
    include/timersengine.h

SOURCES += \
        main.cpp \
        src/metronome.cpp \
        src/metronomepreset.cpp \
        src/musicalbar.cpp \
        src/musicalnote.cpp \
        src/musicalpattern.cpp \
        src/musicalpatternmodel.cpp \
        src/patterneditor.cpp \
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

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

