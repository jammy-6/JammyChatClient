#pragma execution_character_set("utf-8")
#include <QApplication>
#include "LoginWindow.h"
#include "RegisterWindow.h"
#include "HttpManager.h"
#include "RegisterSuccessHintWindow.h"
#include <memory>
#include "Controller.h"
#include "ConfigMgr.h"
#include "ResetPasswordWindow.h"
ConfigMgr gConfigMgr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWindow loginWindow;
    RegisterWindow registerWindow;
    RegisterSuccessHintWindow registerSuccessHintWindow;
    ResetPasswordWindow resetPasswordWindow;

    HttpManager::GetInstance();
    Controller::GetInstance()->init(&loginWindow,&registerWindow,&registerSuccessHintWindow,&resetPasswordWindow);


    return a.exec();
}
