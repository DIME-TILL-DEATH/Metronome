#include <QDebug>

#include "metronome.h"

Metronome::Metronome(QObject *parent) : QObject(parent)
{
    baseSound.setSource(QUrl::fromLocalFile("://Sounds/Metronomes/metronome.wav"));
    baseSound.setVolume(0.25f);

    connect(&timersThread, &TimersThread::mainPatternTimerTimout,
            this, &Metronome::mainPatternTimerEvent);
//    connect(this, &Metronome::isMetronomePlayingChanged,
//            &timersThread, &TimersThread::startStopCounting);

    timersThread.start(QThread::Priority::TimeCriticalPriority);
}

Metronome::~Metronome()
{
    timersThread.quit();
}

Metronome &Metronome::instance()
{
    static Metronome instance;
    return instance;
}

MusicalPatternModel &Metronome::pattern(quint16 id)
{
    return m_activePreset.pattern(id);
}

void Metronome::mainPatternTimerEvent()
{
//    qDebug() << "Time between clicks: " << elapsedTimer.elapsed();
//    elapsedTimer.start();
    baseSound.play();

    MetronomePreset::NextNote nextNote = m_activePreset.proceedNextNote();
    timersThread.setNextInterval(nextNote.timeInterval);
}

quint16 Metronome::tempo()
{
    return m_activePreset.tempo();
}

bool Metronome::isMetronomePlaying()
{
    return timersThread.isTimersCounting();
}

void Metronome::playStopButtonClick()
{
    timersThread.startStopCounting();
    emit isMetronomePlayingChanged();
}

void Metronome::tempoChanged(quint16 tempo)
{
    m_activePreset.setTempo(tempo);
}
