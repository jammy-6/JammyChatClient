#ifndef Controller_H
#define Controller_H


#include "Global.h"
#include "Singleton.h"
#include <memory>
#include <QObject>
#include "LoginWindow.h"
#include "HttpManager.h"
#include "RegisterWindow.h"
class Controller: public QObject,public Singleton<Controller>,public enable_shared_from_this<Controller> {
	Q_OBJECT
public:
	
	~Controller();
	void init(LoginWindow* loginWindow, RegisterWindow* registerWindow);
	void handleGetValidateCodeSuccess(QString data);
private:
	friend class Singleton<Controller>;
	Controller();
	LoginWindow* loginWindow_;
	RegisterWindow* registerWindow_;
};
#endif // !Controller_H