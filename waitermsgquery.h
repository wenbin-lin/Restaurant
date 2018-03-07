#ifndef WAITERMSGQUERY_H
#define WAITERMSGQUERY_H

#include "myquery.h"
#include <QHash>

class WaiterMsgQuery : public MyQuery//用于访问数据库中的服务员消息列表
{
public:
    WaiterMsgQuery();
    //添加新消息
    void insert(int seatId);
    //查看是否被认领
    bool isClaimed(int seatId);
    //认领
    void setWaiterId(int seatId, QString waiterId);
    //获取服务员Id
    QString getWaiterId(int seatId);
    //设置状态
    void setWater(int seatId, bool isDone = false);
    void setUrge(int seatId, bool isDone = false);
    void setSummon(int seatId, bool isDone = false);
    void setServe(int seatId, bool isDone = false);
    void setDishName(int seatId, QString dishName);
    void setPay(int seatId, bool isDone = false);
    //获取任务列表，返回桌号
    QList<int> getNewCustomer(QString waiterId);//新顾客
    QList<int> getWater(QString waiterId);//加水
    QList<int> getUrge(QString waiterId);//催菜
    QList<int> getSummon(QString waiterId);//传唤
    QHash<int, QString> getServe(QString waiterId);//获取上菜的桌号与菜名
    QList<int> getPay(QString waiterId);//结账
    //删除对应桌号的消息
    void deleteMsg(int seatId);
};

#endif // WAITERMSGQUERY_H
