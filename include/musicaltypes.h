#ifndef MUSICALTYPES_H
#define MUSICALTYPES_H

#include <QObject>

class MusicalTypes
{
    Q_GADGET
public:
    static constexpr quint16 OneMinute{60000};

    enum class NoteType : quint8 {
        Whole = 1,
        Half = 2,
        Quarter = 4,
        Eight = 8,
        Sixteenth = 16,
        Thirty_second = 32
    };
    Q_ENUM(NoteType)

    struct TimeIntervals{
        quint16 Whole,
        Half,
        Quarter,
        Eight,
        Eight_triplet,
        Sixteenth,
        Sixteenth_triplet,
        Thirty_second,
        Thirty_second_triplet;
    };
};

#endif // MUSICALTYPES_H
