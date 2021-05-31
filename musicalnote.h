#ifndef MUSICALNOTE_H
#define MUSICALNOTE_H

#include <QString>
#include <QObject>

class MusicalNote
{
    Q_GADGET
public:

    enum class NoteType{
        Whole,
        Half,
        Quarter,
        Eight,
        Sixteenth,
        Thirty_second
    };
    Q_ENUM(NoteType)

    MusicalNote(NoteType type = NoteType::Quarter);
    MusicalNote(NoteType type, QString line1, QString line2);

    Q_INVOKABLE NoteType type() const;
    Q_INVOKABLE const QString &line1() const;
    Q_INVOKABLE const QString &line2() const;

private:
    NoteType m_type;
    QString m_line1;
    QString m_line2;
};

//Q_DECLARE_METATYPE(MusicalNote::NoteType)

#endif // MUSICALNOTE_H
