#ifndef MUSICALPATTERNMODEL_H
#define MUSICALPATTERNMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QHash>

#include "musicalnote.h"
#include "musicalbarmodel.h"

class MusicalPatternModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MusicalPatternModel(QObject *parent = nullptr);
    MusicalPatternModel(std::vector<MusicalBarModel*> barPattern, QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index = {}, int role = Qt::DisplayRole) const override;

//    MusicalNote popNote();
    std::vector<MusicalNote> notePattern();
private:
    std::vector<MusicalBarModel*> m_barPattern;
    quint16 m_selectedBarIndex{0};

    enum PatternRoles{
        BarModelRole= Qt::UserRole + 1,
        BarNumberRole,
        isActiveBarRole
    };
};

#endif // MUSICALPATTERNMODEL_H
