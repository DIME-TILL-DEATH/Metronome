#ifndef MUSICALNOTE_H
#define MUSICALNOTE_H

#include <QString>
#include <QObject>

#include "musicaltypes.h"

class MusicalNote
{
    Q_GADGET
public:
    MusicalNote(MusicalTypes::NoteType type = MusicalTypes::NoteType::Quarter);
    MusicalNote(MusicalTypes::NoteType type, QString line1, QString line2);

    const QString &line1() const;
    const QString &line2() const;

    const MusicalTypes::NoteType &type() const;
private:
    MusicalTypes::NoteType m_type;
    QString m_line1;
    QString m_line2;
};

#endif // MUSICALNOTE_H
