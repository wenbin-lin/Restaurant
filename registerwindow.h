#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include "inputwindow.h"

class RegisterWindow : public InputWindow
{
    Q_OBJECT
public:
    RegisterWindow();

private slots:
    void enroll();//注册

private:
    QLabel* confirmPasswordLbl;//确认密码标签
    QLineEdit* confirmText;//确认密码
    MyPushButton* enrollBtn;//注册按钮
};

#endif // REGISTERWINDOW_H
