#include "systemmanagerwindow.h"

SystemManagerWindow::SystemManagerWindow(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口
    setFixedSize(700,800);
    setWindowTitle("Restaurant");

    //视图
    accountModel = new AlignCenterModel(this);
    accountModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    accountView = new QTableView(this);
    accountView->setModel(accountModel);
    accountView->move(150,150);
    accountView->setFixedSize(550,650);
    accountView->horizontalHeader()->setDefaultSectionSize(249);
    accountView->setAlternatingRowColors( true );
    accountView->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色

    menuModel = new AlignCenterModel(this);
    menuModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    menuModel->setTable("menu");
    menuModel->select();
    menuView = new QTableView(this);
    menuView->setModel(menuModel);
    menuView->move(150,150);
    menuView->setFixedSize(550,650);
    PixmapDelegate* imageDelegate = new PixmapDelegate();//为图片栏设置委托
    menuView->setItemDelegateForColumn(1,imageDelegate);
    menuView->verticalHeader()->setDefaultSectionSize(120);

    seatModel = new AlignCenterModel(this);
    seatModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    seatModel->setTable("seat");
    seatModel->select();
    seatView = new QTableView(this);
    seatView->setModel(seatModel);
    seatView->move(150,150);
    seatView->setFixedSize(550,650);
    seatView->setColumnHidden(2,true);//隐藏座位状态
    seatView->horizontalHeader()->setDefaultSectionSize(249);
    seatView->setAlternatingRowColors( true );
    seatView->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色

    //部件初始化
    QFont font;
    font.setBold(true);
    editMenuBtn = new MyPushButton(tr("编辑菜单"),this);
    editSeatBtn = new MyPushButton(tr("编辑座位"),this);
    editCustomerBtn = new MyPushButton(tr("顾客"),this);
    editSystemManagerBtn = new MyPushButton(tr("系统管理员"),this);
    editCookBtn = new MyPushButton(tr("厨师"),this);
    editWaiterBtn = new MyPushButton(tr("服务员"),this);
    editManagerBtn = new MyPushButton(tr("经理"),this);
    searchBtn = new MyPushButton(tr("搜索"),this);
    searchBtn->setGeometry(630,120,50,25);
    searchText = new QLineEdit(this);
    searchText->setGeometry(470,120,150,25);
    searchText->setFont(font);
    showAllBtn = new MyPushButton(tr("显示全表"),this);
    addBtn = new MyPushButton(tr("添加"),this);
    removeBtn = new MyPushButton(tr("移除"),this);
    modifyBtn = new MyPushButton(tr("修改"),this);
    revertBtn = new MyPushButton(tr("撤回"),this);
    //按键关联
    connect(editMenuBtn,SIGNAL(clicked(bool)),this,SLOT(editMenu()));
    connect(editSeatBtn,SIGNAL(clicked(bool)),this,SLOT(editSeat()));
    connect(editCustomerBtn,SIGNAL(clicked(bool)),this,SLOT(editCustomer()));
    connect(editSystemManagerBtn,SIGNAL(clicked(bool)),this,SLOT(editSystemManager()));
    connect(editCookBtn,SIGNAL(clicked(bool)),this,SLOT(editCook()));
    connect(editWaiterBtn,SIGNAL(clicked(bool)),this,SLOT(editWaiter()));
    connect(editManagerBtn,SIGNAL(clicked(bool)),this,SLOT(editManager()));

    connect(showAllBtn,SIGNAL(clicked(bool)),this,SLOT(showAll()));
    connect(addBtn,SIGNAL(clicked(bool)),this,SLOT(addItem()));
    connect(removeBtn,SIGNAL(clicked(bool)),this,SLOT(removeItem()));
    connect(modifyBtn,SIGNAL(clicked(bool)),this,SLOT(modifyItem()));
    connect(revertBtn,SIGNAL(clicked(bool)),this,SLOT(revert()));
    connect(searchBtn,SIGNAL(clicked(bool)),this,SLOT(search()));
    connect(searchText,SIGNAL(returnPressed()),this,SLOT(search()));
    //关联图片编辑
    connect(menuView,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editImage(QModelIndex)));
    //布局
    optionLayout = new QHBoxLayout();
    optionLayout->addWidget(editMenuBtn);
    optionLayout->addWidget(editSeatBtn);
    optionLayout->addWidget(editCustomerBtn);
    optionLayout->addWidget(editSystemManagerBtn);
    optionLayout->addWidget(editCookBtn);
    optionLayout->addWidget(editWaiterBtn);
    optionLayout->addWidget(editManagerBtn);
    optionLayout->setContentsMargins(20,40,20,0);

    optionWidget = new QWidget(this);
    optionWidget->setLayout(optionLayout);
    optionWidget->setGeometry(0,0,700,110);

    functionLayout = new QVBoxLayout();
    functionLayout->addWidget(showAllBtn);
    functionLayout->addWidget(addBtn);
    functionLayout->addWidget(removeBtn);
    functionLayout->addWidget(modifyBtn);
    functionLayout->addWidget(revertBtn);

    functionWidget = new QWidget(this);
    functionWidget->setLayout(functionLayout);
    functionWidget->setGeometry(15,350,125,300);

    //设置初始显示菜单
    currentModel = new AlignCenterModel();
    currentView = new QTableView();
    editMenu();
}

