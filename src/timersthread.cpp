#include "timersthread.h"

#include <QGuiApplication>


TimersThread::TimersThread(QObject *parent)
                :QThread(parent)
{
    mainPatternTimer.setTimerType(Qt::PreciseTimer);
    mainPatternTimer.setInterval(60*1000/120);
    mainPatternTimer.start();
    mainPatternTimer.moveToThread(this);

    connect(&mainPatternTimer, &QTimer::timeout, this, &TimersThread::processMainPatternTimerTimeout);
    moveToThread(this);
}

TimersThread::~TimersThread()
{
    mainPatternTimer.stop();
}

quint16 TimersThread::nextInterval() const
{
    return m_nextInterval;
}

void TimersThread::setNextInterval(quint16 newNextInterval)
{
    m_nextInterval = newNextInterval;
}

void TimersThread::processMainPatternTimerTimeout()
{
    if(m_isMetronomePlaying)
    {
//        qDebug() << "Time between clicks: " << elapsedTimer.elapsed();
//        elapsedTimer.start();
        emit mainPatternTimerTimout();
        mainPatternTimer.setInterval(m_nextInterval);
    }
}

void TimersThread::startStopCounting()
{
    m_isMetronomePlaying = !m_isMetronomePlaying;
}

bool TimersThread::isTimersCounting()
{
    return m_isMetronomePlaying;
}
