#ifndef DETAILDIALOG_H
#define DETAILDIALOG_H

#include "itemwidget.h"
#include "commentwidget.h"
#include "customerorderquery.h"

#include <QDialog>
#include <QtWidgets>

class DetailDialog : public QDialog//显示菜品详情，包括历史评价与月销量
{
    Q_OBJECT
public:
    DetailDialog(int menuId, QWidget *parent = 0) : QDialog(parent) {
        this->menuId = menuId;
        infoWidget = new ItemWidget(menuId);
        CustomerOrderQuery coQuery;
        int sales = coQuery.getMonthlySales(menuId);
        salesLbl = new QLabel(this);
        salesLbl->setAlignment(Qt::AlignCenter);
        salesLbl->setText(QString(tr("<font color=black size=5 face=华文行楷>%1<font color=black size=6 face=华文行楷>%2")).arg(tr("月销量：")).arg(sales));
        double evaluation = coQuery.getAverEvaluation(menuId);
        evaluationLbl = new QLabel(this);
        evaluationLbl->setAlignment(Qt::AlignCenter);
        evaluationLbl->setText(QString(tr("<font color=black size=5 face=华文行楷>%1<font color=black size=6 face=华文行楷>%2")).arg(tr("评分：")).arg(QString::number(evaluation,10,1)));//显示一位小数
        //查看评价
        cWidget = new CommentWidget(QString::number(menuId));
        QHBoxLayout* cLayout = new QHBoxLayout();
        cLayout->addWidget(cWidget);
        cLayout->setContentsMargins(0,0,0,0);
        QWidget* commentWidget = new QWidget(this);
        commentWidget->setGeometry(0,150,450,300);
        commentWidget->setLayout(cLayout);
        //布局
        gLayout = new QGridLayout();
        gLayout->addWidget(infoWidget,0,0,4,4);
        gLayout->addWidget(salesLbl,1,4,1,2);
        gLayout->addWidget(evaluationLbl,2,4,1,2);
        gLayout->setContentsMargins(0,0,0,300);
        this->setLayout(gLayout);
    }

private:
    ItemWidget* infoWidget;
    CommentWidget* cWidget;
    QLabel* salesLbl;
    QLabel* evaluationLbl;
    QGridLayout* gLayout;
    QSqlQuery query;
    int menuId;
    int sales;
    double totalEvaluation;
};

#endif // DETAILDIALOG_H
