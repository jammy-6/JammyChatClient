#pragma execution_character_set("utf-8")
#include <QVBoxLayout>
#include "ChatWindow.h"
#include <qpushbutton.h>
#include <Config.h>
#include <QSpacerItem>
#include <QStyleOption>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>
ChatWindow::ChatWindow(QWidget *parent) :
    MoveableWidget(parent)
{
    initUI();
    initConnect();
    reloadQss();
}

void ChatWindow::initConnect() {
 
}
void ChatWindow::initUI() {
    this->setObjectName("chatWindow");
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //设置无边框
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    this->setLayout(mainLayout); 
    
    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    sideBar = new QWidget;
    sideBar->setObjectName("sideBar");
    sideBar->setFixedWidth(80);
    sideBar->setMinimumHeight(980);
    QVBoxLayout* sideBarLayout = new QVBoxLayout;
    sideBarLayout->setContentsMargins(15, 45, 15, 45);
    sideBarLayout->setAlignment(Qt::AlignTop);
    sideBarLayout->setSpacing(30);
    sideBar->setLayout(sideBarLayout);

    iconLabel = new QLabel;
    iconLabel->setFixedSize(50, 50);
    iconLabel->setObjectName("iconLabel");
    sideBarLayout->addWidget(iconLabel, 0, Qt::AlignHCenter);

    chatBtn = new QPushButton;
    chatBtn->setFixedSize(32, 32);
    chatBtn->setObjectName("chatBtn");
    chatBtn->setCheckable(true);
    chatBtn->setChecked(false);
    sideBarLayout->addWidget(chatBtn, 0, Qt::AlignHCenter);

    contactListBtn = new QPushButton;
    contactListBtn->setFixedSize(32, 32);
    contactListBtn->setObjectName("contactListBtn");
    contactListBtn->setCheckable(true);
    contactListBtn->setChecked(false);
    sideBarLayout->addWidget(contactListBtn, 0, Qt::AlignHCenter);

    QSpacerItem* sideBarSpacer = new QSpacerItem(80, 300);
    sideBarLayout->addItem(sideBarSpacer);
    mainLayout->addWidget(sideBar, 0, Qt::AlignLeft);


    ///好友列表界面
    contactListWidget = new QWidget;
    contactListWidget->setObjectName("contactListWidget");
    contactListWidget->setFixedWidth(350);
    contactListWidget->setMinimumHeight(980);
    mainLayout->addWidget(contactListWidget, 0, Qt::AlignLeft);
    QVBoxLayout* contactListLayout = new QVBoxLayout;
    contactListLayout->setContentsMargins(0, 0, 0, 0);
    contactListLayout->setSpacing(0);
    contactListWidget->setLayout(contactListLayout);
    

    searchWidget = new QWidget;
    searchWidget->setObjectName("searchWidget");
    searchWidget->setMinimumWidth(350);
    searchWidget->setFixedHeight(100);
    contactListLayout->addWidget(searchWidget, 0, Qt::AlignTop);
    QHBoxLayout* searchLayout = new QHBoxLayout;
    searchLayout->setContentsMargins(20, 50, 10,20 );
    searchLayout->setSpacing(8);
    searchWidget->setLayout(searchLayout);

    searchLineEdit = new QLineEdit;
    searchLineEdit->setObjectName("searchLineEdit");
    searchLineEdit->setMinimumWidth(270);
    searchLineEdit->setMinimumHeight(30);
    searchLayout->addWidget(searchLineEdit, 0, Qt::AlignLeft);

    addFriendBtn = new QPushButton;
    addFriendBtn->setObjectName("addFriendBtn");
    addFriendBtn->setFixedSize(30, 30);
    searchLayout->addWidget(addFriendBtn, 0, Qt::AlignLeft);

    friendWidget = new QListWidget;
    friendWidget->setObjectName("friendWidget");
    friendWidget->setMinimumWidth(350);
    friendWidget->setMinimumHeight(880);
    contactListLayout->addWidget(friendWidget);

    ///聊天界面
    chatWidget = new QWidget;
    chatWidget->setObjectName("chatWidget");
    chatWidget->setMinimumWidth(960);
    chatWidget->setMinimumHeight(45); 
    mainLayout->addWidget(chatWidget, 0, Qt::AlignLeft);
  

}

void ChatWindow::updateMsgHint(QWidget* widget, QString hint, bool status) {
    ///这里的widget参数暂时没用到，可能以后会用到，先留着
    //if (status) {
    //    msgHintLabel->setProperty("status", QString("normal"));
    //}
    //else {
    //    msgHintLabel->setProperty("status", QString("error"));
    //}
    //msgHintLabel->style()->unpolish(msgHintLabel);
    //msgHintLabel->style()->polish(msgHintLabel);
    //msgHintLabel->setText(hint);
}
void ChatWindow::paintEvent(QPaintEvent* event){
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void ChatWindow::reloadQss()
{
    // 重新加载QSS
    QString path = RESOURCE_DIR + QString("/style.qss");
    QFile file(path);
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
}

bool ChatWindow::judgeRegistInfoComplete() {
    //if (userEdit->text().isEmpty()) {
    //    return false;
    //}
    //if (passwordEdit->text().isEmpty()) {
    //    return false;
    //}
    return true;
}
ChatWindow::~ChatWindow()
{

}
