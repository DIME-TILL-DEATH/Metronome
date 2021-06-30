#include <QQmlEngine>

#include "musicalpatternmodel.h"


QHash<int, QByteArray> MusicalPatternModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PatternRoles::BarNumberRole] = "barNumber";
    roles[PatternRoles::BarRole] = "bar";
    return roles;
}

int MusicalPatternModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_barPattern.barsCount());
}

QVariant MusicalPatternModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index))
    {
        return {};
    }

    switch(role)
    {
        case PatternRoles::BarNumberRole:
        {
        // типо хака, может быть надо придумать хранение номер такта в последовательности по-другому
            return QVariant::fromValue(index.row()+1);
        }
        case PatternRoles::BarRole:
        {
            return QVariant::fromValue(m_barPattern[index.row()]);
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

    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.barsCount(), 0));
    return true;
}

bool MusicalPatternModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(row < 0)
    {
        qWarning() << "Trying to insert row in pattern in negative position!";
        return false;
    }
    beginInsertRows(parent, row, row+count-1);

    m_barPattern.addBars(row, count);

    endInsertRows();
    return true;
}

bool MusicalPatternModel::removeRows(int row, int count, const QModelIndex &parent)
{
    quint16 barIndex = static_cast<quint16>(row);

    if(barIndex+count-1 > m_barPattern.barsCount())
    {
        qWarning() << "Trying to remove Bar(removeRows()). Row:" << row <<" + count: "<< count << " out of bounds!";
        return false;
    }
    beginRemoveRows(parent, barIndex, barIndex + count - 1);

    m_barPattern.removeBars(barIndex, count);

    endRemoveRows();

    return true;
}

bool MusicalPatternModel::addBar(const MusicalBar& newBar, quint16 barIndex)
{
    insertRows(barIndex, 1);
    m_barPattern[barIndex] = newBar;
    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.barsCount(), 0));
    return true;
}

bool MusicalPatternModel::removeBar(quint16 barIndex)
{
    bool resultVal = removeRows(barIndex, 1);
    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.barsCount(), 0));
    return resultVal;
}

void MusicalPatternModel::updateModel()
{
    emit dataChanged(createIndex(0, 0), createIndex(m_barPattern.barsCount(), 0));
}
