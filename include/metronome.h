#ifndef METRONOME_H
#define METRONOME_H

#include <QObject>
#include <QTimer>
#include <QSoundEffect>
#include <QAudioOutput>

#include "metronomepreset.h"

class Metronome : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMetronomePlaying READ isMetronomePlaying NOTIFY isMetronomePlayingChanged)

public:
    static Metronome& instance();

    Metronome(const Metronome&) = delete;
    Metronome operator=(const Metronome&) = delete;

    bool isMetronomePlaying();

    // пеерписать чтоб вытаскивало модель наружу и сделать invokable
    MetronomePreset &activePreset();

    // Methods for UI
    // переделать на property
    Q_INVOKABLE quint16 tempo();
private:
    Metronome(QObject *parent = nullptr);

    MetronomePreset m_activePreset;

    QTimer mainPatternTimer; //pattern 1 timer
    // TODO: list of timers for each type of sounde BEHIND the pattern itself
    // (i a e triplet, 2nd pattern), all sounds that you can add by the mixer
    QTimer practiceTimer;

    QSoundEffect baseSound;

signals:
    void isMetronomePlayingChanged();

public slots:
    void mainPatternTimerEvent();
    void playStopButtonClick();
    void tempoChanged(quint16 tempo);

};

#endif // METRONOME_H
