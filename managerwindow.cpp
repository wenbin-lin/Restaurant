#include "managerwindow.h"

ManagerWindow::ManagerWindow(QWidget *parent) : QMainWindow(parent)
{
    //设置窗口
    setFixedSize(1080,750);

    //for menu
    menuTableWidget = new QTableWidget(this);
    menuTableWidget->setGeometry(20,110,450,620);
    menuTableWidget->setColumnCount(5);
    QStringList menuHeader;
    menuHeader<<""<<tr("名称")<<tr("价格")<<tr("销量")<<tr("评价");
    menuTableWidget->setHorizontalHeaderLabels(menuHeader);
    menuTableWidget->verticalHeader()->hide();
    menuTableWidget->setColumnWidth(0,120);
    menuTableWidget->setColumnWidth(1,105);
    menuTableWidget->setColumnWidth(2,80);
    menuTableWidget->setColumnWidth(3,60);
    menuTableWidget->horizontalHeader()->setStretchLastSection(true);
    menuTableWidget->verticalHeader()->hide();
    menuTableWidget->verticalHeader()->setDefaultSectionSize(120);
    menuTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    menuTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能有一项被选择
    menuTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    QList<int> menuIdList = mQuery.getMenuIdList();
    for(int i = 0;i<menuIdList.count();++i){
        addMenuItem(menuIdList.at(i));
    }

    //for cook
    cookWidget = new QTableWidget(this);
    cookWidget->setGeometry(20,110,450,620);
    cookWidget->setColumnCount(3);
    QStringList cookHeader;
    cookHeader<<tr("编号")<<tr("完成菜品数")<<tr("评价");
    cookWidget->setHorizontalHeaderLabels(cookHeader);
    cookWidget->verticalHeader()->hide();
    cookWidget->horizontalHeader()->setDefaultSectionSize(142);
    cookWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    cookWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能有一项被选择
    cookWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    cookWidget->setAlternatingRowColors( true );
    cookWidget->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色
    QStringList cookIdList = aQuery.getCookIdList();
    for(int i = 0;i<cookIdList.count();++i){
        addCookItem(cookIdList.at(i));
    }

    //for waiter
    waiterWidget = new QTableWidget(this);
    waiterWidget->setGeometry(20,110,450,620);
    waiterWidget->setColumnCount(3);
    QStringList waiterHeader;
    waiterHeader<<tr("编号")<<tr("服务桌数")<<tr("评价");
    waiterWidget->setHorizontalHeaderLabels(waiterHeader);
    waiterWidget->verticalHeader()->hide();
    waiterWidget->horizontalHeader()->setDefaultSectionSize(142);
    waiterWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    waiterWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能有一项被选择
    waiterWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    waiterWidget->setAlternatingRowColors( true );
    waiterWidget->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色
    QStringList waiterIdList = aQuery.getWaiterIdList();
    for(int i = 0;i<waiterIdList.count();++i){
        addWaiterItem(waiterIdList.at(i));
    }

    //字体
    QFont lblFont;
    lblFont.setBold(true);
    lblFont.setPixelSize(15);

    //历史记录
    historyLbl = new QLabel(tr("个人报表:"),this);
    historyLbl->setGeometry(620,30,200,30);
    historyLbl->setFont(lblFont);
    //for menu
    menuHistoryTable = new QTableWidget(this);
    menuHistoryTable->setGeometry(610,70,450,320);
    QStringList menuHistoryHeader;
    menuHistoryHeader<<tr("时间")<<tr("销量");
    menuHistoryTable->setColumnCount(2);
    menuHistoryTable->setHorizontalHeaderLabels(menuHistoryHeader);
    menuHistoryTable->horizontalHeader()->setDefaultSectionSize(210);
    menuHistoryTable->verticalHeader()->hide();
    menuHistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    menuHistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    menuHistoryTable->setAlternatingRowColors( true );
    menuHistoryTable->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色
    //for cook
    cookHistoryTable = new QTableWidget(this);
    cookHistoryTable->setGeometry(610,70,450,320);
    QStringList cookHistoryHeader;
    cookHistoryHeader<<tr("时间")<<tr("菜品")<<tr("数量");
    cookHistoryTable->setColumnCount(3);
    cookHistoryTable->setHorizontalHeaderLabels(cookHistoryHeader);
    cookHistoryTable->horizontalHeader()->setDefaultSectionSize(140);
    cookHistoryTable->verticalHeader()->hide();
    cookHistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    cookHistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    cookHistoryTable->setAlternatingRowColors( true );
    cookHistoryTable->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色
    //for waiter
    waiterHistoryTable = new QTableWidget(this);
    waiterHistoryTable->setGeometry(610,70,450,320);
    QStringList waiterHistoryHeader;
    waiterHistoryHeader<<tr("时间")<<tr("服务桌数")<<tr("加水")<<tr("催菜")<<tr("传唤")<<tr("上菜");
    waiterHistoryTable->setColumnCount(6);
    waiterHistoryTable->setHorizontalHeaderLabels(waiterHistoryHeader);
    waiterHistoryTable->horizontalHeader()->setDefaultSectionSize(60);
    waiterHistoryTable->setColumnWidth(0,100);
    waiterHistoryTable->setColumnWidth(1,80);
    waiterHistoryTable->verticalHeader()->hide();
    waiterHistoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选定一行
    waiterHistoryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    waiterHistoryTable->setAlternatingRowColors( true );
    waiterHistoryTable->setStyleSheet( "QTableView{background-color: rgb(255, 255, 255);"
            "alternate-background-color: rgb(220, 220, 220);}" );//设置条纹颜色

    //历史评价
    commentLbl = new QLabel(tr("历史评价："),this);
    commentLbl->setGeometry(620,410,200,30);
    commentLbl->setFont(lblFont);
    QWidget* _cWidget = new QWidget(this);
    cWidget = new CommentWidget(QString::number(menuIdList.at(0)));
    _cWidget->setGeometry(610,440,450,300);
    QHBoxLayout* cLayout = new QHBoxLayout();
    cLayout->setContentsMargins(0,0,0,0);
    cLayout->addWidget(cWidget);
    _cWidget->setLayout(cLayout);

    //部件初始化
    showMenuBtn = new MyPushButton(tr("菜品销量"),this);
    showCookBtn = new MyPushButton(tr("厨师"),this);
    showWaiterBtn = new MyPushButton(tr("服务员"),this);
    salesAscendBtn = new MyPushButton(tr("按销量升序"),this);
    salesDescendBtn = new MyPushButton(tr("按销量降序"),this);
    dishEvaluationAscendBtn = new MyPushButton(tr("按评价升序"),this);
    dishEvaluationDescendBtn = new MyPushButton(tr("按评价降序"),this);
    workloadAscendBtn = new MyPushButton(tr("按工作量升序"),this);
    workloadDescendBtn = new MyPushButton(tr("按工作量降序"),this);
    evaluationAscendBtn = new MyPushButton(tr("按评价升序"),this);
    evaluationDescendBtn = new MyPushButton(tr("按评价降序"),this);

    startDate = new QDateEdit(this);
    startDate->setDisplayFormat("yyyy-MM-dd");
    startDate->setFixedSize(115,35);
    startDate->setDate(QDate::currentDate().addMonths(-1));
    endDate = new QDateEdit(this);
    endDate->setDisplayFormat("yyyy-MM-dd");
    endDate->setFixedSize(115,35);
    endDate->setDate(QDate::currentDate());
    startLbl = new QLabel(tr("起始时间："),this);
    startLbl->setFont(lblFont);
    startLbl->setFixedSize(100,25);
    endLbl = new QLabel(tr("截止时间："),this);
    endLbl->setFont(lblFont);
    endLbl->setFixedSize(100,25);
    selectBtn = new MyPushButton(tr("查看所选时间"),this);
    selectAllBtn = new MyPushButton(tr("所有时间"),this);

    //按键关联
    connect(showMenuBtn,SIGNAL(clicked(bool)),this,SLOT(showMenu()));
    connect(showCookBtn,SIGNAL(clicked(bool)),this,SLOT(showCook()));
    connect(showWaiterBtn,SIGNAL(clicked(bool)),this,SLOT(showWaiter()));
    connect(salesAscendBtn,SIGNAL(clicked(bool)),this,SLOT(salesAscend()));
    connect(dishEvaluationAscendBtn,SIGNAL(clicked(bool)),this,SLOT(dishEvaluationAscend()));
    connect(dishEvaluationDescendBtn,SIGNAL(clicked(bool)),this,SLOT(dishEvaluationDescend()));
    connect(salesDescendBtn,SIGNAL(clicked(bool)),this,SLOT(salesDescend()));
    connect(workloadAscendBtn,SIGNAL(clicked(bool)),this,SLOT(workloadAscend()));
    connect(workloadDescendBtn,SIGNAL(clicked(bool)),this,SLOT(workloadDescend()));
    connect(evaluationAscendBtn,SIGNAL(clicked(bool)),this,SLOT(evaluationAscend()));
    connect(evaluationDescendBtn,SIGNAL(clicked(bool)),this,SLOT(evaluationDescend()));
    connect(selectBtn,SIGNAL(clicked(bool)),this,SLOT(selectDate()));
    connect(selectAllBtn,SIGNAL(clicked(bool)),this,SLOT(selectAll()));
    //点击表格更新评价
    connect(menuTableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setMenuComment(int,int)));
    connect(cookWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setCookComment(int,int)));
    connect(waiterWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setWaiterComment(int,int)));
    //点击表格更新历史
    connect(menuTableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setMenuHistory(int,int)));
    connect(cookWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setCookHistory(int,int)));
    connect(waiterWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(setWaiterHistory(int,int)));


    //布局
    //for option
    optionLayout = new QHBoxLayout();
    optionLayout->addWidget(showMenuBtn);
    optionLayout->addWidget(showCookBtn);
    optionLayout->addWidget(showWaiterBtn);
    optionLayout->setSpacing(40);

    optionWidget = new QWidget(this);
    optionWidget->setLayout(optionLayout);
    optionWidget->setGeometry(20,0,450,110);

    //for menu
    menuFunctionLayout = new QVBoxLayout();
    menuFunctionLayout->addWidget(salesAscendBtn);
    menuFunctionLayout->addWidget(salesDescendBtn);
    menuFunctionLayout->addWidget(dishEvaluationAscendBtn);
    menuFunctionLayout->addWidget(dishEvaluationDescendBtn);
    menuFunctionLayout->setContentsMargins(25,0,25,0);

    menuFunctionWidget = new QWidget(this);
    menuFunctionWidget->setLayout(menuFunctionLayout);
    menuFunctionWidget->setGeometry(460,400,150,250);
    //for dateSelector
    dateSelectorLayout = new QVBoxLayout();
    dateSelectorLayout->addWidget(startLbl);
    dateSelectorLayout->addWidget(startDate);
    dateSelectorLayout->addWidget(endLbl);
    dateSelectorLayout->addWidget(endDate);
    dateSelectorLayout->addWidget(selectBtn);
    dateSelectorLayout->addWidget(selectAllBtn);
    dateSelectorLayout->setContentsMargins(20,0,20,0);

    dateSelectorWdiget = new QWidget(this);
    dateSelectorWdiget->setGeometry(460,100,150,300);
    dateSelectorWdiget->setLayout(dateSelectorLayout);

    //for performance
    performanceFunctionLayout = new QVBoxLayout();
    performanceFunctionLayout->addWidget(workloadAscendBtn);
    performanceFunctionLayout->addWidget(workloadDescendBtn);
    performanceFunctionLayout->addWidget(evaluationAscendBtn);
    performanceFunctionLayout->addWidget(evaluationDescendBtn);
    performanceFunctionLayout->setContentsMargins(25,0,25,0);

    performanceFunctionWidget = new QWidget(this);
    performanceFunctionWidget->setLayout(performanceFunctionLayout);
    performanceFunctionWidget->setGeometry(460,400,150,250);

    showMenu();//默认显示菜单
    selectAll();//默认显示所有时间
    setMenuComment(0,0);//默认显示第一行菜品评价
    setMenuHistory(0,0);//默认显示第一行菜品历史
}

