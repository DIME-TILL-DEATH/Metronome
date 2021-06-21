#include <QDebug>
#include "metronomepreset.h"

MetronomePreset::MetronomePreset()
{
    m_patterns.push_back(new MusicalPatternModel);
    m_patterns.push_back(new MusicalPatternModel);
}

MusicalPatternModel &MetronomePreset::pattern(quint16 id)
{
    if(id > m_patterns.size()-1)
    {
        qWarning() << "Pattern with id: " << id << " doesn't exist! Returning pattern with id 0";
        return *m_patterns.at(0); // ну такое. Надо что-то поумнее
    }
    return *m_patterns.at(id);
}

bool MetronomePreset::setTempo(quint16 tempo)
{
   if (tempo>0)
   {
       m_tempo = tempo;

       // возможно надо переделать в цикл и хранить длительности эффективнее
       // base intervals
       m_timeIntervals.Whole = MusicalTypes::OneMinute/(tempo/4);
       m_timeIntervals.Half = MusicalTypes::OneMinute/(tempo/2);
       m_timeIntervals.Quarter = MusicalTypes::OneMinute/(tempo);
       m_timeIntervals.Eight = MusicalTypes::OneMinute/(tempo*2);
       m_timeIntervals.Sixteenth = MusicalTypes::OneMinute/(tempo*4);
       m_timeIntervals.Thirty_second = MusicalTypes::OneMinute/(tempo*8);

       // triplets
       m_timeIntervals.Eight_triplet = MusicalTypes::OneMinute/(tempo*3);
       m_timeIntervals.Sixteenth_triplet = MusicalTypes::OneMinute/(tempo*6);
       m_timeIntervals.Thirty_second_triplet = MusicalTypes::OneMinute/(tempo*12);

       return true;
   }
   return false;
}

quint16 MetronomePreset::tempo() const
{
    return m_tempo;
}

MetronomePreset::NextNote MetronomePreset::popNote(quint16 patternId)
{
    if(patternId > m_patterns.size()-1)
    {
        qWarning() << "Pattern with id: " << patternId << " doesn't exist!";
        return {100, 0}; // ну такое. Надо что-то поумнее
    }

    MusicalNote note = m_patterns.at(patternId)->popNote();
    MetronomePreset::NextNote returnValue;

    // Убого!!!!
    switch(note.type())
    {
        case MusicalTypes::NoteType::Quarter:
        {
            returnValue.timeInterval = m_timeIntervals.Quarter;
            break;
        }
        case MusicalTypes::NoteType::Eight:
        {
            returnValue.timeInterval = m_timeIntervals.Eight;
            break;
        }
        default:
        {
            returnValue.timeInterval = m_timeIntervals.Quarter;
            break;
        }
    }

    returnValue.isFirstBarNote = false;

    return returnValue;
}

//const MusicalTypes::TimeIntervals &MetronomePreset::timeIntervals() const
//{
//    return m_timeIntervals;
//}
