#ifndef PROGRESSITEMWIDGET_H
#define PROGRESSITEMWIDGET_H

#include "itemwidget.h"

class ProgressItemWidget : public ItemWidget//显示进度的部件
{
    Q_OBJECT

private:
    QLabel* toClaimLbl;
    QLabel* toFinishLbl;
    QLabel* toServeLbl;
    QLabel* servedLbl;
    QVBoxLayout* vLayout;
    int toClaim;
    int toFinish;
    int toServe;
    int served;
public:
    ProgressItemWidget(int menuId, int toClaim, int toFinish, int  toServe, int served, QWidget *parent = 0) : ItemWidget(menuId){
        this->toClaim = toClaim;
        this->toFinish = toFinish;
        this->toServe = toServe;
        this->served = served;
        //Label设置
        font.setPixelSize(20);
        toClaimLbl = new QLabel(QString(tr("待认领："))+QString::number(toClaim),this);
        toClaimLbl->setFont(font);
        toFinishLbl = new QLabel(QString(tr("待完成："))+QString::number(toFinish),this);
        toFinishLbl->setFont(font);
        toServeLbl = new QLabel(QString(tr("待上菜："))+QString::number(toServe),this);
        toServeLbl->setFont(font);
        servedLbl = new QLabel(QString(tr("已上菜："))+QString::number(served),this);
        servedLbl->setFont(font);
        vLayout = new QVBoxLayout();
        vLayout->addWidget(toClaimLbl);
        vLayout->addWidget(toFinishLbl);
        vLayout->addWidget(toServeLbl);
        vLayout->addWidget(servedLbl);
        vLayout->setContentsMargins(380,20,0,20);
        this->setLayout(vLayout);
        hideZero();
    }
    void hideZero(){//状态对应的数目为零时不显示
        toClaimLbl->show();
        toFinishLbl->show();
        toServeLbl->show();
        servedLbl->show();
        if(toClaim==0)
            toClaimLbl->hide();
        if(toFinish==0)
            toFinishLbl->hide();
        if(toServe==0)
            toServeLbl->hide();
        if(served==0)
            servedLbl->hide();
    }
    void reset(int toClaim, int toFinish, int toServe, int served){
        this->toClaim = toClaim;
        this->toFinish = toFinish;
        this->toServe = toServe;
        this->served = served;
        toClaimLbl->setText(QString(tr("待认领："))+QString::number(toClaim));
        toFinishLbl->setText(QString(tr("待完成："))+QString::number(toFinish));
        toServeLbl->setText(QString(tr("待上菜："))+QString::number(toServe));
        servedLbl->setText(QString(tr("已上菜："))+QString::number(served));
        hideZero();
    }
};

#endif // PROGRESSITEMWIDGET_H
