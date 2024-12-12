﻿#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H
#pragma execution_character_set("utf-8")
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QList>
#include <QLabel>
#include <QContextMenuEvent>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>
#include <QDate>
#include <QHttpMultiPart>
#include <QPainter>
#include <QPen>

#include <QScrollArea>
#include <algorithm>
#include <QTimer>
#include <QMutex>
#include <functional>
#include <QColor>
#include <QFrame>
#include <QApplication>
#include <QLayout>
#include <QLineEdit>
class CustomWidgetLabel_LineEdit : public QWidget {
    Q_OBJECT
public:
    CustomWidgetLabel_LineEdit(QWidget*parent = nullptr):QWidget(parent) {
        mainLayout = new QHBoxLayout;
        mainLayout->setSpacing(4);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel;
        label->setFixedHeight(30);
        lineEdit = new QLineEdit;
        lineEdit->setFixedHeight(30);
        mainLayout->addWidget(label);
        mainLayout->addWidget(lineEdit);
        this->setLayout(mainLayout);
    }
    QHBoxLayout* mainLayout;
    QLabel *label;
    QLineEdit *lineEdit;
};

class MsgItemWidget :public QWidget {
    Q_OBJECT
public:
    MsgItemWidget(QWidget* parent = nullptr) :QWidget(parent) {
		QHBoxLayout* mainLayout = new QHBoxLayout;
		mainLayout->setSpacing(5);
		mainLayout->setContentsMargins(0, 10,0, 10);
		mainLayout->setSizeConstraint(QLayout::SetFixedSize);
		this->setLayout(mainLayout);

		QVBoxLayout* leftLayout = new QVBoxLayout;
		leftLayout->setSpacing(0);
        leftLayout->setContentsMargins(0, 0, 0, 0);
		leftLayout->setSizeConstraint(QLayout::SetFixedSize);
		timeLabel_ = new QLabel;
		timeLabel_->setFixedSize(40, 15);
		iconLabel_ = new QLabel;
        iconLabel_->setFixedSize(40, 40);
		msgLabel_ = new QLabel;
        msgLabel_->setWordWrap(true);
		msgLabel_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

		leftLayout->addWidget(timeLabel_,Qt::AlignVCenter);
		leftLayout->addWidget(iconLabel_, Qt::AlignVCenter);

		mainLayout->addLayout(leftLayout);
		mainLayout->addWidget(msgLabel_, Qt::AlignRight);
		timeLabel_->setText(QString("17:12"));
        QPixmap pixmap(":/UserHeadIcon/head_1.jpg");
        // 检查 QPixmap 是否成功加载图像
        if (pixmap.isNull()) {
            qDebug() << "Failed to load image";
        }
        iconLabel_->setPixmap(pixmap);

        // 可选：调整 QLabel 大小以适应图像
        iconLabel_->setScaledContents(true);
        //iconLabel_->setStyleSheet(QString::fromStdString("border-image:url(:/UserHeadIcon/head_1.jpg);"));
		msgLabel_->setText(QString("你好aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	}
    ///提供4个用于设置成员的接口
	void setTimeLabel(QString time) {
		timeLabel_->setText(time);
	}
	void setIconLabel(QString iconPath) {
		iconLabel_->setStyleSheet(QString("border-image:url(%1);").arg(iconPath));
	}
    void setType(int type) {
		type_ = type;
    }
	void setMsgLabel(QString msg) {
		msgLabel_->setText(msg);
	}
private:
	int type_;///0代表自己发的消息，1代表别人发的消息
	QLabel* timeLabel_;
	QLabel* iconLabel_;
	QLabel* msgLabel_;
};
class FriendItemWidget :public QWidget {
    Q_OBJECT
public:
    FriendItemWidget(QWidget* parent = nullptr):QWidget(parent) {
        QHBoxLayout* mainLayout = new QHBoxLayout;
        mainLayout->setSpacing(20);
        mainLayout->setContentsMargins(20, 20, 20, 20);
        mainLayout->setSizeConstraint(QLayout::SetFixedSize);
        this->setFixedHeight(90);
        this->setLayout(mainLayout);
        iconLabel_ = new QLabel;
        iconLabel_->setFixedSize(50, 50);
		///往iconLabel_中添加头像
        setIconLabel(":/UserHeadIcon/head_1.jpg");
        QHBoxLayout *nameAndTimeLayout = new QHBoxLayout;
        nameAndTimeLayout->setSpacing(10);
        nameAndTimeLayout->setContentsMargins(0, 0, 0, 0);
        nameAndTimeLayout->setSizeConstraint(QLayout::SetFixedSize);
        
        nameLabel_ = new QLabel;
        nameLabel_->setFixedSize(160,20);
        timeLabel_ = new QLabel;
        timeLabel_->setFixedSize(50,20);
        nameAndTimeLayout->addWidget(nameLabel_, Qt::AlignLeft);
        nameAndTimeLayout->addWidget(timeLabel_, Qt::AlignRight);

        QVBoxLayout* rightLayout = new QVBoxLayout;
        rightLayout->setSpacing(10);
        rightLayout->setContentsMargins(0, 0, 30, 0);
        rightLayout->setSizeConstraint(QLayout::SetFixedSize);
        msgLabel_ = new QLabel;
        msgLabel_->setFixedSize(220, 20);

        rightLayout->addLayout(nameAndTimeLayout);
        rightLayout->addWidget(msgLabel_);

        mainLayout->addWidget(iconLabel_,Qt::AlignLeft);
        mainLayout->addLayout(rightLayout, Qt::AlignRight);

        nameLabel_->setText(QString("蔡大猫"));
        msgLabel_->setText(QString("你好"));
        timeLabel_->setText(QString("17:12"));

    }
    ///提供4个用于设置成员的接口
	void setIconLabel(QString iconPath) {
        QPixmap pixmap(iconPath);
        // 检查 QPixmap 是否成功加载图像
        if (pixmap.isNull()) {
            qDebug() << "Failed to load image";
        }
        iconLabel_->setPixmap(pixmap);

        // 可选：调整 QLabel 大小以适应图像
        iconLabel_->setScaledContents(true);
	}
	void setNameLabel(QString name) {
		nameLabel_->setText(name);
	}
	void setMsgLabel(QString msg) {
		msgLabel_->setText(msg);
	}
	void setTimeLabel(QString time) {
		timeLabel_->setText(time);
	}

private:
    QLabel* iconLabel_;
    QLabel* nameLabel_;
    QLabel* msgLabel_;
    QLabel* timeLabel_;
};

#endif 
