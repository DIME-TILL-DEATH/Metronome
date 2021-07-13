#ifndef TIMERSENGINE_H
#define TIMERSENGINE_H

#include <QTimer>
#include <QElapsedTimer>
#include <QObject>
#include <QDebug>

#include "metronomepreset.h"
#include "musicaltypes.h"

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
    QTimer metronomeTimer{this};
    QElapsedTimer elapsedTimer;

    // а может все так и хранить в TimingMap?
    std::vector<std::vector<quint16> > m_patternTimeIntervals;
    std::vector<quint16> m_tempoMap;
    std::vector<std::pair<quint8, quint8> > m_timeSignatureMap;

    quint16 m_metronomePosition{0};
    quint16 m_barPosition{0};
    quint16 m_notePosition{0};

private slots:
    void processMetronomeTimerTimeout();
    void processMainPatternTimerTimeout();

public slots:
    void startStopCounting();
    bool isTimersCounting();
//    void setPatternTimeIntervals(const std::vector<std::vector<quint16> >& patternTimeIntervals);
    void setPatternTimeIntervals(const TimingMap& patternTimings);

signals:
    void mainPatternTimerTimout(quint16 barIndex, quint16 noteIndex, MusicalTypes::MetronomeEvents event);
    void isMetronomePlayingChanged();
};

#endif // TIMERSENGINE_H
