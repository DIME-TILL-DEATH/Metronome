#include "soundengine.h"

#include <QCoreApplication>
#include <QFile>
#include <QDataStream>

SoundEngine::SoundEngine(QObject *parent) : QObject(parent)
{
//    baseSound.setSource(/*QUrl::fromLocalFile("://Sounds/Metronomes/metronome.wav")*/);
//    baseSound.setVolume(0.25f);

//    qDebug() << QCoreApplication::applicationDirPath();

    QFile wavFile("://Sounds/Metronomes/metronome.wav");
    if(wavFile.open(QIODevice::ReadOnly))
    {
        QByteArray data = wavFile.readAll();
        const unsigned char* data_ptr = reinterpret_cast<const unsigned char*>(data.constData());

        m_engineSoloud.init(SoLoud::Soloud::FLAGS::CLIP_ROUNDOFF, SoLoud::Soloud::BACKENDS::MINIAUDIO);
        m_waveMetronome.loadMem(data_ptr, data.size(), true);
    }
}

SoundEngine::~SoundEngine()
{
    m_engineSoloud.deinit();
}

void SoundEngine::playMetronomeSound(quint16 activeNoteIndex)
{
    Q_UNUSED(activeNoteIndex)
//    qDebug() << "Time between clicks: " << elapsedTimer.elapsed();
//    elapsedTimer.start();

//    baseSound.play();
    m_engineSoloud.play(m_waveMetronome);
}
