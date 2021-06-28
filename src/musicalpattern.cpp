#include "musicalpattern.h"

MusicalPattern::MusicalPattern()
{
    // временно
    MusicalBar tempBar1;
    MusicalBar tempBar2({
                                        {MusicalTypes::NoteType::Quarter, "R", " "},
                                        {MusicalTypes::NoteType::Eight, "R", " "},
                                        {MusicalTypes::NoteType::Eight, "L", "F"},
                                        {MusicalTypes::NoteType::Quarter, "R", " "},
                                        {MusicalTypes::NoteType::Eight, "L", " "},
                                        {MusicalTypes::NoteType::Eight, "L", "F"}
                                    });
    MusicalBar tempBar3({
                                        {MusicalTypes::NoteType::Whole, "", " "},
                                        {MusicalTypes::NoteType::Half, "", " "},
                                        {MusicalTypes::NoteType::Sixteenth, "", ""},
                                        {MusicalTypes::NoteType::Thirty_second, "", " "},
                                    });

    m_barPattern = {
        tempBar1,
        tempBar2,
        tempBar3
    };
}

MusicalPattern::MusicalPattern(const std::vector<MusicalBar>& barPattern)
{
    m_barPattern = barPattern;
}

MusicalPattern::MusicalPattern(const MusicalPattern &barPattern)
{
    m_barPattern = barPattern.m_barPattern;
}

MusicalPattern::~MusicalPattern()
{

}

MusicalPattern &MusicalPattern::operator=(const MusicalPattern &barPattern)
{
    m_barPattern = barPattern.m_barPattern;
    return *this;
}
MusicalBar &MusicalPattern::operator [](quint16 index)
{
    return m_barPattern.at(index);
}

const MusicalBar &MusicalPattern::operator [](quint16 index) const
{
    return m_barPattern.at(index);
}

MusicalPattern &MusicalPattern::operator+=(const MusicalPattern &barPattern)
{

}

MusicalPattern &MusicalPattern::operator+=(const MusicalBar& bar)
{

}

const std::vector<MusicalBar> &MusicalPattern::barPattern() const
{
    return m_barPattern;
}

void MusicalPattern::setBarPattern(const std::vector<MusicalBar> &newBarPattern)
{
    m_barPattern = newBarPattern;
}

std::vector<MusicalNote> MusicalPattern::notePattern()
{
    std::vector<MusicalNote> flatteredNotePattern;
    for(auto itBar : m_barPattern)
    {
        for(auto& itNote : itBar.notePattern())
        {
            flatteredNotePattern.push_back(itNote);
        }
    }
    return flatteredNotePattern;
}

quint16 MusicalPattern::barsCount()
{
    return m_barPattern.size();
}

