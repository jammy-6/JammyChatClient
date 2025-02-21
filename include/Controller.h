#ifndef Controller_H
#define Controller_H

#include "Global.h"
#include "HttpManager.h"
#include "LoginWindow.h"
#include "RegisterSuccessHintWindow.h"
#include "RegisterWindow.h"
#include "ResetPasswordWindow.h"
#include "Singleton.h"
#include <QObject>
#include <QQmlApplicationEngine>
#include <memory>
class Controller : public QObject, public Singleton<Controller>, public enable_shared_from_this<Controller> {
	Q_OBJECT
public:
	void init(LoginWindow *loginWindow, RegisterWindow *registerWindow, RegisterSuccessHintWindow *registerSuccessHintWindow, ResetPasswordWindow *resetPasswordWindow, QQmlApplicationEngine *engine);
	~Controller();

public slots:
	/// 通用界面跳转槽函数
	void slotHideAndShow(QWidget *hideWidget, QWidget *showWidget);
	/// TcpMgr类连接服务器槽函数
	void slotTcpConnect(bool success);
	void slotTcpRecvMsg(MSG_IDS reqId, QString data);
	/// http响应槽函数
	void slotHttpFinished(MODULE module, ID id, ERRORCODE code, QString data);
	/// 注册或重置密码界面获取验证码槽函数
	void slotGetValidateCode(MODULE module, ID id);
	/// 用户注册面板槽函数
	void slotRegistUser();
	/// 密码重置面板槽函数
	void slotResetPassword();
	/// 登录面板槽函数
	void slotUserLogin();

	/// 对于slotHttpFinished以及TCPMgr会调用的回调函数
	void handleRegisterGetValideCode(nlohmann::json);
	void handleResetPasswordGetValideCode(nlohmann::json responseJson);
	void handleUserRegister(nlohmann::json responseJson);
	void handleResetPassword(nlohmann::json responseJson);
	void handleUserLogin(nlohmann::json responseJson);

	

	/// 设置聊天窗口是否可见,返回值为是否设置成功
	bool setChatWindowVisible(bool visible);

private:
	friend class Singleton<Controller>;
	Controller();
	ServerInfo connectChatServer;
	std::map<int, std::function<void(nlohmann::json)>> allHanlders_;
	LoginWindow *loginWindow_;
	RegisterWindow *registerWindow_;
	RegisterSuccessHintWindow *registerSuccessHintWindow_;
	ResetPasswordWindow *resetPasswordWindow_;
	QQmlApplicationEngine *engine_;
};
#endif // !Controller_H