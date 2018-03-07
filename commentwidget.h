#ifndef COMMENTWIDGET_H
#define COMMENTWIDGET_H

#include <QtWidgets>
#include "waiterlistquery.h"
#include "customerorderquery.h"

class CommentWidget : public QWidget//用于显示评论，适用于菜品，服务员及厨师的评价
{
    Q_OBJECT
public:
    CommentWidget(QString id, int mode = 0, QWidget *parent = 0){
        this->setFixedSize(450,300);
        //部件初始化
        nextBtn = new QPushButton(this);
        prevBtn = new QPushButton(this);
        commentLbl = new QLabel(this);
        dateLbl = new QLabel(this);
        star1 = new QLabel(this);
        star2 = new QLabel(this);
        star3 = new QLabel(this);
        star4 = new QLabel(this);
        star5 = new QLabel(this);

        prevBtn->setFixedSize(40,40);
        prevBtn->setStyleSheet("QPushButton{border-image: url(:/Image/prev.png)}");
        nextBtn->setFixedSize(40,40);
        nextBtn->setStyleSheet("QPushButton{border-image: url(:/Image/next.png)}");
        commentLbl->setStyleSheet("QLabel{border-width: 1px;border-style: solid;border-color: black;background: white}");
        commentLbl->setGeometry(20,100,410,180);
        dateLbl->setFixedSize(110,40);
        QFont dateFont;
        dateFont.setBold(true);
        dateFont.setPixelSize(18);
        dateLbl->setFont(dateFont);
        star1->setFixedSize(25,25);
        star2->setFixedSize(25,25);
        star3->setFixedSize(25,25);
        star4->setFixedSize(25,25);
        star5->setFixedSize(25,25);
        //按键关联
        connect(prevBtn,SIGNAL(clicked(bool)),this,SLOT(showPrev()));
        connect(nextBtn,SIGNAL(clicked(bool)),this,SLOT(showNext()));
        //布局
        hLayout = new QHBoxLayout();
        hLayout->addWidget(prevBtn);
        hLayout->addWidget(nextBtn);
        hLayout->addWidget(dateLbl);
        hLayout->addWidget(star1);
        hLayout->addWidget(star2);
        hLayout->addWidget(star3);
        hLayout->addWidget(star4);
        hLayout->addWidget(star5);
        hLayout->setContentsMargins(0,0,0,200);
        this->setLayout(hLayout);
        resetComment(id, mode);
    }
    void setEvaluation(){
        commentLbl->setText(commentList.at(index));
        commentEvaluation = evaluationList.at(index);
        dateLbl->setText(commentDateList.at(index));
        //根据星级点亮星星
        star1->setStyleSheet("QLabel{border-image: url(:/Image/empty_star.png)}");
        star2->setStyleSheet("QLabel{border-image: url(:/Image/empty_star.png)}");
        star3->setStyleSheet("QLabel{border-image: url(:/Image/empty_star.png)}");
        star4->setStyleSheet("QLabel{border-image: url(:/Image/empty_star.png)}");
        star5->setStyleSheet("QLabel{border-image: url(:/Image/empty_star.png)}");
        if(commentEvaluation>0)
            star1->setStyleSheet("QLabel{border-image: url(:/Image/full_star.png)}");
        if(commentEvaluation>1)
            star2->setStyleSheet("QLabel{border-image: url(:/Image/full_star.png)}");
        if(commentEvaluation>2)
            star3->setStyleSheet("QLabel{border-image: url(:/Image/full_star.png)}");
        if(commentEvaluation>3)
            star4->setStyleSheet("QLabel{border-image: url(:/Image/full_star.png)}");
        if(commentEvaluation>4)
            star5->setStyleSheet("QLabel{border-image: url(:/Image/full_star.png)}");
    }
    void resetComment(QString id, int mode = 0){
        this->id = id;
        this->mode = mode;
        commentList.clear();
        commentDateList.clear();
        evaluationList.clear();
        switch (mode){//获取评论信息
        case 0:{
            commentList = coQuery.getCommentList(id.toInt());
            commentDateList = coQuery.getCommentDateList(id.toInt());
            evaluationList = coQuery.getEvaluationList(id.toInt());
            break;
        }
        case 1:{
            commentList = coQuery.getCommentList(id);
            commentDateList = coQuery.getCommentDateList(id);
            evaluationList = coQuery.getEvaluationList(id);
            break;
        }
        case 2:{
            commentList = wlQuery.getCommentList(id);
            commentDateList = wlQuery.getCommentDateList(id);
            evaluationList = wlQuery.getEvaluationList(id);
            break;
        }
        default:
            break;
        }
        count = commentList.count();
        index = count-1;
        if(count==0)
            commentLbl->setText(tr("暂无评价"));
        else
            setEvaluation();
    }

public slots:
    void showNext(){
        if(index<count-1){
            ++index;
            setEvaluation();
        }
        else
            QMessageBox::warning(this,"Warning",tr("此评论为最后一项"));
    }
    void showPrev(){
        if(index>0){
            --index;
            setEvaluation();
        }
        else
            QMessageBox::warning(this,"Warning",tr("此评论为第一项"));
    }
private:
    QLabel* commentLbl;
    QLabel* dateLbl;
    QLabel* star1;
    QLabel* star2;
    QLabel* star3;
    QLabel* star4;
    QLabel* star5;
    QHBoxLayout* hLayout;
    QHBoxLayout* starsLayout;
    QLabel* timeLbl;
    QPushButton* nextBtn;
    QPushButton* prevBtn;
    WaiterListQuery wlQuery;
    CustomerOrderQuery coQuery;
    //评论记录
    QStringList commentList;
    QStringList commentDateList;
    QList<int> evaluationList;
    int index;//当前位置
    int count;//总数
    int commentEvaluation;
    int mode;//0表示菜品,1表示厨师,2表示服务员
    QString id;
};

#endif // COMMENTWIDGET_H
