#ifndef RESETPASSWORDWINDOW_H
#define RESETPASSWORDWINDOW_H

#include "CustomTimerBtn.h"
#include "CustomerWidget.h"
#include "MoveableWidget.h"
#include <ChatWindowGlobal.h>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>

class Controller;
class CHAT_WINDOW_EXPORT ResetPasswordWindow : public MoveableWidget {
	Q_OBJECT

public:
	explicit ResetPasswordWindow(QWidget *parent = nullptr);
	void initUI();
	void initConnect();
	void updateMsgHint(QWidget *widget, QString hint, bool status);
	/// 用于判断用户所填入的信息是否有误
	bool judgeInfo();
	bool judgeResetInfoComplete();
	/// 判断当前所填入信息是否可以发送验证码
	bool judgeResetInfoCanSendCode();
	/// 禁用当前控件下所有按钮
	void disableAllBtn(bool status);
	~ResetPasswordWindow();

protected:
	void paintEvent(QPaintEvent *event);

private:
	friend class Controller;

	QMenu contextMenu;
	QAction *reloadQssAction;
	QLabel *titleLabel;
	QLabel *msgHintLabel;

	CustomWidgetLabel_LineEdit *resetUser;
	CustomWidgetLabel_LineEdit *resetEmail;

	QLabel *resetValidateCodeLabel;
	QLineEdit *resetValidateCodeEdit;
	CustomTimerBtn *getValidateCodeBtn;

	CustomWidgetLabel_LineEdit *resetPassword;
	QPushButton *resetPasswordVisible;

	QPushButton *confirmBtn;
	QPushButton *returnBtn;
};

#endif
