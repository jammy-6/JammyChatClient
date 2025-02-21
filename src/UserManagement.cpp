#include "UserManagement.h"
#include <QVariant>

// QHash<int, QByteArray> UserManagement::roleNames() const {
// 	QHash<int, QByteArray> roles;
// 	roles[FriendsRole] = "friends";
// 	roles[TestRole] = "test";

// 	return roles;
// }

// QVariant UserManagement::data(const QModelIndex &index, int role) const {
// 	// if (!index.isValid() || index.row() >= 2)
// 	//     return QVariant();
// 	switch (role) {
// 	case FriendsRole:
// 		return QVariant::fromValue(friends);
// 	case TestRole:
// 		return test;
// 	}
// 	return QVariant();
// }

// int UserManagement::rowCount(const QModelIndex &parent) const {
// 	if (parent.isValid())
// 		return 0;
// 	return 2;
// }

// int UserManagement::columnCount(const QModelIndex &parent) const {
// 	if (parent.isValid())
// 		return 0;
// 	return 2;
// }

// QModelIndex UserManagement::parent(const QModelIndex &index) const {
// 	return QModelIndex();
// }

// QModelIndex UserManagement::index(int row, int column, const QModelIndex &parent) const {

// 	return QModelIndex();
// }
UserManagement::UserManagement(QObject *parent) : QObject(parent) {
}
