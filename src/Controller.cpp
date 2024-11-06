#pragma execution_character_set("utf-8")
#include "Controller.h"
#include <QPushButton>
#include "Global.h"
#include "ConfigMgr.h"
#include "nlohmann/json.hpp"
#include <functional>
#include <QPoint>
#include "TcpMgr.h"
using json = nlohmann::json;
Controller::~Controller() {


}
Controller::Controller() {

	
}

void Controller::slotHttpFinished(MODULE module, ID id, ERRORCODE code, QString data) {
	if (code == ERRORCODE::SUCCESS) {
		std::cout << "Http Success : " << data.toStdString() << std::endl;
		switch (id) {
		case ID::ID_REGISTER_GET_VALIDATE_CODE: ///验证码获取成功
			std::cout << " 获取验证码成功！ " << std::endl;
			this->handleGetValidateCodeSuccess(module, data);
			break;
		case ID::ID_RESET_GET_VALIDATE_CODE:
			std::cout << " 获取验证码成功！ " << std::endl;
			this->handleGetValidateCodeSuccess(module, data);
			break;
		case ID::ID_USER_REGISTER:

			if (code == 0) {
				std::cout << "获取返回结果" << data.toStdString() << std::endl;
				std::cout << " 用户注册成功！ " << std::endl;
				registerWindow_->updateMsgHint(nullptr, hintRegisterSuccess, true);
			}
			break;
		case ID::ID_RESET_PASSWORD:
			if (code == 0) {
				std::cout << "获取返回结果" << data.toStdString() << std::endl;
				std::cout << " 用户重置密码成功！ " << std::endl;
				resetPasswordWindow_->updateMsgHint(nullptr, hintResetPasswordSuccessReturn, true);
			}
			break;
		
		case ID::ID_USER_LOGIN:
			if (code == 0) {
				std::cout << "获取返回结果" << data.toStdString() << std::endl;
				std::cout << " 用户登录成功！ " << std::endl;
				ServerInfo si;
				json response_json = json::parse(data.toStdString());
				si.Host = QString::fromStdString(response_json["host"]);
				si.Port = QString::fromStdString(response_json["port"]);
				si.Uid = QString::fromStdString(response_json["uid"]);
				si.Token = QString::fromStdString(response_json["token"]);
				qDebug() << "user is " << "user" << " uid is " << si.Uid << " host is "
					<< si.Host << " Port is " << si.Port << " Token is " << si.Token;
				TcpMgr::GetInstance()->slot_tcp_connect(si);
				///获取chatserver ip 以及 port
				///提示用户登录成功
				/// 
			}
			break;
		};
	}
}
void Controller::slotGetValidateCode(MODULE module, ID id) {
	if (module == MODULE_REGISTER && id == ID_REGISTER_GET_VALIDATE_CODE) {
		if (registerWindow_->judgeInfo()) {
			QString email = registerWindow_->registerEmail->lineEdit->text();
			QString user = registerWindow_->registerUser->lineEdit->text();
			nlohmann::json json;
			json["user"] = user.toStdString();
			json["email"] = email.toStdString();
			std::string url = "http://" + gConfigMgr["JammyGateServer"]["Ip"] + ":" + gConfigMgr["JammyGateServer"]["Port"] + "/get_varifycode_register";
			HttpManager::GetInstance()->postHttpRequest(QUrl(QString::fromStdString(url)), json, module, id);
		}
	}
	else if(module == MODULE_RESET_PASSWORD && id == ID_RESET_GET_VALIDATE_CODE) {
		if (resetPasswordWindow_->judgeResetInfoCanSendCode()) {
			QString email = resetPasswordWindow_->resetEmail->lineEdit->text();
			QString user = resetPasswordWindow_->resetUser->lineEdit->text();
			nlohmann::json json;
			json["email"] = email.toStdString();
			json["user"] = user.toStdString();
			std::string url = "http://" + gConfigMgr["JammyGateServer"]["Ip"] + ":" + gConfigMgr["JammyGateServer"]["Port"] + "/get_varifycode_reset";
			HttpManager::GetInstance()->postHttpRequest(QUrl(QString::fromStdString(url)), json, MODULE::MODULE_RESET_PASSWORD, ID::ID_RESET_GET_VALIDATE_CODE);
		}
	}

}

