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

MusicalPattern &MusicalPattern::operator=(const MusicalPattern &barPattern)
{
    m_barPattern = barPattern.m_barPattern;
    return *this;
}

MusicalPattern &MusicalPattern::operator=(const std::vector<MusicalBar>& barPattern)
{
    m_barPattern = barPattern;
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
    m_barPattern.insert(m_barPattern.end(), barPattern.m_barPattern.begin(), barPattern.m_barPattern.end());
    return *this;
}

MusicalPattern &MusicalPattern::operator+=(const MusicalBar& bar)
{
    m_barPattern.push_back(bar);
    return *this;
}

bool MusicalPattern::addBar(quint16 position, const MusicalBar &bar)
{
    if(position > m_barPattern.size()-1)
    {
        qWarning() << "MusicalPattern.addBar(), position " << position << "is out of range!";
        return false;
    }
    m_barPattern.insert(m_barPattern.begin()+position, bar);
    return true;
}

bool MusicalPattern::addBars(quint16 position, quint16 count, const MusicalBar &bar)
{
    if(position > m_barPattern.size()-1)
    {
        qWarning() << "MusicalBar.addBars(), position " << position << "is out of range!";
        return false;
    }
    m_barPattern.insert(m_barPattern.begin()+position, count, bar);
    return true;
}

bool MusicalPattern::addBars(quint16 position, std::vector<MusicalBar> newBarPattern)
{
    if(position > m_barPattern.size()-1)
    {
        qWarning() << "MusicalBar.addNotes(), position " << position <<"is out of range!";
        return false;
    }
    m_barPattern.insert(m_barPattern.begin()+position, newBarPattern.begin(), newBarPattern.end());
    return true;
}

bool MusicalPattern::removeBar(quint16 position)
{
    if(position > m_barPattern.size()-1)
    {
        qWarning() << "MusicalPattern.removeBar(), position " << position << "is out of range!";
        return false;
    }
    m_barPattern.erase(m_barPattern.begin()+position);
    return true;
}

bool MusicalPattern::removeBars(quint16 position, quint16 count)
{
    if(position+count-1 > static_cast<quint16>(m_barPattern.size()-1))
    {
        qWarning() << "MusicalPattern.removeBars(), start position " << position << ", end position " << position+count <<"is out of range!";
        return false;
    }
    m_barPattern.erase(m_barPattern.begin()+position, m_barPattern.begin()+position+count);
    return true;
}

const std::vector<MusicalBar> &MusicalPattern::barPattern() const
{
    return m_barPattern;
}

std::vector<MusicalNote> MusicalPattern::notePattern()
{
    std::vector<MusicalNote> flatteredNotePattern;
    for(auto& itBar : m_barPattern)
    {
        for(auto& itNote : itBar.notePattern())
        {
            flatteredNotePattern.push_back(itNote);
        }
    }
    return flatteredNotePattern;
}

std::vector<MusicalBar> MusicalPattern::barPattern()
{
    return m_barPattern;
}

quint16 MusicalPattern::barsCount()
{
    return m_barPattern.size();
}

