#ifndef MUSICALTYPES_H
#define MUSICALTYPES_H

#include <QHash>
#include <QObject>

namespace MusicalTypes
{

    static constexpr quint16 OneMinute{60000};

    enum class NoteType : quint8
    {
        Whole = 1,
        Half = 2,
        Quarter = 4,
        Eight = 8,
        Sixteenth = 16,
        Thirty_second = 32,

        Eight_triplet = 12,
        Sixteenth_triplet = 24,
        Thirty_second_triplet = 24
    };

    static QStringList noteOrder
    {
        "Whole",
        "Half",
        "Quarter",
        "Eight",
        "Sixteenth",
        "ThirtySecond",

        "EightTriplet",
        "SixteenthTriplet",
        "ThirtySecondTriplet"
    };

    static QHash<QString, MusicalTypes::NoteType> noteNames
    {
        {"Whole",           MusicalTypes::NoteType::Whole},
        {"Half",            MusicalTypes::NoteType::Half},
        {"Quarter",         MusicalTypes::NoteType::Quarter},
        {"Eight",           MusicalTypes::NoteType::Eight},
        {"Sixteenth",       MusicalTypes::NoteType::Sixteenth},
        {"ThirtySecond",    MusicalTypes::NoteType::Thirty_second},

        {"EightTriplet",        MusicalTypes::NoteType::Eight_triplet},
        {"SixteenthTriplet",    MusicalTypes::NoteType::Sixteenth_triplet},
        {"ThirtySecondTriplet", MusicalTypes::NoteType::Thirty_second_triplet}
    };

    // Быть может всё же создать объект MetronomeEvent????
    enum MetronomeEvents : quint32
    {
        MetronomeClick,
        MetronomeAccentedClick,
        MetronomeSubClick,      // sub division click
        PatternClick
    };

    static QHash<QString, MetronomeEvents> metronomeEventsNames
    {
        {"Click",         MetronomeEvents::MetronomeClick},
        {"AccentedClick", MetronomeEvents::MetronomeAccentedClick},
        {"PatternClick",  MetronomeEvents::PatternClick}
    };
}

Q_DECLARE_METATYPE(MusicalTypes::MetronomeEvents)

#endif // MUSICALTYPES_H
