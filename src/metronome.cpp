#include <QDebug>

#include "metronome.h"

Metronome::Metronome(QObject *parent) : QObject(parent)
{
    timersThread = new QThread();
    timersEngine = new TimersEngine();
    soundThread = new QThread();
    soundEngine = new SoundEngine();

    connect(timersEngine, &TimersEngine::mainPatternTimerTimout,
            this, &Metronome::mainPatternTimerEvent);
    connect(timersEngine, &TimersEngine::mainPatternTimerTimout,
            soundEngine, &SoundEngine::playMetronomeSound);
    connect(timersEngine, &TimersEngine::isMetronomePlayingChanged,
            this, &Metronome::isMetronomePlayingChanged);

    connect(this, &Metronome::startStopPlaying,
            timersEngine, &TimersEngine::startStopCounting, Qt::QueuedConnection);
    connect(this, &Metronome::setTimerNextInterval,
            timersEngine, &TimersEngine::setNextInterval, Qt::QueuedConnection);


    timersEngine->moveToThread(timersThread);
    timersThread->start(QThread::Priority::TimeCriticalPriority);

    soundEngine->moveToThread(soundThread);
    soundThread->start(QThread::Priority::TimeCriticalPriority);
}

Metronome::~Metronome()
{
    timersThread->quit();
    soundThread->quit();
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
//    MetronomePreset::NextNote nextNote = m_activePreset.popNote();
    emit setTimerNextInterval(m_activePreset.popNote().timeInterval);
}

quint16 Metronome::tempo()
{
    return m_activePreset.tempo();
}

bool Metronome::isMetronomePlaying()
{
    // TODO: переписать так, чтобы timersEngine можно было
    // не делать членом Metronome
    return timersEngine->isTimersCounting();
}

void Metronome::playStopButtonClick()
{
    emit startStopPlaying();
//    emit setTimerNextInterval(m_activePreset.popNote().timeInterval);
}

void Metronome::tempoChanged(quint16 tempo)
{
    m_activePreset.setTempo(tempo);
}
