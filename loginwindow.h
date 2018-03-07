#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "inputwindow.h"
#include "registerwindow.h"

class LoginWindow : public InputWindow
{
    Q_OBJECT

public:
    LoginWindow();

public:
    bool checkPassword();//检查密码正确性

private slots:
    void logIn();//登录
    void enroll();//注册

private:
    MyPushButton* enrollBtn;//注册按钮
    MyPushButton* logInBtn;//登录按钮
};

#endif // LOGINWINDOW_H