void Controller::slotRegistUser(){
	if (!registerWindow_->judgeRegistInfoComplete()) {
		return;
	}
	json request_json;
	request_json["email"] = registerWindow_->registerEmail->lineEdit->text().toStdString();
	request_json["user"] = registerWindow_->registerUser->lineEdit->text().toStdString();
	request_json["passwd"] = registerWindow_->registerPassword->lineEdit->text().toStdString();
	request_json["confirm"] = registerWindow_->registerConfirmPassword->lineEdit->text().toStdString();
	request_json["code"] = registerWindow_->registerValidateCodeEdit->text().toStdString();
	std::string url = "http://" + gConfigMgr["JammyGateServer"]["Ip"] + ":" + gConfigMgr["JammyGateServer"]["Port"] + "/user_register";
	HttpManager::GetInstance()->postHttpRequest(QString::fromStdString(url), request_json, MODULE::MODULE_REGISTER, ID::ID_USER_REGISTER);
	registerWindow_->updateMsgHint(nullptr, hintRegisterProcess, true);
	return;
}

void Controller::slotResetPassword() {
	if (!resetPasswordWindow_->judgeResetInfoComplete()) {
		return;
	}
	json request_json;
	request_json["email"] = resetPasswordWindow_->resetEmail->lineEdit->text().toStdString();
	request_json["user"] = resetPasswordWindow_->resetUser->lineEdit->text().toStdString();
	request_json["passwd"] = resetPasswordWindow_->resetPassword->lineEdit->text().toStdString();
	request_json["code"] = resetPasswordWindow_->resetValidateCodeEdit->text().toStdString();
	std::string url = "http://" + gConfigMgr["JammyGateServer"]["Ip"] + ":" + gConfigMgr["JammyGateServer"]["Port"] + "/user_reset_password";
	HttpManager::GetInstance()->postHttpRequest(QString::fromStdString(url), request_json, MODULE::MODULE_RESET_PASSWORD, ID::ID_RESET_PASSWORD);
	registerWindow_->updateMsgHint(nullptr, hintResetPasswordProcess, true);
	return;
}
void Controller::slotHideAndShow(QWidget* hideWidget, QWidget* showWidget) {
		QSize hideSize = hideWidget->size();
		QSize showSize = showWidget->size();
		QPoint center = QPoint(
			hideWidget->mapToGlobal(hideWidget->rect().topLeft()).x() + hideWidget->width()/2,
			hideWidget->mapToGlobal(hideWidget->rect().topLeft()).y() + hideWidget->height() / 2
		);
		
		QPoint newPos = center - QPoint(showSize.width() / 2, showSize.height() / 2);
		showWidget->move(QPoint(newPos));
		hideWidget->hide();
		
		showWidget->show();
		//showWidget->move(newPos);
		
}
void Controller::init(LoginWindow* loginWindow, RegisterWindow* registerWindow, RegisterSuccessHintWindow* registerSuccessHintWindow, ResetPasswordWindow* resetPasswordWindow) {
	this->loginWindow_ = loginWindow;
	this->registerWindow_ = registerWindow;
	this->registerSuccessHintWindow_ = registerSuccessHintWindow;
	this->resetPasswordWindow_ = resetPasswordWindow;
	loginWindow_->show();
	auto self = shared_from_this();
	///TCP连接成功后槽函数处理
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_con_success, this, &Controller::slotTcpConnect);
	///处理http请求连接
	QObject::connect(HttpManager::GetInstance().get(), &HttpManager::signalHttpFinish,this,&Controller::slotHttpFinished);
	///注册面板
	connect(registerWindow_->getValidateCodeBtn, &QPushButton::clicked, this, std::bind(&Controller::slotGetValidateCode,this,MODULE::MODULE_REGISTER,ID::ID_REGISTER_GET_VALIDATE_CODE));
    connect(registerWindow_->confirmBtn,&QPushButton::clicked,this,&Controller::slotRegistUser);
	///重置密码面板
	connect(resetPasswordWindow_->getValidateCodeBtn, &QPushButton::clicked, this, std::bind(&Controller::slotGetValidateCode, this, MODULE::MODULE_RESET_PASSWORD, ID::ID_RESET_GET_VALIDATE_CODE));
	connect(resetPasswordWindow_->confirmBtn, &QPushButton::clicked, this, &Controller::slotResetPassword);
	///登录面板
	connect(loginWindow_->loginBtn, &QPushButton::clicked, this, &Controller::slotUserLogin);
	///面板显示隐藏逻辑
	connect(loginWindow_->registerBtn, &QPushButton::clicked, std::bind(&Controller::slotHideAndShow, this, loginWindow_,registerWindow_));
	connect(loginWindow_->forgetPasswordBtn, &QPushButton::clicked, std::bind(&Controller::slotHideAndShow, this, loginWindow_, resetPasswordWindow_));
	connect(registerWindow_->cancelBtn, &QPushButton::clicked, std::bind(&Controller::slotHideAndShow, this, registerWindow_, loginWindow_));
	connect(registerSuccessHintWindow_, &RegisterSuccessHintWindow::signalReturnLoginWindow, std::bind(&Controller::slotHideAndShow, this, registerSuccessHintWindow_, loginWindow_));
	connect(resetPasswordWindow_->returnBtn, &QPushButton::clicked, std::bind(&Controller::slotHideAndShow, this, resetPasswordWindow_, loginWindow_));


}

