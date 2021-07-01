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

INCLUDEPATH += $$PWD/include

windows{
    INCLUDEPATH += $$PWD/SoLoud/include
    LIBS += -L$$PWD/SoLoud/lib -lsoloud_static
}

android{
# i can't build library for android now

HEADERS += \
    ../../C++/SoLoud/include/soloud.h \
    ../../C++/SoLoud/include/soloud_audiosource.h \
    ../../C++/SoLoud/include/soloud_bassboostfilter.h \
    ../../C++/SoLoud/include/soloud_biquadresonantfilter.h \
    ../../C++/SoLoud/include/soloud_bus.h \
    ../../C++/SoLoud/include/soloud_c.h \
    ../../C++/SoLoud/include/soloud_dcremovalfilter.h \
    ../../C++/SoLoud/include/soloud_echofilter.h \
    ../../C++/SoLoud/include/soloud_error.h \
    ../../C++/SoLoud/include/soloud_fader.h \
    ../../C++/SoLoud/include/soloud_fft.h \
    ../../C++/SoLoud/include/soloud_fftfilter.h \
    ../../C++/SoLoud/include/soloud_file.h \
    ../../C++/SoLoud/include/soloud_file_hack_off.h \
    ../../C++/SoLoud/include/soloud_file_hack_on.h \
    ../../C++/SoLoud/include/soloud_filter.h \
    ../../C++/SoLoud/include/soloud_flangerfilter.h \
    ../../C++/SoLoud/include/soloud_freeverbfilter.h \
    ../../C++/SoLoud/include/soloud_internal.h \
    ../../C++/SoLoud/include/soloud_lofifilter.h \
    ../../C++/SoLoud/include/soloud_misc.h \
    ../../C++/SoLoud/include/soloud_monotone.h \
    ../../C++/SoLoud/include/soloud_noise.h \
    ../../C++/SoLoud/include/soloud_openmpt.h \
    ../../C++/SoLoud/include/soloud_queue.h \
    ../../C++/SoLoud/include/soloud_robotizefilter.h \
    ../../C++/SoLoud/include/soloud_sfxr.h \
    ../../C++/SoLoud/include/soloud_speech.h \
    ../../C++/SoLoud/include/soloud_tedsid.h \
    ../../C++/SoLoud/include/soloud_thread.h \
    ../../C++/SoLoud/include/soloud_vic.h \
    ../../C++/SoLoud/include/soloud_vizsn.h \
    ../../C++/SoLoud/include/soloud_wav.h \
    ../../C++/SoLoud/include/soloud_waveshaperfilter.h \
    ../../C++/SoLoud/include/soloud_wavstream.h \
    ../../C++/SoLoud/src/audiosource/speech/darray.h \
    ../../C++/SoLoud/src/audiosource/speech/klatt.h \
    ../../C++/SoLoud/src/audiosource/speech/resonator.h \
    ../../C++/SoLoud/src/audiosource/speech/tts.h \
    ../../C++/SoLoud/src/audiosource/tedsid/sid.h \
    ../../C++/SoLoud/src/audiosource/tedsid/ted.h \
    ../../C++/SoLoud/src/audiosource/wav/dr_flac.h \
    ../../C++/SoLoud/src/audiosource/wav/dr_mp3.h \
    ../../C++/SoLoud/src/audiosource/wav/dr_wav.h \
    ../../C++/SoLoud/src/audiosource/wav/stb_vorbis.h \
    ../../C++/SoLoud/src/backend/miniaudio/miniaudio.h \

SOURCES += \
        ../../C++/SoLoud/src/audiosource/monotone/soloud_monotone.cpp \
        ../../C++/SoLoud/src/audiosource/noise/soloud_noise.cpp \
        ../../C++/SoLoud/src/audiosource/openmpt/soloud_openmpt.cpp \
        ../../C++/SoLoud/src/audiosource/openmpt/soloud_openmpt_dll.c \
        ../../C++/SoLoud/src/audiosource/sfxr/soloud_sfxr.cpp \
        ../../C++/SoLoud/src/audiosource/speech/darray.cpp \
        ../../C++/SoLoud/src/audiosource/speech/klatt.cpp \
        ../../C++/SoLoud/src/audiosource/speech/resonator.cpp \
        ../../C++/SoLoud/src/audiosource/speech/soloud_speech.cpp \
        ../../C++/SoLoud/src/audiosource/speech/tts.cpp \
        ../../C++/SoLoud/src/audiosource/tedsid/sid.cpp \
        ../../C++/SoLoud/src/audiosource/tedsid/soloud_tedsid.cpp \
        ../../C++/SoLoud/src/audiosource/tedsid/ted.cpp \
        ../../C++/SoLoud/src/audiosource/vic/soloud_vic.cpp \
        ../../C++/SoLoud/src/audiosource/vizsn/soloud_vizsn.cpp \
        ../../C++/SoLoud/src/audiosource/wav/dr_impl.cpp \
        ../../C++/SoLoud/src/audiosource/wav/soloud_wav.cpp \
        ../../C++/SoLoud/src/audiosource/wav/soloud_wavstream.cpp \
        ../../C++/SoLoud/src/audiosource/wav/stb_vorbis.c \
        ../../C++/SoLoud/src/backend/miniaudio/soloud_miniaudio.cpp \
        ../../C++/SoLoud/src/c_api/soloud_c.cpp \
        ../../C++/SoLoud/src/core/soloud.cpp \
        ../../C++/SoLoud/src/core/soloud_audiosource.cpp \
        ../../C++/SoLoud/src/core/soloud_bus.cpp \
        ../../C++/SoLoud/src/core/soloud_core_3d.cpp \
        ../../C++/SoLoud/src/core/soloud_core_basicops.cpp \
        ../../C++/SoLoud/src/core/soloud_core_faderops.cpp \
        ../../C++/SoLoud/src/core/soloud_core_filterops.cpp \
        ../../C++/SoLoud/src/core/soloud_core_getters.cpp \
        ../../C++/SoLoud/src/core/soloud_core_setters.cpp \
        ../../C++/SoLoud/src/core/soloud_core_voicegroup.cpp \
        ../../C++/SoLoud/src/core/soloud_core_voiceops.cpp \
        ../../C++/SoLoud/src/core/soloud_fader.cpp \
        ../../C++/SoLoud/src/core/soloud_fft.cpp \
        ../../C++/SoLoud/src/core/soloud_fft_lut.cpp \
        ../../C++/SoLoud/src/core/soloud_file.cpp \
        ../../C++/SoLoud/src/core/soloud_filter.cpp \
        ../../C++/SoLoud/src/core/soloud_misc.cpp \
        ../../C++/SoLoud/src/core/soloud_queue.cpp \
        ../../C++/SoLoud/src/core/soloud_thread.cpp \
        ../../C++/SoLoud/src/filter/soloud_bassboostfilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_biquadresonantfilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_dcremovalfilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_echofilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_fftfilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_flangerfilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_freeverbfilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_lofifilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_robotizefilter.cpp \
        ../../C++/SoLoud/src/filter/soloud_waveshaperfilter.cpp

INCLUDEPATH += $$PWD/../../C++/SoLoud/include/
LIBS += -lOpenSLES
}
