#include "musicalbar.h"

MusicalBar::MusicalBar()
{
    // default fill
    m_notePattern = {
        {MusicalTypes::NoteType::Quarter, "", ""},
        {MusicalTypes::NoteType::Quarter, "", ""},
        {MusicalTypes::NoteType::Quarter, "", ""},
        {MusicalTypes::NoteType::Quarter, "", ""}
    };
}

MusicalBar::MusicalBar(std::vector<MusicalNote> pattern)
{
    m_notePattern = pattern;
}

MusicalBar::MusicalBar(const MusicalBar &bar)
{
    m_notePattern = bar.m_notePattern;
    m_timeSignature = bar.m_timeSignature;
}

MusicalBar::~MusicalBar()
{

}

int MusicalBar::notePatternSize()
{
    return m_notePattern.size();
}

bool MusicalBar::addNote(quint16 position, MusicalNote note)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->addNote(), position " << position << "is out of range!";
        return false;
    }
    m_notePattern.insert(m_notePattern.begin()+position, note);
    return true;
}

bool MusicalBar::addNotes(quint16 position, quint16 count, MusicalNote note)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->addNotes()position " << position << "is out of range!";
        return false;
    }
    m_notePattern.insert(m_notePattern.begin()+position, count,note);
    return true;
}

bool MusicalBar::addNotes(quint16 position, std::vector<MusicalNote> newNotePattern)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->addNotes(), position " << position <<"is out of range!";
        return false;
    }
    m_notePattern.insert(m_notePattern.begin()+position, newNotePattern.begin(), newNotePattern.end());
    return true;
}

bool MusicalBar::setNote(quint16 position, MusicalNote note)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->setNote(), position " << position << "is out of range!";
        return false;
    }
    m_notePattern.at(position) = note;
    return true;
}

bool MusicalBar::setNotes(quint16 position, quint16 count, MusicalNote note)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->setNote(), position " << position << "is out of range!";
        return false;
    }

    if(position+count > m_notePattern.size())
    {
        m_notePattern.resize(position+count);
    }
    for(int i=position; i!=position+count; i++)
    {
        m_notePattern.at(i)=note;
    }
    return true;
}

bool MusicalBar::setNotes(quint16 position, std::vector<MusicalNote> newNotePattern)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->setNote(), position " << position << "is out of range!";
        return false;
    }
    if(position+newNotePattern.size() > m_notePattern.size())
    {
        m_notePattern.resize(position+newNotePattern.size());
    }
    for(unsigned int i=0; i!=newNotePattern.size()-1; i++)
    {
        m_notePattern.at(i+position)=newNotePattern.at(i);
    }
    return true;
}

void MusicalBar::replaceNotePattern(std::vector<MusicalNote> newNotePattern)
{
    m_notePattern = newNotePattern;
}

bool MusicalBar::removeNote(quint16 position)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->removeNote(), position " << position << "is out of range!";
        return false;
    }
    m_notePattern.erase(m_notePattern.begin()+position);
    return true;
}

bool MusicalBar::removeNotes(quint16 position, quint16 count)
{
    if(position+count > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->removeNotes(), start position " << position << ", end position " << position+count <<"is out of range!";
        return false;
    }
    m_notePattern.erase(m_notePattern.begin()+position, m_notePattern.begin()+position+count);
    return true;
}

const MusicalNote &MusicalBar::noteAt(quint16 position) const
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->noteAt(), position " << position << "is out of range!";
        // переделать на std::pair с результатом?
        return m_notePattern.at(0);
    }
    return m_notePattern.at(position);
}

MusicalNote MusicalBar::noteQMLAt(quint16 position)
{
    if(position > m_notePattern.size()-1)
    {
        qWarning() << "MusicalBar->noteAt(), position " << position << "is out of range!";
        return m_notePattern.at(0);
    }
    return m_notePattern.at(position);
}

const std::pair<quint8, MusicalTypes::NoteType> &MusicalBar::timeSignature() const
{
    return m_timeSignature;
}

void MusicalBar::setTimeSignature(const std::pair<quint8, MusicalTypes::NoteType> &newTimeSignature)
{
    m_timeSignature = newTimeSignature;
}

const std::vector<MusicalNote> &MusicalBar::notePattern() const
{
    return m_notePattern;
}

