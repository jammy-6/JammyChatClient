#ifndef REGISTERSUCCESSHINTWINDOW_H
#define REGISTERSUCCESSHINTWINDOW_H

#include "ChatWindowGlobal.h"
#include "MoveableWidget.h"
#include <QLabel>
#include <QPushButton>
class CHAT_WINDOW_EXPORT RegisterSuccessHintWindow : public MoveableWidget {
	Q_OBJECT

public:
	explicit RegisterSuccessHintWindow(QWidget *parent = nullptr);
	void initUI();
	void initConnect();
	~RegisterSuccessHintWindow();

protected:
	void paintEvent(QPaintEvent *event) override;
	void showEvent(QShowEvent *event) override;
	void hideEvent(QHideEvent *event) override;
signals:
	void signalReturnLoginWindow();

private:
	QLabel *titleLabel;
	QLabel *hintLabel;
	QPushButton *returnBtn;
	QTimer *timer_;
};

#endif // !1
