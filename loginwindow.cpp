#include "loginwindow.h"

LoginWindow::LoginWindow()
{
    //窗口初始化
    this->setWindowTitle("Login");
    this->resize(500,300);
    //部件初始化
    enrollBtn = new MyPushButton(tr("注册"),this);
    enrollBtn->setGeometry(140,220,80,28);
    logInBtn = new MyPushButton(tr("登录"),this);
    logInBtn->setGeometry(280,220,80,28);
    //按键关联
    connect(enrollBtn,SIGNAL(clicked(bool)),this,SLOT(enroll()));
    connect(logInBtn,SIGNAL(clicked(bool)),this,SLOT(logIn()));
}

void LoginWindow::logIn()
{
    if(!checkLegality()){
        return;
    }
    if(checkPassword()){
        createMainWindow();
    }
    else QMessageBox::warning(this,"Warning","用户名或密码错误");
}

void LoginWindow::enroll()
{
    RegisterWindow* w = new RegisterWindow();
    w->setStyleSheet("QMainWindow{border-image: url(:/Image/gray.jpg)}");
    w->show();
    this->close();
}

bool LoginWindow::checkPassword()
{
    AccountsQuery aQuery;
    aQuery.setTable(accountTables[modeSeletor->currentIndex()]);
    QString passwordStr = aQuery.getPassword(userNameText->text());
    if(passwordStr == passwordText->text())//若密码正确直接登陆
        return true;
    return false;
}
