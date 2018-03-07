#include "customerwindow.h"

CustomerWindow::CustomerWindow(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口
    setFixedSize(700,800);
    setWindowTitle("Restaurant");

    //设置初始状态
    totalPrice = 0;
    currentPrice = 0;
    isPaid = false;
    isOrder = false;
    isEvaluated = false;

    //Model&View
    //for menu
    menuList = new QListWidget(this);
    menuList->setGeometry(150,150,550,650);
    MenuQuery mQuery;
    QList<int> menuIdList = mQuery.getMenuIdList();
    for(int i = 0;i<menuIdList.count();++i){
        QListWidgetItem* menuItem = new QListWidgetItem();
        menuItem->setSizeHint(QSize(520,150));
        menuList->addItem(menuItem);
        MenuItemWidget* widget = new MenuItemWidget(menuIdList.at(i));
        connect(widget,SIGNAL(amountChanged(int,int)),this,SLOT(updatePrice(int,int)));
        menuList->setItemWidget(menuItem,widget);
        amountList<<0;
    }
    //for progress
    progressList = new QListWidget(this);
    progressList->setGeometry(150,150,550,650);
    //for evaluation
    evaluationList = new QListWidget(this);
    evaluationList->setGeometry(150,150,550,650);

    //for seat
    seatModel = new AlignCenterModel(this);
    seatModel->setTable("seat");
    seatModel->select();
    seatModel->setHeaderData(0,Qt::Orientation::Horizontal,tr("桌号"));
    seatModel->setHeaderData(1,Qt::Orientation::Horizontal,tr("容纳人数"));
    seatModel->setHeaderData(2,Qt::Orientation::Horizontal,tr("状态"));

    seatView = new QTableView(this);
    seatView->setModel(seatModel);
    seatView->move(150,150);
    seatView->setFixedSize(550,650);
    seatView->horizontalHeader()->setDefaultSectionSize(175);
    seatView->verticalHeader()->setDefaultSectionSize(40);
    //设置委托
    SeatIdDelegate* idDelegate = new SeatIdDelegate();
    SeatTakenDelegate* isTakenDelegate = new SeatTakenDelegate();
    ReadOnlyDelegate* capacityDelegate = new ReadOnlyDelegate();

    seatView->setItemDelegateForColumn(0,idDelegate);
    seatView->setItemDelegateForColumn(1,capacityDelegate);
    seatView->setItemDelegateForColumn(2,isTakenDelegate);

    seatView->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    seatView->setFocusPolicy(Qt::NoFocus);//设置无焦点
    seatView->verticalHeader()->setVisible(false);//隐藏标头
    seatView->setAlternatingRowColors( true );
    seatView->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色

    //部件初始化
    QFont font;
    font.setBold(true);
    QFont numFont;
    numFont.setPixelSize(20);
    numFont.setBold(true);
    showSeatBtn = new MyPushButton(tr("查看座位"),this);
    showMenuBtn = new MyPushButton(tr("查看菜单"),this);
    checkProgressBtn = new MyPushButton(tr("查看进度"),this);
    callWaiterBtn = new MyPushButton(tr("服务员"),this);
    billBtn = new MyPushButton(tr("付款"),this);
    evaluateBtn = new MyPushButton(tr("评价"),this);
    checkEmptyBtn = new MyPushButton(tr("查看空桌"),this);
    showAllSeatBtn = new MyPushButton(tr("显示全部"),this);
    seatSelectorLbl = new QLabel(tr("请输入桌号:"),this);
    seatSelectorLbl->setFont(font);
    seatSelectorLbl->setFixedSize(100,25);
    seatSelectorText = new QLineEdit(this);
    seatSelectorText->setFont(font);
    seatSelectorBtn = new MyPushButton(tr("确认选桌"),this);
    cartBtn = new MyPushButton(tr("购物车"),this);
    showAllMenuBtn = new MyPushButton(tr("显示全部"),this);
    orderBtn = new MyPushButton(tr("下单"),this);
    waterBtn = new MyPushButton(tr("加水"),this);
    urgeBtn = new MyPushButton(tr("催菜"),this);
    summonBtn = new MyPushButton(tr("传唤"),this);
    submitEvaluationBtn = new MyPushButton(tr("提交评论"),this);
    submitEvaluationBtn->setGeometry(25,400,100,28);
    seatNumMarkLbl = new QLabel(tr("桌号："),this);
    seatNumMarkLbl->setFont(font);
    seatNumLbl = new QLabel(tr("??"),this);
    seatNumLbl->setFont(numFont);
    seatNumLbl->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    totalPriceMarkLbl = new QLabel(tr("总价："),this);
    totalPriceMarkLbl->setFont(font);
    totalPriceLbl = new QLabel(tr("0￥"),this);
    totalPriceLbl->setFont(numFont);
    totalPriceLbl->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    //布局
    optionLayout = new QHBoxLayout();
    optionLayout->addWidget(showSeatBtn);
    optionLayout->addWidget(showMenuBtn);
    optionLayout->addWidget(checkProgressBtn);
    optionLayout->addWidget(callWaiterBtn);
    optionLayout->addWidget(billBtn);
    optionLayout->addWidget(evaluateBtn);

    optionWidget = new QWidget(this);
    optionWidget->setLayout(optionLayout);
    optionWidget->setGeometry(0,0,700,150);

    infoLayout = new QVBoxLayout();
    infoLayout->addWidget(seatNumMarkLbl);
    infoLayout->addWidget(seatNumLbl);
    infoLayout->addWidget(totalPriceMarkLbl);
    infoLayout->addWidget(totalPriceLbl);

    infoWidget = new QWidget(this);
    infoWidget->setLayout(infoLayout);
    infoWidget->setGeometry(25,550,125,150);

    menuFunctionLayout = new QVBoxLayout();
    menuFunctionLayout->addWidget(cartBtn);
    menuFunctionLayout->addWidget(showAllMenuBtn);
    menuFunctionLayout->addWidget(orderBtn);

    menuFunctionWidget = new QWidget(this);
    menuFunctionWidget->setLayout(menuFunctionLayout);
    menuFunctionWidget->setGeometry(15,350,125,200);

    seatFunctionLayout = new QVBoxLayout();
    seatFunctionLayout->addWidget(checkEmptyBtn);
    seatFunctionLayout->addWidget(showAllSeatBtn);
    seatFunctionLayout->addWidget(seatSelectorLbl);
    seatFunctionLayout->addWidget(seatSelectorText);
    seatFunctionLayout->addWidget(seatSelectorBtn);
    seatFunctionLayout->setSpacing(15);

    seatFunctionWidget = new QWidget(this);
    seatFunctionWidget->setLayout(seatFunctionLayout);
    seatFunctionWidget->setGeometry(15,250,125,300);

    waiterFunctionLayout = new QVBoxLayout();
    waiterFunctionLayout->addWidget(waterBtn);
    waiterFunctionLayout->addWidget(urgeBtn);
    waiterFunctionLayout->addWidget(summonBtn);

    waiterFunctionWidget = new QWidget(this);
    waiterFunctionWidget->setLayout(waiterFunctionLayout);
    waiterFunctionWidget->setGeometry(15,350,125,200);

    //按键关联
    connect(showSeatBtn,SIGNAL(clicked(bool)),this,SLOT(showSeat()));
    connect(showMenuBtn,SIGNAL(clicked(bool)),this,SLOT(showMenu()));
    connect(checkEmptyBtn,SIGNAL(clicked(bool)),this,SLOT(checkEmpty()));
    connect(seatSelectorBtn,SIGNAL(clicked(bool)),this,SLOT(seatSelect()));
    connect(cartBtn,SIGNAL(clicked(bool)),this,SLOT(showCart()));
    connect(showAllSeatBtn,SIGNAL(clicked(bool)),this,SLOT(showAllSeat()));
    connect(showAllMenuBtn,SIGNAL(clicked(bool)),this,SLOT(showAllMenu()));
    connect(checkProgressBtn,SIGNAL(clicked(bool)),this,SLOT(checkProgress()));
    connect(callWaiterBtn,SIGNAL(clicked(bool)),this,SLOT(callWaiter()));
    connect(waterBtn,SIGNAL(clicked(bool)),this,SLOT(water()));
    connect(urgeBtn,SIGNAL(clicked(bool)),this,SLOT(urge()));
    connect(summonBtn,SIGNAL(clicked(bool)),this,SLOT(summon()));
    connect(submitEvaluationBtn,SIGNAL(clicked(bool)),this,SLOT(submitEvaluation()));
    connect(billBtn,SIGNAL(clicked(bool)),this,SLOT(pay()));
    connect(evaluateBtn,SIGNAL(clicked(bool)),this,SLOT(evaluate()));
    connect(orderBtn,SIGNAL(clicked(bool)),this,SLOT(order()));
    //设置初始显示座位
    showSeat();

}