void ManagerWindow::showMenu()
{
    menuTableWidget->show();
    cookWidget->hide();
    waiterWidget->hide();
    menuFunctionWidget->show();
    performanceFunctionWidget->hide();
}

void ManagerWindow::showCook()
{
    cookWidget->show();
    menuTableWidget->hide();
    waiterWidget->hide();
    menuFunctionWidget->hide();
    performanceFunctionWidget->show();
}

void ManagerWindow::showWaiter()
{
    waiterWidget->show();
    menuTableWidget->hide();
    cookWidget->hide();
    menuFunctionWidget->hide();
    performanceFunctionWidget->show();
}

void ManagerWindow::salesAscend()
{
    menuTableWidget->sortItems(3,Qt::AscendingOrder);
}

void ManagerWindow::salesDescend()
{
    menuTableWidget->sortItems(3,Qt::DescendingOrder);
}

void ManagerWindow::dishEvaluationAscend()
{
    menuTableWidget->sortItems(4,Qt::AscendingOrder);
}

void ManagerWindow::dishEvaluationDescend()
{
    menuTableWidget->sortItems(4,Qt::DescendingOrder);
}

void ManagerWindow::workloadAscend()
{
    if(cookWidget->isHidden())
        waiterWidget->sortItems(1,Qt::AscendingOrder);
    else
        cookWidget->sortItems(1,Qt::AscendingOrder);
}

