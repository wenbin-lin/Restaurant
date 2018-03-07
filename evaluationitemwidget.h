#ifndef EVALUATIONITEMWIDGET_H
#define EVALUATIONITEMWIDGET_H

#include "itemwidget.h"
#include "starsitemwidget.h"

class EvaluationItemWidget : public ItemWidget//写入评价的部件
{
    Q_OBJECT

public:
    EvaluationItemWidget(int menuId, QWidget *parent = 0) : ItemWidget(menuId){
        this->resize(520,150);
        starsWidget = new StarsItemWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout;
        hLayout->addWidget(starsWidget);
        hLayout->setContentsMargins(300,0,0,0);
        setLayout(hLayout);
    }
    int getEvaluation(){//获取星级
        return starsWidget->getEvaluation();
    }
    QString getComment(){//获取文字评价
        return starsWidget->getComment();
    }

private:
    StarsItemWidget* starsWidget;
};

#endif // EVALUATIONITEMWIDGET_H
