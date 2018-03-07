#include "customerorderquery.h"

CustomerOrderQuery::CustomerOrderQuery()
{
    tableName = "customerOrder";
    isAllTime = true;
}

void CustomerOrderQuery::insert(int seatId, int menuId, int amount)
{
    int lastId;
    if(this->count() == 0)
        lastId = -1;
    else
        lastId = this->getRecord("id",false).toInt();
    for(int i = 0; i<amount; i++){//创建订单
        query.prepare("insert into customerOrder(id,seatId,menuId,claimed,finished,served,time) "
                      "values(?,?,?,?,?,?,?)");
        query.addBindValue(++lastId);
        query.addBindValue(seatId);
        query.addBindValue(menuId);
        query.addBindValue(0);
        query.addBindValue(0);
        query.addBindValue(0);
        QDate time = QDate::currentDate();//获取系统现在的时间
        QString str = time.toString("yyyy-MM-dd");//设置显示格式
        query.addBindValue(str);
        query.exec();
        if(!menuIdList.contains(menuId))
            menuIdList<<menuId;//存储菜品Id
        orderIdList<<lastId;//储存订单号
    }
}

QList<int> CustomerOrderQuery::getMenuIdList()
{
    return menuIdList;
}

QList<int> CustomerOrderQuery::getProgress(int menuId)
{
    QList<int> progressList;
    int toClaim, toFinish, toServe, served;
    toClaim = toFinish = toServe = served = 0;
    this->setTable("customerOrder");
    for(int i = 0;i<orderIdList.count();++i){
        this->setFilter("id",orderIdList.at(i));
        if(this->contains("menuId",menuId)){
            if(!this->getRecord("claimed").toBool()){
                ++toClaim;
                continue;
            }
            if(!this->getRecord("finished").toBool()){
                ++toFinish;
                continue;
            }
            if(!this->getRecord("served").toBool()){
                ++toServe;
                continue;
            }
            else{
                served++;
            }
        }
    }
    progressList<<toClaim;
    progressList<<toFinish;
    progressList<<toServe;
    progressList<<served;
    return progressList;
}

void CustomerOrderQuery::setEvaluation(int menuId, int evaluation)
{
    this->setTable("customerOrder");
    for(int i = 0;i<orderIdList.count();++i){
        this->setFilter("id",orderIdList.at(i));
        if(this->contains("menuId",menuId)){
            this->setRecord("evaluation",evaluation);
            break;
        }
    }
}

void CustomerOrderQuery::setComment(int menuId, QString comment)
{
    if(comment=="")
        return;
    this->setTable("customerOrder");
    for(int i = 0;i<orderIdList.count();++i){
        this->setFilter("id",orderIdList.at(i));
        if(this->contains("menuId",menuId)){
            this->setRecord("comment",comment);
            break;
        }
    }
}

QStringList CustomerOrderQuery::getDateList(QString cookId)
{
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    QStringList dateList;
    this->getUniqueRecords("time",dateList);
    return dateList;
}

QList<int> CustomerOrderQuery::getWorkloadList(QString cookId, QStringList dateList)
{
    QList<int> workloadList;
    this->setTable("customerOrder");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("cookId",cookId);
        this->addFilter("time",dateList.at(i));
        workloadList<<this->count();
    }
    return workloadList;
}

QHash<QString,int> CustomerOrderQuery::getDailyWorkloadList(QString cookId, QString date)
{
    QHash<QString, int> dailyWorkloadTable;
    this->setTable("customerOrder");
    QList<int> dishList;
    this->getUniqueRecords("menuId",dishList);
    for(int i = 0;i<dishList.count();++i){
        MenuQuery mQuery;
        this->setFilter("cookId",cookId);
        this->addFilter("time",date);
        this->addFilter("menuId",dishList.at(i));
        if(this->count()>0)
            dailyWorkloadTable.insert(mQuery.getName(dishList.at(i)),this->count());
    }
    return dailyWorkloadTable;
}

QStringList CustomerOrderQuery::getDateList(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    QStringList dateList;
    this->getUniqueRecords("time",dateList);
    return dateList;
}

QList<int> CustomerOrderQuery::getDailySalesList(int menuId, QStringList dateList)
{
    QList<int> salesList;
    this->setTable("customerOrder");
    for(int i = 0;i<dateList.count();++i){
        this->setFilter("menuId",menuId);
        this->addFilter("time",dateList.at(i));
        salesList<<this->count();
    }
    return salesList;
}

