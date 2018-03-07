#ifndef WAITEREVALUATIONWIDGET_H
#define WAITEREVALUATIONWIDGET_H

#include "starsitemwidget.h"

class WaiterEvaluationWidget : public QWidget//根据服务员Id生成服务员评价部件
{
    Q_OBJECT

public:
    WaiterEvaluationWidget(QString waiterId, QWidget *parent = 0){
        this->waiterId = waiterId;
        starsWidget = new StarsItemWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addWidget(starsWidget);
        hLayout->setContentsMargins(300,0,0,0);
        setLayout(hLayout);
        waiterIdLbl = new QLabel(tr("服务员：")+"\n"+waiterId,this);
        QFont font;
        font.setFamily(tr("华文行楷"));
        font.setPixelSize(30);
        waiterIdLbl->setFont(font);
        waiterIdLbl->setGeometry(80,25,140,100);
    }
    int getEvaluation(){//获取星级
        return starsWidget->getEvaluation();
    }
    QString getWaiterId(){//获取Id
        return waiterId;
    }
    QString getComment(){//获取文字评论
        return starsWidget->getComment();
    }

private:
    StarsItemWidget* starsWidget;
    QLabel* waiterIdLbl;
    QString waiterId;
};

#endif // WAITEREVALUATIONWIDGET_H
