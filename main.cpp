#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QTimer>
#include <QObject>

#include <QSoundEffect>

#ifdef Q_OS_ANDROID
#include <QtSvg>    //Because deployment sometimes just forgets to include this lib otherwise
#endif

#include "musicalpatternmodel.h"
#include "musicalnote.h"

#include "metronome.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
//------------------------------------------------------------------
    // Singletone
    Metronome& metronome{Metronome::instance()};
    engine.rootContext()->setContextProperty("Metronome", &metronome);
    engine.rootContext()->setContextProperty("mainPattern", &metronome.pattern(0));
    engine.rootContext()->setContextProperty("secondaryPattern", &metronome.pattern(1));

//    qmlRegisterSingletonInstance("SingletoneMetronome", 1, 0, "Metronome", &metronome);
//    MusicalPatternModel::registerMe("CoreApplicationModule");

    // перенести регистрацию класса(или нет?)
    qmlRegisterUncreatableType<MusicalTypes>("MusicalTypesModule", 1, 0,
                                            "MusicalTypes",
                                            "Error: Only for enums!"); // Зарегистрировать данный класс в качестве мета объекта

//---------------------------------------------------------------------
    engine.addImportPath(":/qml");
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