void ManagerWindow::workloadDescend()
{
    if(cookWidget->isHidden())
        waiterWidget->sortItems(1,Qt::DescendingOrder);
    else
        cookWidget->sortItems(1,Qt::DescendingOrder);
}

void ManagerWindow::evaluationAscend()
{
    if(cookWidget->isHidden())
        waiterWidget->sortItems(2,Qt::AscendingOrder);
    else
        cookWidget->sortItems(2,Qt::AscendingOrder);
}

void ManagerWindow::evaluationDescend()
{
    if(cookWidget->isHidden())
        waiterWidget->sortItems(2,Qt::DescendingOrder);
    else
        cookWidget->sortItems(2,Qt::DescendingOrder);
}

void ManagerWindow::selectDate()
{
    wlQuery.setStartDate(startDate->date());
    wlQuery.setEndDate(endDate->date());
    wlQuery.setAllTime(false);
    coQuery.setStartDate(startDate->date());
    coQuery.setEndDate(endDate->date());
    coQuery.setAllTime(false);
    QString startStr = startDate->date().toString("yyyy-MM-dd");
    QString endStr = endDate->date().toString("yyyy-MM-dd");
    if(startStr>endStr){
        QMessageBox::warning(this,"Warning",tr("无效时间区间"));
        return;
    }
    setMenuPerformance();
    setCookPerformance();
    setWaiterPerformance();
}

