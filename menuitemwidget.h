#ifndef MENUITEMWIDGET_H
#define MENUITEMWIDGET_H

#include "itemwidget.h"
#include "detaildialog.h"

class MenuItemWidget : public ItemWidget//操作菜品购买数目的部件
{
    Q_OBJECT

signals:
    amountChanged(int menuId, int amount);

public slots:
    void add(){
        ++amount;
        emit amountChanged(menuId,amount);//数目变化时触发计价更新
        updateAmount();
    }
    void minus(){
        --amount;
        emit amountChanged(menuId,amount);//数目变化时触发计价更新
        updateAmount();
    }
    void showDitail(){//点击详情按钮显示详情界面
        DetailDialog* dlg = new DetailDialog(menuId,this);
        dlg->show();
        dlg->setFixedSize(450,450);
        dlg->setStyleSheet("QDialog{border-image: url(:/Image/gray.jpg)}");
    }

private:
    QPushButton* minusBtn;
    QPushButton* addBtn;
    QLabel* amountLbl;
    QPushButton* showDetailBtn;
    int menuId;
    int amount;

public:
    MenuItemWidget(int menuId, QWidget *parent = 0) : ItemWidget(menuId){
        this->menuId = menuId;
        amount = 0;
        //部件初始化
        minusBtn = new QPushButton(this);
        minusBtn->setStyleSheet("QPushButton{border-image: url(:/Image/minus3.png)}");
        addBtn = new QPushButton(this);
        addBtn->setStyleSheet("QPushButton{border-image: url(:/Image/add3.png)}");
        amountLbl = new QLabel(this);
        amountLbl->setAlignment(Qt::AlignCenter);
        amountLbl->setFont(font);
        amountLbl->setText(QString::number(amount));
        minusBtn->setGeometry(350,57,35,35);
        amountLbl->setGeometry(400,57,35,35);
        addBtn->setGeometry(450,57,35,35);
        showDetailBtn = new QPushButton(this);
        showDetailBtn->setStyleSheet("QPushButton{border-image: url(:/Image/detail.png)}");
        showDetailBtn->setGeometry(300,110,30,20);
        //按键关联
        connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(add()));
        connect(minusBtn,SIGNAL(clicked(bool)),this,SLOT(minus()));
        connect(showDetailBtn,SIGNAL(clicked(bool)),this,SLOT(showDitail()));
        updateAmount();
    }
    void updateAmount(){
        if(amount==0){
            amountLbl->hide();
            minusBtn->hide();
        }
        else{
            amountLbl->show();
            minusBtn->show();
        }
        amountLbl->setText(QString::number(amount));
    }
    void reset(){
        amount = 0;
        updateAmount();
    }
    int getAmount(){
        return amount;
    }
    void setAmount(int amount){
        this->amount = amount;
        updateAmount();
    }
};

#endif // MENUITEMWIDGET_H
