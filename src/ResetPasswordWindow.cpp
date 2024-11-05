#pragma execution_character_set("utf-8")
#include <QVBoxLayout>
#include "ResetPasswordWindow.h"
#include <qpushbutton.h>
#include <Config.h>
#include <QSpacerItem>
#include <QStyleOption>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>

ResetPasswordWindow::ResetPasswordWindow(QWidget *parent) :
    MoveableWidget(parent)
{
    initUI();
    initConnect();
    reloadQss();
}

void ResetPasswordWindow::initConnect() {
    // 连接QAction的triggered信号到一个槽函数
    connect(reloadQssAction, &QAction::triggered, this, &ResetPasswordWindow::reloadQss);
    ///邮箱输入格式验证
    connect(resetEmail->lineEdit, &QLineEdit::textChanged, [=](const QString& text) {
        QRegularExpression regex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
        // 使用正则表达式匹配 email
        QRegularExpressionMatch match = regex.match(text);
        if (match.hasMatch()) {
            updateMsgHint(resetEmail->lineEdit, "", true);
            getValidateCodeBtn->setEnabled(true);
        }
        else {
            updateMsgHint(resetEmail->lineEdit, errorMailFormat, false);
            getValidateCodeBtn->setEnabled(false);
        }
     });
}

bool ResetPasswordWindow::judgeInfo() {
    if (msgHintLabel->property("status") == "error") {
        return false;
    }
    else if(msgHintLabel->property("status") == "normal"){
        return true;
    }
    return false;
}

bool ResetPasswordWindow::judgeResetInfoComplete() {
    if (resetUser->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserNameEmpty, false);
        return false;
    }
    if (resetEmail->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserEmailEmpty, false);
        return false;
    }
    if (resetPassword->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserPasswordEmpty, false);
        return false;
    }
    if (resetValidateCodeEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserValidateCodeEmpty, false);
        return false;
    }


    return judgeInfo();

}
bool ResetPasswordWindow::judgeResetInfoCanSendCode() {
    if (resetUser->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserNameEmpty, false);
        return false;
    }
    if (resetEmail->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserEmailEmpty, false);
        return false;
    }
    return judgeInfo();
}

