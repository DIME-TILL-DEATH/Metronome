#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QDebug>
#include <QObject>
#include <QSoundEffect>
#include <QAudioOutput>

#include <QElapsedTimer>
#include <QHash>

#include "musicaltypes.h"
#include "soloud.h"
#include "soloud_wav.h"

class SoundEngine : public QObject
{
    Q_OBJECT
public:
    explicit SoundEngine(QObject *parent = nullptr);
    ~SoundEngine();

    const QHash<MusicalTypes::MetronomeEvents, double> &volumesMap() const;
    void setVolumesMap(const QHash<MusicalTypes::MetronomeEvents, double> &newVolumesMap);

public slots:
    void playMetronomeSound(quint16 barIndex, quint16 noteIndex, MusicalTypes::MetronomeEvents event);

signals:

private:
    SoLoud::Soloud m_engineSoloud;

    SoLoud::Wav m_waveMetronome;

    QHash<MusicalTypes::MetronomeEvents, SoLoud::Wav> m_sounds{
        {MusicalTypes::MetronomeEvents::MetronomeClick, {}},
        {MusicalTypes::MetronomeEvents::MetronomeAccentedClick, {}},
        {MusicalTypes::MetronomeEvents::PatternClick, {}}
    };

    QHash<MusicalTypes::MetronomeEvents, double> m_volumesMap;

    QElapsedTimer elapsedTimer;
};

#endif // SOUNDENGINE_H
