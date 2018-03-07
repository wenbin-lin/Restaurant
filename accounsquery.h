#ifndef ACCOUNTSQUERY_H
#define ACCOUNTSQUERY_H

#include "myquery.h"

class AccountsQuery : public MyQuery//用于访问数据库中各个存储账户的表格
{
public:
    AccountsQuery() : MyQuery(){}
    void insert(QString userName, QString password){//插入新行
        query.prepare(QString("insert into %1 (id, password) values(?,?)").arg(tableName));
        query.addBindValue(userName);
        query.addBindValue(password);
        query.exec();
    }
    QString getPassword(QString userName){//通过用户名获取密码
        if(!this->contains("id",userName))
            return "";
        this->addFilter("id",userName);
        return this->getRecord("password").toString();
    }
    void setTable(QString name){//设置操作的表格
        MyQuery::setTable(name);
    }
    QStringList getCookIdList(){//获取厨师Id列表
        this->setTable("cook");
        QStringList cookIdList;
        this->getRecords("id",cookIdList);
        return cookIdList;
    }
    QStringList getWaiterIdList(){//获取服务员Id列表
        this->setTable("waiter");
        QStringList waiterIdList;
        this->getRecords("id",waiterIdList);
        return waiterIdList;
    }
};

#endif // ACCOUNTSQUERY_H
