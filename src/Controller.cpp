#pragma execution_character_set("utf-8")

#include "Controller.h"
#include <QPushButton>
#include "Global.h"
#include "ConfigMgr.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
Controller::~Controller() {

}
Controller::Controller() {

	
}

void Controller::slotHttpFinished(MODULE module, ID id, ERRORCODE code, QString data) {
	if (code == ERRORCODE::SUCCESS) {
        std::cout<<"Http Success : "<<data.toStdString()<<std::endl;
		switch (id) {
		case ID::ID_GET_VALIDATE_CODE: ///验证码获取成功
            std::cout<<" 获取验证码成功！ "<<std::endl;
			this->handleGetValidateCodeSuccess(data);
			break;
		case ID::ID_USER_REGISTER:

			if (code == 0) {
				std::cout << "获取返回结果" << data.toStdString() << std::endl;
				std::cout << " 用户注册成功！ " << std::endl;
				registerWindow_->updateMsgHint(nullptr, hintRegisterSuccess, true);
			}
			break;
		};
	}
}
void Controller::slotGetValidateCode() {
	if (registerWindow_->judgeInfo()) {
		QString email = registerWindow_->registerEmail->lineEdit->text();
		nlohmann::json json;
		json["email"] = email.toStdString();
		std::string url = "http://" + gConfigMgr["JammyGateServer"]["Ip"]+":"+ gConfigMgr["JammyGateServer"]["Port"] +"/get_varifycode" ;
		HttpManager::GetInstance()->postHttpRequest(QUrl(QString::fromStdString(url)), json, MODULE::MOUDLE_REGISTER, ID::ID_GET_VALIDATE_CODE);
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
	HttpManager::GetInstance()->postHttpRequest(QString::fromStdString(url), request_json, MODULE::MOUDLE_REGISTER, ID::ID_USER_REGISTER);
	registerWindow_->updateMsgHint(nullptr, hintRegisterProcess, true);
	return;
}

void Controller::init(LoginWindow* loginWindow, RegisterWindow* registerWindow) {
	this->loginWindow_ = loginWindow;
	this->registerWindow_ = registerWindow;

	auto self = shared_from_this();
	///处理http请求连接
	QObject::connect(HttpManager::GetInstance().get(), &HttpManager::signalHttpFinish,this,&Controller::slotHttpFinished);
	///连接获取验证码信号槽
	connect(registerWindow_->getValidateCodeBtn, &QPushButton::clicked, this, &Controller::slotGetValidateCode);
    connect(registerWindow_->confirmBtn,&QPushButton::clicked,this,&Controller::slotRegistUser);
}

void Controller::handleGetValidateCodeSuccess(QString data) {
	nlohmann::json responseBody = nlohmann::json::parse(data.toStdString());
	if (responseBody.contains("error_code")&& responseBody["error_code"]==0) {
		registerWindow_->updateMsgHint(nullptr, hintGetValidateCodeSuccess, true);
	}
	std::cout << data.toStdString()<<std::endl;
}
