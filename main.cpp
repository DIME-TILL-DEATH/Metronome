#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QTimer>
#include <QObject>

#include <QSoundEffect>

#include "musicalpatternmodel.h"
#include "musicalnote.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    //------------------------------
    // попробовать QAudioOutput вместо QSoundEffect
    QSoundEffect baseSound;
    baseSound.setSource(QUrl::fromLocalFile("://Sounds/Metronomes/metronome.wav"));
   // baseSound.setLoopCount(QSoundEffect::Infinite);
   // baseSound.setVolume(0.25f);
   // baseSound.play();

    QTimer mainTimer;
    mainTimer.setTimerType(Qt::PreciseTimer);
    mainTimer.setInterval(60*1000/120);
    mainTimer.start();

    QObject::connect(&mainTimer, &QTimer::timeout, &baseSound, &QSoundEffect::play);

    //-----------------------------

    QQmlApplicationEngine engine;

    MusicalPatternModel::registerMe("Pattern");
    // перенести регистрацию класса(или нет?)
    qmlRegisterUncreatableType<MusicalNote>("MusicalNoteModule", 1, 0,
                                            "MusicalNote",
                                            "Error: Only for enums!"); // Зарегистрировать данный класс в качестве мета объекта

    engine.addImportPath(":/qml");  // добавляем базовую директорию qml в пути импорта
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
