#ifndef PIXMAPDELEGATE_H
#define PIXMAPDELEGATE_H

#include <QApplication>
#include <QItemDelegate>
#include <QPixmap>

class PixmapDelegate : public QItemDelegate//将表格中的ByteArray显示为图片的代理
{
public:
    PixmapDelegate(QObject* parent = 0) : QItemDelegate(parent) {}
    void  paint(QPainter *painter,  const  QStyleOptionViewItem &option,
                const  QModelIndex & index )  const
    {
        for(int i = 0; i<index.model()->rowCount();++i){
            if(index.row()==i){
                QPixmap photo;
                photo.loadFromData(index.model()->data(index, Qt::EditRole).toByteArray(),"JPG");
                photo = photo.scaled(120,120);
                QApplication::style()->drawItemPixmap(painter, option.rect,  Qt::AlignCenter, photo);
            }
        }
    }
    QWidget *createEditor(QWidget*parent,  const QStyleOptionViewItem &option,
                          const  QModelIndex &index)  const//不可编辑
    {
         return  NULL;
    }
};

#endif // PIXMAPDELEGATE_H
