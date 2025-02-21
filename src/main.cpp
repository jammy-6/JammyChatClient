#pragma execution_character_set("utf-8")

#include "ConfigMgr.h"
#include "Controller.h"
#include "FriendListModel.h"
#include "GlobalTool.h"
#include "HttpManager.h"
#include "LoginWindow.h"
#include "RegisterSuccessHintWindow.h"
#include "RegisterWindow.h"
#include "ResetPasswordWindow.h"
#include "UserManagement.h"
#include "spdlog/spdlog.h"
#include <QApplication>
#include <QFile>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <memory>
#include <stdlib.h>
#include <thread>
ConfigMgr gConfigMgr;
int main(int argc, char *argv[]) {
	initSpdlog();
	QApplication a(argc, argv);
	QQmlApplicationEngine engine;

	UserManagement::GetInstance()->loginUser.userId = 0;
	UserManagement::GetInstance()->loginUser.avatar = "qrc:/UserHeadIcon/head_1.jpg";
	UserManagement::GetInstance()->friends = new FriendModel;

	// std::thread th([]() {
	for (int i = 1; i <= 200; ++i) {
		// _sleep(1000);
		FriendData friendData;
		friendData.name = QString("Friend %1").arg(rand() % 1000);
		friendData.status = (i % 2 == 0);
		friendData.email = "随机email";
		friendData.userId = i;
		friendData.avatar = QString("qrc:/UserHeadIcon/head_%1.jpg").arg(i % 5 + 1); // 设置头像路径，假设有5个头像图片
		QVector<Message> chatMsgs;
		for (int j = 0; j < 1000; j++) {
			QString msg = QString("这是一个随机生成的较长消息，内容大概在100字到200字之间。消息的具体内容可以是任何东西，比如说一些随机的句子，或者是一些随机的字符。总之，这条消息的长度应该足够长，以便测试聊天系统的处理能力。希望这条消息能够满足要求，并且在实际使用中表现良好。");
			if (rand() % 2 == 0) {
				chatMsgs << Message(MESSAGE_TYPE::TEXT, i, 0, QTime::currentTime().addSecs(rand() % 3600), msg);
			}

			else {
				chatMsgs << Message(MESSAGE_TYPE::TEXT, 0, i, QTime::currentTime().addSecs(rand() % 3600), msg);
			}
		}
		friendData.chatMsgs = chatMsgs;
		UserManagement::GetInstance()->friends->addFriend(friendData);
	}
	// });
	spdlog::info("start thread");
	engine.rootContext()->setContextProperty("userManagement", UserManagement::GetInstance().get());

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;
	reloadQss();
	LoginWindow loginWindow;
	RegisterWindow registerWindow;
	RegisterSuccessHintWindow registerSuccessHintWindow;
	ResetPasswordWindow resetPasswordWindow;

	HttpManager::GetInstance();
	Controller::GetInstance()->init(&loginWindow, &registerWindow, &registerSuccessHintWindow, &resetPasswordWindow, &engine);
	// Controller::GetInstance()->setChatWindowVisible(true);

	return a.exec();
}