void ResetPasswordWindow::initUI() {
    this->setObjectName("resetPasswordWindow");
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setFixedWidth(350);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(8, 16, 8, 16);
    
    QSpacerItem* titleSpacer = new QSpacerItem(334, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(titleSpacer);

    titleLabel = new QLabel;
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText(QString("Jammy用户重置密码"));
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    ///错误提示
    msgHintLabel = new QLabel;
    msgHintLabel->setObjectName("msgHintLabel");
    
    mainLayout->addWidget(msgHintLabel, 0, Qt::AlignHCenter);

    ///用户
    resetUser = new CustomWidgetLabel_LineEdit;
    resetUser->label->setObjectName("resetUserLabel");
    resetUser->lineEdit->setObjectName("resetUserEdit");
    resetUser->label->setText(QString("用户："));
    mainLayout->addWidget(resetUser,0,Qt::AlignHCenter);
    ///邮箱
    resetEmail = new CustomWidgetLabel_LineEdit;
    resetEmail->label->setObjectName("resetEmailLabel");
    resetEmail->lineEdit->setObjectName("resetEmailEdit");
    resetEmail->label->setText(QString("邮箱："));
    mainLayout->addWidget(resetEmail, 0, Qt::AlignHCenter);
    ///密码
    resetPassword = new CustomWidgetLabel_LineEdit;
    resetPassword->label->setObjectName("resetPasswordLabel");
    resetPassword->lineEdit->setObjectName("resetPasswordEdit");
    resetPassword->label->setText(QString("新密码："));
    resetPassword->lineEdit->setEchoMode(QLineEdit::Password);
    resetPasswordVisible = new QPushButton;
    resetPasswordVisible->setObjectName("resetPasswordVisible");
    resetPasswordVisible->setFixedSize(30, 30);
    resetPasswordVisible->setCheckable(true);
    connect(resetPasswordVisible, &QPushButton::toggled, [this](bool checked) {
        if (checked) {
            resetPassword->lineEdit->setEchoMode(QLineEdit::Normal);
        }
        else {
            resetPassword->lineEdit->setEchoMode(QLineEdit::Password);
        }
        });
    resetPassword->lineEdit->setFixedWidth(
        resetPassword->lineEdit->sizeHint().width() - resetPasswordVisible->size().width() - resetPassword->layout()->spacing()
    );
    resetPassword->mainLayout->addWidget(resetPasswordVisible);
    QSpacerItem* rightPushSpacerItem1 = new QSpacerItem(
        resetPassword->label->sizeHint().width() - resetUser->label->sizeHint().width()
        , 30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    resetPassword->mainLayout->addItem(rightPushSpacerItem1);

    mainLayout->addWidget(resetPassword, 0, Qt::AlignHCenter);

    ///验证码
    QWidget* validateWidget = new QWidget;
    QHBoxLayout* validateCodeLayout = new QHBoxLayout;
    validateWidget->setLayout(validateCodeLayout);
    validateCodeLayout->setSpacing(4);
    validateCodeLayout->setContentsMargins(0, 0, 0, 0);
    validateCodeLayout->setSizeConstraint(QLayout::SetFixedSize);
    resetValidateCodeLabel = new QLabel;
    resetValidateCodeLabel->setObjectName("resetValidateCodeLabel");
    resetValidateCodeLabel->setText(QString("验证码："));
    resetValidateCodeLabel->setFixedWidth(resetValidateCodeLabel->sizeHint().width());
    validateCodeLayout->addWidget(resetValidateCodeLabel);
    resetValidateCodeEdit = new QLineEdit;
    resetValidateCodeEdit->setObjectName("resetValidateCodeEdit");
    validateCodeLayout->addWidget(resetValidateCodeEdit);
    getValidateCodeBtn = new CustomTimerBtn;
    getValidateCodeBtn->setText(QString("获取"));
    getValidateCodeBtn->setFixedWidth(60);
    getValidateCodeBtn->setObjectName("getValidateCodeBtn");
    getValidateCodeBtn->setEnabled(false);
    validateCodeLayout->addWidget(getValidateCodeBtn);
    resetValidateCodeEdit->setFixedSize(resetValidateCodeEdit->sizeHint().width()- getValidateCodeBtn->width()- validateCodeLayout->spacing(), 30);
    QSpacerItem* rightPushSpacerItem2 = new QSpacerItem(
        resetValidateCodeLabel->sizeHint().width() - resetUser->label->sizeHint().width()
        , 30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    validateCodeLayout->addItem(rightPushSpacerItem2);
    mainLayout->addWidget(validateWidget,0,Qt::AlignHCenter);


    ///确认及取消
    QWidget* confirmAndCancelWidget = new QWidget;
    QHBoxLayout *confirmAndCancelLayout = new QHBoxLayout;
    confirmAndCancelLayout->setContentsMargins(0, 0, 0, 0);
    confirmAndCancelLayout->setSpacing(8);
    confirmAndCancelWidget->setLayout(confirmAndCancelLayout);
    confirmBtn = new QPushButton;
    confirmBtn->setObjectName("confirmBtn");
    confirmBtn->setText(QString("确认"));
    confirmBtn->setFixedWidth(60);
    confirmAndCancelLayout->addWidget(confirmBtn);
    returnBtn = new QPushButton;
    returnBtn->setObjectName("returnBtn");
    returnBtn->setText(QString("返回"));
    returnBtn->setFixedWidth(60);
    confirmAndCancelLayout->addWidget(returnBtn);
    mainLayout->addWidget(confirmAndCancelWidget,0, Qt::AlignHCenter);

    ///尾部加一些间隔更美观
    QSpacerItem* tailSpacer = new QSpacerItem(334, 30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(tailSpacer);

    // 创建一个新的QAction
    reloadQssAction = new QAction(tr("Reload QSS"), this);
    // 添加QAction到右键菜单
    contextMenu.addAction(reloadQssAction);

}
void ResetPasswordWindow::paintEvent(QPaintEvent* event){
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
void ResetPasswordWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // 在鼠标右键点击的位置显示菜单
    contextMenu.exec(event->globalPos());
}
void ResetPasswordWindow::reloadQss()
{
    // 重新加载QSS
    QString path = RESOURCE_DIR + QString("/style.qss");
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qDebug() << styleSheet;
    qApp->setStyleSheet(styleSheet);
}
///更新提示信息
void ResetPasswordWindow::updateMsgHint(QWidget* widget,QString hint, bool status) {
    ///这里的widget参数暂时没用到，可能以后会用到，先留着
    if (status) {
        msgHintLabel->setProperty("status", QString("normal"));
    }
    else {
        msgHintLabel->setProperty("status", QString("error"));
    }
    msgHintLabel->style()->unpolish(msgHintLabel);
    msgHintLabel->style()->polish(msgHintLabel);
    msgHintLabel->setText(hint);
    
}

ResetPasswordWindow::~ResetPasswordWindow()
{

}
