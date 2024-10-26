#pragma execution_character_set("utf-8")

#include "Controller.h"
#include <QPushButton>
#include "Global.h"
Controller::~Controller() {

}
Controller::Controller() {

	
}

void Controller::slotGetValidateCode() {
	if (registerWindow_->judgeInfo()) {
		QString email = registerWindow_->registerEmail->lineEdit->text();
		nlohmann::json json;
		json["email"] = email.toStdString();
		HttpManager::GetInstance()->postHttpRequest(QUrl("http://192.168.0.205:8080/get_varifycode"), json, MODULE::MOUDLE_REGISTER, ID::ID_GET_VALIDATE_CODE);
	}

}
void Controller::init(LoginWindow* loginWindow, RegisterWindow* registerWindow) {
	this->loginWindow_ = loginWindow;
	this->registerWindow_ = registerWindow;

	auto self = shared_from_this();
	///����http��������
	QObject::connect(HttpManager::GetInstance().get(), &HttpManager::signalHttpFinish, [self](MODULE module, ID id, ERRORCODE code, QString data) {
		if (code == ERRORCODE::SUCCESS) {
			switch (id) {
			case ID::ID_GET_VALIDATE_CODE: ///��֤���ȡ�ɹ�
				self->handleGetValidateCodeSuccess(data);
				break;
			case ID::ID_USER_REGISTER:
				
				break;
			};
		}
	});
	///���ӻ�ȡ��֤���źŲ�
	connect(registerWindow_->getValidateCodeBtn, &QPushButton::clicked, this, &Controller::slotGetValidateCode);
}

void Controller::handleGetValidateCodeSuccess(QString data) {
	nlohmann::json responseBody = nlohmann::json::parse(data.toStdString());
	if (responseBody.contains("error")&& responseBody["error"]==0) {
		registerWindow_->updateMsgHint(nullptr,QString( "��ȡ��֤��ɹ���"), true);
	}
	std::cout << data.toStdString()<<std::endl;

}
