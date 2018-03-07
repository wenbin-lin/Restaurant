#include "waiterwindow.h"

WaiterWindow::WaiterWindow(QString id, QWidget *parent) : QMainWindow(parent)
{
    //窗口
    setFixedSize(500,600);
    waiterId = id;
    //任务列表
    assignmentList = new QTableWidget(this);
    assignmentList->setColumnCount(2);
    assignmentList->setGeometry(150,0,350,600);
    assignmentList->alternatingRowColors();
    QStringList header;
    header<<tr("桌号")<<tr("需求");
    assignmentList->setHorizontalHeaderLabels(header);
    assignmentList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置无法编辑
    assignmentList->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    assignmentList->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能有一项被选择
    assignmentList->verticalHeader()->hide();
    assignmentList->setColumnWidth(0,100);
    assignmentList->horizontalHeader()->setStretchLastSection(true);//自动填充剩余空间
    assignmentList->setAlternatingRowColors(true);
    assignmentList->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色
    //按键
    QFont font;
    font.setBold(true);
    refreshBtn = new MyPushButton(tr("刷新任务"),this);
    claimBtn = new MyPushButton(tr("认领"),this);
    finishBtn = new MyPushButton(tr("完成"),this);
    showToClaimBtn = new MyPushButton(tr("新任务"),this);
    showToFinishBtn = new MyPushButton(tr("待完成任务"),this);
    showAllBtn = new MyPushButton(tr("显示全部"),this);
    //按键关联
    connect(refreshBtn,SIGNAL(clicked(bool)),this,SLOT(refresh()));
    connect(claimBtn,SIGNAL(clicked(bool)),this,SLOT(claim()));
    connect(finishBtn,SIGNAL(clicked(bool)),this,SLOT(finish()));
    connect(showToClaimBtn,SIGNAL(clicked(bool)),this,SLOT(showToClaim()));
    connect(showToFinishBtn,SIGNAL(clicked(bool)),this,SLOT(showToFinish()));
    connect(showAllBtn,SIGNAL(clicked(bool)),this,SLOT(showAll()));
    //点击事件处理
    connect(assignmentList,SIGNAL(cellClicked(int,int)),this,SLOT(activateBtns(int,int)));
    //布局
    functionLayout = new QVBoxLayout();
    functionLayout->addWidget(refreshBtn);
    functionLayout->addWidget(showToClaimBtn);
    functionLayout->addWidget(showToFinishBtn);
    functionLayout->addWidget(showAllBtn);
    functionLayout->addWidget(claimBtn);
    functionLayout->addWidget(finishBtn);

    functionWidget = new QWidget(this);
    functionWidget->setLayout(functionLayout);
    functionWidget->setGeometry(15,150,125,300);
    //刷新消息
    refresh();
    //关闭按钮
    claimBtn->setEnabled(false);
    finishBtn->setEnabled(false);
}

void WaiterWindow::refresh()
{
    assignmentList->setRowCount(0);
    QList<int> newCustomerList = wmQuery.getNewCustomer(waiterId);
    for(int i = 0;i<newCustomerList.count();++i){
        addMsgItem(newCustomerList.at(i),tr("有新的客人"));
    }
    QList<int> waterList = wmQuery.getWater(waiterId);
    for(int i = 0;i<waterList.count();++i){
        addMsgItem(waterList.at(i),tr("加水"));
    }
    QList<int> urgeList = wmQuery.getUrge(waiterId);
    for(int i = 0;i<urgeList.count();++i){
        addMsgItem(urgeList.at(i),tr("催菜"));
    }
    QList<int> summonList = wmQuery.getSummon(waiterId);
    for(int i = 0;i<summonList.count();++i){
        addMsgItem(summonList.at(i),tr("传唤"));
    }
    QHash<int, QString> serveTable = wmQuery.getServe(waiterId);
    QHashIterator<int, QString> iter(serveTable);
    while(iter.hasNext()){
        iter.next();
        addMsgItem(iter.key(),tr("上菜：")+iter.value());
    }
    QList<int> payList = wmQuery.getPay(waiterId);
    for(int i = 0;i<payList.count();++i){
        addMsgItem(payList.at(i),tr("结账"));
    }
    claimBtn->setEnabled(false);
    finishBtn->setEnabled(false);
}

void WaiterWindow::activateBtns(int row, int column)
{
    QString text = assignmentList->item(row,1)->text();
    if(text == QString(tr("有新的客人"))){
        claimBtn->setEnabled(true);
        finishBtn->setEnabled(false);
    }
    else{
        claimBtn->setEnabled(false);
        finishBtn->setEnabled(true);
    }
}

void WaiterWindow::showToClaim()
{
    for(int i=0;i<assignmentList->rowCount();++i){
        if(assignmentList->item(i,1)->text()==tr("有新的客人"))
            assignmentList->setRowHidden(i,false);
        else
            assignmentList->setRowHidden(i,true);
    }
}

void WaiterWindow::showToFinish()
{
    for(int i=0;i<assignmentList->rowCount();++i){
        if(assignmentList->item(i,1)->text()==tr("有新的客人"))
            assignmentList->setRowHidden(i,true);
        else
            assignmentList->setRowHidden(i,false);
    }
}

void WaiterWindow::showAll()
{
    for(int i=0;i<assignmentList->rowCount();++i){
        assignmentList->setRowHidden(i,false);
    }
}

void WaiterWindow::claim()
{
    int ok = QMessageBox::information(this,tr("认领"),
                                  tr("是否确定？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        int currentRow = assignmentList->currentIndex().row();
        QString seatIdStr = assignmentList->item(currentRow,0)->text();
        int seatId = seatIdStr.toInt();
        wmQuery.setWaiterId(seatId,waiterId);//更新消息
        wlQuery.insert(seatId,waiterId);//添加工作记录
        refresh();
    }
}

void WaiterWindow::finish()
{
    int ok = QMessageBox::information(this,tr("完成任务"),
                                  tr("确认完成？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        int currentRow = assignmentList->currentIndex().row();
        QString msg = assignmentList->item(currentRow,1)->text();
        QString seatIdStr = assignmentList->item(currentRow,0)->text();
        int seatId = seatIdStr.toInt();
        if(msg==tr("加水")){
            wmQuery.setWater(seatId, true);//更新消息
            wlQuery.addWater(seatId);//添加工作记录
        }
        else if(msg==tr("催菜")){
            wmQuery.setUrge(seatId, true);//更新消息
            wlQuery.addUrge(seatId);//添加工作记录
        }
        else if(msg==tr("传唤")){
            wmQuery.setSummon(seatId, true);//更新消息
            wlQuery.addSummon(seatId);//添加工作记录
        }
        else if(msg==tr("结账")){
            wmQuery.setPay(seatId, true);//更新消息
            wlQuery.addPay(seatId);//添加工作记录
        }
        else{
            wmQuery.setServe(seatId, true);//更新消息
            wlQuery.addServe(seatId);//添加工作记录
        }
        refresh();
    }
}

void WaiterWindow::addMsgItem(int seatId, QString msg)
{
    QString idText = QString("%1").arg(seatId, 2, 10, QChar('0'));
    QTableWidgetItem* seatItem = new QTableWidgetItem(idText);
    seatItem->setTextAlignment(Qt::AlignCenter);
    int currentRow = assignmentList->rowCount();
    assignmentList->insertRow(currentRow);
    assignmentList->setItem(currentRow,0,seatItem);
    QTableWidgetItem* msgItem = new QTableWidgetItem(msg);
    msgItem->setTextAlignment(Qt::AlignCenter);
    assignmentList->setItem(currentRow,1,msgItem);
}
