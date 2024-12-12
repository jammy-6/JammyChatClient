// friendlistmodel.cpp
#include "friendlistmodel.h"

FriendListModel::FriendListModel(QObject *parent)
    : QAbstractListModel(parent) {
}

void FriendListModel::addFriend(const Friend &friendData) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_friends << friendData;
    endInsertRows();
}

int FriendListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_friends.count();
}

QVariant FriendListModel::data(const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_friends.count())
        return QVariant();

    const Friend &friendData = m_friends[index.row()];
    if (role == NameRole)
        return friendData.name;
    else if (role == StatusRole)
        return friendData.status;
    else if (role == LastMessageRole)
        return friendData.lastMessage;
    else if (role == TimeRole)
        return friendData.time;
    else if (role == AvatarRole)
        return friendData.avatar; // 返回头像路径
    return QVariant();
}

QHash<int, QByteArray> FriendListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[StatusRole] = "status";
    roles[LastMessageRole] = "lastMessage";
    roles[TimeRole] = "time";
    roles[AvatarRole] = "avatar"; // 添加头像角色名称
    return roles;
}
