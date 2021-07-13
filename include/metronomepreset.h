#ifndef METRONOMEPRESET_H
#define METRONOMEPRESET_H

#include <QList>
#include "musicaltypes.h"
#include "musicalnote.h"
#include "musicalpatternmodel.h"

struct TimingMap
{
    std::vector<quint16> tempoMap;
    std::vector<std::pair<quint8, quint8> > timeSignatureMap;
    // по-хорошему надо вектор паттернов передавать
    // но тройной вектор это чересчур, нужен отдельный объект, видимо
    std::vector<std::vector<quint16> > timeIntervals;
};
Q_DECLARE_METATYPE(TimingMap)

class MetronomePreset
{
public:
    MetronomePreset();
    ~MetronomePreset();

    MusicalPatternModel& pattern(quint16 id=0);

    bool setTempo(quint16 tempo);
    quint16 tempo() const;

//    std::vector<quint16> patternTimeIntervals(quint16 patternIndex=0);
    std::vector<std::vector<quint16> > timeIntervals(quint16 patternIndex=0);
    const TimingMap &timings();

    bool addBar(const MusicalBar &newBar, quint16 barIndex, quint16 patternIndex);
    bool removeBar(quint16 barIndex, quint16 patternIndex = 0);
    void updateModel(quint16 patternIndex = 0);

private:
    quint16 m_tempo {120};
    std::pair<quint8, quint8> m_timeSignature {4, 4};

    // Скорее всего тайминги не надо хранить в пресете постояно
    // а надо собирать структуру прямо перед отправкой
    void recalculateTimings();
    TimingMap m_timings;

    std::map<MusicalTypes::NoteType, quint16> m_noteTimeIntervals;
    std::vector<MusicalPattern> m_patterns;

    std::vector<MusicalPatternModel*> m_patternModels;
};

#endif // METRONOMEPRESET_H
