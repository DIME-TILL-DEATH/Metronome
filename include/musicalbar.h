#ifndef MUSICALBAR_H
#define MUSICALBAR_H

#include <QObject>
#include <QDebug>

#include "musicalnote.h"

class MusicalBar
{
    Q_GADGET
public:
    MusicalBar();
    MusicalBar(std::vector<MusicalNote> pattern);
    MusicalBar(const MusicalBar& bar);
    ~MusicalBar();

    Q_INVOKABLE int notePatternSize();

    bool addNote(quint16 position, MusicalNote note);
    bool addNotes(quint16 position, quint16 count, MusicalNote note);
    bool addNotes(quint16 position, std::vector<MusicalNote> notePattern);

    bool setNote(quint16 position, MusicalNote note);
    bool setNotes(quint16 position, quint16 count, MusicalNote note);
    bool setNotes(quint16 position, std::vector<MusicalNote> notePattern);

    void replaceNotePattern(std::vector<MusicalNote> newNotePattern);

    bool removeNote(quint16 position);
    bool removeNotes(quint16 position, quint16 count);

    Q_INVOKABLE const MusicalNote& noteAt(quint16 position) const;

    const std::pair<quint8, MusicalTypes::NoteType> &timeSignature() const;
    void setTimeSignature(const std::pair<quint8, MusicalTypes::NoteType> &newTimeSignature);

    const std::vector<MusicalNote> &notePattern() const;

private:
    std::vector<MusicalNote> m_notePattern;
    std::pair<quint8, MusicalTypes::NoteType> m_timeSignature {4, MusicalTypes::NoteType::Quarter};

};
Q_DECLARE_METATYPE(MusicalBar)

#endif // MUSICALBAR_H
