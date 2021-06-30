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
    ~MetronomePreset();

    MusicalPatternModel& pattern(quint16 id=0);

    bool setTempo(quint16 tempo);
    quint16 tempo() const;

    std::vector<quint16> patternTimeIntervals(quint16 patternIndex=0);

    bool addBar(const MusicalBar &newBar, quint16 barIndex, quint16 patternIndex);
    bool removeBar(quint16 barIndex, quint16 patternIndex = 0);
    void updateModel(quint16 patternIndex = 0);
private:
    quint16 m_tempo {120};
    std::map<MusicalTypes::NoteType, quint16> m_timeIntervals;
    std::vector<MusicalPattern> m_patterns;

//     Временно!
//    MusicalPatternModel* model1;
//    MusicalPatternModel* model2;
    std::vector<MusicalPatternModel*> m_patternModels;
};

#endif // METRONOMEPRESET_H