void ManagerWindow::selectAll()
{
    wlQuery.setAllTime(true);
    coQuery.setAllTime(true);
    setMenuPerformance();
    setCookPerformance();
    setWaiterPerformance();
}

void ManagerWindow::addMenuItem(int menuId)
{
    int currentRow = menuTableWidget->rowCount();
    menuTableWidget->insertRow(currentRow);
    QString name = mQuery.getName(menuId);
    QString price = mQuery.getPriceAndUnit(menuId);
    QPixmap photo = mQuery.getImage(menuId,120,120);
    QLabel* photoLbl = new QLabel(this);
    photoLbl->resize(120,120);
    photoLbl->setPixmap(photo);
    menuTableWidget->setCellWidget(currentRow,0,photoLbl);
    QTableWidgetItem* nameItem = new QTableWidgetItem(name);
    QTableWidgetItem* priceItem = new QTableWidgetItem(price);
    nameItem->setTextAlignment(Qt::AlignCenter);
    priceItem->setTextAlignment(Qt::AlignCenter);
    menuTableWidget->setItem(currentRow,1,nameItem);
    menuTableWidget->setItem(currentRow,2,priceItem);
}

void ManagerWindow::addCookItem(QString cookId)
{
    int currentRow = cookWidget->rowCount();
    cookWidget->insertRow(currentRow);
    QTableWidgetItem* idItem = new QTableWidgetItem(cookId);
    idItem->setTextAlignment(Qt::AlignCenter);
    cookWidget->setItem(currentRow,0,idItem);
}

void ManagerWindow::addWaiterItem(QString waiterId)
{
    int currentRow = waiterWidget->rowCount();
    waiterWidget->insertRow(currentRow);
    QTableWidgetItem* idItem = new QTableWidgetItem(waiterId);
    idItem->setTextAlignment(Qt::AlignCenter);
    waiterWidget->setItem(currentRow,0,idItem);
}

