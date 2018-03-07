#include "connection.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::addLibraryPath("./plugins");

    if(!createConnection()) return 1;

    //显示登录界面
    LoginWindow w;
    w.setStyleSheet("QMainWindow{border-image: url(:/Image/gray.jpg)}");
    w.show();

    return a.exec();
}
