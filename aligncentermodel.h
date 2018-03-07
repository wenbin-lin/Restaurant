#ifndef ALIGNCENTERMODEL_H
#define ALIGNCENTERMODEL_H

#include <QSqlTableModel>

class AlignCenterModel : public QSqlTableModel//实现居中效果的QSqlTableModel
{
public:
    AlignCenterModel(QObject* parent = 0) : QSqlTableModel(parent) {}
    QVariant  data(const QModelIndex & item, int role) const//重写data函数以实现居中
    {
        QVariant value = QSqlTableModel::data(item, role);
        if (role == Qt::TextAlignmentRole)
        {
            value = (Qt::AlignCenter);
            return value;
        }
        return value;
    }
};

#endif // ALIGNCENTERMODEL_H
