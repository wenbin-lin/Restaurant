#ifndef STARSITEMWIDGET_H
#define STARSITEMWIDGET_H

#include <QtWidgets>

class StarsItemWidget : public QWidget//评论编辑部件，包括文字和星级
{
    Q_OBJECT
public:
    StarsItemWidget(QWidget *parent = 0) {
        evaluation = 0;
        //部件初始化
        star1 = new QPushButton(this);
        star1->setFixedSize(25,25);
        star2 = new QPushButton(this);
        star2->setFixedSize(25,25);
        star3 = new QPushButton(this);
        star3->setFixedSize(25,25);
        star4 = new QPushButton(this);
        star4->setFixedSize(25,25);
        star5 = new QPushButton(this);
        star5->setFixedSize(25,25);
        setBtns();
        commentEdit = new QLineEdit(this);
        commentEdit->setPlaceholderText(tr("此处添加评论，说点什么吧"));
        commentEdit->setStyleSheet("background-color: rgba(0, 0, 0, 0)");
        QFont font;
        font.setBold(true);
        commentEdit->setFont(font);
        writeLbl = new QLabel(this);
        writeLbl->setStyleSheet("QLabel{border-image: url(:/Image/write.png)}");
        writeLbl->setFixedSize(20,20);
        gLayout = new QGridLayout();
        gLayout->addWidget(star1,0,1);
        gLayout->addWidget(star2,0,2);
        gLayout->addWidget(star3,0,3);
        gLayout->addWidget(star4,0,4);
        gLayout->addWidget(star5,0,5);
        gLayout->addWidget(writeLbl,1,0);
        gLayout->addWidget(commentEdit,1,1,1,6);
        gLayout->setContentsMargins(0,50,0,0);
        this->setLayout(gLayout);
        //点击事件
        connect(star1,SIGNAL(clicked(bool)),this,SLOT(star1Clicked()));
        connect(star2,SIGNAL(clicked(bool)),this,SLOT(star2Clicked()));
        connect(star3,SIGNAL(clicked(bool)),this,SLOT(star3Clicked()));
        connect(star4,SIGNAL(clicked(bool)),this,SLOT(star4Clicked()));
        connect(star5,SIGNAL(clicked(bool)),this,SLOT(star5Clicked()));
    }
    void setBtns(){//根据评价星级设置星星图标的显示
        star1->setStyleSheet("QPushButton{border-image: url(:/Image/empty_star.png)}");
        star2->setStyleSheet("QPushButton{border-image: url(:/Image/empty_star.png)}");
        star3->setStyleSheet("QPushButton{border-image: url(:/Image/empty_star.png)}");
        star4->setStyleSheet("QPushButton{border-image: url(:/Image/empty_star.png)}");
        star5->setStyleSheet("QPushButton{border-image: url(:/Image/empty_star.png)}");
        if(evaluation>0)
            star1->setStyleSheet("QPushButton{border-image: url(:/Image/full_star.png)}");
        if(evaluation>1)
            star2->setStyleSheet("QPushButton{border-image: url(:/Image/full_star.png)}");
        if(evaluation>2)
            star3->setStyleSheet("QPushButton{border-image: url(:/Image/full_star.png)}");
        if(evaluation>3)
            star4->setStyleSheet("QPushButton{border-image: url(:/Image/full_star.png)}");
        if(evaluation>4)
            star5->setStyleSheet("QPushButton{border-image: url(:/Image/full_star.png)}");
    }
    int getEvaluation(){//获取星级
        return evaluation;
    }
    QString getComment(){//获取评论
        return commentEdit->text();
    }

public slots:
    void star1Clicked(){
        evaluation = 1;
        setBtns();
    }
    void star2Clicked(){
        evaluation = 2;
        setBtns();
    }
    void star3Clicked(){
        evaluation = 3;
        setBtns();
    }
    void star4Clicked(){
        evaluation = 4;
        setBtns();
    }
    void star5Clicked(){
        evaluation = 5;
        setBtns();
    }

private:
    QPushButton* star1;
    QPushButton* star2;
    QPushButton* star3;
    QPushButton* star4;
    QPushButton* star5;
    QLineEdit* commentEdit;
    QLabel* writeLbl;
    QGridLayout* gLayout;
    int evaluation;
};

#endif // STARSITEMWIDGET_H
