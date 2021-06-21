#ifndef METRONOMEPRESET_H
#define METRONOMEPRESET_H

#include <QList>
#include "musicaltypes.h"
#include "musicalnote.h"
#include "musicalpatternmodel.h"

class MetronomePreset
{
public:
    MetronomePreset();

    MusicalPatternModel& pattern(quint16 id=0);

    bool setTempo(quint16 tempo);
    quint16 tempo() const;

    // maybe std::tuple?
    struct NextNote{
        quint16 timeInterval;
        bool isFirstBarNote;
    };

    NextNote popNote(quint16 patternId=0);
//    const MusicalTypes::TimeIntervals &timeIntervals() const;

private:
    quint16 m_tempo {120};
    MusicalTypes::TimeIntervals m_timeIntervals;

    quint16 m_nowPosition{0};

    std::vector<MusicalPatternModel*> m_patterns;
};

#endif // METRONOMEPRESET_H
