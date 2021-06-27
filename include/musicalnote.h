#ifndef MUSICALNOTE_H
#define MUSICALNOTE_H

#include <QString>
#include <QObject>

#include "musicaltypes.h"

class MusicalNote
{
    Q_GADGET
//    Q_PROPERTY(QString name READ name) //WRITE setName NOTIFY nameChanged)
public:
    MusicalNote(MusicalTypes::NoteType type = MusicalTypes::NoteType::Quarter);
    MusicalNote(MusicalTypes::NoteType type, QString line1, QString line2);

    // Не используем ссылки в возвращаемом значении тк необходима работа в QML
    Q_INVOKABLE QString line1() const;
    Q_INVOKABLE QString line2() const;
    Q_INVOKABLE QString name();

    const MusicalTypes::NoteType &type() const;

    Q_INVOKABLE static MusicalTypes::NoteType noteTypeByName(QString name)
    {
        return MusicalTypes::noteNames.value(name);
    }
    Q_INVOKABLE static QString noteNameByType(MusicalTypes::NoteType type)
    {
        return MusicalTypes::noteNames.key(type);
    }
private:
    MusicalTypes::NoteType m_type;
    QString m_line1;
    QString m_line2;
};
Q_DECLARE_METATYPE(MusicalNote)

#endif // MUSICALNOTE_H
