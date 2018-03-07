#include "MyQuery.h"

MyQuery::MyQuery()
{
    tableName = "";
    filter = "";
}

void MyQuery::setTable(QString tableName)
{
    this->tableName = tableName;
    this->filter = "";//切换表格时清除过滤条件
}

void MyQuery::setFilter(QString fieldName, int value, bool isEqual)
{
    if(isEqual)
        filter = QString("where %1 = %2").arg(fieldName).arg(value);
    else
        filter = QString("where %1 != %2").arg(fieldName).arg(value);
}

void MyQuery::setFilter(QString fieldName, QString value, bool isEqual)
{
    if(isEqual)
        filter = QString("where %1 = '%2'").arg(fieldName).arg(value);
    else
        filter = QString("where %1 != '%2'").arg(fieldName).arg(value);
}

void MyQuery::setFilter(QString fieldName, bool isNull)
{
    if(isNull)
        filter += QString("where %1 is null").arg(fieldName);
    else
        filter += QString("where %1 is not null").arg(fieldName);
}

void MyQuery::setFilter(QString fieldName, int min, int max)
{
    filter = QString("where %1 >= %2 and %1 <= %3").arg(fieldName).arg(QString::number(min)).arg(QString::number(max));
}

void MyQuery::setFilter(QString fieldName, QDate min, QDate max)
{
    QString minStr = min.toString("yyyy-MM-dd");
    QString maxStr = max.toString("yyyy-MM-dd");
    filter = QString("where datetime(%1) >= datetime('%2') and datetime(%1) <= datetime('%3')").arg(fieldName).arg(minStr).arg(maxStr);
}

void MyQuery::clearFilter()
{
    filter = "";
}

void MyQuery::addFilter(QString fieldName, int value, bool isEqual)
{
    if(filter == ""){
        setFilter(fieldName,value,isEqual);
        return;
    }
    if(isEqual)
        filter += QString(" and %1 = %2").arg(fieldName).arg(value);
    else
        filter += QString( "and %1 != %2").arg(fieldName).arg(value);
}

void MyQuery::addFilter(QString fieldName, QString value, bool isEqual)
{
    if(filter == ""){
        setFilter(fieldName,value,isEqual);
        return;
    }
    if(isEqual)
        filter += QString(" and %1 = '%2'").arg(fieldName).arg(value);
    else
        filter += QString(" and %1 != '%2'").arg(fieldName).arg(value);
}

void MyQuery::addFilter(QString fieldName, bool isNull)
{
    if(filter == ""){
        setFilter(fieldName,isNull);
        return;
    }
    if(isNull)
        filter += QString(" and %1 is null").arg(fieldName);
    else
        filter += QString(" and %1 is not null").arg(fieldName);
}

void MyQuery::addFilter(QString fieldName, int min, int max)
{
    if(filter == ""){
        setFilter(fieldName,min,max);
        return;
    }
    filter += QString(" and %1 >= %2 and %1 <= %3").arg(fieldName).arg(QString::number(min)).arg(QString::number(max));
}

void MyQuery::addFilter(QString fieldName, QDate min, QDate max)
{
    QString minStr = min.toString("yyyy-MM-dd");
    QString maxStr = max.toString("yyyy-MM-dd");
    filter += QString(" and datetime(%1) >= datetime('%2') and datetime(%1) <= datetime('%3')").arg(fieldName).arg(minStr).arg(maxStr);
}

bool MyQuery::contains(QString fieldName, int value)
{
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    while(query.next()){
        if(query.value(fieldName).toInt()==value){
            return true;
        }
    }
    return false;
}

bool MyQuery::contains(QString fieldName, QString value)
{
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    while(query.next()){
        if(query.value(fieldName).toString()==value){
            return true;
        }
    }
    return false;
}

int MyQuery::count()
{
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    query.last();
    if(query.at()<0)
        return 0;
    else
        return query.at()+1;
}

QVariant MyQuery::getRecord(QString fieldName, bool isFirst)
{
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    if(isFirst)
        query.first();
    else
        query.last();
    return query.value(fieldName);
    return query.value(QString("%1").arg(fieldName));
}

void MyQuery::getRecords(QString fieldName, QList<int>& list)
{
    list.clear();
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    while(query.next()){
        list<<query.value(fieldName).toInt();
    }
}

void MyQuery::getRecords(QString fieldName, QStringList& list)
{
    list.clear();
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    while(query.next()){
        list<<query.value(fieldName).toString();
    }
}

void MyQuery::getUniqueRecords(QString fieldName, QList<int>& list)
{
    list.clear();
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    while(query.next()){
        if(!list.contains(query.value(fieldName).toInt()))
            list<<query.value(fieldName).toInt();
    }
}

void MyQuery::getUniqueRecords(QString fieldName, QStringList& list)
{
    list.clear();
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    while(query.next()){
        if(!list.contains(query.value(fieldName).toString()))
            list<<query.value(fieldName).toString();
    }
}

double MyQuery::getAver(QString fieldName)
{
    query.exec(QString("select avg(%1) from %2 %3").arg(fieldName).arg(tableName).arg(filter));
    query.next();
    return query.value(0).toDouble();
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
}

int MyQuery::getSum(QString fieldName)
{
    query.exec(QString("select sum(%1) from %2 %3").arg(fieldName).arg(tableName).arg(filter));
    query.next();
    return query.value(0).toInt();
}

void MyQuery::setRecord(QString fieldName, int value)
{
    qDebug()<<QString("update %1 set %2 = %3 %4").arg(tableName).arg(fieldName).arg(QString::number(value)).arg(filter);
    query.exec(QString("update %1 set %2 = %3 %4").arg(tableName).arg(fieldName).arg(QString::number(value)).arg(filter));
    qDebug()<<query.lastError();
    qDebug()<<QString("update %1 set %2 = %3 %4").arg(tableName).arg(fieldName).arg(QString::number(value)).arg(filter);
}

void MyQuery::setRecord(QString fieldName, QString value)
{
    qDebug()<<QString("update %1 set %2 = '%3' %4").arg(tableName).arg(fieldName).arg(value).arg(filter);
    query.exec(QString("update %1 set %2 = '%3' %4").arg(tableName).arg(fieldName).arg(value).arg(filter));
    qDebug()<<query.lastError();
    qDebug()<<QString("update %1 set %2 = '%3' %4").arg(tableName).arg(fieldName).arg(value).arg(filter);
}

void MyQuery::setRecordNull(QString fieldName)
{
    query.exec(QString("update %1 set %2 = null %3").arg(tableName).arg(fieldName).arg(filter));
}

void MyQuery::setRecordAdd(QString fieldName)
{
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    int value = this->getRecord(fieldName).toInt();
    ++value;
    setRecord(fieldName, value);
}

void MyQuery::setRecordMinus(QString fieldName)
{
    query.exec(QString("select * from %1 %2").arg(tableName).arg(filter));
    int value = this->getRecord(fieldName).toInt();
    --value;
    setRecord(fieldName, value);
}

void MyQuery::deleteRecord()
{
    query.exec(QString("delete from %1 %2").arg(tableName).arg(filter));
}
