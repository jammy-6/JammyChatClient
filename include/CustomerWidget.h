#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H
#pragma execution_character_set("utf-8")

#include "ChatWindowGlobal.h"
#include <QLabel>
#include <QLayout>
#include <QLineEdit>

class CHAT_WINDOW_EXPORT CustomWidgetLabel_LineEdit : public QWidget {
	Q_OBJECT
public:
	CustomWidgetLabel_LineEdit(QWidget *parent = nullptr);
	QHBoxLayout *mainLayout;
	QLabel *label;
	QLineEdit *lineEdit;
};

class CHAT_WINDOW_EXPORT MsgItemWidget : public QWidget {
	Q_OBJECT
public:
	MsgItemWidget(QWidget *parent);
	/// 提供4个用于设置成员的接口
	void setTimeLabel(QString time);
	void setIconLabel(QString iconPath);
	void setType(int type);
	void setMsgLabel(QString msg);

private:
	int type_; /// 0代表自己发的消息，1代表别人发的消息
	QLabel *timeLabel_;
	QLabel *iconLabel_;
	QLabel *msgLabel_;
};
class CHAT_WINDOW_EXPORT FriendItemWidget : public QWidget {
	Q_OBJECT
public:
	FriendItemWidget(QWidget *parent);
	/// 提供4个用于设置成员的接口
	void setIconLabel(QString iconPath);
	void setNameLabel(QString name);
	void setMsgLabel(QString msg);
	void setTimeLabel(QString time);

private:
	QLabel *iconLabel_;
	QLabel *nameLabel_;
	QLabel *msgLabel_;
	QLabel *timeLabel_;
};

#endif
