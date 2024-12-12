#pragma execution_character_set("utf-8")
#include <QVBoxLayout>
#include "RegisterWindow.h"
#include <qpushbutton.h>
#include <Config.h>
#include <QSpacerItem>
#include <QStyleOption>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>

RegisterWindow::RegisterWindow(QWidget *parent) :
    MoveableWidget(parent)
{
    initUI();
    initConnect();
    reloadQss();
}

void RegisterWindow::initConnect() {
    // 连接QAction的triggered信号到一个槽函数
    connect(reloadQssAction, &QAction::triggered, this, &RegisterWindow::reloadQss);
    ///邮箱输入格式验证
    connect(registerEmail->lineEdit, &QLineEdit::textChanged, [=](const QString& text) {
        QRegularExpression regex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
        // 使用正则表达式匹配 email
        QRegularExpressionMatch match = regex.match(text);
        if (match.hasMatch()) {
            updateMsgHint(registerEmail->lineEdit, "", true);
            if(false == getValidateCodeBtn->getCountingStatus())
                getValidateCodeBtn->setEnabled(true);
        }
        else {
            updateMsgHint(registerEmail->lineEdit, errorMailFormat, false);
            if (false == getValidateCodeBtn->getCountingStatus())
                getValidateCodeBtn->setEnabled(false);
        }
     });
}

