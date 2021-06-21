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

void TimersEngine::processMainPatternTimerTimeout()
{
//        qDebug() << "Time between clicks: " << elapsedTimer.elapsed();
//        elapsedTimer.start();
        emit mainPatternTimerTimout();

    // при нажатии кнопки Play(или, в будущем, редактирования "на ходу")
    // передавать вектор с набором интервалов таймера и играть по нему.
    // не использовать "pop note" и прочее вытаскивание "наверх" ноты.
    // отображение проигрывания ноты сделать не на основе роли ноты,
    // а на основе индекса по вектору интервалов через класс Metronome
    // ***а индекс в "role" оставить для "select" ради редактирования или старта проигрывания
        mainPatternTimer.setInterval(m_nextInterval);
}

void TimersEngine::startStopCounting()
{
    if(mainPatternTimer.isActive())
    {
        mainPatternTimer.stop();
    }
    else
    {
        mainPatternTimer.start(m_nextInterval);
    }
    emit isMetronomePlayingChanged();
}

bool TimersEngine::isTimersCounting()
{
    return mainPatternTimer.isActive();
}
