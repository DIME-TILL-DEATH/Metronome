#include "soundengine.h"

SoundEngine::SoundEngine(QObject *parent) : QObject(parent)
{
    baseSound.setSource(QUrl::fromLocalFile("://Sounds/Metronomes/metronome.wav"));
    baseSound.setVolume(0.25f);
}

void SoundEngine::playMetronomeSound(quint16 activeNoteIndex)
{
    Q_UNUSED(activeNoteIndex)
//    qDebug() << "Time between clicks: " << elapsedTimer.elapsed();
//    elapsedTimer.start();

    baseSound.play();
}
