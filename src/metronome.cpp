#include <QDebug>

#include "metronome.h"

Metronome::Metronome(QObject *parent) : QObject(parent)
{
    baseSound.setSource(QUrl::fromLocalFile("://Sounds/Metronomes/metronome.wav"));
    baseSound.setVolume(0.25f);

    mainTimer.setTimerType(Qt::PreciseTimer);
    mainTimer.setInterval(60*1000/120);

    connect(&mainTimer, &QTimer::timeout, this, &Metronome::mainTimerEvent);
}

Metronome &Metronome::instance()
{
    static Metronome instance;
    return instance;
}

MetronomePreset &Metronome::activePreset()
{
    return m_activePreset;
}

void Metronome::mainTimerEvent()
{
    baseSound.play();
    mainTimer.setInterval(m_activePreset.timeIntervals().Quarter);
}

quint16 Metronome::tempo()
{
    return m_activePreset.tempo();
}

bool Metronome::isPlaying()
{
    return mainTimer.isActive();
}

void Metronome::playStopButtonClick()
{
    if(mainTimer.isActive())
    {
        mainTimer.stop();
    }
    else
    {
       mainTimer.start();
    }
}

void Metronome::tempoChanged(quint16 tempo)
{
    m_activePreset.setTempo(tempo);
}
