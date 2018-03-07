#include "waiterlistquery.h"

WaiterListQuery::WaiterListQuery()
{
    tableName = "waiterList";
    isAllTime = true;
}

void WaiterListQuery::insert(int seatId, QString waiterId)
{
    this->setTable("waiterList");
    int lastId;
    if(this->count() == 0)
        lastId = -1;
    else
        lastId = this->getRecord("id",false).toInt();
    query.prepare("insert into waiterList(id,seatId,waiterId,time) "
                  "values(?,?,?,?)");
    query.addBindValue(++lastId);
    query.addBindValue(seatId);
    query.addBindValue(waiterId);
    QDate time = QDate::currentDate();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd");//设置显示格式
    query.addBindValue(str);
    query.exec();
}

void WaiterListQuery::setEvaluation(int seatId, int evaluation)
{
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id",false).toInt();
    this->setFilter("id",id);
    this->setRecord("evaluation",evaluation);
}

void WaiterListQuery::setComment(int seatId, QString comment)
{
    if(comment=="")
        return;
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id",false).toInt();
    this->setFilter("id",id);
    this->setRecord("comment",comment);
}

QStringList WaiterListQuery::getDateList(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    QStringList dateList;
    this->getUniqueRecords("time",dateList);
    return dateList;
}

QList<int> WaiterListQuery::getWorkloadList(QString waiterId, QStringList dateList)
{
    QList<int> workloadList;
    this->setTable("waiterList");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("waiterId",waiterId);
        this->addFilter("time",dateList.at(i));
        workloadList<<this->count();
    }
    return workloadList;
}

QList<int> WaiterListQuery::getWaterList(QString waiterId, QStringList dateList)
{
    QList<int> waterList;
    this->setTable("waiterList");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("waiterId",waiterId);
        this->addFilter("time",dateList.at(i));
        waterList<<this->getSum("water");
    }
    return waterList;
}

QList<int> WaiterListQuery::getUrgeList(QString waiterId, QStringList dateList)
{
    QList<int> urgeList;
    this->setTable("waiterList");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("waiterId",waiterId);
        this->addFilter("time",dateList.at(i));
        urgeList<<this->getSum("urge");
    }
    return urgeList;
}

QList<int> WaiterListQuery::getSummonList(QString waiterId, QStringList dateList)
{
    QList<int> summonList;
    this->setTable("waiterList");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("waiterId",waiterId);
        this->addFilter("time",dateList.at(i));
        summonList<<this->getSum("summon");
    }
    return summonList;
}

QList<int> WaiterListQuery::getServeList(QString waiterId, QStringList dateList)
{
    QList<int> serveList;
    this->setTable("waiterList");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("waiterId",waiterId);
        this->addFilter("time",dateList.at(i));
        serveList<<this->getSum("serve");
    }
    return serveList;
}

void WaiterListQuery::addWater(int seatId)
{
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id", false).toInt();
    this->addFilter("id",id);
    this->setRecordAdd("water");
}

void WaiterListQuery::addUrge(int seatId)
{
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id", false).toInt();
    this->addFilter("id",id);
    this->setRecordAdd("urge");
}

void WaiterListQuery::addSummon(int seatId)
{
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id", false).toInt();
    this->addFilter("id",id);
    this->setRecordAdd("summon");
}

void WaiterListQuery::addServe(int seatId)
{
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id", false).toInt();
    this->addFilter("id",id);
    this->setRecordAdd("serve");
}

void WaiterListQuery::addPay(int seatId)
{
    this->setTable("waiterList");
    this->setFilter("seatId",seatId);
    int id = this->getRecord("id", false).toInt();
    this->addFilter("id",id);
    this->setRecordAdd("pay");
}

QStringList WaiterListQuery::getCommentList(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    this->addFilter("comment",false);
    QStringList commentList;
    this->getRecords("comment",commentList);
    return commentList;
}

QList<int> WaiterListQuery::getEvaluationList(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    this->addFilter("comment",false);
    QList<int> evaluationList;
    this->getRecords("evaluation",evaluationList);
    return evaluationList;
}

QStringList WaiterListQuery::getCommentDateList(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    this->addFilter("comment",false);
    QStringList commentDateList;
    this->getRecords("time",commentDateList);
    return commentDateList;
}

int WaiterListQuery::countWorkload(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->count();
}

int WaiterListQuery::countWater(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getSum("water");
}

int WaiterListQuery::countUrge(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getSum("urge");
}

int WaiterListQuery::countSummon(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getSum("summon");
}

int WaiterListQuery::countServe(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getSum("serve");
}

double WaiterListQuery::getAverEvaluation(QString waiterId)
{
    this->setTable("waiterList");
    this->setFilter("waiterId",waiterId);
    this->addFilter("evaluation", false);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getAver("evaluation");
}

void WaiterListQuery::setStartDate(QDate date)
{
    startDate = date;
}

void WaiterListQuery::setEndDate(QDate date)
{
    endDate = date;
}

void WaiterListQuery::setAllTime(bool isAll)
{
    isAllTime = isAll;
}
