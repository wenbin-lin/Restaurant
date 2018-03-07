#ifndef SAETTAKENDELEGATE_H
#define SAETTAKENDELEGATE_H

#include <QItemDelegate>

class SeatTakenDelegate : public QItemDelegate//将作为的布尔信息显示为“有客”“空”的代理
{
public:
    SeatTakenDelegate(QObject* parent = 0) : QItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        bool isTaken = index.model()->data(index, Qt::DisplayRole).toBool();
        QString text;
        if(isTaken){
            text = tr("有客");
        }
        else text = tr("空");
        //获取项风格设置
        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
        //绘制文本
        QApplication::style()->drawItemText ( painter, myOption.rect , myOption.displayAlignment, QApplication::palette(), true,text );
    }
};

#endif // SAETTAKENDELEGATE_H
