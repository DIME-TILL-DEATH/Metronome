#include <QDebug>
#include "metronomepreset.h"

MetronomePreset::MetronomePreset()
{
    // времянка. Инициализировать из default файла
    m_patterns.push_back(MusicalPattern());
    m_patterns.push_back(MusicalPattern());

    model1 = new MusicalPatternModel(m_patterns.at(0));
    model2 = new MusicalPatternModel(m_patterns.at(1));

    setTempo(m_tempo);
}

MetronomePreset::~MetronomePreset()
{
    delete model1;
    delete model2;
}

MusicalPatternModel &MetronomePreset::pattern(quint16 id)
{
    if(id > m_patterns.size()-1)
    {
        qWarning() << "Pattern with id: " << id << " doesn't exist! Returning pattern with id 0";
//        return *m_patterns.at(0); // ну такое. Надо что-то поумнее
    }
//    return *m_patterns.at(id);
    return *model1;
}

bool MetronomePreset::setTempo(quint16 tempo)
{
   if (tempo>0)
   {
       m_tempo = tempo;

       m_timeIntervals.clear();

       // возможно можно сделать не вручную, а через цикл перебор типов и рассчёт
       m_timeIntervals[MusicalTypes::NoteType::Whole] = MusicalTypes::OneMinute/(tempo/4);
       m_timeIntervals[MusicalTypes::NoteType::Half] = MusicalTypes::OneMinute/(tempo/2);
       m_timeIntervals[MusicalTypes::NoteType::Quarter] = MusicalTypes::OneMinute/(tempo);
       m_timeIntervals[MusicalTypes::NoteType::Eight] = MusicalTypes::OneMinute/(tempo*2);
       m_timeIntervals[MusicalTypes::NoteType::Sixteenth] = MusicalTypes::OneMinute/(tempo*4);
       m_timeIntervals[MusicalTypes::NoteType::Thirty_second] = MusicalTypes::OneMinute/(tempo*8);

       // triplets
       m_timeIntervals[MusicalTypes::NoteType::Eight_triplet] = MusicalTypes::OneMinute/(tempo*3);
       m_timeIntervals[MusicalTypes::NoteType::Sixteenth_triplet] = MusicalTypes::OneMinute/(tempo*6);
       m_timeIntervals[MusicalTypes::NoteType::Thirty_second_triplet] = MusicalTypes::OneMinute/(tempo*12);

       return true;
   }
   return false;
}

quint16 MetronomePreset::tempo() const
{
    return m_tempo;
}

std::vector<quint16> MetronomePreset::patternTimeIntervals(quint16 patternIndex)
{
    if(patternIndex > m_patterns.size()-1)
    {
        qWarning() << "Pattern with id: " << patternIndex << " doesn't exist!";
        return {120}; // ну такое. Надо что-то поумнее
    }

    std::vector<quint16> resultVector;
    for(auto& itNote : m_patterns.at(patternIndex).notePattern())
    {
        resultVector.push_back(m_timeIntervals.at(itNote.type()));
    }
    return resultVector;
}

bool MetronomePreset::addBar(MusicalBar* newBar, quint16 barIndex, quint16 patternIndex)
{
    if(patternIndex > m_patterns.size()-1)
    {
        qWarning() << "Trying to add bar. Pattern with index " << patternIndex << " is not availiable";
        return false;
    }
    model1->addBar(newBar, barIndex);
    return true;
}

bool MetronomePreset::removeBar(quint16 barIndex, quint16 patternIndex)
{
    if(patternIndex > m_patterns.size()-1)
    {
        qWarning() << "Trying to remove bar. Pattern with index " << patternIndex << " is not availiable";
        return false;
    }
    model2->removeBar(barIndex);
    return true;
}
