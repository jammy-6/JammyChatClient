#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include "ChatWindowGlobal.h"
#include "CustomTimerBtn.h"
#include "CustomerWidget.h"
#include "MoveableWidget.h"
#include <QLabel>
#include <QLineEdit>
#include <QMenu>

class Controller;
class CHAT_WINDOW_EXPORT RegisterWindow : public MoveableWidget {
	Q_OBJECT

public:
	explicit RegisterWindow(QWidget *parent = nullptr);
	void initUI();
	void initConnect();
	void updateMsgHint(QWidget *widget, QString hint, bool status);
	/// 用于判断用户所填入的信息是否有误
	bool judgeInfo();
	bool judgeRegistInfoComplete();
	~RegisterWindow();

protected:
	void paintEvent(QPaintEvent *event);

private:
	friend class Controller;

	QMenu contextMenu;
	QAction *reloadQssAction;
	QLabel *titleLabel;
	QLabel *msgHintLabel;

	CustomWidgetLabel_LineEdit *registerUser;
	CustomWidgetLabel_LineEdit *registerEmail;
	CustomWidgetLabel_LineEdit *registerPassword;
	QPushButton *registerPasswordVisible;
	CustomWidgetLabel_LineEdit *registerConfirmPassword;
	QPushButton *registerConfirmPasswordVisible;

	QLabel *registerValidateCodeLabel;
	QLineEdit *registerValidateCodeEdit;
	CustomTimerBtn *getValidateCodeBtn;

	QPushButton *confirmBtn;
	QPushButton *cancelBtn;
};

#endif