void Controller::handleGetValidateCodeSuccess(MODULE module,QString data) {
	if (module == MODULE::MODULE_REGISTER) {
		nlohmann::json responseBody = nlohmann::json::parse(data.toStdString());
		if (responseBody.contains("error_code") && responseBody["error_code"] == 0) {
			registerWindow_->updateMsgHint(nullptr, hintGetValidateCodeSuccess, true);
		}
		std::cout << data.toStdString() << std::endl;
	}
	else if (module == MODULE::MODULE_RESET_PASSWORD) {
		nlohmann::json responseBody = nlohmann::json::parse(data.toStdString());
		if (responseBody.contains("error_code") && responseBody["error_code"] == 0) {
			resetPasswordWindow_->updateMsgHint(nullptr, hintGetValidateCodeSuccess, true);
		}
		std::cout << data.toStdString() << std::endl;
	}

}
void Controller::slotUserLogin() {
	if (!loginWindow_->judgeRegistInfoComplete()) {
		///界面提示错误信息
		return;
	}
	///调用http post 请求
	json request_json;
	request_json["user"] = loginWindow_->userEdit->text().toStdString();
	request_json["passwd"] = loginWindow_->passwordEdit->text().toStdString();
	std::string url = "http://" + gConfigMgr["JammyGateServer"]["Ip"] + ":" + gConfigMgr["JammyGateServer"]["Port"] + "/user_login";

	HttpManager::GetInstance()->postHttpRequest(QUrl(QString::fromStdString(url)), request_json, MODULE::MODULE_LOGIN, ID_USER_LOGIN);
	///界面提示正在登录中

}

void Controller::slotTcpConnect(bool success) {
	if (success) {
		//(tr("聊天服务连接成功，正在登录..."), true);
		//QJsonObject jsonObj;
		//jsonObj["uid"] = _uid;
		//jsonObj["token"] = _token;
		//QJsonDocument doc(jsonObj);
		//QString jsonString = doc.toJson(QJsonDocument::Indented);
		////发送tcp请求给chat server
		//TcpMgr::GetInstance()->sig_send_data(ReqId::ID_CHAT_LOGIN, jsonString);
	}
	else {
		//showTip(tr("网络异常"), false);
		//enableBtn(true);
	}
}