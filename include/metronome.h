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
    Q_PROPERTY(quint16 activeNoteIndex READ activeNoteIndex NOTIFY activeNoteIndexChanged)
public:
    static Metronome& instance();

    Metronome(const Metronome&) = delete;
    Metronome operator=(const Metronome&) = delete;

    bool isMetronomePlaying();
    quint16 activeNoteIndex();

    // Methods for UI
    Q_INVOKABLE quint16 tempo();// переделать на property
    Q_INVOKABLE MusicalPatternModel &pattern(quint16 id=0);

private:
    Metronome(QObject *parent = nullptr);
    ~Metronome();

    quint16 m_activeNoteIndex{0};

    TimersEngine* timersEngine;
    SoundEngine* soundEngine;
    QThread* timersThread;
    QThread* soundThread;

    MetronomePreset m_activePreset;

    QTimer practiceTimer;

signals:
    void isMetronomePlayingChanged();
    void activeNoteIndexChanged();
    void setTimerIntervals(const std::vector<quint16>& patternTimeIntervals);
    void startStopPlaying();

public slots:
    // заменить на timerEvent, принимать id таймера у которого произошёл таймаут, в соотвтествии
    // с ним извлекать ноту из нужного паттерна
    // или ничего не делать, если это событие базового метронома, а не паттерна
    void mainPatternTimerEvent(quint16 activeNoteIndex);

    void playStopButtonClick();
    void tempoChanged(quint16 tempo);

    // Операции редактирования из UI
    void addBar(quint16 barIndex, quint16 patternIndex = 0, MusicalBar bar = MusicalBar());
    void removeBar(quint16 barIndex, quint16 patternIndex = 0);
    void updateModel(quint16 patternIndex = 0);
};

#endif // METRONOME_H
