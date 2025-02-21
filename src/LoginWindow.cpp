#pragma execution_character_set("utf-8")
#include "LoginWindow.h"
#include <QPainter>
#include <QSpacerItem>
#include <QStyleOption>
#include <QVBoxLayout>
#include <qpushbutton.h>
LoginWindow::LoginWindow(QWidget *parent) : MoveableWidget(parent) {
	initUI();
	initConnect();
}

void LoginWindow::initConnect() {
}
void LoginWindow::initUI() {
	this->setObjectName("loginWindow");
	this->setAttribute(Qt::WA_TranslucentBackground, true);
	// 设置无边框
	this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	QVBoxLayout *mainLayout = new QVBoxLayout;
	this->setLayout(mainLayout);
	this->setFixedWidth(300);
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->setContentsMargins(8, 16, 8, 16);
	/// 标题
	titleLabel = new QLabel;
	titleLabel->setObjectName("titleLabel");
	titleLabel->setText(QString("Jammy通信客户端"));
	mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
	msgHintLabel = new QLabel;
	msgHintLabel->setObjectName("msgHintLabel");
	msgHintLabel->setText(QString(""));
	mainLayout->addWidget(msgHintLabel, 0, Qt::AlignHCenter);

	QSpacerItem *titleSpacer = new QSpacerItem(284, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
	mainLayout->addItem(titleSpacer);
	/// 图片
	titlePhotoLabel = new QLabel;
	titlePhotoLabel->setObjectName("titlePhotoLabel");
	titlePhotoLabel->setFixedSize(250, 291);
	mainLayout->addWidget(titlePhotoLabel, 0, Qt::AlignHCenter);

	/// 用户栏
	QHBoxLayout *userLayout = new QHBoxLayout;
	userLayout->setSpacing(4);
	userLayout->setSizeConstraint(QLayout::SetFixedSize);
	userLabel = new QLabel;
	userLabel->setObjectName("userLabel");
	userLabel->setText(QString("用户:"));
	userLabel->setFixedSize(userLabel->sizeHint().width(), 30);
	userLayout->addWidget(userLabel);
	userEdit = new QLineEdit;
	userEdit->setObjectName("userEdit");
	userEdit->setFixedSize(200, 30);
	userLayout->addWidget(userEdit);
	mainLayout->addLayout(userLayout);
	/// 密码栏
	QHBoxLayout *passwordLayout = new QHBoxLayout;
	passwordLayout->setSpacing(4);
	passwordLayout->setSizeConstraint(QLayout::SetFixedSize);
	passwordLabel = new QLabel;
	passwordLabel->setObjectName("passwordLabel");
	passwordLabel->setText(QString("密码:"));
	passwordLabel->setFixedSize(passwordLabel->sizeHint().width(), 30);
	passwordLayout->addWidget(passwordLabel);
	passwordEdit = new QLineEdit;
	passwordEdit->setObjectName("passwordEdit");
	passwordEdit->setFixedSize(200, 30);
	passwordLayout->addWidget(passwordEdit);
	mainLayout->addLayout(passwordLayout);

	/// 忘记密码
	forgetPasswordBtn = new QPushButton;
	forgetPasswordBtn->setObjectName("forgetPasswordBtn");
	forgetPasswordBtn->setText(QString("忘记密码"));
	forgetPasswordBtn->setFixedSize(forgetPasswordBtn->sizeHint());
	mainLayout->addWidget(forgetPasswordBtn, 0, Qt::AlignRight);

	/// 登录以及注册按钮
	loginBtn = new QPushButton;
	loginBtn->setObjectName(QString("loginBtn"));
	loginBtn->setText(QString("登录"));
	loginBtn->setFixedSize(loginBtn->sizeHint().width(), 30);
	mainLayout->addWidget(loginBtn, 0, Qt::AlignHCenter);
	registerBtn = new QPushButton;
	registerBtn->setObjectName(QString("registerBtn"));
	registerBtn->setText(QString("注册"));
	registerBtn->setFixedSize(registerBtn->sizeHint().width(), 30);
	mainLayout->addWidget(registerBtn, 0, Qt::AlignHCenter);

	// 创建一个新的QAction
	reloadQssAction = new QAction(tr("Reload QSS"), this);
	// 添加QAction到右键菜单
	contextMenu.addAction(reloadQssAction);
}

void LoginWindow::updateMsgHint(QWidget *widget, QString hint, bool status) {
	/// 这里的widget参数暂时没用到，可能以后会用到，先留着
	if (status) {
		msgHintLabel->setProperty("status", QString("normal"));
	} else {
		msgHintLabel->setProperty("status", QString("error"));
	}
	msgHintLabel->style()->unpolish(msgHintLabel);
	msgHintLabel->style()->polish(msgHintLabel);
	msgHintLabel->setText(hint);
}
void LoginWindow::paintEvent(QPaintEvent *event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

bool LoginWindow::judgeRegistInfoComplete() {
	if (userEdit->text().isEmpty()) {
		return false;
	}
	if (passwordEdit->text().isEmpty()) {
		return false;
	}
	return true;
}
LoginWindow::~LoginWindow() {
}
