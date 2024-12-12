// friendlistmodel.h
#ifndef FRIENDLISTMODEL_H
#define FRIENDLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVector>

struct Friend {
    QString name;
    QString status;
    QString lastMessage;
    QString time;
    QString avatar; // 添加头像路径属性
};

class FriendListModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum FriendRoles {
        NameRole = Qt::UserRole + 1,
        StatusRole,
        LastMessageRole,
        TimeRole,
        AvatarRole // 添加头像角色
    };

    FriendListModel(QObject *parent = nullptr);

    void addFriend(const Friend &friendData);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Friend> m_friends;
};

#endif // FRIENDLISTMODEL_H
