#include "soundengine.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDataStream>

#include <QJsonDocument>
#include <QJsonObject>

SoundEngine::SoundEngine(QObject *parent) : QObject(parent)
{
    m_engineSoloud.init(SoLoud::Soloud::FLAGS::CLIP_ROUNDOFF,
                        SoLoud::Soloud::BACKENDS::MINIAUDIO,
                        44100,
                        128);

    QFile loadFile(QStringLiteral(":/qml/metronomesounds.json"));
    if (loadFile.open(QIODevice::ReadOnly))
    {
        QByteArray fileData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(fileData));
        QJsonObject jsonObject = loadDoc.object();

        for(auto it = MusicalTypes::metronomeEventsNames.begin();
                 it != MusicalTypes::metronomeEventsNames.end(); ++it)
        {
            if (jsonObject.contains(it.key()) && jsonObject[it.key()].isString())
            {
                QFile wavFile(jsonObject[it.key()].toString());
                if(wavFile.open(QIODevice::ReadOnly))
                {
                    QByteArray data = wavFile.readAll();
                    m_sounds[it.value()].loadMem(reinterpret_cast<const unsigned char*>(data.constData()), data.size(), true, true);
                    m_sounds[it.value()].setInaudibleBehavior(true, false);
                    wavFile.close();
                }
            }
            else
            {
                qWarning() << it.key() << " path not found";
            }
        }
    }
}

SoundEngine::~SoundEngine()
{
    m_engineSoloud.deinit();
}

void SoundEngine::playMetronomeSound(quint16 barIndex, quint16 noteIndex, MusicalTypes::MetronomeEvents event)
{
//    qDebug() << elapsedTimer.elapsed();

    Q_UNUSED(barIndex)
    Q_UNUSED(noteIndex)
//    elapsedTimer.start();

    m_engineSoloud.play(m_sounds[event]);
}
