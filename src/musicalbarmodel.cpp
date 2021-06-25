#include "musicalbarmodel.h"

MusicalBarModel::MusicalBarModel(QObject *parent)
            : QAbstractListModel {parent}
{
    // default fill for debug(mock)
    m_bar = new MusicalBar( {
        {MusicalTypes::NoteType::Quarter, "R", " "},
        {MusicalTypes::NoteType::Quarter, "R", " "},
        {MusicalTypes::NoteType::Quarter, "R", " "},
        {MusicalTypes::NoteType::Quarter, "R", " "}
    });
}

MusicalBarModel::MusicalBarModel(std::vector<MusicalNote> pattern, QObject *parent)
    : QAbstractListModel {parent}
{
    m_bar = new MusicalBar(pattern);
}

MusicalBarModel::~MusicalBarModel()
{
    delete m_bar;
}

QHash<int, QByteArray> MusicalBarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[PatternRoles::TypeRole]       = "type";
    roles[PatternRoles::Line1Role]      = "line1";
    roles[PatternRoles::Line2Role]      = "line2";

    return roles;
}

int MusicalBarModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return static_cast<int>(m_bar->notePatternSize());
}

QVariant MusicalBarModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount(index))
    {
        return {};
    }

    const MusicalNote& note {m_bar->noteAt(index.row())};

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

bool MusicalBarModel::insertRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)
    if(row < 0)
    {
        qWarning() << "Trying to insert row in bar in negative position!";
        return false;
    }
    beginInsertRows(parent, row, row+count-1);

//    m_notePattern.insert(m_notePattern.begin()+row, count, {MusicalTypes::NoteType::Sixteenth, " ", " "});
    // может надо добавлять null? Да и вообще, нужна ли реализация этой функции?
    m_bar->addNotes(row, count, {MusicalTypes::NoteType::Sixteenth, "", ""});

    endInsertRows();
    return true;
}

bool MusicalBarModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    quint16 noteIndex = static_cast<quint16>(row);
    quint16 noteCount = static_cast<quint16>(count);

    if(noteIndex+noteCount > m_bar->notePatternSize()-1)
    {
        qWarning() << "Trying to remove note. Index " << row <<" out of bounds!";
        return false;
    }

    beginRemoveRows(QModelIndex(), noteIndex, noteIndex + noteCount - 1);

//    m_notePattern.erase(m_notePattern.begin()+noteIndex, m_notePattern.begin()+noteIndex+noteCount);
    m_bar->removeNotes(noteIndex, noteCount);
    endRemoveRows();

    return true;
}

bool MusicalBarModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)
    if(!index.isValid() || index.row() > rowCount(index))
    {
        qWarning() << "Try to set data, index is invalid";
        return false;
    }

//    m_notePattern.at(index.row()) = value.value<MusicalNote>();
    m_bar->setNote(index.row(), value.value<MusicalNote>());

    emit dataChanged(createIndex(0, 0), createIndex(m_bar->notePatternSize()-1, 0));
    return true;
}

const std::vector<MusicalNote> &MusicalBarModel::notePattern() const
{
    return m_bar->notePattern();
}

//void MusicalBarModel::updateLayout()
//{
//    emit dataChanged(createIndex(0, 0), createIndex(m_bar->notePatternSize()-1, 0));
//}

MusicalBar *MusicalBarModel::bar() const
{
    return m_bar;
}

void MusicalBarModel::setBar(MusicalBar *newBar)
{
    m_bar = newBar;
}
//void MusicalBarModel::changeContent(const MusicalBarModel &newBar)
//{
//    // пока так. Удаляем все ноты из старого и записываем новый.
//    // возможно в будущем надо сделать как-то поэффективнее
//    m_timeSignature = newBar.timeSignature();
//    removeRows(0, m_notePattern.size());
//    insertRows(0, newBar.m_notePattern.size());
//    m_notePattern = newBar.notePattern();
//    emit layoutChanged();
//    emit dataChanged(createIndex(0, 0), createIndex(m_notePattern.size()-1, 0));
//}

//const std::pair<quint8, MusicalTypes::NoteType> &MusicalBarModel::timeSignature() const
//{
//    return m_timeSignature;
//}
