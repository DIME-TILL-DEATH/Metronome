#ifndef TIMERSTHREAD_H
#define TIMERSTHREAD_H

#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include <QObject>
#include <QDebug>

class TimersThread : public QThread
{
    Q_OBJECT
public:
    explicit TimersThread(QObject* parent=nullptr);
    ~TimersThread();

private:
        // TODO: list of timers for each type of sounde BEHIND the pattern itself
        // (i a e triplet, 2nd pattern), all sounds that you can add by the mixer
    QTimer mainPatternTimer;
    QElapsedTimer elapsedTimer;

    bool m_isMetronomePlaying{false};
    quint16 m_nextInterval{500};
private slots:
    void processMainPatternTimerTimeout();


public:
    void startStopCounting();
    bool isTimersCounting();

    quint16 nextInterval() const;
    void setNextInterval(quint16 newNextInterval);

signals:
    void mainPatternTimerTimout();
};

#endif // TIMERSTHREAD_H
