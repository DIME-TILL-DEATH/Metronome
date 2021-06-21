#ifndef TIMERSENGINE_H
#define TIMERSENGINE_H

#include <QTimer>
#include <QElapsedTimer>
#include <QObject>
#include <QDebug>

class TimersEngine : public QObject
{
    Q_OBJECT
public:
    explicit TimersEngine(QObject* parent=nullptr);
    ~TimersEngine();

private:
        // TODO: list of timers for each type of sounde BEHIND the pattern itself
        // (i a e triplet, 2nd pattern), all sounds that you can add by the mixer
    QTimer mainPatternTimer{this};
    QElapsedTimer elapsedTimer;

    quint16 m_nextInterval{500};
private slots:
    void processMainPatternTimerTimeout();


public slots:
    void startStopCounting();
    bool isTimersCounting();
    void setNextInterval(quint16 newNextInterval);

signals:
    void mainPatternTimerTimout();
    void isMetronomePlayingChanged();
};

#endif // TIMERSENGINE_H
