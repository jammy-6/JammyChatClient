#include "Controller.h"

Controller::~Controller() {

}
Controller::Controller() {

}
void Controller::init(LoginWindow* loginWindow, RegisterWindow* registerWindow) {
	this->loginWindow_ = loginWindow;
	this->registerWindow_ = registerWindow;

	auto self = shared_from_this();
	///����http��������
	QObject::connect(HttpManager::GetInstance().get(), &HttpManager::signalHttpFinish, [self](MOUDLE module, ID id, ERRORCODE code, QString data) {
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
}

void Controller::handleGetValidateCodeSuccess(QString data) {

}
