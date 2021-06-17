#include <QQmlEngine>

#include "musicalpatternmodel.h"

MusicalPatternModel::MusicalPatternModel(QObject *parent)
    : QAbstractListModel(parent)
{
    static MusicalBarModel tempBar1(parent);
    static MusicalBarModel tempBar2(parent);
//            ({{MusicalTypes::NoteType::Quarter, "L", "F"},
//                                     {MusicalTypes::NoteType::Quarter, "L", " "},
//                                     {MusicalTypes::NoteType::Quarter, "L", " "},
//                                     {MusicalTypes::NoteType::Quarter, "R", " "}}, parent);
    static MusicalBarModel tempBar3(parent);

    m_barPattern = {
        &tempBar1,
        &tempBar2,
        &tempBar3
    };
}

MusicalPatternModel::MusicalPatternModel(std::vector<MusicalBarModel *> barPattern, QObject *parent)
                    : MusicalPatternModel(parent)
{
    m_barPattern = barPattern;
}

QHash<int, QByteArray> MusicalPatternModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PatternRoles::BarModelRole] = "barModel";
    roles[PatternRoles::BarNumberRole] = "barNumber";
    roles[PatternRoles::isActiveBarRole] = "isActiveBar";

    return roles;
}

int MusicalPatternModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_barPattern.size());
}

QVariant MusicalPatternModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index))
    {
        return {};
    }


    switch(role)
    {
        case PatternRoles::BarModelRole:
        {
            return QVariant::fromValue<QObject*>(m_barPattern.at(index.row()));
        }
        case PatternRoles::BarNumberRole:
        {
        // типо хака, может быть надо придумать хранение номер такта в последовательности по-другому
            return QVariant::fromValue(index.row()+1);
        }
        case PatternRoles::isActiveBarRole:
        {
            return QVariant::fromValue(m_activeBarIndex == index.row());
        }
        default:
        {
            return true;
        }
    }
}

MusicalNote MusicalPatternModel::proceedNextNote()
{
    // TODO: проверка размера такта, если нота была последняя, увеличить m_activeBar
    // и уже после запускать proceedNextNote

    std::pair<MusicalNote, int> activeNote = m_barPattern.at(m_activeBarIndex)->proceedNextNote();

    if(activeNote.second == 1)
    {
        if(m_activeBarIndex == m_barPattern.size()-1)
        {
            m_activeBarIndex=0;
        }
        else
        {
            m_activeBarIndex++;
        }
    }

    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.size()-1, 0), {PatternRoles::isActiveBarRole});


    return activeNote.first;
}
