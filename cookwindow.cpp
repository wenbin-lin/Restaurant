#include "cookwindow.h"

CookWindow::CookWindow(QString id, QWidget *parent) : QMainWindow(parent)
{

    //窗口
    setFixedSize(500,600);
    cookId = id;
    //任务列表
    assignmentList = new QTableWidget(this);
    assignmentList->setColumnCount(3);
    assignmentList->setGeometry(150,0,350,600);
    assignmentList->alternatingRowColors();
    assignmentList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置无法编辑
    assignmentList->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    assignmentList->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能有一项被选择
    assignmentList->verticalHeader()->hide();
    assignmentList->horizontalHeader()->hide();
    assignmentList->setColumnWidth(0,120);
    assignmentList->setColumnWidth(1,80);
    assignmentList->verticalHeader()->setDefaultSectionSize(120);
    assignmentList->horizontalHeader()->setStretchLastSection(true);//自动填充剩余空间
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

void CookWindow::refresh()
{
    assignmentList->setRowCount(0);
    QList<int> toClaimList = coQuery.getToClaim();//获取任务列表
    QList<int> toFinishList = coQuery.getToFinish(cookId);
    QList<int> toServeList = coQuery.getToserve(cookId);
    for(int i = 0;i<toClaimList.count();++i){
        addMsgItem(toClaimList.at(i),tr("新任务，待认领"));
    }
    for(int i = 0;i<toFinishList.count();++i){
        addMsgItem(toFinishList.at(i),tr("待完成"));
    }
    for(int i = 0;i<toServeList.count();++i){
        addMsgItem(toServeList.at(i),tr("待服务员上菜"));
    }
    claimBtn->setEnabled(false);
    finishBtn->setEnabled(false);
}

void CookWindow::activateBtns(int row, int column)
{
    QString text = assignmentList->item(row,2)->text();
    if(text == QString(tr("新任务，待认领"))){
        claimBtn->setEnabled(true);
        finishBtn->setEnabled(false);
    }
    else{
        claimBtn->setEnabled(false);
        finishBtn->setEnabled(true);
    }
}

void CookWindow::claim()
{
    int ok = QMessageBox::information(this,tr("认领"),
                                  tr("是否确定？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        int currentRow = assignmentList->currentIndex().row();
        QString dishName = assignmentList->item(currentRow,1)->text();
        coQuery.setCookId(dishName,cookId);
        refresh();
    }
}

void CookWindow::finish()
{
    int ok = QMessageBox::information(this,tr("完成任务"),
                                  tr("确认完成？"),QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        int currentRow = assignmentList->currentIndex().row();
        QString dishName = assignmentList->item(currentRow,1)->text();
        QString msg = assignmentList->item(currentRow,2)->text();
        if(msg==tr("待完成")){
            //添加服务员消息
            int seatId = coQuery.setFinish(dishName);
            WaiterMsgQuery mwQuery;
            mwQuery.setServe(seatId);
            mwQuery.setDishName(seatId,dishName);
        }
        else if(msg==tr("待服务员上菜")){
            coQuery.setServe(dishName);
        }
        refresh();
    }
}

void CookWindow::showToClaim()
{
    for(int i=0;i<assignmentList->rowCount();++i){
        if(assignmentList->item(i,2)->text()==tr("新任务，待认领"))
            assignmentList->setRowHidden(i,false);
        else
            assignmentList->setRowHidden(i,true);
    }
}

void CookWindow::showToFinish()
{
    for(int i=0;i<assignmentList->rowCount();++i){
        if(assignmentList->item(i,2)->text()==tr("新任务，待认领"))
            assignmentList->setRowHidden(i,true);
        else
            assignmentList->setRowHidden(i,false);
    }
}

void CookWindow::showAll()
{
    for(int i=0;i<assignmentList->rowCount();++i){
        assignmentList->setRowHidden(i,false);
    }
}

void CookWindow::addMsgItem(int menuId, QString msg)
{
    int currentRow = assignmentList->rowCount();
    assignmentList->insertRow(currentRow);
    MenuQuery mQuery;
    QString name = mQuery.getName(menuId);
    QPixmap photo = mQuery.getImage(menuId,120,120);
    QLabel* photoLbl = new QLabel(this);
    photoLbl->resize(120,120);
    photoLbl->setPixmap(photo);
    assignmentList->setCellWidget(currentRow,0,photoLbl);
    QTableWidgetItem* nameItem = new QTableWidgetItem(name);
    nameItem->setTextAlignment(Qt::AlignCenter);
    assignmentList->setItem(currentRow,1,nameItem);
    QTableWidgetItem* msgItem = new QTableWidgetItem(msg);
    msgItem->setTextAlignment(Qt::AlignCenter);
    assignmentList->setItem(currentRow,2,msgItem);
}
