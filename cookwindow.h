#ifndef COOKWINDOW_H
#define COOKWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlError>
#include <QtWidgets>
#include <QSqlRecord>
#include <QTableWidget>
#include <QTableWidgetItem>

#include "mypushbutton.h"
#include "menuquery.h"
#include "waitermsgquery.h"
#include "customerorderquery.h"

class CookWindow : public QMainWindow//厨师界面
{
    Q_OBJECT
public:
    explicit CookWindow(QString id, QWidget *parent = 0);
    void addMsgItem(int menuId, QString msg);//添加消息
signals:

public slots:
    //点击事件处理
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
    MyPushButton* refreshBtn;//更新
    MyPushButton* showToClaimBtn;//显示新任务
    MyPushButton* showToFinishBtn;//显示待完成任务
    MyPushButton* showAllBtn;//显示全部
    MyPushButton* claimBtn;//认领新任务
    MyPushButton* finishBtn;//完成任务
    //布局
    QWidget* functionWidget;
    QVBoxLayout* functionLayout;

    QString cookId;//厨师Id

    CustomerOrderQuery coQuery;

};
#endif // COOKWINDOW_H
