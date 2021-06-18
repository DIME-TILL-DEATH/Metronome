#ifndef METRONOME_H
#define METRONOME_H

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>
#include <QSoundEffect>
#include <QAudioOutput>

#include "metronomepreset.h"
#include "timersthread.h"

class Metronome : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isMetronomePlaying READ isMetronomePlaying NOTIFY isMetronomePlayingChanged)

public:
    static Metronome& instance();

    Metronome(const Metronome&) = delete;
    Metronome operator=(const Metronome&) = delete;

    bool isMetronomePlaying();

    // переписать чтоб вытаскивало модель наружу и сделать invokable

    // Methods for UI
    // переделать на property
    Q_INVOKABLE quint16 tempo();
    Q_INVOKABLE MusicalPatternModel &pattern(quint16 id=0);
private:
    Metronome(QObject *parent = nullptr);
    ~Metronome();


    TimersThread timersThread;

    MetronomePreset m_activePreset;

    QElapsedTimer elapsedTimer;
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
