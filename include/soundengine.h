#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <QDebug>
#include <QObject>
#include <QSoundEffect>
#include <QAudioOutput>

#include <QElapsedTimer>

class SoundEngine : public QObject
{
    Q_OBJECT
public:
    explicit SoundEngine(QObject *parent = nullptr);

public slots:
    void playMetronomeSound();

signals:

private:
    QSoundEffect baseSound{this};

    QElapsedTimer elapsedTimer;
};

#endif // SOUNDENGINE_H
