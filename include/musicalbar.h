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

    MusicalBar& operator=(const MusicalBar& bar);

    Q_INVOKABLE int notesCount();

    Q_INVOKABLE bool addNote(quint16 position, MusicalNote note = MusicalTypes::NoteType::Half);
    bool addNotes(quint16 position, quint16 count, MusicalNote note);
    bool addNotes(quint16 position, std::vector<MusicalNote> notePattern);

    bool setNote(quint16 position, MusicalNote note);
    bool setNotes(quint16 position, quint16 count, MusicalNote note);
    bool setNotes(quint16 position, std::vector<MusicalNote> notePattern);

    // заменить на оператор
    void replaceNotePattern(std::vector<MusicalNote> newNotePattern);

    bool removeNote(quint16 position);
    bool removeNotes(quint16 position, quint16 count);

    // Заменить на оператор
    const MusicalNote& noteAt(quint16 position) const;
    // а нужна ли версия с возвращаемой ссылкой?
    Q_INVOKABLE MusicalNote noteQMLAt(quint16 position);

//    const std::pair<quint8, quint8> &timeSignature() const;
//    void setTimeSignature(const std::pair<quint8, quint8> &newTimeSignature);

    const std::vector<MusicalNote> &notePattern() const;

private:
    std::vector<MusicalNote> m_notePattern;
//    std::pair<quint8, quint8> m_timeSignature {4, 4};

};
Q_DECLARE_METATYPE(MusicalBar)

#endif // MUSICALBAR_H
