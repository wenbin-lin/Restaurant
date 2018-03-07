#ifndef WAITERLISTQUERY_H
#define WAITERLISTQUERY_H

#include "myquery.h"

class WaiterListQuery : public MyQuery//用于访问数据库中的服务员工作列表
{
public:
    WaiterListQuery();
    //插入新行
    void insert(int seatId, QString waiterId);
    //写入评论
    void setEvaluation(int seatId, int evaluation);
    void setComment(int seatId, QString comment);
    //获取工作记录
    QStringList getDateList(QString waiterId);
    QList<int> getWorkloadList(QString waiterId, QStringList dateList);
    QList<int> getWaterList(QString waiterId, QStringList dateList);
    QList<int> getUrgeList(QString waiterId, QStringList dateList);
    QList<int> getSummonList(QString waiterId, QStringList dateList);
    QList<int> getServeList(QString waiterId, QStringList dateList);
    //添加工作记录
    void addWater(int seatId);
    void addUrge(int seatId);
    void addSummon(int seatId);
    void addServe(int seatId);
    void addPay(int seatId);
    //查看评价
    QStringList getCommentList(QString waiterId);
    QList<int> getEvaluationList(QString waiterId);
    QStringList getCommentDateList(QString waiterId);
    //统计工作量
    int countWorkload(QString waiterId);
    int countWater(QString waiterId);
    int countUrge(QString waiterId);
    int countSummon(QString waiterId);
    int countServe(QString waiterId);
    //获取平均评价
    double getAverEvaluation(QString waiterId);
    //设置时间筛选
    void setStartDate(QDate date);
    void setEndDate(QDate date);
    void setAllTime(bool isAll);
private:
    //时间筛选
    QDate startDate;
    QDate endDate;
    bool isAllTime;
};

#endif // WAITERLISTQUERY_H
