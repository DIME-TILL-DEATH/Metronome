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
    connect(this, &Metronome::setTimerIntervals,
            timersEngine, &TimersEngine::setPatternTimeIntervals, Qt::QueuedConnection);


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

void Metronome::mainPatternTimerEvent(quint16 barIndex, quint16 noteIndex, MusicalTypes::MetronomeEvents event)
{
    m_activeBarIndex = barIndex;
    m_activeNoteIndex = noteIndex;

    emit activeNoteIndexChanged();
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

quint16 Metronome::activeBarIndex() const
{
    return m_activeBarIndex;
}

quint16 Metronome::activeNoteIndex()
{
    return m_activeNoteIndex;
}

void Metronome::playStopButtonClick()
{
//    emit setTimerIntervals(m_activePreset.timeIntervals());
    emit setTimerIntervals(m_activePreset.timings());
    emit startStopPlaying();
    emit activeNoteIndexChanged();
}

void Metronome::tempoChanged(quint16 tempo)
{
    m_activePreset.setTempo(tempo);
//    emit setTimerIntervals(m_activePreset.timeIntervals());
    emit setTimerIntervals(m_activePreset.timings());
}

void Metronome::addBar(quint16 barIndex, quint16 patternIndex, MusicalBar bar)
{
    m_activePreset.addBar(bar, barIndex, patternIndex);
}

void Metronome::removeBar(quint16 barIndex, quint16 patternIndex)
{
    m_activePreset.removeBar(barIndex, patternIndex);
}

void Metronome::updateModel(quint16 patternIndex)
{
    m_activePreset.updateModel(patternIndex);
}