void CustomerWindow::showSeat()
{
    menuList->hide();
    menuFunctionWidget->hide();
    seatView->show();
    seatFunctionWidget->show();
    waiterFunctionWidget->hide();
    progressList->hide();
    evaluationList->hide();
    submitEvaluationBtn->hide();
}

void CustomerWindow::showMenu()
{
    seatView->hide();
    seatFunctionWidget->hide();
    menuList->show();
    menuFunctionWidget->show();
    waiterFunctionWidget->hide();
    progressList->hide();
    evaluationList->hide();
    submitEvaluationBtn->hide();
}

void CustomerWindow::showCart()
{
    if(totalPrice==0){
        QMessageBox::warning(this,"Waring",tr("购物车为空"));
        return;
    }
    for(int i=0;i<menuList->count();++i){
        QWidget* widgetPtr = menuList->itemWidget(menuList->item(i));
        MenuItemWidget* menuWidgetPtr = (MenuItemWidget*) widgetPtr;
        if(menuWidgetPtr->getAmount()==0){
            menuList->setRowHidden(i,true);
        }
    }
}

void CustomerWindow::showAllMenu()
{
    for(int i=0;i<menuList->count();++i){
        QWidget* widgetPtr = menuList->itemWidget(menuList->item(i));
        MenuItemWidget* menuWidgetPtr = (MenuItemWidget*) widgetPtr;
        if(menuWidgetPtr->getAmount()==0){
            menuList->setRowHidden(i,false);
        }
    }
}

