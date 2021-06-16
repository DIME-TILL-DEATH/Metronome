#ifndef MUSICALPATTERNMODEL_H
#define MUSICALPATTERNMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QList>
#include <QHash>

#include "musicalnote.h"

class MusicalPatternModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MusicalPatternModel(QObject *parent = nullptr);
    MusicalPatternModel(std::vector<MusicalNote> pattern, QObject *parent = nullptr);

//    static void registerMe(const std::string &moduleName);

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex& index = {}, int role = Qt::DisplayRole) const override;

private:
    std::vector<MusicalNote> m_pattern;

    enum PatternRoles{
        TypeRole = Qt::UserRole + 1,
        Line1Role,
        Line2Role
    };
};

#endif // MUSICALPATTERNMODEL_H
