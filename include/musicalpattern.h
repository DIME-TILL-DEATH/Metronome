#ifndef MUSICALPATTERN_H
#define MUSICALPATTERN_H

#include <QDebug>

#include "musicalnote.h"
#include "musicalbar.h"

class MusicalPattern
{
public:
    MusicalPattern();
    MusicalPattern(const std::vector<MusicalBar> &barPattern);
    MusicalPattern(const MusicalPattern& barPattern);

    MusicalPattern& operator=(const MusicalPattern& barPattern);
    MusicalPattern& operator=(const std::vector<MusicalBar>& barPattern);
    MusicalBar& operator[](quint16 index);
    const MusicalBar& operator[](quint16 index) const;

    //  может быть стоит сделать дружественными с
    // left value и right value
    MusicalPattern& operator+=(const MusicalPattern& barPattern);
    MusicalPattern& operator+=(const MusicalBar& bar);

    bool addBar(quint16 position, const MusicalBar& bar = MusicalBar());
    bool addBars(quint16 position, quint16 count, const MusicalBar& bar = MusicalBar());
    bool addBars(quint16 position, std::vector<MusicalBar> newBarPattern);

    bool removeBar(quint16 position);
    bool removeBars(quint16 position, quint16 count);

    const std::vector<MusicalBar> &barPattern() const;

    std::vector<MusicalNote> notePattern();
    quint16 barsCount();
private:
    std::vector<MusicalBar> m_barPattern;
};

#endif // MUSICALPATTERN_H
