#ifndef MUSICABARMODEL_H
#define MUSICABARMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QHash>

#include "musicalnote.h"

class MusicalBarModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MusicalBarModel(QObject *parent = nullptr);
    MusicalBarModel(std::vector<MusicalNote> pattern, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index = {}, int role = Qt::DisplayRole) const override;

    //TODO: подумать какие роли, кроме последней могут быть у второго значения(normal, last, invalid?), заменить int на структуру
    std::pair<MusicalNote, int> proceedNextNote();
private:
    std::vector<MusicalNote> m_notePattern;
    std::pair<quint8, MusicalTypes::NoteType> m_timeSignature {4, MusicalTypes::NoteType::Quarter};

    quint16 m_activeNoteIndex{0};

    enum PatternRoles{
        TypeRole = Qt::UserRole + 1,
        isActiveNoteRole,
        Line1Role,
        Line2Role
    };
};

#endif // MUSICABARMODEL_H