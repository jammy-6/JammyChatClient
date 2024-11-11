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
	allHanlders_[ID_REGISTER_GET_VALIDATE_CODE] 
		= std::bind(&Controller::handleRegisterGetValideCode,this,std::placeholders::_1);
	allHanlders_[ID_RESET_GET_VALIDATE_CODE]
		= std::bind(&Controller::handleResetPasswordGetValideCode, this, std::placeholders::_1);
	allHanlders_[ID_RESET_PASSWORD]
		= std::bind(&Controller::handleResetPassword, this, std::placeholders::_1);
	allHanlders_[ID_USER_REGISTER]
		= std::bind(&Controller::handleUserRegister, this, std::placeholders::_1);

	allHanlders_[ID_REGISTER_GET_VALIDATE_CODE]
		= std::bind(&Controller::handleRegisterGetValideCode, this, std::placeholders::_1);
	
}

void Controller::slotHttpFinished(MODULE module, ID id, ERRORCODE code, QString data) {
	if (code == ERRORCODE::SUCCESS) {
		qDebug() << "HTTP请求成功返回，数据为: " << data;
		nlohmann::json responseJson = nlohmann::json::parse(data.toStdString());
		///回调函数进行处理
		allHanlders_[id](responseJson);
	}
	else {
		qDebug() << "HTTP请求失败，数据为: " << data;
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
		registerWindow_->updateMsgHint(nullptr, hintResetPasswordImformationNotComplete, false);
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
	connect(TcpMgr::GetInstance().get(), &TcpMgr::sig_recv_data, this, &Controller::slotTcpRecvMsg);

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
void Controller::slotTcpRecvMsg(MSG_IDS reqId, QString data) {
	qDebug() << "接收到来自TCPMgr提取出来的消息：id =" << (int)reqId << ", data = " << data;
}
void Controller::slotTcpConnect(bool success) {
	if (success) {
		//(tr("聊天服务连接成功，正在登录..."), true);
		loginWindow_->updateMsgHint(nullptr, hintConnectChatServerSuccess, true);
		json responseJson;
		responseJson["uid"] = connectChatServer.Uid.toStdString();
		responseJson["token"] = connectChatServer.Token.toStdString();
		////发送tcp请求给chat server
		TcpMgr::GetInstance()->sig_send_data(MSG_IDS::MSG_LOGIN, QString::fromStdString(responseJson.dump()));
	}
	else {
		loginWindow_->updateMsgHint(nullptr, hintConnectChatServerFailed, false);
	}
}

void Controller::handleRegisterGetValideCode(nlohmann::json responseJson) {
	int errorcode = responseJson["error_code"];
	if (errorcode != ERRORCODE::SUCCESS) {
		qDebug() << "注册模块：获取验证码失败，错误码为" << errorcode;
		registerWindow_->updateMsgHint(nullptr, "验证码获取失败", false);
		return;
	}
	qDebug() << "注册模块：获取验证码成功！";
	registerWindow_->updateMsgHint(nullptr, hintGetValidateCodeSuccess, true);
}

void Controller::handleResetPasswordGetValideCode(nlohmann::json responseJson) {
	int errorcode = responseJson["error_code"];
	if (errorcode != ERRORCODE::SUCCESS) {
		qDebug() << "重置密码模块：获取验证码失败，错误码为" << errorcode;
		resetPasswordWindow_->updateMsgHint(nullptr, "验证码获取失败", false);
		return;
	}
	qDebug() << "重置密码模块：获取验证码成功！";
	resetPasswordWindow_->updateMsgHint(nullptr, hintGetValidateCodeSuccess, true);
}

void Controller::handleUserRegister(nlohmann::json responseJson) {
	int errorcode = responseJson["error_code"];
	if (errorcode != ERRORCODE::SUCCESS) {
		qDebug() << "注册模块：用户注册失败，错误码为" << errorcode;
		registerWindow_->updateMsgHint(nullptr, "用户注册失败", false);
		return;
	}
	qDebug() << "注册模块：用户注册成功！";
	registerWindow_->updateMsgHint(nullptr, hintRegisterSuccess, true);
	slotHideAndShow(registerWindow_, registerSuccessHintWindow_);
}

void Controller::handleResetPassword(nlohmann::json responseJson) {
	int errorcode = responseJson["error_code"];
	if (errorcode != ERRORCODE::SUCCESS) {
		qDebug() << " 用户重置密码失败，错误码为！ " << errorcode;
		resetPasswordWindow_->updateMsgHint(nullptr, hintResetPasswordFailedReturn, false);
		return;
	}else{
		qDebug() << " 用户重置密码成功！ ";
		qDebug() << "获取返回结果" << QString::fromStdString(responseJson.dump());
		resetPasswordWindow_->updateMsgHint(nullptr, hintResetPasswordSuccessReturn, true);
	}
}

void Controller::handleUserLogin(nlohmann::json responseJson) {
	ServerInfo si;
	int errorcode = responseJson["error_code"];
	QString data = QString::fromStdString(responseJson.dump());
	if (errorcode != ERRORCODE::SUCCESS) {
		qDebug() << "用户登录失败，错误码为！ " << errorcode;
		loginWindow_->updateMsgHint(nullptr, hintResetPasswordFailedReturn, false);
		return;
	}
	else {
		qDebug() << "用户登录成功，响应数据为：" << data;
		si.Host = QString::fromStdString(responseJson.at("host").get<std::string>());
		si.Port = QString::fromStdString(responseJson.at("port").get<std::string>());
		si.Uid = QString::fromStdString(responseJson.at("uid").get<std::string>());
		si.Token = QString::fromStdString(responseJson.at("token").get<std::string>());
		///提示用户获取聊天服务器IP及PORT成功
		loginWindow_->updateMsgHint(nullptr, hintGetChatServerFailed, true);
		connectChatServer = si;
		TcpMgr::GetInstance()->slot_tcp_connect(connectChatServer);
	}

}