bool RegisterWindow::judgeInfo() {
    if (msgHintLabel->property("status") == "error") {
        return false;
    }
    else if(msgHintLabel->property("status") == "normal"){
        return true;
    }
    return false;
}
bool RegisterWindow::judgeRegistInfoComplete() {
    if (registerUser->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserNameEmpty, false);
        return false;
    }
    if (registerEmail->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserEmailEmpty, false);
        return false;
    }
    if (registerPassword->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserPasswordEmpty, false);
        return false;
    }
    if (registerConfirmPassword->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserConfirmPasswordEmpty, false);
        return false;
    }
    if (registerValidateCodeEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserValidateCodeEmpty, false);
        return false;
    }
    if (registerConfirmPassword->lineEdit->text().isEmpty()) {
        updateMsgHint(nullptr, errorUserConfirmPasswordEmpty, false);
        return false;
    }
    if (registerPassword->lineEdit->text() != registerConfirmPassword->lineEdit->text()) {
        updateMsgHint(nullptr, errorUserPasswordNotEqual, false);
        return false;
    }
    return true;

}
void RegisterWindow::initUI() {
    this->setObjectName("registerWindow");
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    //// 创建阴影效果
    //QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
    //shadowEffect->setBlurRadius(20);
    //shadowEffect->setOffset(5, 5);
    //shadowEffect->setColor(QColor(240,240,240));

    //// 将阴影效果应用到子窗口
    //this->setGraphicsEffect(shadowEffect);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setFixedWidth(350);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(8, 16, 8, 16);
    
    QSpacerItem* titleSpacer = new QSpacerItem(334, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(titleSpacer);

    titleLabel = new QLabel;
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText(QString("Jammy用户注册"));
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    ///错误提示
    msgHintLabel = new QLabel;
    msgHintLabel->setObjectName("msgHintLabel");
    
    mainLayout->addWidget(msgHintLabel, 0, Qt::AlignHCenter);

    ///用户
    registerUser = new CustomWidgetLabel_LineEdit;
    registerUser->label->setObjectName("registerUserLabel");
    registerUser->lineEdit->setObjectName("registerUserEdit");
    registerUser->label->setText(QString("用户："));
    mainLayout->addWidget(registerUser,0,Qt::AlignHCenter);
    ///邮箱
    registerEmail = new CustomWidgetLabel_LineEdit;
    registerEmail->label->setObjectName("registerEmailLabel");
    registerEmail->lineEdit->setObjectName("registerEmailEdit");
    registerEmail->label->setText(QString("邮箱："));
    mainLayout->addWidget(registerEmail, 0, Qt::AlignHCenter);
    ///密码
    registerPassword = new CustomWidgetLabel_LineEdit;
    registerPassword->label->setObjectName("registerPasswordLabel");
    registerPassword->lineEdit->setObjectName("registerPasswordEdit");
    registerPassword->label->setText(QString("密码："));
    registerPassword->lineEdit->setEchoMode(QLineEdit::Password);
    registerPasswordVisible = new QPushButton;
    registerPasswordVisible->setObjectName("registerPasswordVisible");
    registerPasswordVisible->setFixedSize(30, 30);
    registerPasswordVisible->setCheckable(true);
    connect(registerPasswordVisible, &QPushButton::toggled, [this](bool checked) {
        if (checked) {
            registerPassword->lineEdit->setEchoMode(QLineEdit::Normal);
        }
        else {
            registerPassword->lineEdit->setEchoMode(QLineEdit::Password);
        }
        });
    registerPassword->lineEdit->setFixedWidth(
        registerPassword->lineEdit->sizeHint().width() - registerPasswordVisible->size().width() - registerPassword->layout()->spacing()
    );
    registerPassword->mainLayout->addWidget(registerPasswordVisible);

    mainLayout->addWidget(registerPassword, 0, Qt::AlignHCenter);
    ///确认密码
    registerConfirmPassword = new CustomWidgetLabel_LineEdit;
    registerConfirmPassword->label->setObjectName("registerConfirmPasswordLabel");
    registerConfirmPassword->lineEdit->setObjectName("registerConfirmPasswordEdit");
    registerConfirmPassword->label->setText(QString("确认密码："));
    registerConfirmPassword->lineEdit->setEchoMode(QLineEdit::Password);
    registerConfirmPasswordVisible = new QPushButton;
    registerConfirmPasswordVisible->setFixedSize(30, 30);
    registerConfirmPasswordVisible->setObjectName("registerConfirmPasswordVisible");
    registerConfirmPasswordVisible->setCheckable(true);
    connect(registerConfirmPasswordVisible, &QPushButton::toggled, [this](bool checked) {
        if (checked) {
            registerConfirmPassword->lineEdit->setEchoMode(QLineEdit::Normal);
        }
        else {
            registerConfirmPassword->lineEdit->setEchoMode(QLineEdit::Password);
        }
        });
    registerConfirmPassword->lineEdit->setFixedWidth(
        registerPassword->lineEdit->sizeHint().width() - registerConfirmPasswordVisible->size().width() - registerPassword->layout()->spacing()
    );
    registerConfirmPassword->mainLayout->addWidget(registerConfirmPasswordVisible);

    ///让确认密码的lineEdit与前面的lineEdit左对齐，更美观些
    QSpacerItem* rightPushSpacerItem1 = new QSpacerItem(
         registerConfirmPassword->label->sizeHint().width()- registerPassword->label->sizeHint().width()
        ,30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    registerConfirmPassword->layout()->addItem(rightPushSpacerItem1);
    mainLayout->addWidget(registerConfirmPassword, 0, Qt::AlignHCenter);

    ///验证码
    QWidget* validateWidget = new QWidget;
    QHBoxLayout* validateCodeLayout = new QHBoxLayout;
    validateWidget->setLayout(validateCodeLayout);
    validateCodeLayout->setSpacing(4);
    validateCodeLayout->setContentsMargins(0, 0, 0, 0);
    validateCodeLayout->setSizeConstraint(QLayout::SetFixedSize);
    registerValidateCodeLabel = new QLabel;
    registerValidateCodeLabel->setObjectName("registerValidateCodeLabel");
    registerValidateCodeLabel->setText(QString("验证码："));
    registerValidateCodeLabel->setFixedWidth(registerValidateCodeLabel->sizeHint().width());
    validateCodeLayout->addWidget(registerValidateCodeLabel);
    registerValidateCodeEdit = new QLineEdit;
    registerValidateCodeEdit->setObjectName("registerValidateCodeEdit");
    validateCodeLayout->addWidget(registerValidateCodeEdit);
    getValidateCodeBtn = new CustomTimerBtn;
    getValidateCodeBtn->setText(QString("获取"));
    getValidateCodeBtn->setFixedWidth(60);
    getValidateCodeBtn->setObjectName("getValidateCodeBtn");
    getValidateCodeBtn->setEnabled(false);
    validateCodeLayout->addWidget(getValidateCodeBtn);
    registerValidateCodeEdit->setFixedSize(registerValidateCodeEdit->sizeHint().width()- getValidateCodeBtn->width()- validateCodeLayout->spacing(), 30);
    QSpacerItem* rightPushSpacerItem2 = new QSpacerItem(
        registerValidateCodeLabel->sizeHint().width() - registerPassword->label->sizeHint().width()
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
    cancelBtn = new QPushButton;
    cancelBtn->setObjectName("cancelBtn");
    cancelBtn->setText(QString("取消"));
    cancelBtn->setFixedWidth(60);
    confirmAndCancelLayout->addWidget(cancelBtn);
    mainLayout->addWidget(confirmAndCancelWidget,0, Qt::AlignHCenter);

    ///尾部加一些间隔更美观
    QSpacerItem* tailSpacer = new QSpacerItem(334, 30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(tailSpacer);

    // 创建一个新的QAction
    reloadQssAction = new QAction(tr("Reload QSS"), this);
    // 添加QAction到右键菜单
    contextMenu.addAction(reloadQssAction);

}
void RegisterWindow::paintEvent(QPaintEvent* event){
    QStyleOption opt;
    opt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
void RegisterWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // 在鼠标右键点击的位置显示菜单
    contextMenu.exec(event->globalPos());
}
#include <QFile>
void RegisterWindow::reloadQss()
{
    // 重新加载QSS
    QString path = RESOURCE_DIR + QString("/style.qss");
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
}
///更新提示信息
void RegisterWindow::updateMsgHint(QWidget* widget,QString hint, bool status) {
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

RegisterWindow::~RegisterWindow()
{

}
