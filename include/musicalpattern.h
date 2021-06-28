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
    ~MusicalPattern();

    MusicalPattern& operator=(const MusicalPattern& barPattern);
    MusicalBar& operator[](quint16 index);
    const MusicalBar& operator[](quint16 index) const;

    //  может быть стоит сделать дружественными с
    // left value и right value
    MusicalPattern& operator+=(const MusicalPattern& barPattern);
    MusicalPattern& operator+=(const MusicalBar& bar);

    const std::vector<MusicalBar> &barPattern() const;
    void setBarPattern(const std::vector<MusicalBar> &newBarPattern);

    std::vector<MusicalNote> notePattern();
    quint16 barsCount();
private:
    std::vector<MusicalBar> m_barPattern;
};

#endif // MUSICALPATTERN_H
