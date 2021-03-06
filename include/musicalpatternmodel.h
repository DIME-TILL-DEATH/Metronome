#ifndef MUSICALPATTERNMODEL_H
#define MUSICALPATTERNMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QHash>

#include "musicalnote.h"
#include "musicalbar.h"
#include "musicalpattern.h"

class MusicalPatternModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MusicalPatternModel(MusicalPattern &barPattern) : m_barPattern{barPattern}{};

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index = {}, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = BarRole) override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    bool addBar(const MusicalBar &newBar, quint16 barIndex);
    bool removeBar(quint16 barIndex);
    void updateModel();
private:
    MusicalPattern& m_barPattern;
    quint16 m_selectedBarIndex{0};

    enum PatternRoles{
        BarNumberRole= Qt::UserRole + 1,
        BarRole
    };
};

#endif // MUSICALPATTERNMODEL_H
