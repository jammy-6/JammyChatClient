///QWidget的写法，现在弃用了，改为QML

//#include "FriendManager.h"
//#include <QPixmapCache>
//FriendMgr::FriendMgr(){}
//void FriendMgr::addUser(const Friend& friend_) {
//    friends.push_back(friend_);
//    emit friendAdded(friends.size() - 1);
//}
//
//void FriendMgr::updateUser(int index, const Friend& friend_) {
//    if (index >= 0 && index < friends.size()) {
//        friends[index] = friend_;
//        emit friendUpdated(index);
//    }
//}
//
//void FriendMgr::removeFriend(int index) {
//    if (index < 0 || index >= friends.size()) {
//        friends.erase(friends.begin() + index);
//        emit friendRemoved(index);
//    }
//}
//
//
//FriendModel::FriendModel(QObject* parent) : QAbstractListModel(parent) {
//    connect(FriendMgr::GetInstance().get(), &FriendMgr::friendAdded, this, &FriendModel::onFriendAdded);
//    connect(FriendMgr::GetInstance().get(), &FriendMgr::friendUpdated, this, &FriendModel::onFriendUpdated);
//    connect(FriendMgr::GetInstance().get(), &FriendMgr::friendRemoved, this, &FriendModel::onFriendRemoved);
//}
//
//int FriendModel::rowCount(const QModelIndex& parent)const {
//    Q_UNUSED(parent);
//    return FriendMgr::GetInstance()->getFriends().size();
//}
//
//QVariant FriendModel::data(const QModelIndex& index, int role) const  {
//    if (!index.isValid() || index.row() >= FriendMgr::GetInstance()->getFriends().size())
//        return QVariant();
//
//    const Friend& friend_ = FriendMgr::GetInstance()->getFriends().at(index.row());
//
//    switch (role) {
//    case Qt::UserRole + 1:
//        return friend_.avatarPath;
//    case Qt::UserRole + 2:
//        return friend_.name;
//    case Qt::UserRole + 3:
//        return friend_.lastMessageTime;
//    case Qt::UserRole + 4:
//        return friend_.lastMessage;
//    default:
//        return QVariant();
//    }
//}
//
//void FriendModel::onFriendAdded(int index) {
//    beginInsertRows(QModelIndex(), index, index);
//    endInsertRows();
//}
//void FriendModel::onFriendRemoved(int index) {
//    beginRemoveRows(QModelIndex(), index, index);
//    endRemoveRows();
//}
//
//void FriendModel::onFriendUpdated(int index) {
//    emit dataChanged(createIndex(index, 0), createIndex(index, 0));
//}
//
//FriendItemDelegate::FriendItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}
//#include <QHBoxLayout>
//#include <QLabel>
//void FriendItemDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const  {
//
//    
//}
//
//QSize FriendItemDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const  {
//    return QSize(200, 70);
//}