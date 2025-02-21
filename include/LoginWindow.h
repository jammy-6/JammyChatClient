#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "ChatWindowGlobal.h"
#include <MoveableWidget.h>
#include <QLabel>
#include <QMenu>
#include <qlineedit.h>
#include <qpushbutton.h>
class Controller;

class CHAT_WINDOW_EXPORT LoginWindow : public MoveableWidget {
	Q_OBJECT

public:
	explicit LoginWindow(QWidget *parent = nullptr);
	void initUI();
	void initConnect();
	~LoginWindow();
	bool judgeRegistInfoComplete();
	void updateMsgHint(QWidget *widget, QString hint, bool status);

protected:
	void paintEvent(QPaintEvent *event) override;

private:
	bool m_dragging = false;
	QPoint m_dragPosition;

private:
	friend class Controller;
	QMenu contextMenu;
	QAction *reloadQssAction;
	QLabel *titleLabel;
	QLabel *msgHintLabel;
	QLabel *titlePhotoLabel;
	QLabel *userLabel;
	QLineEdit *userEdit;
	QLabel *passwordLabel;
	QLineEdit *passwordEdit;
	QPushButton *forgetPasswordBtn;
	QPushButton *loginBtn;
	QPushButton *registerBtn;
};

#endif