void SystemManagerWindow::editMenu()
{
    menuView->show();
    seatView->hide();
    accountView->hide();
    currentModel = menuModel;
    currentView = menuView;
    searchText->setPlaceholderText(tr("搜索菜名"));
}

void SystemManagerWindow::editSeat()
{
    menuView->hide();
    seatView->show();
    accountView->hide();
    currentModel = seatModel;
    currentView = seatView;
    searchText->setPlaceholderText(tr("搜索桌号"));
}

void SystemManagerWindow::editCustomer()
{
    accountModel->setTable("customer");
    accountModel->select();
    menuView->hide();
    seatView->hide();
    accountView->show();
    currentModel = accountModel;
    currentView = accountView;
    searchText->setPlaceholderText(tr("搜索ID"));
}

void SystemManagerWindow::editSystemManager()
{
    accountModel->setTable("systemManager");
    accountModel->select();
    menuView->hide();
    seatView->hide();
    accountView->show();
    currentModel = accountModel;
    currentView = accountView;
    searchText->setPlaceholderText(tr("搜索ID"));
}

void SystemManagerWindow::editCook()
{
    accountModel->setTable("cook");
    accountModel->select();
    menuView->hide();
    seatView->hide();
    accountView->show();
    currentModel = accountModel;
    currentView = accountView;
    searchText->setPlaceholderText(tr("搜索ID"));
}

void SystemManagerWindow::editWaiter()
{
    accountModel->setTable("waiter");
    accountModel->select();
    menuView->hide();
    seatView->hide();
    accountView->show();
    currentModel = accountModel;
    currentView = accountView;
    searchText->setPlaceholderText(tr("搜索ID"));
}

void SystemManagerWindow::editManager()
{
    accountModel->setTable("manager");
    accountModel->select();
    menuView->hide();
    seatView->hide();
    accountView->show();
    currentModel = accountModel;
    currentView = accountView;
    searchText->setPlaceholderText(tr("搜索ID"));
}

void SystemManagerWindow::search()
{
    QString text = searchText->text();
    if(currentModel==menuModel)
        currentModel->setFilter(QString("name = '%1'").arg(text));
    else
        currentModel->setFilter(QString("id = '%1'").arg(text));
    currentModel->select();
}

void SystemManagerWindow::showAll()
{
    currentModel->setFilter("");
    currentModel->select();
}

void SystemManagerWindow::addItem()
{
    currentModel->insertRow(currentModel->rowCount());
    if(currentModel==menuModel){
        currentModel->setData(currentModel->index(currentModel->rowCount()-1,5),0,Qt::EditRole);
        currentModel->setData(currentModel->index(currentModel->rowCount()-1,6),0,Qt::EditRole);
    }
    else if(currentModel==seatModel){
        currentModel->setData(currentModel->index(currentModel->rowCount()-1,2),0,Qt::EditRole);
    }
    currentView->scrollToBottom();
}

void SystemManagerWindow::removeItem()
{
    int curRow = currentView->currentIndex().row();
    currentModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行"),
                                  tr("是否确定？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::No){
        currentModel->revertAll();
    }
    else{
        currentModel->submitAll();
    }
}

void SystemManagerWindow::modifyItem()
{
    currentModel->database().transaction();
    if(currentModel->submitAll()){
        if(currentModel->database().commit())
            QMessageBox::information(this,"Information",tr("数据修改成功"));
    }
    else{
        currentModel->database().rollback();
        QMessageBox::warning(this,"Warning",tr("数据库出错：%1").arg(currentModel->lastError().text()),
                             QMessageBox::Ok);
    }
}

void SystemManagerWindow::revert()
{
    currentModel->revertAll();
}

void SystemManagerWindow::editImage(const QModelIndex &index)
{
    if(index.column()==1){
        QString imagePath = QFileDialog::getOpenFileName(this,tr("请选择要上传的图片"),
                                                        "C:",tr("图片文件(*png *jpg)"));
        if(!imagePath.isEmpty()){
            imagePath.replace("/","\\");//绝对路径
            QByteArray data;
            QFile* file = new QFile(imagePath);
            file->open(QIODevice::ReadOnly);
            data = file->readAll();
            file->close();
            menuModel->setData(index,data,Qt::EditRole);//将图片储存
        }
    }
}
