#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton//字体加粗的按钮
{
    Q_OBJECT
public:
    MyPushButton(QWidget *parent = 0) : QPushButton(parent){
        QFont font;
        font.setBold(true);
        this->setFont(font);
    }
    MyPushButton(QString text, QWidget *parent = 0) : QPushButton(parent){
        this->setText(text);
        QFont font;
        font.setBold(true);
        this->setFont(font);
    }
};

#endif // MYPUSHBUTTON_H
