#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVariant>
#include <QFile>
#include <QDebug>

static bool createConnection()//创建各个表格
{
    //创建数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("restaurant.db");
    //若无法创建连接则提示信息
    if(!db.open()){
        QMessageBox::critical(0,"Cannot open database",
                              "Unable to establish a database connection.",QMessageBox::Cancel);
        return false;
    }
    QSqlQuery query(db);

    //用于储存菜单
    query.exec("create table menu (id int primary key, "
               "image longblob not null,"
               "name varchar(20) not null unique,"
               "price double not null,"
               "unit varchar(10) not null )");
    //用于储存座位
    query.exec("create table seat (id int primary key, "
               "capacity int not null,"
               "isTaken bool not null)");
    //储存customer账号
    query.exec("create table customer (id varchar(20) primary key, "
               "password varchar(20) not null)");
    //储存systemManager账号
    query.exec("create table systemManager (id varchar(20) primary key, "
               "password varchar(20) not null)");
    //储存cook账号以及工作状况
    query.exec("create table cook (id varchar(20) primary key, "
               "password varchar(20) not null )");
    //储存waiter账号以及工作状况
    query.exec("create table waiter (id varchar(20) primary key, "
               "password varchar(20) not null)");
    //储存manager账号
    query.exec("create table manager (id varchar(20) primary key, "
               "password varchar(20) not null)");
    //储存订单列表
    query.exec("create table customerOrder (id int primary key, "
               "seatId int not null, "
               "menuId int not null, "
               "claimed bool not null, "
               "finished bool not null, "
               "served bool not null, "
               "cookId varchar(20), "
               "evaluation int, "
               "comment text, "
               "time varchar(10) not null)");
    //储存服务员工作列表
    query.exec("create table waiterList (id int primary key, "
               "seatId int not null, "
               "waiterId varchar(20) not null, "
               "water int default 0, "
               "urge int default 0, "
               "summon int default 0, "
               "serve int default 0, "
               "pay int default 0, "
               "evaluation int, "
               "comment text, "
               "time varchar(10) not null)");
    //储存服务员消息
    query.exec("create table waiterMsg (seatId int not null, "
               "waiterId varchar(20), "
               "water bool not null, "
               "urge bool not null, "
               "summon bool not null, "
               "serve bool not null, "
               "pay bool not null, "
               "dishName text)");

    return true;
}

#endif // CONNECTION_H