void ManagerWindow::setMenuPerformance()
{
    QList<int> menuIdList = mQuery.getMenuIdList();
    for(int i = 0;i<menuTableWidget->rowCount();++i){
        int sales = coQuery.countSales(menuIdList.at(i));
        QTableWidgetItem* salesItem = new QTableWidgetItem(QString::number(sales));
        salesItem->setTextAlignment(Qt::AlignCenter);
        menuTableWidget->setItem(i,3,salesItem);
        double evaluation = coQuery.getAverEvaluation(menuIdList.at(i));
        QTableWidgetItem* evaluationItem = new QTableWidgetItem(QString::number(evaluation,10,1));
        evaluationItem->setTextAlignment(Qt::AlignCenter);
        menuTableWidget->setItem(i,4,evaluationItem);
    }
}

void ManagerWindow::setCookPerformance()
{
    QStringList cookIdList;
    for(int i = 0;i<cookWidget->rowCount();++i){
        cookIdList<<cookWidget->item(i,0)->text();
    }
    for(int i = 0;i<cookIdList.count();++i){
        int workload = coQuery.countWorkload(cookIdList.at(i));
        QTableWidgetItem* workloadItem = new QTableWidgetItem(QString::number(workload));
        workloadItem->setTextAlignment(Qt::AlignCenter);
        cookWidget->setItem(i,1,workloadItem);
        double evaluation = coQuery.getAverEvaluation(cookIdList.at(i));
        QTableWidgetItem* evaluationItem = new QTableWidgetItem(QString::number(evaluation,10,1));
        evaluationItem->setTextAlignment(Qt::AlignCenter);
        cookWidget->setItem(i,2,evaluationItem);
    }
}

void ManagerWindow::setWaiterPerformance()
{
    QStringList waiterIdList;
    for(int i = 0;i<waiterWidget->rowCount();++i){
        waiterIdList<<waiterWidget->item(i,0)->text();
    }
    for(int i = 0;i<waiterIdList.count();++i){
        int workload = wlQuery.countWorkload(waiterIdList.at(i));
        QTableWidgetItem* workloadItem = new QTableWidgetItem(QString::number(workload));
        workloadItem->setTextAlignment(Qt::AlignCenter);
        waiterWidget->setItem(i,1,workloadItem);
        double evaluation = wlQuery.getAverEvaluation(waiterIdList.at(i));
        QTableWidgetItem* evaluationItem = new QTableWidgetItem(QString::number(evaluation,10,1));
        evaluationItem->setTextAlignment(Qt::AlignCenter);
        waiterWidget->setItem(i,2,evaluationItem);
    }
}

void ManagerWindow::setMenuComment(int row, int column)
{
    QString dishName = menuTableWidget->item(row,1)->text();
    cWidget->resetComment(QString::number(mQuery.getMenuId(dishName)));
    commentLbl->setText(dishName+tr("历史评价："));
}

void ManagerWindow::setCookComment(int row, int column)
{
    QString cookId = cookWidget->item(row,0)->text();
    cWidget->resetComment(cookId, 1);
    commentLbl->setText(tr("厨师")+cookId+tr("历史评价："));
}

void ManagerWindow::setWaiterComment(int row, int column)
{
    QString waiterId = waiterWidget->item(row,0)->text();
    cWidget->resetComment(waiterId, 2);
    commentLbl->setText(tr("服务员")+waiterId+tr("历史评价"));
}

void ManagerWindow::setMenuHistory(int row, int column)
{
    menuHistoryTable->show();
    cookHistoryTable->hide();
    waiterHistoryTable->hide();

    menuHistoryTable->setRowCount(0);
    QString dishName = menuTableWidget->item(row,1)->text();
    int menuId = mQuery.getMenuId(dishName);
    QStringList dateList = coQuery.getDateList(menuId);
    QList<int> salesList = coQuery.getDailySalesList(menuId,dateList);
    for(int i = 0;i<dateList.count();++i){
        menuHistoryTable->insertRow(i);
        QTableWidgetItem* dateItem = new QTableWidgetItem(dateList.at(i));
        dateItem->setTextAlignment(Qt::AlignCenter);
        menuHistoryTable->setItem(i,0,dateItem);
        QTableWidgetItem* salesItem = new QTableWidgetItem(QString::number(salesList.at(i)));
        salesItem->setTextAlignment(Qt::AlignCenter);
        menuHistoryTable->setItem(i,1,salesItem);
    }
    historyLbl->setText(dishName+tr("销售记录："));
}

