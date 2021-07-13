#include "patterneditor.h"



MusicalNote PatternEditor::noteByName(QString name)
{
    return MusicalNote(MusicalTypes::noteNames.value(name));
}

QStringList PatternEditor::getAllNoteNames()
{
    return MusicalTypes::noteOrder;
}
