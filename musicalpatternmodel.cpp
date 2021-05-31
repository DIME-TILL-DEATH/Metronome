#include <QQmlEngine>

#include "musicalpatternmodel.h"

MusicalPatternModel::MusicalPatternModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_pattern = {
        {MusicalNote::NoteType::Eight, "L", "F"},
        {MusicalNote::NoteType::Quarter, "R", " "},
        {MusicalNote::NoteType::Eight, "L", " "},
        {MusicalNote::NoteType::Quarter, "R", " "}
    };
}

void MusicalPatternModel::registerMe(const std::string &moduleName)
{
    qmlRegisterType<MusicalPatternModel>(moduleName.c_str(), 1, 0, "MusicalPatternModel");
}

QHash<int, QByteArray> MusicalPatternModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PatternRoles::TypeRole] = "type";
    roles[PatternRoles::Line1Role] = "line1";
    roles[PatternRoles::Line2Role] = "line2";

    return roles;
}

int MusicalPatternModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_pattern.size());
}

QVariant MusicalPatternModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index))
    {
        return {};
    }

    const MusicalNote& note {m_pattern.at(index.row())};

    switch(role)
    {
        case PatternRoles::TypeRole: {
            return QVariant::fromValue(note.type());
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