void ManagerWindow::setCookHistory(int row, int column)
{
    menuHistoryTable->hide();
    cookHistoryTable->show();
    waiterHistoryTable->hide();
    cookHistoryTable->setRowCount(0);
    QString cookId = cookWidget->item(row,0)->text();
    QStringList dateList = coQuery.getDateList(cookId);
    QHash<QString, int> workloadTable;
    int currentRow;
    for(int i = 0;i<dateList.count();++i){
        workloadTable = coQuery.getDailyWorkloadList(cookId,dateList.at(i));
        QHashIterator<QString, int> iter(workloadTable);
        while(iter.hasNext()){
            iter.next();
            currentRow = cookHistoryTable->rowCount();
            cookHistoryTable->insertRow(currentRow);
            QTableWidgetItem* dateItem = new QTableWidgetItem(dateList.at(i));
            dateItem->setTextAlignment(Qt::AlignCenter);
            cookHistoryTable->setItem(currentRow,0,dateItem);
            QTableWidgetItem* dishNameItem = new QTableWidgetItem(iter.key());
            dishNameItem->setTextAlignment(Qt::AlignCenter);
            cookHistoryTable->setItem(currentRow,1,dishNameItem);
            QTableWidgetItem* salesItem = new QTableWidgetItem(QString::number(iter.value()));
            salesItem->setTextAlignment(Qt::AlignCenter);
            cookHistoryTable->setItem(currentRow,2,salesItem);
        }
    }
    historyLbl->setText(tr("厨师")+cookId+tr("工作记录："));
}

void ManagerWindow::setWaiterHistory(int row, int column)
{
    menuHistoryTable->hide();
    cookHistoryTable->hide();
    waiterHistoryTable->show();
    waiterHistoryTable->setRowCount(0);
    QString waiterId = waiterWidget->item(row,0)->text();
    QStringList dateList = wlQuery.getDateList(waiterId);
    QList<int> workloadList = wlQuery.getWorkloadList(waiterId,dateList);
    QList<int> waterList = wlQuery.getWaterList(waiterId,dateList);
    QList<int> urgeList = wlQuery.getUrgeList(waiterId,dateList);
    QList<int> summonList = wlQuery.getSummonList(waiterId,dateList);
    QList<int> serveList = wlQuery.getServeList(waiterId,dateList);
    for(int i = 0;i<dateList.count();++i){
        waiterHistoryTable->insertRow(i);
        QTableWidgetItem* dateItem = new QTableWidgetItem(dateList.at(i));
        dateItem->setTextAlignment(Qt::AlignCenter);
        waiterHistoryTable->setItem(i,0,dateItem);
        QTableWidgetItem* seatItem = new QTableWidgetItem(QString::number(workloadList.at(i)));
        seatItem->setTextAlignment(Qt::AlignCenter);
        waiterHistoryTable->setItem(i,1,seatItem);
        QTableWidgetItem* waterItem = new QTableWidgetItem(QString::number(waterList.at(i)));
        waterItem->setTextAlignment(Qt::AlignCenter);
        waiterHistoryTable->setItem(i,2,waterItem);
        QTableWidgetItem* urgeItem = new QTableWidgetItem(QString::number(urgeList.at(i)));
        urgeItem->setTextAlignment(Qt::AlignCenter);
        waiterHistoryTable->setItem(i,3,urgeItem);
        QTableWidgetItem* summonItem = new QTableWidgetItem(QString::number(summonList.at(i)));
        summonItem->setTextAlignment(Qt::AlignCenter);
        waiterHistoryTable->setItem(i,4,summonItem);
        QTableWidgetItem* serveItem = new QTableWidgetItem(QString::number(serveList.at(i)));
        serveItem->setTextAlignment(Qt::AlignCenter);
        waiterHistoryTable->setItem(i,5,serveItem);
    }
    historyLbl->setText(tr("服务员")+waiterId+tr("工作记录："));
}