int CustomerOrderQuery::getMonthlySales(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    QDate curr = QDate::currentDate();
    QDate prev = curr.addMonths(-1);
    this->addFilter("time",prev,curr);
    return this->count();
}

QStringList CustomerOrderQuery::getCommentList(QString cookId)
{
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    this->addFilter("comment",false);
    QStringList commentList;
    this->getRecords("comment",commentList);
    return commentList;
}

QList<int> CustomerOrderQuery::getEvaluationList(QString cookId)
{
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    this->addFilter("comment",false);
    QList<int> evaluationList;
    this->getRecords("evaluation",evaluationList);
    return evaluationList;
}

QStringList CustomerOrderQuery::getCommentDateList(QString cookId)
{
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    this->addFilter("comment",false);
    QStringList commentDateList;
    this->getRecords("time",commentDateList);
    return commentDateList;
}

QStringList CustomerOrderQuery::getCommentList(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    this->addFilter("comment",false);
    QStringList commentList;
    this->getRecords("comment",commentList);
    return commentList;
}

QList<int> CustomerOrderQuery::getEvaluationList(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    this->addFilter("comment",false);
    QList<int> evaluationList;
    this->getRecords("evaluation",evaluationList);
    return evaluationList;
}

QStringList CustomerOrderQuery::getCommentDateList(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    this->addFilter("comment",false);
    QStringList commentDateList;
    this->getRecords("time",commentDateList);
    return commentDateList;
}

int CustomerOrderQuery::countWorkload(QString cookId)
{
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->count();
}

int CustomerOrderQuery::countSales(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->count();
}

double CustomerOrderQuery::getAverEvaluation(QString cookId)
{
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    this->addFilter("evaluation", false);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getAver("evaluation");
}

double CustomerOrderQuery::getAverEvaluation(int menuId)
{
    this->setTable("customerOrder");
    this->setFilter("menuId",menuId);
    this->addFilter("evaluation", false);
    if(!isAllTime)
        this->addFilter("time",startDate,endDate);
    return this->getAver("evaluation");
}

void CustomerOrderQuery::setStartDate(QDate date)
{
    startDate = date;
}

void CustomerOrderQuery::setEndDate(QDate date)
{
    endDate = date;
}

void CustomerOrderQuery::setAllTime(bool isAll)
{
    isAllTime = isAll;
}

void CustomerOrderQuery::setCookId(QString dishName, QString cookId)
{
    MenuQuery mQuery;
    qDebug()<<"set cookId";
    this->setTable("customerOrder");
    this->setFilter("cookId");
    this->addFilter("claimed",0);
    this->addFilter("menuId",mQuery.getMenuId(dishName));
    int id = getRecord("id").toInt();
    this->setFilter("id",id);
    this->setRecord("cookId",cookId);
    this->setRecord("claimed",1);
}

int CustomerOrderQuery::setFinish(QString dishName)
{
    MenuQuery mQuery;
    this->setTable("customerOrder");
    this->setFilter("finished",0);
    this->addFilter("menuId",mQuery.getMenuId(dishName));
    int id = getRecord("id").toInt();
    this->setFilter("id",id);
    this->setRecord("finished",1);
    return getRecord("seatId").toInt();
}

void CustomerOrderQuery::setServe(QString dishName)
{
    MenuQuery mQuery;
    this->setTable("customerOrder");
    this->setFilter("served",0);
    this->addFilter("menuId",mQuery.getMenuId(dishName));
    int id = getRecord("id").toInt();
    this->setFilter("id",id);
    this->setRecord("served",1);
}

QList<int> CustomerOrderQuery::getToClaim()
{
    QList<int> dishList;
    this->setTable("customerOrder");
    this->setFilter("cookId");
    this->addFilter("claimed",0);
    this->getRecords("menuId",dishList);
    return dishList;
}

QList<int> CustomerOrderQuery::getToFinish(QString cookId)
{
    QList<int> toFinishList;
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    this->addFilter("finished", 0);
    this->getRecords("menuId",toFinishList);
    return toFinishList;
}

QList<int> CustomerOrderQuery::getToserve(QString cookId)
{
    QList<int> toServeList;
    this->setTable("customerOrder");
    this->setFilter("cookId",cookId);
    this->addFilter("served", 0);
    this->addFilter("finished", 1);
    this->getRecords("menuId",toServeList);
    return toServeList;
}
