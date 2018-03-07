#include "inputwindow.h"

InputWindow::InputWindow()
{
    //窗口初始化
    this->setWindowTitle("Login");
    this->resize(500,300);

    //部件初始化
    font.setBold(true);
    font.setPixelSize(16);
    modeLabel = new QLabel(tr("模式"),this);
    modeLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    modeLabel->setFont(font);
    userNameLabel = new QLabel(tr("用户名"),this);
    userNameLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    userNameLabel->setFont(font);
    passwordLabel = new QLabel(tr("密码"),this);
    passwordLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    passwordLabel->setFont(font);
    QStringList modeStrs = {
        tr("顾客"),tr("系统管理员"),tr("厨师"),tr("服务员"),tr("经理")
    };
    modeSeletor = new QComboBox(this);
    modeSeletor->addItems(modeStrs);
    modeSeletor->setFont(font);
    modeSeletor->setFixedHeight(25);
    userNameText = new QLineEdit(this);
    userNameText->setPlaceholderText(tr("用户名"));
    userNameText->setFont(font);
    userNameText->setFixedHeight(25);
    passwordText = new QLineEdit(this);
    passwordText->setFont(font);
    passwordText->setEchoMode(QLineEdit::Password);
    passwordText->setFixedHeight(25);
    passwordText->setPlaceholderText(tr("密码"));

    //布局设置
    layout = new QGridLayout();
    layout->addWidget(modeLabel,0,0);
    layout->addWidget(modeSeletor,0,1);
    layout->addWidget(userNameLabel,1,0);
    layout->addWidget(userNameText,1,1);
    layout->addWidget(passwordLabel,2,0);
    layout->addWidget(passwordText,2,1);
    layout->setSpacing(20);

    QWidget* widget = new QWidget(this);
    widget->setLayout(layout);
    widget->setGeometry(100,50,300,150);

    connect(modeSeletor,SIGNAL(currentIndexChanged(int)),this,SLOT(changeEditMode(int)));//根据模式设置用户名输入限制

    userNameText->setFocus();//默认焦点为用户名输入限制
    changeEditMode(0);
}

bool InputWindow::checkLegality()
{
    QString userNameStr = userNameText->text();
    QString passwordStr = passwordText->text();
    if(userNameStr==nullptr){
        QMessageBox::warning(this,"Warning","用户名不能为空");
        return false;
    }
    else if(passwordStr==nullptr){
        QMessageBox::warning(this,"Warning","密码不能为空");
        return false;
    }
    if(modeSeletor->currentIndex()==0){//若选择顾客模式则判定电话号码有效性
        if((userNameStr.at(0)!='1'||userNameStr.count()!=11)){
            QMessageBox::warning(this,"Warning","无效电话号码");
            return false;
            for(int i = 0;i<userNameStr.count();++i){
                if(userNameStr.at(i)<'0'||userNameStr.at(i)>'9'){
                    QMessageBox::warning(this,"Warning","无效电话号码");
                    return false;
                }
            }
        }
    }
    return true;
}

void InputWindow::changeEditMode(int mode)
{
    if(mode==0){
        userNameText->setPlaceholderText(tr("请输入手机号"));
    }
    else{
        userNameText->setPlaceholderText(tr("用户名"));
    }
}

void InputWindow::createMainWindow()
{
    QMainWindow* w;
    switch(modeSeletor->currentIndex()){
    case 0:{
        w = new CustomerWindow();
        break;
    }
    case 1:{
        w = new SystemManagerWindow();
        break;
    }
    case 2:{
        w = new CookWindow(userNameText->text());
        break;
    }
    case 3:{
        w = new WaiterWindow(userNameText->text());
        break;
    }
    case 4:{
        w = new ManagerWindow();
        break;
    }
    default:
        break;
    }
    w->setStyleSheet("QMainWindow{border-image: url(:/Image/gray.jpg)}");
    w->show();
    this->close();
}
