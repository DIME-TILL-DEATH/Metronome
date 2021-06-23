#include "timersengine.h"

#include <QGuiApplication>


TimersEngine::TimersEngine(QObject *parent)
                :QObject(parent)
{
    mainPatternTimer.setTimerType(Qt::PreciseTimer);

    connect(&mainPatternTimer, &QTimer::timeout, this, &TimersEngine::processMainPatternTimerTimeout);
}

TimersEngine::~TimersEngine()
{
    mainPatternTimer.stop();
}

void TimersEngine::setNextInterval(quint16 newNextInterval)
{
    m_nextInterval = newNextInterval;
}

void TimersEngine::setPatternTimeIntervals(const std::vector<quint16>& patternTimeIntervals)
{
    m_patternTimeIntervals = patternTimeIntervals;
}

void TimersEngine::processMainPatternTimerTimeout()
{
//        qDebug() << "Time between clicks: " << elapsedTimer.elapsed();
//        elapsedTimer.start();
        if(m_countingPosition >= m_patternTimeIntervals.size()-1)
        {
            m_countingPosition = 0;
        }
        else
        {
            m_countingPosition++;
        }
        emit mainPatternTimerTimout(m_countingPosition);
        mainPatternTimer.setInterval(m_patternTimeIntervals.at(m_countingPosition));
        // отображение проигрывания ноты сделать не на основе роли ноты,
        // а на основе индекса по вектору интервалов через класс Metronome
        // ***а индекс в "role" оставить для "select" ради редактирования или старта проигрывания
}

void TimersEngine::startStopCounting()
{
    // пока установка проигрывания с нуля, чтобы после редактирования
    // не вывалиться за пределы вектора и не словить exception
    // TODO: сделать правильное проигрывание просле редактирования(удаления такта)
    if(m_countingPosition > m_patternTimeIntervals.size()-1)
    {
        m_countingPosition = 0;
    }

    if(mainPatternTimer.isActive())
    {
        mainPatternTimer.stop();
    }
    else
    {
        mainPatternTimer.start(m_patternTimeIntervals.at(m_countingPosition));
    }
    emit isMetronomePlayingChanged();
}

bool TimersEngine::isTimersCounting()
{
    return mainPatternTimer.isActive();
}
