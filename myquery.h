#ifndef MYQUERY_H
#define MYQUERY_H

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDate>
#include <QDebug>

class MyQuery : public QObject//访问数据库表格的基类
{
    Q_OBJECT

protected:
    //设置操作的表格
    void setTable(QString tableName);
    //筛选条件设置
    void setFilter(QString fieldName, int value, bool isEqual = true);
    void setFilter(QString fieldName, QString value, bool isEqual = true);
    void setFilter(QString fieldName, bool isNull = true);
    void setFilter(QString fieldName, int min, int max);
    void setFilter(QString fieldName, QDate min, QDate max);
    void clearFilter();
    void addFilter(QString fieldName, int value, bool isEqual = true);
    void addFilter(QString fieldName, QString value, bool isEqual = true);
    void addFilter(QString fieldName, bool isNull = true);
    void addFilter(QString fieldName, int min, int max);
    void addFilter(QString fieldName, QDate min, QDate max);
    //获取记录
    QVariant getRecord(QString fieldName, bool isFirst = true);//获取单条记录
    void getRecords(QString fieldName, QList<int>& list);//获取多条记录
    void getRecords(QString fieldName, QStringList& list);
    void getUniqueRecords(QString fieldName, QList<int>& list);//获取不含有重复元素的记录
    void getUniqueRecords(QString fieldName, QStringList& list);
    //计算
    int count();//计算记录数目
    double getAver(QString fieldName);//获取平均值
    int getSum(QString fieldName);//获取总和
    //更新记录
    void setRecord(QString fieldName, int value);
    void setRecord(QString fieldName, QString value);
    void setRecordNull(QString fieldName);//置空
    //数量更新
    void setRecordAdd(QString fieldName);//增加
    void setRecordMinus(QString fieldName);//减少

public:
    //查询是否含有某元素
    bool contains(QString fieldName, int value);
    bool contains(QString fieldName, QString value);

    //添加记录的操作由具体表格决定，在派生类中实现
    //删除记录
    void deleteRecord();

public:
    MyQuery();

protected:
    QString tableName;
    QString filter;
    QSqlQuery query;
};

#endif // MYQUERY_H
