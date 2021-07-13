#include <QDebug>

#include "metronomepreset.h"

MetronomePreset::MetronomePreset()
{
    // времянка. Инициализировать из default файла
    m_patterns.push_back(MusicalPattern());
    m_patterns.push_back(MusicalPattern());

    m_patternModels.push_back(new MusicalPatternModel(m_patterns.at(0)));
    m_patternModels.push_back(new MusicalPatternModel(m_patterns.at(1)));

    setTempo(m_tempo);
}

MetronomePreset::~MetronomePreset()
{
    for(auto it : m_patternModels)
    {
        delete it;
    }
}

MusicalPatternModel &MetronomePreset::pattern(quint16 id)
{
    if(id > m_patterns.size()-1)
    {
        qWarning() << "Pattern with id: " << id << " doesn't exist! Returning pattern with id 0";
        return *m_patternModels.at(0); // ну такое. Надо что-то поумнее
    }
    return *m_patternModels.at(id);
}

bool MetronomePreset::setTempo(quint16 tempo)
{
   if (tempo>0)
   {
       m_tempo = tempo;

       m_noteTimeIntervals.clear();

       // возможно можно сделать не вручную, а через цикл перебор типов и рассчёт
       m_noteTimeIntervals[MusicalTypes::NoteType::Whole] = MusicalTypes::OneMinute/(tempo/4);
       m_noteTimeIntervals[MusicalTypes::NoteType::Half] = MusicalTypes::OneMinute/(tempo/2);
       m_noteTimeIntervals[MusicalTypes::NoteType::Quarter] = MusicalTypes::OneMinute/(tempo);
       m_noteTimeIntervals[MusicalTypes::NoteType::Eight] = MusicalTypes::OneMinute/(tempo*2);
       m_noteTimeIntervals[MusicalTypes::NoteType::Sixteenth] = MusicalTypes::OneMinute/(tempo*4);
       m_noteTimeIntervals[MusicalTypes::NoteType::Thirty_second] = MusicalTypes::OneMinute/(tempo*8);

       // triplets
       m_noteTimeIntervals[MusicalTypes::NoteType::Eight_triplet] = MusicalTypes::OneMinute/(tempo*3);
       m_noteTimeIntervals[MusicalTypes::NoteType::Sixteenth_triplet] = MusicalTypes::OneMinute/(tempo*6);
       m_noteTimeIntervals[MusicalTypes::NoteType::Thirty_second_triplet] = MusicalTypes::OneMinute/(tempo*12);

       return true;
   }
   return false;
}

quint16 MetronomePreset::tempo() const
{
    return m_tempo;
}

//std::vector<quint16> MetronomePreset::patternTimeIntervals(quint16 patternIndex)
//{
//    if(patternIndex > m_patterns.size()-1)
//    {
//        qWarning() << "Pattern with id: " << patternIndex << " doesn't exist!";
//        return {120}; // ну такое. Надо что-то поумнее
//    }

//    std::vector<quint16> resultVector;
//    for(auto& itNote : m_patterns.at(patternIndex).notePattern())
//    {
//        resultVector.push_back(m_timeIntervals.at(itNote.type()));
//    }
//    return resultVector;
//}

std::vector<std::vector<quint16> > MetronomePreset::timeIntervals(quint16 patternIndex)
{
    if(patternIndex > m_patterns.size()-1)
    {
        qWarning() << "Pattern with id: " << patternIndex << " doesn't exist!";
        return {}; // ну такое. Надо что-то поумнее
    }

    std::vector<MusicalBar> barPattern = m_patterns.at(patternIndex).barPattern();
    std::vector<std::vector<quint16> > resultVector;
    for(unsigned int i=0; i < barPattern.size(); i++)
    {
        resultVector.push_back({});
        for(auto& itNote : barPattern.at(i).notePattern())
        {
            resultVector.at(i).push_back(m_noteTimeIntervals.at(itNote.type()));
        }
    }
    return resultVector;
}

bool MetronomePreset::addBar(const MusicalBar& newBar, quint16 barIndex, quint16 patternIndex)
{
    if(patternIndex > m_patterns.size()-1)
    {
        qWarning() << "Trying to add bar. Pattern with index " << patternIndex << " is not availiable";
        return false;
    }
    m_patternModels.at(patternIndex)->addBar(newBar, barIndex);
    return true;
}

bool MetronomePreset::removeBar(quint16 barIndex, quint16 patternIndex)
{
    if(patternIndex > m_patterns.size()-1)
    {
        qWarning() << "Trying to remove bar. Pattern with index " << patternIndex << " is not availiable";
        return false;
    }
    m_patternModels.at(patternIndex)->removeBar(barIndex);
    return true;
}

void MetronomePreset::updateModel(quint16 patternIndex)
{
    m_patternModels.at(patternIndex)->updateModel();
}

const TimingMap &MetronomePreset::timings()
{
    recalculateTimings();
    return m_timings;
}

void MetronomePreset::recalculateTimings()
{
    m_timings.tempoMap.clear();
    m_timings.timeIntervals.clear();
    m_timings.timeSignatureMap.clear();

    std::vector<MusicalBar> barPattern = m_patterns.at(0).barPattern();
    for(unsigned int i=0; i < barPattern.size(); i++)
    {
        m_timings.timeIntervals.push_back({});
        m_timings.tempoMap.push_back(m_noteTimeIntervals[MusicalTypes::NoteType::Quarter]);
        m_timings.timeSignatureMap.push_back(m_timeSignature);

        for(auto& itNote : barPattern.at(i).notePattern())
        {
            m_timings.timeIntervals.at(i).push_back(m_noteTimeIntervals.at(itNote.type()));
        }
    }
}
