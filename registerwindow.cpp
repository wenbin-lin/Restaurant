#include "registerwindow.h"

RegisterWindow::RegisterWindow() : InputWindow()
{
    //窗口设置
    this->resize(500,350);
    this->setWindowTitle("Register");
    //部件初始化
    confirmPasswordLbl = new QLabel(this);
    confirmPasswordLbl->setText(tr("确认密码"));
    confirmPasswordLbl->setFont(font);
    confirmPasswordLbl->setGeometry(100,210,80,28);
    confirmText = new QLineEdit(this);
    confirmText->setPlaceholderText(tr("确认密码"));
    confirmText->setFont(font);
    confirmText->setGeometry(181,210,209,25);
    confirmText->setEchoMode(QLineEdit::Password);

    enrollBtn = new MyPushButton(tr("注册"),this);
    enrollBtn->setGeometry(170,260,80,28);

    connect(enrollBtn,SIGNAL(clicked(bool)),this,SLOT(enroll()));
}

void RegisterWindow::enroll()
{
    AccountsQuery aQuery;
    if (!checkLegality()){
        return;
    }
    aQuery.setTable(accountTables[modeSeletor->currentIndex()]);
    QString passwordStr = aQuery.getPassword(userNameText->text());
    if(passwordStr != ""){//检查Id是否存在
        if(passwordStr == passwordText->text()){//若密码正确直接登录
            QMessageBox::warning(this,"Warning","账号已注册");
            createMainWindow();
            return;
        }
        else{
            QMessageBox::warning(this,"Warning","账号已注册");
            return;
        }
    }
    if(passwordText->text()!=confirmText->text()){
        QMessageBox::warning(this,"Warning",tr("两次输入密码不一致"));
        return;
    }
    aQuery.setTable(accountTables[modeSeletor->currentIndex()]);
    aQuery.insert(userNameText->text(),passwordText->text());
    QMessageBox::information(this,"Infomation","账号注册成功");
    createMainWindow();
}
