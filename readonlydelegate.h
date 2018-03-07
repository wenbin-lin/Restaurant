#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QItemDelegate>

class ReadOnlyDelegate : public QItemDelegate//只读代理
{
public:
    ReadOnlyDelegate(QObject* parent = 0) : QItemDelegate(parent) {}
    QWidget *createEditor(QWidget*parent,  const QStyleOptionViewItem &option,//重写createEditor函数实现只读
                          const  QModelIndex &index)  const
    {
         return  NULL;
    }
};

#endif // READONLYDELEGATE_H
