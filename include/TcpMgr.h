#ifndef TCPMGR_H
#define TCPMGR_H
#include <QTcpSocket>
#include <singleton.h>
#include <Global.h>


class TcpMgr : public QObject, public Singleton<TcpMgr>,
    public std::enable_shared_from_this<TcpMgr>
{
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
public slots:
    void slot_tcp_connect(ServerInfo);
    void slot_send_data(MSG_IDS reqId, QString data);
signals:
    void sig_con_success(bool bsuccess);
    void sig_send_data(MSG_IDS reqId, QString data);
    void sig_recv_data(MSG_IDS reqId, QString data);
};
#endif  TCPMGR_H