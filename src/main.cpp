#pragma execution_character_set("utf-8")
#include <QApplication>
#include "LoginWindow.h"
#include "RegisterWindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow w;
    w.show();
    RegisterWindow w1;
    w1.show();
    return a.exec();
}
