#include <QQmlEngine>

#include "musicalpatternmodel.h"

MusicalPatternModel::MusicalPatternModel(QObject *parent)
    : QAbstractListModel(parent)
{
    static MusicalBarModel tempBar1(parent);
    static MusicalBarModel tempBar2({
                                        {MusicalTypes::NoteType::Quarter, "R", " "},
                                        {MusicalTypes::NoteType::Eight, "R", " "},
                                        {MusicalTypes::NoteType::Eight, "L", "F"},
                                        {MusicalTypes::NoteType::Quarter, "R", " "},
                                        {MusicalTypes::NoteType::Eight, "L", " "},
                                        {MusicalTypes::NoteType::Eight, "L", "F"}
                                    }, parent);
    static MusicalBarModel tempBar3({
                                        {MusicalTypes::NoteType::Whole, "", " "},
                                        {MusicalTypes::NoteType::Half, "", " "},
                                        {MusicalTypes::NoteType::Sixteenth, "", ""},
                                        {MusicalTypes::NoteType::Thirty_second, "", " "},
                                    }, parent);

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
    roles[PatternRoles::BarRole] = "bar";
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
        case PatternRoles::BarRole:
        {
            return QVariant::fromValue(*m_barPattern.at(index.row())->bar());
        }
        default:
        {
            return true;
        }
    }
}

bool MusicalPatternModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    if(!index.isValid() || index.row() > rowCount(index))
    {
        qWarning() << "Try to set data, index is invalid";
        return false;
    }

    // вообще не доделано

//    MusicalBarModel* newBar = value.value<MusicalBarModel*>();
    // если паттерн меньше нового - добавить, если больше-удалить лишнее, потом переписать те что остались
    // не забыть присвоить такту размер!
//    m_barPattern.at(index.row())->removeRows(0, m_barPattern.at(index.row())->notePattern().size());
//    m_barPattern.at(index.row())->insertRows(0, newBar->notePattern().size());
//    for(quint16 i=0; i < newBar->notePattern().size(); i++)
//    {
//        m_barPattern.at(index.row())->setData(createIndex(i, 0), QVariant::fromValue<MusicalNote>(newBar->notePattern().at(i)));
//    }
//    delete newBar;
//    m_barPattern.at(index.row())->changeContent(*value.value<MusicalBarModel*>());

    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.size()-1, 0));
    return true;
}

std::vector<MusicalNote> MusicalPatternModel::notePattern()
{
    std::vector<MusicalNote> flatteredNotePattern;
    for(const auto itBar : m_barPattern)
    {
        for(const auto& itNote : itBar->notePattern())
        {
            flatteredNotePattern.push_back(itNote);
        }
    }
    return flatteredNotePattern;
}


bool MusicalPatternModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    if(row < 0)
    {
        qWarning() << "Trying to insert row in pattern in negative position!";
        return false;
    }
    beginInsertRows(parent, row, row+count-1);

    // Не появляется ли тут утечка памяти из-за new MusicalBarModel()?
    // удаляется ли этот объект в деструкторе?
    m_barPattern.insert(m_barPattern.begin()+row, count, new MusicalBarModel());
    endInsertRows();
    return true;
}

bool MusicalPatternModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    quint16 barIndex = static_cast<quint16>(row);

    if(barIndex > m_barPattern.size()-1 )
    {
        qWarning() << "Trying to remove Bar. Index " << row <<" out of bounds!";
        return false;
    }
    beginRemoveRows(QModelIndex(), barIndex, barIndex + count - 1);

    m_barPattern.erase(m_barPattern.begin()+barIndex, m_barPattern.begin()+barIndex+count);

    endRemoveRows();

    return true;
}

bool MusicalPatternModel::addBar(MusicalBar* newBar, quint16 barIndex)
{
    insertRows(barIndex, 1);
    m_barPattern.at(barIndex)->setBar(newBar);

    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.size()-1, 0));
    return true;
}

bool MusicalPatternModel::removeBar(quint16 barIndex)
{
    bool resultVal = removeRows(barIndex, 1);
    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.size()-1, 0));
    return resultVal;
}
