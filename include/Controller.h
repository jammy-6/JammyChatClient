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
	/// ͨ�ý�����ת�ۺ���
	void slotHideAndShow(QWidget* hideWidget, QWidget* showWidget);
	/// TcpMgr�����ӷ������ۺ���
	void slotTcpConnect(bool success);
	/// http��Ӧ�ۺ���
	void slotHttpFinished(MODULE module, ID id, ERRORCODE code, QString data);
	/// ע���������������ȡ��֤��ۺ���
	void slotGetValidateCode(MODULE module, ID id);
	/// �û�ע�����ۺ���
    void slotRegistUser();
	/// �����������ۺ���
	void slotResetPassword();
	///��¼���ۺ���
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