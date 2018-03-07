#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include "aligncentermodel.h"
#include "pixmapdelegate.h"
#include "mypushbutton.h"
#include "commentwidget.h"
#include "accounsquery.h"
#include "menuquery.h"
#include "waiterlistquery.h"
#include "customerorderquery.h"

#include <QMainWindow>
#include <QtWidgets>
#include <QSql>
#include <QSqlQuery>
#include <QTableView>
#include <QDebug>

class ManagerWindow : public QMainWindow//经理界面
{
    Q_OBJECT
public:
    explicit ManagerWindow(QWidget *parent = 0);
    void addMenuItem(int menuId);
    void addCookItem(QString cookId);
    void addWaiterItem(QString waiterId);
    void setMenuPerformance();
    void setCookPerformance();
    void setWaiterPerformance();

signals:

public slots:
    //切换表格
    void showMenu();
    void showCook();
    void showWaiter();
    //排序
    void salesAscend();
    void salesDescend();
    void dishEvaluationAscend();
    void dishEvaluationDescend();
    void workloadAscend();
    void workloadDescend();
    void evaluationAscend();
    void evaluationDescend();
    //时间筛选
    void selectDate();
    void selectAll();
    //对应显示评论
    void setMenuComment(int row, int column);
    void setCookComment(int row, int column);
    void setWaiterComment(int row, int column);
    //对应显示工作记录
    void setMenuHistory(int row, int column);
    void setCookHistory(int row, int column);
    void setWaiterHistory(int row, int column);

private:
    //总表格
    QTableWidget* menuTableWidget;
    QTableWidget* cookWidget;
    QTableWidget* waiterWidget;
    //个人表格
    QLabel* historyLbl;
    QTableWidget* menuHistoryTable;
    QTableWidget* cookHistoryTable;
    QTableWidget* waiterHistoryTable;
    //查询
    WaiterListQuery wlQuery;
    CustomerOrderQuery coQuery;
    MenuQuery mQuery;
    AccountsQuery aQuery;
    //功能按键
    MyPushButton* showMenuBtn;//显示菜单
    MyPushButton* showCookBtn;//显示厨师
    MyPushButton* showWaiterBtn;//显示服务员
    MyPushButton* salesAscendBtn;//按销量排序
    MyPushButton* salesDescendBtn;
    MyPushButton* dishEvaluationAscendBtn;//按菜品评价排序
    MyPushButton* dishEvaluationDescendBtn;
    MyPushButton* workloadAscendBtn;//按工作量排序
    MyPushButton* workloadDescendBtn;
    MyPushButton* evaluationAscendBtn;//按评价排序
    MyPushButton* evaluationDescendBtn;
    MyPushButton* showPerson;//查看个人报表
    //时间筛选部��?
    QLabel* startLbl;
    QLabel* endLbl;
    QDateEdit* startDate;
    QDateEdit* endDate;
    MyPushButton* selectBtn;
    MyPushButton* selectAllBtn;
    //历史评价
    QLabel* commentLbl;
    CommentWidget* cWidget;
    //布局
    QWidget* optionWidget;
    QWidget* menuFunctionWidget;
    QWidget* performanceFunctionWidget;
    QWidget* dateSelectorWdiget;
    QHBoxLayout* optionLayout;
    QVBoxLayout* menuFunctionLayout;
    QVBoxLayout* performanceFunctionLayout;
    QVBoxLayout* dateSelectorLayout;
};

#endif // MANAGERWINDOW_H
