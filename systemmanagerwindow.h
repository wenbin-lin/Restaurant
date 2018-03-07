#ifndef SYSTEMMANAGERWINDOW_H
#define SYSTEMMANAGERWINDOW_H

#include "aligncentermodel.h"
#include "pixmapdelegate.h"
#include "seatiddelegate.h"
#include "mypushbutton.h"

#include <QMainWindow>
#include <QSql>
#include <QSqlError>
#include <QtWidgets>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QTableView>
#include <QDebug>
#include <QVariant>

class SystemManagerWindow : public QMainWindow//系统管理员界面
{
    Q_OBJECT
public:
    explicit SystemManagerWindow(QWidget *parent = 0);

signals:

public slots:
    //按键处理
    void editMenu();
    void editSeat();
    void editCustomer();
    void editSystemManager();
    void editCook();
    void editWaiter();
    void editManager();
    void showAll();
    void addItem();
    void removeItem();
    void modifyItem();
    void revert();
    void search();
    //双击编辑图片
    void editImage(const QModelIndex& index);

private:
    //Model&View
    AlignCenterModel* accountModel;
    QTableView* accountView;

    AlignCenterModel* menuModel;
    AlignCenterModel* seatModel;
    QTableView* menuView;
    QTableView* seatView;

    AlignCenterModel* currentModel;//为按键通用于不同Model
    QTableView* currentView;
    //布局
    QWidget* optionWidget;
    QWidget* functionWidget;
    QHBoxLayout* optionLayout;
    QVBoxLayout* functionLayout;

    //操作按键
    MyPushButton* editMenuBtn;//编辑菜单
    MyPushButton* editSeatBtn;//编辑座位
    MyPushButton* editCustomerBtn;//编辑顾客
    MyPushButton* editSystemManagerBtn;//编辑系统管理员
    MyPushButton* editCookBtn;//编辑厨师
    MyPushButton* editWaiterBtn;//编辑服务员
    MyPushButton* editManagerBtn;//编辑经理
    MyPushButton* searchBtn;//根据名称搜索
    QLineEdit* searchText;//输入搜索内容
    MyPushButton* showAllBtn;//显示全表
    MyPushButton* addBtn;//添加
    MyPushButton* removeBtn;//移除
    MyPushButton* modifyBtn;//修改
    MyPushButton* revertBtn;//撤回
};

#endif // SYSTEMMANAGERWINDOW_H