void CustomerWindow::showAllSeat()
{
    seatModel->setFilter("");
    seatModel->select();
}

void CustomerWindow::checkEmpty()
{
    seatModel->setFilter(QString("%1=0").arg("isTaken"));//筛选空桌
    seatModel->select();
}

void CustomerWindow::seatSelect()
{
    if(seatSelectorText->text()==""){//检测桌号有效性
        QMessageBox::warning(this,tr("选桌错误"),tr("桌号无效"));
        return;
    }
    int seatId = seatSelectorText->text().toInt();
    for(int i = 0;i<seatModel->rowCount();++i){
        if(seatId==seatModel->data(seatModel->index(i,0),Qt::EditRole).toInt()){
            if(seatModel->data(seatModel->index(i,2),Qt::EditRole).toBool()){
                QMessageBox::warning(this,tr("选桌错误"),tr("该桌已有客人"));
            }
            else{
                QMessageBox::information(this,tr("Information"),tr("选桌成功"));
                QString text = QString("%1").arg(seatId, 2, 10, QChar('0'));//更新桌号显示
                seatNumLbl->setText(text);
                seatSelectorBtn->setEnabled(false);//将选座按钮设为无效，防止二次选桌
                seatModel->setData(seatModel->index(i,2),1,Qt::EditRole);//更新座位状态
                seatModel->submitAll();
                seatNum = seatId;
                WaiterMsgQuery wmQuery;
                wmQuery.insert(seatId);
            }
            return;
        }
    }
    QMessageBox::warning(this,tr("选桌错误"),tr("桌号无效"));
}

void CustomerWindow::callWaiter()
{
    if(seatNumLbl->text()=="??"){//尚未选桌无法发出服务员请求
        QMessageBox::warning(this,"Warning",tr("您尚未选桌"));
        return;
    }
    menuFunctionWidget->hide();
    seatFunctionWidget->hide();
    waiterFunctionWidget->show();
    submitEvaluationBtn->hide();
}

void CustomerWindow::water()
{
    WaiterMsgQuery wmQuery;
    wmQuery.setWater(seatNum);
    QMessageBox::information(this,"Informaiton",tr("已通知服务员加水"));
}

void CustomerWindow::urge()
{
    WaiterMsgQuery wmQuery;
    wmQuery.setUrge(seatNum);
    QMessageBox::information(this,"Informaiton",tr("已通知服务员催菜"));
}

void CustomerWindow::summon()
{
    WaiterMsgQuery wmQuery;
    wmQuery.setSummon(seatNum);
    QMessageBox::information(this,"Informaiton",tr("已传唤服务员"));
}

