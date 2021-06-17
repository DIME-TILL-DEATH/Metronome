#include <QDebug>

#include "metronome.h"

Metronome::Metronome(QObject *parent) : QObject(parent)
{
    baseSound.setSource(QUrl::fromLocalFile("://Sounds/Metronomes/metronome.wav"));
    baseSound.setVolume(0.25f);

    mainPatternTimer.setTimerType(Qt::PreciseTimer);
    mainPatternTimer.setInterval(60*1000/120);

    connect(&mainPatternTimer, &QTimer::timeout, this, &Metronome::mainPatternTimerEvent);
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

void Metronome::mainPatternTimerEvent()
{
    baseSound.play();

    MetronomePreset::NextNote nextNote = m_activePreset.proceedNextNote();
    mainPatternTimer.setInterval(nextNote.timeInterval);

}

quint16 Metronome::tempo()
{
    return m_activePreset.tempo();
}

bool Metronome::isMetronomePlaying()
{
    return mainPatternTimer.isActive();
}

void Metronome::playStopButtonClick()
{
    if(mainPatternTimer.isActive())
    {
        mainPatternTimer.stop();
    }
    else
    {
       mainPatternTimer.start();
    }

    emit isMetronomePlayingChanged();
}

void Metronome::tempoChanged(quint16 tempo)
{
    m_activePreset.setTempo(tempo);
}
