///QWidget的写法，现在弃用了，改为QML
//#ifndef CHATWINDOW_H
//#define CHATWINDOW_H
//
//#include <QWidget>
//#include <QMenu>
//#include <QAction>
//#include <QList>
//#include <QLabel>
//#include <QContextMenuEvent>
//#include <QNetworkAccessManager>
//#include <QMessageBox>
//#include <QNetworkReply>
//#include <QDate>
//#include <QHttpMultiPart>
//#include <QPainter>
//#include <QPen>
//
//#include <QScrollArea>
//#include <algorithm>
//#include <QTimer>
//#include <QMutex>
//#include <functional>
//#include <QColor>
//#include <QFrame>
//#include <QApplication>
//#include <QLayout>
//#include <qlineedit.h>
//#include <MoveableWidget.h>
//#include <QListWidget>
//#include "Singleton.h"
//#include "ChatUserList.h"
//#include "FriendManager.h"
//#include "ChatMsgList.h"
//class Controller;
//
//class ChatWindow : public MoveableWidget
//{
//    Q_OBJECT
//
//public:
//    explicit ChatWindow(QWidget *parent = nullptr);
//    void initUI();
//    void initConnect();
//    ~ChatWindow();
//    bool judgeRegistInfoComplete();
//    void updateMsgHint(QWidget* widget, QString hint, bool status);
//protected:
//    void paintEvent(QPaintEvent* event) override;
//
//private:
//    friend class Controller;
//
//    QWidget* sideBar;
//    QLabel* iconLabel;
//    QPushButton* chatBtn;
//    QPushButton* contactListBtn;
//
//    QWidget* contactListWidget;
//    QWidget* searchWidget;
//    QLineEdit* searchLineEdit;
//    QPushButton* addFriendBtn;
//    ChatUserList* friendWidget;
//	QListView* friendListView;
//    FriendModel friendModel;
//    QWidget* chatWidget;
//    QWidget* chatTopBar;
//    QLabel* nameLabel;
//    QPushButton* closeBtn;
//    //ChatMsgList* chatMsgListWidget;
//    QWidget* chatMsgListWidget;
//private slots:
//    void reloadQss();
//    
//
//};
//
//#endif 
