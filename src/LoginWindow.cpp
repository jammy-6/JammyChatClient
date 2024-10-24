#pragma execution_character_set("utf-8")
#include <QVBoxLayout>
#include "LoginWindow.h"
#include <qpushbutton.h>
#include <Config.h>
#include <QSpacerItem>
#include <QStyleOption>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent)
{
    initUI();
    initConnect();
    reloadQss();
}

void LoginWindow::initConnect() {
    // 连接QAction的triggered信号到一个槽函数
    connect(reloadQssAction, &QAction::triggered, this, &LoginWindow::reloadQss);
}
void LoginWindow::initUI() {
    this->setObjectName("loginWindow");
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
    this->setFixedWidth(300);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(8, 16, 8, 16);
    ///标题
    titleLabel = new QLabel;
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText(QString("Jammy通信客户端"));
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    QSpacerItem* titleSpacer = new QSpacerItem(284, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(titleSpacer);
    ///图片
    titlePhotoLabel = new QLabel;
    titlePhotoLabel->setObjectName("titlePhotoLabel");
    titlePhotoLabel->setFixedSize(250, 291);
    mainLayout->addWidget(titlePhotoLabel, 0,Qt::AlignHCenter);

    ///用户栏
    QHBoxLayout* userLayout = new QHBoxLayout;
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
    QHBoxLayout* passwordLayout = new QHBoxLayout;
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

    ///忘记密码

    forgetPasswordBtn = new QPushButton;
    forgetPasswordBtn->setObjectName("forgetPasswordBtn");
    forgetPasswordBtn->setText(QString("忘记密码"));
    forgetPasswordBtn->setFixedSize(forgetPasswordBtn->sizeHint());
    mainLayout->addWidget(forgetPasswordBtn,0, Qt::AlignRight);

    ///登录以及注册按钮
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
void LoginWindow::paintEvent(QPaintEvent* event){
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
void LoginWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // 在鼠标右键点击的位置显示菜单
    contextMenu.exec(event->globalPos());
}
void LoginWindow::reloadQss()
{
    // 重新加载QSS
    QString path = RESOURCE_DIR + QString("/style.qss");
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

//鼠标左击更新坐标值
void LoginWindow::mousePressEvent(QMouseEvent *event){
    cur_pos = event->globalPos()-pos();
}

//鼠标左击并移动更新窗体位置
void LoginWindow::mouseMoveEvent(QMouseEvent *event){
    move(event->globalPos()-cur_pos);
}

LoginWindow::~LoginWindow()
{

}
