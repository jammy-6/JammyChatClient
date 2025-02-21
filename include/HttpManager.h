#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H

#include "ChatMgrGlobal.h"
#include "Global.h"
#include "Singleton.h"
#include "nlohmann/json.hpp"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <memory>
class CHAT_MGR_EXPORT HttpManager : public QObject, public Singleton<HttpManager>, public enable_shared_from_this<HttpManager> {
	Q_OBJECT
private:
	friend class Singleton<HttpManager>;
	HttpManager();

	QNetworkAccessManager manager_;

public:
	~HttpManager();
	void postHttpRequest(QUrl url, nlohmann::json json, MODULE module, ID id);
signals:
	void signalHttpFinish(MODULE module, ID id, ERRORCODE code, QString data);
};
#endif // !HTTPMANAGER_H