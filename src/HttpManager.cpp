#include "HttpManager.h"

HttpManager::HttpManager() {

}

HttpManager::~HttpManager() {

}

void HttpManager::postHttpRequest(QUrl url, nlohmann::json json, MOUDLE module, ID id) {
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, json.size());
	auto self = shared_from_this();
	QNetworkReply* reply = manager_.post(request, QByteArray(json.dump().c_str()));
	QObject::connect(reply, &QNetworkReply::finished, [self, reply, module, id]() {
		if (reply->error() != QNetworkReply::NoError) {
			qDebug() << reply->errorString();
			emit self->signalHttpFinish(module, id, ERRORCODE::ERROR_NETWORK, "");
		}
		else {
			QString data = reply->readAll();
			emit self->signalHttpFinish(module, id, ERRORCODE::SUCCESS,data);
		}
		reply->deleteLater();
		return;

	});
}