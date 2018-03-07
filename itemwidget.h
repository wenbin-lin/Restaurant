#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include "menuquery.h"

#include <QtWidgets>

class ItemWidget : public QWidget//通过菜品Id生成显示菜品名称，图片，价格
{
    Q_OBJECT

protected:
    QLabel* imageLbl;
    QLabel* nameLbl;
    QLabel* priceLbl;
    QFont font;
    int menuId;

public:
    ItemWidget(int menuId, QWidget *parent = 0) : QWidget(parent){
        this->resize(300,150);
        this->menuId = menuId;
        //根据菜品编号读取信息
        MenuQuery mQuery;
        QPixmap photo = mQuery.getImage(menuId,150,150);
        QString name = mQuery.getName(menuId);
        double price = mQuery.getPrice(menuId);
        QString unit = mQuery.getUnit(menuId);
        //字体
        font.setPixelSize(30);
        font.setFamily(tr("华文行楷"));
        //设置部件
        imageLbl = new QLabel(this);
        imageLbl->setGeometry(0,0,150,150);
        imageLbl->setPixmap(photo);
        nameLbl = new QLabel(this);
        nameLbl->setGeometry(150,0,150,100);
        nameLbl->setAlignment(Qt::AlignCenter);
        nameLbl->setText(name);
        nameLbl->setFont(font);
        priceLbl = new QLabel(this);
        priceLbl->setGeometry(150,100,150,50);
        priceLbl->setAlignment(Qt::AlignCenter);
        priceLbl->setText(QString(tr("<font color=black size=6 face=华文行楷>%1<font color=black size=4 face=华文行楷>%2")).arg(price).arg(unit));
    }
    int getMenuId(){
        return menuId;
    }
};

#endif // ITEMWIDGET_H
