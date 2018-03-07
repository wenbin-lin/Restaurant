#ifndef MENUQUERY_H
#define MENUQUERY_H

#include <QPixmap>
#include "myquery.h"

class MenuQuery : public MyQuery//用于访问菜单表格
{
public:
    MenuQuery() : MyQuery(){
        setTable("menu");
    }
    int getMenuId(QString dishName){//根据菜名获取菜品Id
        this->setTable("menu");
        this->setFilter("name",dishName);
        return this->getRecord("id").toInt();
    }
    QString getName(int menuId){//根据菜品Id获取菜名
        this->setTable("menu");
        this->setFilter("id",menuId);
        return this->getRecord("name").toString();
    }
    double getPrice(int menuId){//根据菜品Id获取价格
        this->setTable("menu");
        this->setFilter("id",menuId);
        return this->getRecord("price").toDouble();
    }
    QString getUnit(int menuId){//根据菜品Id获取单位
        this->setTable("menu");
        this->setFilter("id",menuId);
        return this->getRecord("unit").toString();
    }
    QString getPriceAndUnit(int menuId){//根据菜品Id获取带有单位的价格
        this->setTable("menu");
        this->setFilter("id",menuId);
        double price = this->getRecord("price").toDouble();
        return QString::number(price)+this->getRecord("unit").toString();
    }
    QList<int> getMenuIdList(){//获取菜品Id列表
        this->setTable("menu");
        QList<int> menuIdList;
        this->getRecords("id",menuIdList);
        return menuIdList;
    }
    QPixmap getImage(int menuId, int width, int height){//获取指定大小的菜品图片
        this->setTable("menu");
        this->setFilter("id",menuId);
        QPixmap photo;
        photo.loadFromData(this->getRecord("image").toByteArray(),"JPG");
        photo = photo.scaled(width,height);
        return photo;
    }
    double countPrice(QList<int> amountList){//通过购买数目列表获取总价
        double totalPrice = 0;
        QList<int> menuIdList = getMenuIdList();
        for(int i = 0;i<amountList.count();++i){
            totalPrice += getPrice(menuIdList.at(i))*amountList.at(i);
        }
        return totalPrice;
    }
};

#endif // MENUQUERY_H
