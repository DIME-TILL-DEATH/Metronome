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
public:
    static Metronome& instance();

    Metronome(const Metronome&) = delete;
    Metronome operator=(const Metronome&) = delete;

    MetronomePreset &activePreset();

    // Methods for UI
    Q_INVOKABLE quint16 tempo();
    Q_INVOKABLE bool isPlaying();
private:
    Metronome(QObject *parent = nullptr);

    MetronomePreset m_activePreset;

    QTimer mainTimer;
    QTimer practiceTimer;

    QSoundEffect baseSound;

signals:

public slots:
    void mainTimerEvent();
    void playStopButtonClick();
    void tempoChanged(quint16 tempo);

};

#endif // METRONOME_H