void CustomerWindow::checkProgress()
{
    if(!isOrder){
        QMessageBox::warning(this,"Warning",tr("您并未购买菜品"));
        return;
    }
    menuList->hide();
    seatView->hide();
    evaluationList->hide();
    progressList->show();
    //查询进度
    int toClaim, toFinish, toServe, served;
    QList<int> menuIdList = coQuery.getMenuIdList();
    for(int i = 0;i<menuIdList.count();++i){
        QList<int> dishProgress = coQuery.getProgress(menuIdList.at(i));
        toClaim = dishProgress.at(0);
        toFinish = dishProgress.at(1);
        toServe = dishProgress.at(2);
        served = dishProgress.at(3);
        QWidget* widgetPtr = progressList->itemWidget(progressList->item(i));
        if(widgetPtr==nullptr){
            QListWidgetItem* item = new QListWidgetItem();
            item->setSizeHint(QSize(520,150));
            progressList->addItem(item);
            ProgressItemWidget* widget = new ProgressItemWidget(menuIdList.at(i),toClaim,toFinish,toServe,served);
            progressList->setItemWidget(item,widget);
        }
        else{
            ProgressItemWidget* progressPtr = (ProgressItemWidget*) widgetPtr;
            progressPtr->reset(toClaim,toFinish,toServe,served);
        }
    }
}

void CustomerWindow::pay()
{
    if(currentPrice==0){
        QMessageBox::warning(this,"Warning",tr("您并未购买菜品"));
        return;
    }
    QString msg = tr("需支付")+QString::number(currentPrice)+tr("元，是否付款？");
    int ok = QMessageBox::warning(this,tr("付款"),msg,QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        currentPrice = 0;
        isPaid = true;
        for(int i = 0;i<seatModel->rowCount();++i){
            if(seatModel->data(seatModel->index(i,0),Qt::EditRole).toInt()==seatNum){
                seatModel->setData(seatModel->index(seatNum,2),0,Qt::EditRole);//将座位重新置空
                break;
            }
        }
        seatModel->submitAll();
        WaiterMsgQuery wmQuery;
        wmQuery.setPay(seatNum);
        QMessageBox::information(this,"Information",tr("已为您通知服务员"));
    }
}

void CustomerWindow::evaluate()
{
    if(!isPaid){
        QMessageBox::warning(this,"Warning",tr("完成付款后才能评价"));
        return;
    }
    menuList->hide();
    seatView->hide();
    progressList->hide();
    evaluationList->show();
    menuFunctionWidget->hide();
    seatFunctionWidget->hide();
    waiterFunctionWidget->hide();
    submitEvaluationBtn->show();
    QList<int> menuIdList = coQuery.getMenuIdList();
    for(int i = 0;i<menuIdList.count();++i){
        QWidget* widgetPtr = evaluationList->itemWidget(evaluationList->item(i));
        if(widgetPtr==nullptr){//检查是否添加过
            QListWidgetItem* item = new QListWidgetItem();
            item->setSizeHint(QSize(520,150));
            evaluationList->addItem(item);
            EvaluationItemWidget* widget = new EvaluationItemWidget(menuIdList[i]);
            evaluationList->setItemWidget(item,widget);
        }
    }
    QWidget* widgetPtr = evaluationList->itemWidget(evaluationList->item(menuIdList.count()));
    WaiterMsgQuery wmQuery;
    if(wmQuery.isClaimed(seatNum)&&widgetPtr==nullptr){//若服务员非空则创建评价，同时检查是否已添加
        QString waiterId = wmQuery.getWaiterId(seatNum);
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(520,150));
        evaluationList->addItem(item);
        WaiterEvaluationWidget* widget = new WaiterEvaluationWidget(waiterId);
        evaluationList->setItemWidget(item,widget);
    }
}

