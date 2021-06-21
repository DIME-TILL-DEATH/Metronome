#include "musicalbarmodel.h"

MusicalBarModel::MusicalBarModel(QObject *parent)
            : QAbstractListModel {parent}
{
    // default fill for debug(mock)
    m_notePattern = {
        {MusicalTypes::NoteType::Quarter, "R", " "},
        {MusicalTypes::NoteType::Quarter, "R", " "},
        {MusicalTypes::NoteType::Quarter, "R", " "},
        {MusicalTypes::NoteType::Quarter, "R", " "}
    };
}

MusicalBarModel::MusicalBarModel(std::vector<MusicalNote> pattern, QObject *parent)
    : QAbstractListModel {parent},
      m_notePattern {pattern}
{

}

QHash<int, QByteArray> MusicalBarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PatternRoles::TypeRole]       = "type";
    roles[PatternRoles::isActiveNoteRole]  = "isActiveNote";
    roles[PatternRoles::Line1Role]      = "line1";
    roles[PatternRoles::Line2Role]      = "line2";

    return roles;
}

int MusicalBarModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_notePattern.size());
}

QVariant MusicalBarModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index))
    {
        return {};
    }

    const MusicalNote& note {m_notePattern.at(index.row())};

    switch(role)
    {
        case PatternRoles::TypeRole: {
            return QVariant::fromValue(note.type());
        }
        case PatternRoles::isActiveNoteRole:
        {
//            return QVariant::fromValue(note.isPlaying);
            return QVariant::fromValue(index.row() == m_activeNoteIndex);
        }
        case PatternRoles::Line1Role: {
            return QVariant::fromValue(note.line1());
        }
        case PatternRoles::Line2Role: {
            return QVariant::fromValue(note.line2());
        }
        default:
        {
            return true;
        }
    }
}

std::pair<MusicalNote, int> MusicalBarModel::popNote()
{
    MusicalNote tempNote = m_notePattern.at(m_activeNoteIndex);
    int noteRole=0;

    if(m_activeNoteIndex == m_notePattern.size()-1)
    {
        m_activeNoteIndex = 0;
        noteRole=1;
    }
    else
    {
        m_activeNoteIndex++;
        noteRole=0;
    }
    emit dataChanged(createIndex(0, 0), createIndex(m_notePattern.size()-1, 0), {PatternRoles::isActiveNoteRole});

    return std::make_pair(tempNote, noteRole);
}
