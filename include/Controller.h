#ifndef Controller_H
#define Controller_H


#include "Global.h"
#include "Singleton.h"
#include <memory>
#include <QObject>
#include "LoginWindow.h"
#include "HttpManager.h"
#include "RegisterWindow.h"
#include "RegisterSuccessHintWindow.h"
#include "ResetPasswordWindow.h"
class Controller: public QObject,public Singleton<Controller>,public enable_shared_from_this<Controller> {
	Q_OBJECT
public:
	void init(LoginWindow* loginWindow, RegisterWindow* registerWindow, RegisterSuccessHintWindow* registerSuccessHintWindow, ResetPasswordWindow* resetPasswordWindow);
	~Controller();
	void handleGetValidateCodeSuccess(MODULE module,QString data);

public slots:
	/// 通用界面跳转槽函数
	void slotHideAndShow(QWidget* hideWidget, QWidget* showWidget);
	/// TcpMgr类连接服务器槽函数
	void slotTcpConnect(bool success);
	/// http响应槽函数
	void slotHttpFinished(MODULE module, ID id, ERRORCODE code, QString data);
	/// 注册或重置密码界面获取验证码槽函数
	void slotGetValidateCode(MODULE module, ID id);
	/// 用户注册面板槽函数
    void slotRegistUser();
	/// 密码重置面板槽函数
	void slotResetPassword();
	///登录面板槽函数
	void slotUserLogin();
private:
	friend class Singleton<Controller>;
	Controller();
	
	LoginWindow* loginWindow_;
	RegisterWindow* registerWindow_;
	RegisterSuccessHintWindow* registerSuccessHintWindow_;
	ResetPasswordWindow* resetPasswordWindow_;
};
#endif // !Controller_H