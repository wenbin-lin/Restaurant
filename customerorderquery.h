#ifndef CUSTOMERORDERQUERY_H
#define CUSTOMERORDERQUERY_H

#include "myquery.h"
#include "menuquery.h"

class CustomerOrderQuery : public MyQuery//用于访问数据库中的订单列表
{
public:
    CustomerOrderQuery();
    //插入新行
    void insert(int seatId, int menuId, int amount);
    //获取进度
    QList<int> getMenuIdList();
    QList<int> getProgress(int menuId);
    //写入评论
    void setEvaluation(int menuId, int evaluation);//同一菜品仅写入一次评论，其余设置为null
    void setComment(int menuId, QString comment);//同一菜品仅写入一次评论，其余设置为空字符
    //获取厨师工作记录
    QStringList getDateList(QString cookId);
    QList<int> getWorkloadList(QString cookId, QStringList dateList);//每日完成总菜品数
    QHash<QString,int> getDailyWorkloadList(QString cookId, QString date);//获取每样菜品完成量
    //获取菜品销售记录
    QStringList getDateList(int menuId);
    QList<int> getDailySalesList(int menuId, QStringList dateList);//日销量
    int getMonthlySales(int menuId);//月销量
    //查看厨师评价
    QStringList getCommentList(QString cookId);
    QList<int> getEvaluationList(QString cookId);
    QStringList getCommentDateList(QString cookId);
    //查看菜品评价
    QStringList getCommentList(int menuId);
    QList<int> getEvaluationList(int menuId);
    QStringList getCommentDateList(int menuId);
    //统计厨师工作量
    int countWorkload(QString cookId);
    //统计菜品销量
    int countSales(int menuId);
    //获取平均评价
    double getAverEvaluation(QString cookId);
    double getAverEvaluation(int menuId);
    //设置时间筛选
    void setStartDate(QDate date);
    void setEndDate(QDate date);
    void setAllTime(bool isAll);
    //认领
    void setCookId(QString dishName, QString cookId);
    //设置状态
    int setFinish(QString dishName);//返回桌号以添加服务员消息
    void setServe(QString dishName);
    //获取任务列表
    QList<int> getToClaim();
    QList<int> getToFinish(QString cookId);
    QList<int> getToserve(QString cookId);

private:
    //时间筛选
    QDate startDate;
    QDate endDate;
    bool isAllTime;
    QList<int> orderIdList;//记录订单号
    QList<int> menuIdList;//记录菜品编号
};

#endif // CUSTOMERORDERQUERY_H
