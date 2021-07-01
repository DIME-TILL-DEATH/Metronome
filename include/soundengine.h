#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QDebug>
#include <QObject>
#include <QSoundEffect>
#include <QAudioOutput>

#include <QElapsedTimer>
#include <QString>

#include "soloud.h"
#include "soloud_wav.h"

class SoundEngine : public QObject
{
    Q_OBJECT
public:
    explicit SoundEngine(QObject *parent = nullptr);
    ~SoundEngine();

public slots:
    void playMetronomeSound(quint16 activeNoteIndex);

signals:

private:
//    QSoundEffect baseSound{this};

    SoLoud::Soloud m_engineSoloud;
    SoLoud::Wav m_waveMetronome;

    QElapsedTimer elapsedTimer;
};

#endif // SOUNDENGINE_H
