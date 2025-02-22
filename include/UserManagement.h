// USERMANAGEMENT_H
#ifndef USERMANAGEMENT_H
#define USERMANAGEMENT_H

#include "FriendListModel.h"
#include "Singleton.h"
#include <QAbstractItemModel>
#include <QAbstractListModel>
#include <QObject>
#include <QVector>
class UserManagement : public QObject, public Singleton<UserManagement> {
	Q_OBJECT
	Q_PROPERTY(FriendModel *friends READ getFriends)
	Q_PROPERTY(int loginId READ getLoginId)
	Q_PROPERTY(QString test READ getTest)
	Q_PROPERTY(QString loginAvatar READ getLoginAvatar)

	enum UserManagementRoles {
		/*        TypeRole*/
		FriendsRole = Qt::UserRole + 1,
		TestRole,
	};

public:
	UserManagement(QObject *parent = nullptr);
	FriendModel *getFriends() {
		return friends;
	}
	Q_INVOKABLE QString getFriendAvatarBySelectIndex(int index) {
		if (index >= 0 && index < friends->rowCount()) {
			return friends->m_friends[index].avatar;
		}
		return "";
	}

	int getLoginId() {
		return loginUser.userId;
	}
	QString getTest() {
		return test;
	}
	QString getLoginAvatar() {
		return loginUser.avatar;
	}

	// QVariant data(const QModelIndex &index, int role) const override;
	// int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	// int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	// QModelIndex parent(const QModelIndex &index) const override;
	// QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
	// QHash<int, QByteArray> roleNames() const override;

	QString test = "测试qproperty";
	UserData loginUser;
	FriendModel *friends;
};

#endif // USERMANAGEMENT_H
