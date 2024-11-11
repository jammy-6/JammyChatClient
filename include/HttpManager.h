#ifndef HTTPMANAGER_H
#define HTTPMANAGER_H


#include <QNetworkAccessManager>
#include "Singleton.h"
#include "nlohmann/json.hpp"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <memory>
#include "Global.h"
#include <QNetworkRequest>
#include <QNetworkReply>
class HttpManager : public QObject,public Singleton<HttpManager>,public enable_shared_from_this<HttpManager>
{
    Q_OBJECT
private:
    friend class Singleton<HttpManager>;
    HttpManager();

    QNetworkAccessManager manager_;
public:
    ~HttpManager();
    void postHttpRequest(QUrl url, nlohmann::json json, MODULE module,ID id);
signals:
    void signalHttpFinish(MODULE module, ID id,ERRORCODE code,QString data);

};
#endif // !HTTPMANAGER_H