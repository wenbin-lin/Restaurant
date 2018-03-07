#ifndef WAITERWINDOW_H
#define WAITERWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlError>
#include <QtWidgets>
#include <QTableWidget>

#include "mypushbutton.h"
#include "waitermsgquery.h"
#include "waiterlistquery.h"

class WaiterWindow : public QMainWindow//服务员界面
{
    Q_OBJECT
public:
    explicit WaiterWindow(QString id, QWidget *parent = 0);
    void addMsgItem(int seatId, QString msg);

signals:

public slots:
    //按键处理函数
    void refresh();
    void showToClaim();
    void showToFinish();
    void showAll();
    void claim();
    void finish();
    void activateBtns(int row, int column);//根据点击项设置认领或完成按键的Enable设置

private:
    QTableWidget* assignmentList;//任务列表
    //按键
    MyPushButton* refreshBtn;//更新消息
    MyPushButton* showToClaimBtn;//显示新任务
    MyPushButton* showToFinishBtn;//显示待完成任务
    MyPushButton* showAllBtn;//显示全部
    MyPushButton* claimBtn;//认领新任务
    MyPushButton* finishBtn;//完成任务
    //布局
    QWidget* functionWidget;
    QVBoxLayout* functionLayout;

    QString waiterId;//服务员Id

    WaiterMsgQuery wmQuery;
    WaiterListQuery wlQuery;
};

#endif // WAITERWINDOW_H
