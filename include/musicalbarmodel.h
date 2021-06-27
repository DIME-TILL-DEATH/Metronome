#ifndef MUSICABARMODEL_H
#define MUSICABARMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QHash>
#include <QDebug>

#include "musicalnote.h"
#include "musicalbar.h"

class MusicalBarModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MusicalBarModel(QObject *parent = nullptr);
    MusicalBarModel(std::vector<MusicalNote> pattern, QObject *parent = nullptr);
    ~MusicalBarModel();

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index = {}, int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = MusicalNoteRole) override;

    // по идее вытаскиваем notePattern напрямую из MusicBar
    // поэтому отказаться от этого метода и полностью развязать
    // хранение и модель
    const std::vector<MusicalNote> &notePattern() const;

    MusicalBar *bar() const;
    void setBar(MusicalBar *newBar);

private:
//    std::vector<MusicalNote> m_notePattern;
//    std::pair<quint8, MusicalTypes::NoteType> m_timeSignature {4, MusicalTypes::NoteType::Quarter};
    MusicalBar* m_bar;

    quint16 m_selectedNoteIndex{0};

    enum PatternRoles{
        MusicalNoteRole = Qt::UserRole + 1
    };
};

#endif // MUSICABARMODEL_H
