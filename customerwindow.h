#ifndef CUSTOMERWINDOW_H
#define CUSTOMERWINDOW_H

#include "aligncentermodel.h"
#include "pixmapdelegate.h"
#include "readonlydelegate.h"
#include "seatiddelegate.h"
#include "seattakendelegate.h"
#include "menuitemwidget.h"
#include "evaluationitemwidget.h"
#include "progressitemwidget.h"
#include "starsitemwidget.h"
#include "waiterevaluationwidget.h"
#include "mypushbutton.h"
#include "waitermsgquery.h"
#include "waiterlistquery.h"
#include "customerorderquery.h"

#include <QMainWindow>
#include <QSql>
#include <QSqlError>
#include <QtWidgets>
#include <QSqlTableModel>
#include <QTableView>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>
#include <QVariant>

class CustomerWindow : public QMainWindow//顾客界面
{
    Q_OBJECT
public:
    explicit CustomerWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);
signals:

public slots:
    //按键处理函数
    void showSeat();
    void showMenu();
    void checkEmpty();
    void seatSelect();
    void showCart();
    void showAllMenu();
    void showAllSeat();
    void callWaiter();
    void checkProgress();
    void order();
    void pay();
    void evaluate();
    void water();
    void urge();
    void summon();
    void submitEvaluation();
    //更新总价
    void updatePrice(int menuId, int amount);

private:
    double totalPrice;//购物车总价
    double currentPrice;//付款价格
    int seatNum;//桌号
    bool isOrder;//记录是否已点单
    bool isPaid;//记录是否已付款
    bool isEvaluated;//记录是否评论
    QList<int> amountList;//购买数目表

    AlignCenterModel* seatModel;//座位表格
    QTableView* seatView;//座位显示
    QListWidget* menuList;//菜单列表
    QListWidget* progressList;//进度列表
    QListWidget* evaluationList;//评价列表

    //查询与更新数据库
    //WaiterMsgQuery wmQuery;
    //WaiterListQuery wlQuery;
    CustomerOrderQuery coQuery;
    //MenuQuery mQuery;

    //布局
    QWidget* optionWidget;
    QWidget* infoWidget;
    QWidget* menuFunctionWidget;
    QWidget* seatFunctionWidget;
    QWidget* waiterFunctionWidget;
    QHBoxLayout* optionLayout;
    QVBoxLayout* infoLayout;
    QVBoxLayout* menuFunctionLayout;
    QVBoxLayout* seatFunctionLayout;
    QVBoxLayout* waiterFunctionLayout;
    //按钮
    MyPushButton* showMenuBtn;//查看菜单
    MyPushButton* showSeatBtn;//查看座位
    MyPushButton* showAllMenuBtn;//显示全部菜单
    MyPushButton* showAllSeatBtn;//显示全部座位
    MyPushButton* cartBtn;//购物车，可查询加入食物托盘的菜品
    MyPushButton* callWaiterBtn;//叫服务员
    MyPushButton* checkProgressBtn;//查看厨师进度
    MyPushButton* orderBtn;//下单
    MyPushButton* billBtn;//付钱
    MyPushButton* evaluateBtn;//评价
    MyPushButton* checkEmptyBtn;//查看空位
    QLabel* seatSelectorLbl;//选择座位
    QLineEdit* seatSelectorText;//输入框
    MyPushButton* seatSelectorBtn;//选择座位按钮
    MyPushButton* waterBtn;//加水
    MyPushButton* urgeBtn;//催菜
    MyPushButton* summonBtn;//传唤
    MyPushButton* submitEvaluationBtn;//提交评论
    QLabel* seatNumMarkLbl;//桌号标志
    QLabel* seatNumLbl;//桌号
    QLabel* totalPriceMarkLbl;//总价标志
    QLabel* totalPriceLbl;//总价
};

#endif // CUSTOMERWINDOW_H
