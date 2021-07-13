#ifndef PATTERNEDITOR_H
#define PATTERNEDITOR_H

/*******************************************
 *
 * Wrapper for QML(factory)
 *
 *******************************************/

#include <QObject>

#include "musicaltypes.h"
#include "musicalnote.h"
#include "musicalbar.h"

class PatternEditor : public QObject
{
    Q_OBJECT
public slots:
    MusicalNote createNote() { return MusicalNote();}
    MusicalBar createBar() {return MusicalBar();}

    MusicalNote noteByName(QString name);
    QStringList getAllNoteNames();
};

#endif // PATTERNEDITOR_H
