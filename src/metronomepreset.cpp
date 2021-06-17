#include <QDebug>
#include "metronomepreset.h"

MetronomePreset::MetronomePreset()
{

}

MusicalPatternModel &MetronomePreset::mainPattern()
{
    return m_mainPattern;
}

MusicalPatternModel &MetronomePreset::secondaryPattern()
{
    return m_secondaryPattern;
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

MetronomePreset::NextNote MetronomePreset::proceedNextNote()
{
    MusicalNote note = m_mainPattern.proceedNextNote();
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
