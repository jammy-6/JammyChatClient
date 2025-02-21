// friendlistmodel.h
#ifndef FRIENDLISTMODEL_H
#define FRIENDLISTMODEL_H

#include <QAbstractListModel>
#include <QMap>
#include <QObject>
#include <QTime>
#include <QVector>
struct UserData {
	QString name;
	QString email;
	int userId;
	QString avatar;
};

enum MESSAGE_TYPE {
	TEXT,
	AUDIO
};

struct Message {
	MESSAGE_TYPE type;
	int from;
	int to;
	QTime time;
	QString data;
	// 构造函数
	Message() : type(TEXT), from(0), to(0), time(QTime::currentTime()), data("") {}
	Message(MESSAGE_TYPE type, int from, int to, QTime time, QString data)
		: type(type), from(from), to(to), time(time), data(data) {}
};
struct FriendData : public UserData {
	int status;				   // 1代表上线，0代表下线
	QVector<Message> chatMsgs; // 与该用户所有的聊天消息
};

class MessageModel : public QAbstractListModel {
	Q_OBJECT

public:
	enum MessageRoles {
		TypeRole = Qt::UserRole + 1,
		FromRole,
		ToRole,
		TimeRole,
		DataRole
	};
	Q_INVOKABLE QString getLastMsg() const {
		if (m_messages.size() > 0) {
			return m_messages.last().data;
		}
		return "";
	}
	Q_INVOKABLE QString getLastMsgTime() const {
		if (m_messages.size() > 0) {
			return m_messages.last().time.toString("hh:mm");
		}
		return "";
	}
	MessageModel(QObject *parent = nullptr);

	void setMessages(const QVector<Message> &messages);
	void appendMessage(const Message &message);
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

private:
	QVector<Message> m_messages;
};

class FriendModel : public QAbstractListModel {
	Q_OBJECT

public:
	enum FriendRoles {
		NameRole = Qt::UserRole + 1,
		EmailRole,
		UserIdRole,
		AvatarRole,
		StatusRole,
		ChatMsgsRole
	};

	FriendModel(QObject *parent = nullptr);
	Q_INVOKABLE MessageModel *getChatMsgsByIndex(int userId) {
		if (m_messageModels.contains(userId)) {
			return static_cast<MessageModel *>(m_messageModels[userId]);
		}
		return nullptr;
	}
	Q_INVOKABLE void appendMessage(int from,
								   int to,
								   QTime time,
								   QString data);

	void setFriends(const QVector<FriendData> &friends);
	void addFriend(FriendData &newFriend);

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
	QHash<int, QByteArray> roleNames() const override;

private:
	QVector<FriendData> m_friends;
	QMap<int, QAbstractListModel *> m_messageModels; // 存储每个好友的MessageModel实例
};

// 旧的接口
// struct Friend {
// 	QString name;
// 	QString status;
// 	QString lastMessage;
// 	QString time;
// 	QString avatar; // 添加头像路径属性
// };
// class FriendListModel : public QAbstractListModel {
// 	Q_OBJECT

// public:
// 	enum FriendRoles {
// 		/*        TypeRole*/
// 		NameRole = Qt::UserRole + 1,
// 		StatusRole,
// 		LastMessageRole,
// 		TimeRole,
// 		AvatarRole // 添加头像角色
// 	};

// 	FriendListModel(QObject *parent = nullptr);
// 	void insertFriend(const Friend &friendData, int index);
// 	void addFriend(const Friend &friendData);

// 	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
// 	QVariant data(const QModelIndex &index, int role) const override;
// 	QHash<int, QByteArray> roleNames() const override;

// private:
// 	QVector<Friend> m_friends;
// signals:
// 	void modelChanged();
// };

#endif // FRIENDLISTMODEL_H
