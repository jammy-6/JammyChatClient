///QWidget的写法，现在弃用了，改为QML

//#pragma execution_character_set("utf-8")
//#include <QVBoxLayout>
//#include "ChatWindow.h"
//#include <qpushbutton.h>
//#include <Config.h>
//#include <QSpacerItem>
//#include <QStyleOption>
//#include <QLineEdit>
//#include <QGraphicsDropShadowEffect>
//#include "CustomerWidget.h"
//#include "qscrollarea.h"
//ChatWindow::ChatWindow(QWidget *parent) :
//    MoveableWidget(parent)
//{
//    initUI();
//    initConnect();
//    reloadQss();
//}
//
//void ChatWindow::initConnect() {
// 
//}
//void ChatWindow::initUI() {
//    this->setObjectName("chatWindow");
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    //设置无边框
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
//
//    QHBoxLayout* mainLayout = new QHBoxLayout;
//    this->setLayout(mainLayout); 
//    
//    //mainLayout->setSizeConstraint(QLayout::SetFixedSize);
//    mainLayout->setContentsMargins(0, 0, 0, 0);
//    mainLayout->setSpacing(0);
//
//    sideBar = new QWidget;
//    sideBar->setObjectName("sideBar");
//    sideBar->setFixedWidth(80);
//    sideBar->setFixedHeight(980);
//    QVBoxLayout* sideBarLayout = new QVBoxLayout;
//    sideBarLayout->setContentsMargins(15, 45, 15, 45);
//    sideBarLayout->setAlignment(Qt::AlignTop);
//    sideBarLayout->setSpacing(30);
//    sideBar->setLayout(sideBarLayout);
//
//    iconLabel = new QLabel;
//    iconLabel->setFixedSize(50, 50);
//    iconLabel->setObjectName("iconLabel");
//    sideBarLayout->addWidget(iconLabel, 0, Qt::AlignHCenter);
//
//    chatBtn = new QPushButton;
//    chatBtn->setFixedSize(32, 32);
//    chatBtn->setObjectName("chatBtn");
//    chatBtn->setCheckable(true);
//    chatBtn->setChecked(false);
//    sideBarLayout->addWidget(chatBtn, 0, Qt::AlignHCenter);
//
//    contactListBtn = new QPushButton;
//    contactListBtn->setFixedSize(32, 32);
//    contactListBtn->setObjectName("contactListBtn");
//    contactListBtn->setCheckable(true);
//    contactListBtn->setChecked(false);
//    sideBarLayout->addWidget(contactListBtn, 0, Qt::AlignHCenter);
//
//    QSpacerItem* sideBarSpacer = new QSpacerItem(80, 300);
//    sideBarLayout->addItem(sideBarSpacer);
//    mainLayout->addWidget(sideBar, 0, Qt::AlignLeft);
//
//
//    ///好友列表界面
//    contactListWidget = new QWidget;
//    contactListWidget->setObjectName("contactListWidget");
//    contactListWidget->setFixedWidth(350);
//    contactListWidget->setMinimumHeight(980);
//    mainLayout->addWidget(contactListWidget, 0, Qt::AlignLeft);
//    QVBoxLayout* contactListLayout = new QVBoxLayout;
//    contactListLayout->setContentsMargins(0, 0, 0, 0);
//    contactListLayout->setSpacing(0);
//
//    contactListWidget->setLayout(contactListLayout);
//    
//
//    searchWidget = new QWidget;
//    searchWidget->setObjectName("searchWidget");
//    searchWidget->setMinimumWidth(350);
//    searchWidget->setFixedHeight(70);
//    contactListLayout->addWidget(searchWidget);
//    QHBoxLayout* searchLayout = new QHBoxLayout;
//    searchLayout->setContentsMargins(20, 20, 10,20 );
//    searchLayout->setSpacing(8);
//    searchWidget->setLayout(searchLayout);
//
//    searchLineEdit = new QLineEdit;
//    searchLineEdit->setObjectName("searchLineEdit");
//    searchLineEdit->setMinimumWidth(270);
//    searchLineEdit->setMinimumHeight(30);
//    searchLayout->addWidget(searchLineEdit, 0, Qt::AlignLeft);
//
//    addFriendBtn = new QPushButton;
//    addFriendBtn->setObjectName("addFriendBtn");
//    addFriendBtn->setFixedSize(30, 30);
//    searchLayout->addWidget(addFriendBtn, 0, Qt::AlignLeft);
//
//    //friendWidget = new ChatUserList;
//   
//    //friendWidget->setFixedHeight(910);
//    //contactListLayout->addWidget(friendWidget);
//	friendListView = new QListView;
//	friendListView->setObjectName("friendListView");
//	friendListView->setFixedSize(350, 910);
//    contactListLayout->addWidget(friendListView);
//
//
//    friendListView->setModel(&friendModel);
//    friendListView->setItemDelegate(new FriendItemDelegate(friendListView));
//
//    // 添加用户数据
//    for (int i = 0; i <10; i++) {
//        FriendMgr::GetInstance()->addUser({ 101,":/UserHeadIcon/head_1.jpg", "User 1", "10:30 AM", "Hello!" });
//        FriendMgr::GetInstance()->addUser({ 102,":/UserHeadIcon/head_1.jpg", "User 2", "10:45 AM", "How are you?" });
//    }
//
//
//    // 模拟数据更新
//    //QTimer::singleShot(3000, []() {
//    //    //for (int i = 0; i < 100; i++) {
//    //        FriendMgr::GetInstance()->updateUser(0, { 103, "path/to/avatar1.png", "User 1", "10:35 AM", "Updated message" });
//
//    //    //}
//    //    });
//
//    ///聊天界面
//    chatWidget = new QWidget;
//    chatWidget->setObjectName("chatWidget");
//    mainLayout->addWidget(chatWidget, 0, Qt::AlignLeft);
//	QLayout* chatLayout = new QVBoxLayout;
//	chatLayout->setContentsMargins(0, 0, 0, 0);
//	chatLayout->setSpacing(0);
//	chatLayout->setSizeConstraint(QLayout::SetFixedSize);
//	chatWidget->setLayout(chatLayout);
//
//	QWidget* chatTopBar = new QWidget;
//    chatTopBar->setFixedSize(960, 70);
//	chatTopBar->setObjectName("chatTopBar");
//	QHBoxLayout* chatTopBarLayout = new QHBoxLayout;
//	chatTopBarLayout->setContentsMargins(10, 20, 10, 20);
//	chatTopBarLayout->setSpacing(0);
//	
//    chatTopBar->setLayout(chatTopBarLayout);
//	nameLabel = new QLabel;
//	nameLabel->setObjectName("nameLabel");
//	nameLabel->setText("蔡大猫");
//	chatTopBarLayout->addWidget(nameLabel, 0, Qt::AlignLeft);
//	closeBtn = new QPushButton;
//	closeBtn->setObjectName("closeBtn");
//	closeBtn->setFixedSize(30, 30);
//	chatTopBarLayout->addWidget(closeBtn, 0, Qt::AlignRight);
//    chatLayout->addWidget(chatTopBar);
//
//    ///改写为QScrollArea
//	QScrollArea* area = new QScrollArea;
//	///设置chatMsgListWidget为area的widget
//    area->setFixedWidth(960);
//    area->setFixedHeight(910);
//    chatMsgListWidget = new QWidget;
//
//    
//    area->setWidget(chatMsgListWidget);
//	area->setWidgetResizable(true);
//	area->setObjectName("chatMsgListWidget");
//    QVBoxLayout* chatMsgListLayout = new QVBoxLayout;
//    chatMsgListLayout->setContentsMargins(0, 0, 0, 0);
//    chatMsgListLayout->setSpacing(5);
//    chatMsgListWidget->setLayout(chatMsgListLayout);/*
//	chatMsgListWidget->setItemAlignment(Qt::AlignRight);*/
//    chatLayout->addWidget(area);
//    for (int i = 0; i < 3; i++) {
//        MsgItemWidget* widget = new MsgItemWidget;
//        widget->setLayoutDirection(Qt::RightToLeft);
//		chatMsgListLayout->addWidget(widget,Qt::AlignTop);
//
//
//
//    }
//
//}
//
//void ChatWindow::updateMsgHint(QWidget* widget, QString hint, bool status) {
//    ///这里的widget参数暂时没用到，可能以后会用到，先留着
//    //if (status) {
//    //    msgHintLabel->setProperty("status", QString("normal"));
//    //}
//    //else {
//    //    msgHintLabel->setProperty("status", QString("error"));
//    //}
//    //msgHintLabel->style()->unpolish(msgHintLabel);
//    //msgHintLabel->style()->polish(msgHintLabel);
//    //msgHintLabel->setText(hint);
//}
//void ChatWindow::paintEvent(QPaintEvent* event){
//    QStyleOption opt;
//    opt.initFrom(this);
//    QPainter painter(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
//}
//#include <QFile>
//void ChatWindow::reloadQss()
//{
//    // 重新加载QSS
//    QString path = RESOURCE_DIR + QString("/style.qss");
//    QFile file(path);
//    file.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(file.readAll());
//    qApp->setStyleSheet(styleSheet);
//}
//
//bool ChatWindow::judgeRegistInfoComplete() {
//    //if (userEdit->text().isEmpty()) {
//    //    return false;
//    //}
//    //if (passwordEdit->text().isEmpty()) {
//    //    return false;
//    //}
//    return true;
//}
//ChatWindow::~ChatWindow()
//{
//
//}
