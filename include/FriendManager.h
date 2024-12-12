///QWidget的写法，现在弃用了，改为QML
//#ifndef FRIENDMANAGER_H
//#define FRIENDMANAGER_H
//#include <QString>
//#include <QObject>
//#include <singleton.h>
//#include <Global.h>
//#include <algorithm>
//#include <QAbstractListModel>
//#include <QPainter>
//#include <QStyledItemDelegate>
//#include "FriendListModel.h"
////struct Friend {
////	int uid;
////    QString avatarPath;
////    QString name;
////    QString lastMessageTime;
////    QString lastMessage;
////};
//
//
//
//
//class FriendMgr : public QObject, public Singleton<FriendMgr>,
//    public std::enable_shared_from_this<FriendMgr>
//{
//    Q_OBJECT
//
//private:
//    friend class Singleton<FriendMgr>;
//    FriendMgr();
//    std::vector<Friend> friends;
//signals:
//    void friendAdded(int index);
//    void friendUpdated(int index);
//	void friendRemoved(int index);
//public:
//    void addUser(const Friend& user);
//    void updateUser(int index, const Friend& user);
//	void removeFriend(int index);
//	const std::vector<Friend>& getFriends() const { return friends; }
//};
//
//
//class FriendModel : public QAbstractListModel {
//    Q_OBJECT
//
//public:
//    FriendModel(QObject* parent = nullptr);
//
//    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
//
//    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
//
//private slots:
//    void onFriendAdded(int index);
//    void onFriendRemoved(int index);
//
//    void onFriendUpdated(int index);
//};
//
//
//class FriendItemDelegate : public QStyledItemDelegate {
//public:
//    FriendItemDelegate(QObject* parent = nullptr) ;
//
//    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
//
//    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override;
//};
//#endif