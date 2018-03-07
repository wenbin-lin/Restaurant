#ifndef SEATIDDELEGATE_H
#define SEATIDDELEGATE_H

#include <QItemDelegate>

class SeatIdDelegate : public QItemDelegate//将座位显示为两位数字，个位数补零的代理
{
public:
    SeatIdDelegate(QObject* parent = 0) : QItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
    {
        int seatId = index.model()->data(index, Qt::DisplayRole).toInt();
        //设置桌号格式为两位，不足补零
        QString text = QString("%1").arg(seatId, 2, 10, QChar('0'));
        //获取项风格设置
        QStyleOptionViewItem myOption = option;
        myOption.displayAlignment = Qt::AlignHCenter | Qt::AlignVCenter;
        //绘制文本
        QApplication::style()->drawItemText ( painter, myOption.rect , myOption.displayAlignment, QApplication::palette(), true,text );
    }
    QWidget *createEditor(QWidget*parent,  const QStyleOptionViewItem &option,
                          const  QModelIndex &index)  const//不可编辑
    {
         return  NULL;
    }
};

#endif // SEATIDDELEGATE_H
