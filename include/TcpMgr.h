#ifndef TCPMGR_H
#define TCPMGR_H
#include "ChatMgrGlobal.h"
#include <Global.h>
#include <QTcpSocket>
#include <singleton.h>

class CHAT_MGR_EXPORT TcpMgr : public QObject, public Singleton<TcpMgr>, public std::enable_shared_from_this<TcpMgr> {
	Q_OBJECT
private:
	friend class Singleton<TcpMgr>;

	TcpMgr();
	QTcpSocket _socket;
	QString _host;
	uint16_t _port;
	QByteArray _buffer;
	bool _b_recv_pending;
	quint16 _message_id;
	quint16 _message_len;

public:
	void connectToServer(ServerInfo);
public slots:
	void slot_send_data(MSG_IDS reqId, QString data);
signals:
	void sig_con_success(bool bsuccess);
	void sig_send_data(MSG_IDS reqId, QString data);
	void sig_recv_data(MSG_IDS reqId, QString data);
};
#endif TCPMGR_H