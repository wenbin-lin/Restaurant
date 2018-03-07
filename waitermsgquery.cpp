#include "waitermsgquery.h"

WaiterMsgQuery::WaiterMsgQuery() : MyQuery()
{
    tableName = "waiterMsg";
}

void WaiterMsgQuery::insert(int seatId)
{
    query.prepare("insert into waiterMsg(seatId,water,urge,summon,serve,pay)"
                   "values(?,?,?,?,?,?)");
    query.addBindValue(seatId);
    query.addBindValue(0);
    query.addBindValue(0);
    query.addBindValue(0);
    query.addBindValue(0);
    query.addBindValue(0);
    query.exec();
}

bool WaiterMsgQuery::isClaimed(int seatId)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(this->getRecord("waiterId").isNull())
        return false;
    else
        return true;
}

 void WaiterMsgQuery::setWaiterId(int seatId, QString waiterId)
 {
     this->setTable("waiterMsg");
     this->setFilter("seatId",seatId);
     this->setRecord("waiterId",waiterId);
 }

QString WaiterMsgQuery::getWaiterId(int seatId)
{
    if(isClaimed(seatId)){
        this->setTable("waiterMsg");
        this->setFilter("seatId",seatId);
        return getRecord("waiterId").toString();
    }
    else
        return "";
}

void WaiterMsgQuery::setWater(int seatId, bool isDone)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(isDone){
        this->setRecord("water",0);
    }
    else
        this->setRecord("water",1);
}

void WaiterMsgQuery::setUrge(int seatId, bool isDone)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(isDone)
        this->setRecord("urge",0);
    else
        this->setRecord("urge",1);
}

void WaiterMsgQuery::setSummon(int seatId, bool isDone)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(isDone)
        this->setRecord("summon",0);
    else
        this->setRecord("summon",1);
}

void WaiterMsgQuery::setServe(int seatId, bool isDone)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(isDone){
        this->setRecord("serve",0);
        this->setRecordNull("dishName");
    }
    else
        this->setRecord("serve",1);
}

void WaiterMsgQuery::setDishName(int seatId, QString dishName)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(this->getRecord("dishName").isNull()){
        this->setRecord("dishName", dishName);
    }
    else{
        QString oldName = this->getRecord("dishName").toString();
        this->setRecord("dishName",oldName+tr("，")+dishName);
    }
}

void WaiterMsgQuery::setPay(int seatId, bool isDone)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    if(isDone)
        this->setRecord("pay",0);
    else
        this->setRecord("pay",1);
}

QList<int> WaiterMsgQuery::getNewCustomer(QString waiterId)
{
    this->setTable("waiterMsg");
    this->setFilter("waiterId");
    QList<int> seatIdList;
    this->getRecords("seatId",seatIdList);
    return seatIdList;
}

QList<int> WaiterMsgQuery::getWater(QString waiterId)
{
    this->setTable("waiterMsg");
    this->setFilter("water",1);
    this->addFilter("waiterId", waiterId);
    QList<int> waterList;
    this->getRecords("seatId",waterList);
    return waterList;
}

QList<int> WaiterMsgQuery::getUrge(QString waiterId)
{
    this->setTable("waiterMsg");
    this->setFilter("urge",1);
    this->addFilter("waiterId", waiterId);
    QList<int> urgeList;
    this->getRecords("seatId",urgeList);
    return urgeList;
}

QList<int> WaiterMsgQuery::getSummon(QString waiterId)
{
    this->setTable("waiterMsg");
    this->setFilter("summon",1);
    this->addFilter("waiterId", waiterId);
    QList<int> summonList;
    this->getRecords("seatId",summonList);
    return summonList;
}

QHash<int, QString> WaiterMsgQuery::getServe(QString waiterId)
{
    QHash<int, QString> serveTable;
    this->setTable("waiterMsg");
    this->setFilter("serve",1);
    this->addFilter("waiterId", waiterId);
    QList<int> seatList;
    this->getRecords("seatId",seatList);
    QStringList dishNameList;
    this->getRecords("dishName",dishNameList);
    for(int i = 0;i<seatList.count();++i){
        serveTable.insert(seatList.at(i),dishNameList.at(i));
    }
    return serveTable;
}

QList<int> WaiterMsgQuery::getPay(QString waiterId)
{
    this->setTable("waiterMsg");
    this->setFilter("pay",1);
    this->addFilter("waiterId", waiterId);
    QList<int> payList;
    this->getRecords("seatId",payList);
    return payList;
}

void WaiterMsgQuery::deleteMsg(int seatId)
{
    this->setTable("waiterMsg");
    this->setFilter("seatId",seatId);
    this->deleteRecord();
}
