#ifndef MUSICALNOTE_H
#define MUSICALNOTE_H

#include <QString>
#include <QObject>

#include "musicaltypes.h"

class MusicalNote
{
    Q_GADGET
    Q_PROPERTY(QString name READ name) //WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString line1 READ line1) //WRITE setLine1 NOTIFY line1Changed)
    Q_PROPERTY(QString line2 READ line2) //WRITE setLine2 NOTIFY line2Changed)
public:
    MusicalNote(MusicalTypes::NoteType type = MusicalTypes::NoteType::Quarter);
    MusicalNote(MusicalTypes::NoteType type, QString line1, QString line2);

    // Не используем ссылки в возвращаемом значении тк необходима работа в QML
    const QString& line1() const;
    const QString& line2() const;
    QString name() const;

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