void CustomerWindow::submitEvaluation()
{
    if(isEvaluated){
        QMessageBox::warning(this,"Warning",tr("您已提交过评论"));
        return;
    }
    for(int i=0;i<progressList->count();++i){
        QWidget* widgetPtr = evaluationList->itemWidget(evaluationList->item(i));
        EvaluationItemWidget* evaluationPtr = (EvaluationItemWidget*) widgetPtr;
        if(evaluationPtr->getEvaluation()==0){
            QMessageBox::warning(this,"Warning",tr("评论填写不完整"));
            return;
        }
    }
    int ok = QMessageBox::warning(this,tr("提交评论"),
                                  tr("是否确定？"),QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::Yes){
        QList<int> menuIdList = coQuery.getMenuIdList();
        QWidget* widgetPtr = evaluationList->itemWidget(evaluationList->item(menuIdList.count()));//判断是否有服务员栏
        int flag = 1;
        if(widgetPtr==nullptr){
            flag = 0;
        }
        for(int i=0;i<evaluationList->count()-flag;++i){
            QWidget* widgetPtr = evaluationList->itemWidget(evaluationList->item(i));
            EvaluationItemWidget* evaluationPtr = (EvaluationItemWidget*) widgetPtr;
            int evaluation = evaluationPtr->getEvaluation();
            int menuId = evaluationPtr->getMenuId();
            QString commentStr = evaluationPtr->getComment();
            //写入评价
            coQuery.setComment(menuId,commentStr);
            coQuery.setEvaluation(menuId,evaluation);
        }
        if(flag==1){//设置服务员评价
            QWidget* widgetPtr = evaluationList->itemWidget(evaluationList->item(evaluationList->count()-1));
            WaiterEvaluationWidget* evaluationPtr = (WaiterEvaluationWidget*) widgetPtr;
            int evaluation = evaluationPtr->getEvaluation();
            QString commentStr = evaluationPtr->getComment();
            WaiterListQuery wlQuery;
            wlQuery.setEvaluation(seatNum,evaluation);
            wlQuery.setComment(seatNum,commentStr);
        }
        QMessageBox::information(this,"Information",tr("评论提交成功"));
        isEvaluated = true;
    }
}

void CustomerWindow::order()
{
    if(seatNumLbl->text()=="??"){
        QMessageBox::warning(this,"Warning",tr("您尚未选桌"));
        return;
    }
    if(totalPrice==0){
        QMessageBox::warning(this,"Warning",tr("您尚未选择菜品"));
        return;
    }
    int ok = QMessageBox::warning(this,tr("点单"),
                                  tr("是否确定？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        for(int i=0;i<menuList->count();++i){
            QWidget* widgetPtr = menuList->itemWidget(menuList->item(i));
            MenuItemWidget* menuWidgetPtr = (MenuItemWidget*)widgetPtr;
            int amount = menuWidgetPtr->getAmount();
            int menuId = menuWidgetPtr->getMenuId();
            //存储订单
            coQuery.insert(seatNum,menuId,amount);
        }
        currentPrice += totalPrice;//计价更新
        for(int i=0;i<amountList.count();++i){//清空计数
            amountList[i]=0;
        }
        totalPrice = 0;
        totalPriceLbl->setText(QString::number(totalPrice)+QString(tr("￥")));
        showAllMenu();//显示所有菜品
        for(int i=0;i<menuList->count();++i){//重设菜单项
            QWidget* widgetPtr = menuList->itemWidget(menuList->item(i));
            MenuItemWidget* menuWidgetPtr = (MenuItemWidget*)widgetPtr;
            menuWidgetPtr->reset();
        }
        QMessageBox::information(this,"Information",tr("点单成功"));
        isOrder = true;
        isPaid = false;
    }
}

void CustomerWindow::updatePrice(int menuId, int amount)
{
    for(int i = 0;i<menuList->count();++i){//更改对应项
        QWidget* widgetPtr = menuList->itemWidget(menuList->item(i));
        MenuItemWidget* menuWidgetPtr = (MenuItemWidget*) widgetPtr;
        if(menuWidgetPtr->getMenuId()==menuId){
            amountList[i] = amount;
            break;
        }
    }
    MenuQuery mQuery;
    totalPrice = mQuery.countPrice(amountList);
    QString msg = QString::number(totalPrice)+QString(tr("￥"));
    totalPriceLbl->setText(msg);
}

void CustomerWindow::closeEvent(QCloseEvent *event)
{
    if(seatNumLbl->text()!="??"){
        WaiterMsgQuery wmQuery;
        wmQuery.deleteMsg(seatNum);//删除服务员消息//多用户同时操作时需要添加
        for(int i = 0;i<seatModel->rowCount();++i){
            if(seatModel->data(seatModel->index(i,0),Qt::EditRole).toInt()==seatNum){
                seatModel->setData(seatModel->index(seatNum,2),0,Qt::EditRole);//将座位重新置空
                break;
            }
        }
        seatModel->submitAll();
    }
}
