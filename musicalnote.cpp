#include "musicalnote.h"

MusicalNote::MusicalNote(NoteType type)
    : m_type(type)
{
}

MusicalNote::MusicalNote(NoteType type, QString line1, QString line2)
    : m_type(type),
      m_line1(line1),
      m_line2(line2)
{

}

MusicalNote::NoteType MusicalNote::type() const
{
    return m_type;
}

const QString &MusicalNote::line1() const
{
    return m_line1;
}

const QString &MusicalNote::line2() const
{
    return m_line2;
}
