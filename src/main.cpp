#pragma execution_character_set("utf-8")
#include <QApplication>
#include "LoginWindow.h"
#include "RegisterWindow.h"
#include "HttpManager.h"
#include <memory>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    LoginWindow loginWindow;
    RegisterWindow registerWindow;
    
    HttpManager::GetInstance();

    loginWindow.show();
    registerWindow.show();
    return a.exec();
}
