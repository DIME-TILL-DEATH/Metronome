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



    MusicalPatternModel &mainPattern();
    MusicalPatternModel &secondaryPattern();

    bool setTempo(quint16 tempo);
    quint16 tempo() const;

    const MusicalTypes::TimeIntervals &timeIntervals() const;

private:
    quint16 m_tempo {120};
    MusicalTypes::TimeIntervals m_timeIntervals;

    std::pair<quint8, MusicalTypes::NoteType> m_timeSignature {4, MusicalTypes::NoteType::Quarter};

    MusicalPatternModel m_mainPattern;
    MusicalPatternModel m_secondaryPattern{{
                                               {MusicalTypes::NoteType::Eight, "L", " "},
                                               {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                                {MusicalTypes::NoteType::Eight, "R", " "},
                                               {MusicalTypes::NoteType::Eight, "L", " "}
                                           }, nullptr};
};

#endif // METRONOMEPRESET_H
