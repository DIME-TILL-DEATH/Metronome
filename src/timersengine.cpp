#include "timersengine.h"

#include <QGuiApplication>


TimersEngine::TimersEngine(QObject *parent)
                :QObject(parent)
{
    mainPatternTimer.setTimerType(Qt::PreciseTimer);
    metronomeTimer.setTimerType(Qt::PreciseTimer);

    connect(&metronomeTimer, &QTimer::timeout, this, &TimersEngine::processMetronomeTimerTimeout);
    connect(&mainPatternTimer, &QTimer::timeout, this, &TimersEngine::processMainPatternTimerTimeout);
}

TimersEngine::~TimersEngine()
{
    mainPatternTimer.stop();
    metronomeTimer.stop();
}

void TimersEngine::setPatternTimeIntervals(const TimingMap& patternTimings)
{
    m_patternTimeIntervals = patternTimings.timeIntervals;
    m_timeSignatureMap = patternTimings.timeSignatureMap;
    m_tempoMap = patternTimings.tempoMap;
}

void TimersEngine::processMetronomeTimerTimeout()
{
//    elapsedTimer.start();

    if(m_metronomePosition == m_timeSignatureMap.at(m_barPosition).second-1)
    {
        emit mainPatternTimerTimout(m_barPosition, m_notePosition, MusicalTypes::MetronomeEvents::MetronomeAccentedClick);
        m_metronomePosition = 0;
        if(m_barPosition >= m_patternTimeIntervals.size()-1)
        {
            m_barPosition = 0;
            m_notePosition = 0;
        }
        else
        {
            m_barPosition++;
            m_notePosition = 0;
        }
        // break last note of pattern
        mainPatternTimer.start(m_patternTimeIntervals.at(m_barPosition).at(m_notePosition));
        emit mainPatternTimerTimout(m_barPosition, m_notePosition, MusicalTypes::MetronomeEvents::PatternClick);
    }
    else
    {
        emit mainPatternTimerTimout(m_barPosition, m_notePosition, MusicalTypes::MetronomeEvents::MetronomeClick);
        m_metronomePosition++;
    }
    // Где-то здесь надо добавить считывание m_tempoMap в основной метроном!!!
    // m_metronomePosition не соответствует напрямую записям в tempoMap
    metronomeTimer.start(m_tempoMap.at(0));
}

void TimersEngine::processMainPatternTimerTimeout()
{
//    qDebug() << elapsedTimer.elapsed();
        if(m_notePosition >= m_patternTimeIntervals.at(m_barPosition).size()-1)
        {
            m_notePosition = 0;
        }
        else
        {
            m_notePosition++;
        }

        emit mainPatternTimerTimout(m_barPosition, m_notePosition, MusicalTypes::MetronomeEvents::PatternClick);
        mainPatternTimer.setInterval(m_patternTimeIntervals.at(m_barPosition).at(m_notePosition));

        // ***а индекс в "role" оставить для "select" ради редактирования или старта проигрывания
}

void TimersEngine::startStopCounting()
{
    // пока установка проигрывания с нуля, чтобы после редактирования
    // не вывалиться за пределы вектора и не словить exception
    // TODO: сделать правильное проигрывание просле редактирования(удаления такта)
//    if(m_countingPosition > m_patternTimeIntervals.size()-1)
//    {
//        m_countingPosition = 0;
//    }

    if(mainPatternTimer.isActive())
    {
        mainPatternTimer.stop();
        metronomeTimer.stop();
    }
    else
    {
        mainPatternTimer.start(m_patternTimeIntervals.at(m_barPosition).at(m_notePosition));
        // m_tempoMap неполная, всего пара позиций
        // m_metronomePosition не соответствует напрямую записям в tempoMap
        metronomeTimer.start(m_tempoMap.at(0));
    }
    emit isMetronomePlayingChanged();
}

bool TimersEngine::isTimersCounting()
{
    return mainPatternTimer.isActive();
}
