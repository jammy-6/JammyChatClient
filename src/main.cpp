#pragma execution_character_set("utf-8")

#include "LoginWindow.h"
#include "RegisterWindow.h"
#include "HttpManager.h"
#include "RegisterSuccessHintWindow.h"
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "FriendListModel.h"
#include <memory>
#include "Controller.h"
#include "ConfigMgr.h"
#include "ResetPasswordWindow.h"
//#include "ChatWindow.h"
ConfigMgr gConfigMgr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QQmlApplicationEngine engine;

    FriendListModel friendListModel;
    for (int i = 1; i <= 10000; ++i) {
        Friend friendData;
        friendData.name = QString("Friend %1").arg(i);
        friendData.status = (i % 2 == 0) ? "在线" : "离线";
        friendData.lastMessage = "随机消息";
        friendData.time = QString("时间 %1").arg(i);
        friendData.avatar = QString("qrc:/UserHeadIcon/head_%1.jpg").arg(i % 5 + 1); // 设置头像路径，假设有5个头像图片
        friendListModel.addFriend(friendData);
    }

    engine.rootContext()->setContextProperty("friendListModel", &friendListModel);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    LoginWindow loginWindow;
    RegisterWindow registerWindow;
    RegisterSuccessHintWindow registerSuccessHintWindow;
    ResetPasswordWindow resetPasswordWindow;

    HttpManager::GetInstance();
    Controller::GetInstance()->init(&loginWindow,&registerWindow,&registerSuccessHintWindow,&resetPasswordWindow,&engine);
	//Controller::GetInstance()->setChatWindowVisible(true);

    return a.exec();
}
