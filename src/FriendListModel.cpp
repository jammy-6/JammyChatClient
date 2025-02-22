#include "FriendListModel.h"
#include "UserManagement.h"
MessageModel::MessageModel(QObject *parent)
	: QAbstractListModel(parent) {}

// MessageModel::MessageModel(QVector<Message> &messages, QObject *parent)
// 	: QAbstractListModel(parent), m_messages(messages) {}
void MessageModel::setMessages(const QVector<Message> &messages) {
	beginResetModel();
	m_messages = messages;
	endResetModel();
}

void MessageModel::appendMessage(const Message &message) {
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_messages << message;
	endInsertRows();
	emit dataChanged();
}

int MessageModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid())
		return 0;
	return m_messages.size();
}

QVariant MessageModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() >= m_messages.size())
		return QVariant();

	const Message &message = m_messages.at(index.row());
	switch (role) {
	case TypeRole:
		return message.type;
	case FromRole:
		return message.from;
	case ToRole:
		return message.to;
	case TimeRole:
		return message.time.toString("hh:mm");
	case DataRole:
		return message.data;
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> MessageModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[TypeRole] = "type";
	roles[FromRole] = "from";
	roles[ToRole] = "to";
	roles[TimeRole] = "time";
	roles[DataRole] = "data";
	return roles;
}

FriendModel::FriendModel(QObject *parent)
	: QAbstractListModel(parent) {}
void FriendModel::appendMessage(int from,
								int to,
								QTime time,
								QString data) {
	Message message(MESSAGE_TYPE::TEXT, from, to, time, data);
	if (message.from == UserManagement::GetInstance()->loginUser.userId) {
		static_cast<MessageModel *>(m_messageModels[message.to])->appendMessage(message);
	} else if (message.to == UserManagement::GetInstance()->loginUser.userId) {
		static_cast<MessageModel *>(m_messageModels[message.to])->appendMessage(message);
	}
	return;
}
void FriendModel::setFriends(QVector<FriendData> &friends) {
	beginResetModel();
	m_friends = friends;
	m_messageModels.clear();
	for (FriendData &friendData : friends) {
		MessageModel *messageModel = new MessageModel(this);
		messageModel->setMessages(friendData.chatMsgs);
		m_messageModels.insert(friendData.userId, messageModel);
	}
	endResetModel();
}

void FriendModel::addFriend(FriendData &newFriend) {
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	m_friends << newFriend;
	if (m_messageModels.contains(newFriend.userId)) {
		return;
	}
	MessageModel *messageModel = new MessageModel(this);
	messageModel->setMessages(newFriend.chatMsgs);
	m_messageModels.insert(newFriend.userId, messageModel);
	endInsertRows();
}
int FriendModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid())
		return 0;
	return m_friends.size();
}

QVariant FriendModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() >= m_friends.size())
		return QVariant();

	const FriendData &friendData = m_friends.at(index.row());

	switch (role) {
	case NameRole:
		return friendData.name;
	case EmailRole:
		return friendData.email;
	case UserIdRole:
		return friendData.userId;
	case AvatarRole:
		return friendData.avatar;
	case StatusRole:
		return friendData.status;
	case ChatMsgsRole:
		return QVariant::fromValue(m_messageModels[friendData.userId]);
	default:
		return QVariant();
	}
}

QHash<int, QByteArray> FriendModel::roleNames() const {
	QHash<int, QByteArray> roles;
	roles[NameRole] = "name";
	roles[EmailRole] = "email";
	roles[UserIdRole] = "userId";
	roles[AvatarRole] = "avatar";
	roles[StatusRole] = "status";
	roles[ChatMsgsRole] = "chatMsgs";
	return roles;
}

// 以下为旧接口，待删除
// FriendListModel::FriendListModel(QObject *parent)
// 	: QAbstractListModel(parent) {
// }

// void FriendListModel::addFriend(const Friend &friendData) {
// 	beginInsertRows(QModelIndex(), rowCount(), rowCount());
// 	m_friends << friendData;
// 	endInsertRows();
// 	emit modelChanged();
// }

// void FriendListModel::insertFriend(const Friend &friendData, int index) {
// 	beginInsertRows(QModelIndex(), index, index);
// 	m_friends.insert(index, friendData);
// 	endInsertRows();
// }

// int FriendListModel::rowCount(const QModelIndex &parent) const {
// 	Q_UNUSED(parent);
// 	return m_friends.count();
// }

// QVariant FriendListModel::data(const QModelIndex &index, int role) const {
// 	if (index.row() < 0 || index.row() >= m_friends.count())
// 		return QVariant();

// 	const Friend &friendData = m_friends[index.row()];
// 	if (role == NameRole)
// 		return friendData.name;
// 	else if (role == StatusRole)
// 		return friendData.status;
// 	else if (role == LastMessageRole)
// 		return friendData.lastMessage;
// 	else if (role == TimeRole)
// 		return friendData.time;
// 	else if (role == AvatarRole)
// 		return friendData.avatar; // 返回头像路径
// 	return QVariant();
// }

// QHash<int, QByteArray> FriendListModel::roleNames() const {
// 	QHash<int, QByteArray> roles;
// 	// roles[TypeRole] = "type";
// 	roles[NameRole] = "name";
// 	roles[StatusRole] = "status";
// 	roles[LastMessageRole] = "lastMessage";
// 	roles[TimeRole] = "time";
// 	roles[AvatarRole] = "avatar"; // 添加头像角色名称
// 	return roles;
// }
