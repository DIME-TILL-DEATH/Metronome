#ifndef METRONOME_H
#define METRONOME_H

#include <QObject>
#include <QTimer>
#include <QThread>

#include "metronomepreset.h"
#include "timersengine.h"
#include "soundengine.h"

class Metronome : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMetronomePlaying READ isMetronomePlaying NOTIFY isMetronomePlayingChanged)

public:
    static Metronome& instance();

    Metronome(const Metronome&) = delete;
    Metronome operator=(const Metronome&) = delete;

    bool isMetronomePlaying();

    // Methods for UI
    Q_INVOKABLE quint16 tempo();// переделать на property
    Q_INVOKABLE MusicalPatternModel &pattern(quint16 id=0);

private:
    Metronome(QObject *parent = nullptr);
    ~Metronome();


    TimersEngine* timersEngine;
    SoundEngine* soundEngine;
    QThread* timersThread;
    QThread* soundThread;

    MetronomePreset m_activePreset;

    QTimer practiceTimer;

signals:
    void isMetronomePlayingChanged();

    // передавать std::map или аналог с интервалами соответствующими следующей ноте
    void setTimerNextInterval(quint16 interval);
    void startStopPlaying();

public slots:
    // заменить на timerEvent, принимать id таймера у которого произошёл таймаут, в соотвтествии
    // с ним извлекать ноту из нужного паттерна
    // или ничего не делать, если это событие базового метронома, а не паттерна
    void mainPatternTimerEvent();
    void playStopButtonClick();
    void tempoChanged(quint16 tempo);
};

#endif // METRONOME_H
