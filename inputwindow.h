#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include "customerwindow.h"
#include "systemmanagerwindow.h"
#include "cookwindow.h"
#include "waiterwindow.h"
#include "managerwindow.h"
#include "mypushbutton.h"
#include "accounsquery.h"

#include <QMainWindow>
#include <QtWidgets>

class InputWindow : public QMainWindow//输入界面
{
    Q_OBJECT
public:
    const QStringList accountTables{
        "customer", "systemManager", "cook", "waiter", "manager"
    };

public:
    InputWindow();
    void createMainWindow();//创建主界面
    bool checkLegality();//检查填写合法性

public slots: 
    void changeEditMode(int mode);//设置编辑模式

protected:
    QFont font;
    QLabel* userNameLabel;//用户名标签
    QLabel* passwordLabel;//密码标签
    QLabel* modeLabel;//模式标签
    QLineEdit* userNameText;//用户名编辑框
    QLineEdit* passwordText;//密码编辑器
    QComboBox* modeSeletor;//模式选择器
    QGridLayout* layout;//布局
};

#endif // INPUTWINDOW_H
