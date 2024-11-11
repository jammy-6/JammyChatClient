
#include "TcpMgr.h"
#include <QDataStream>

//QTcpSocket _socket;
//QString _host;
//uint16_t _port;
//QByteArray _buffer;
//bool _b_recv_pending;
//quint16 _message_id;
//quint16 _message_len;

TcpMgr::TcpMgr() :
	_socket(nullptr), _host(""),_port(0),_buffer(),
	_b_recv_pending(false),_message_id(0),_message_len(0)
{
    QObject::connect(&_socket, &QTcpSocket::connected, [&]() {
        qDebug() << "Connected to server!";
        // ���ӽ���������Ϣ
        emit sig_con_success(true);
    });

    QObject::connect(&_socket, &QTcpSocket::readyRead, [&]() {
        // �������ݿɶ�ʱ����ȡ��������
        // ��ȡ�������ݲ�׷�ӵ�������
        _buffer.append(_socket.readAll());
        QDataStream stream(&_buffer, QIODevice::ReadOnly);
        stream.setVersion(QDataStream::Qt_5_0);
        forever{
            //�Ƚ���ͷ��
           if (!_b_recv_pending) {
               // ��黺�����е������Ƿ��㹻������һ����Ϣͷ����ϢID + ��Ϣ���ȣ�
               if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
                   return; // ���ݲ������ȴ���������
               }
               // Ԥ��ȡ��ϢID����Ϣ���ȣ������ӻ��������Ƴ�
               stream >> _message_id >> _message_len;
               //��buffer �е�ǰ�ĸ��ֽ��Ƴ�
               _buffer = _buffer.mid(sizeof(quint16) * 2);
               // �����ȡ������
               qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;
           }
            //bufferʣ�೤���Ƿ�������Ϣ�峤�ȣ����������˳������ȴ�����
           if (_buffer.size() < _message_len) {
                _b_recv_pending = true;
                return;
           }
           _b_recv_pending = false;
           // ��ȡ��Ϣ��
           QByteArray messageBody = _buffer.mid(0, _message_len);
            qDebug() << "receive body msg is " << messageBody;
           _buffer = _buffer.mid(_message_len);
           emit sig_recv_data((MSG_IDS)_message_id, QString::fromStdString(messageBody.toStdString()));
        }
    });


    QObject::connect(&_socket, static_cast<void (QTcpSocket::*)(QTcpSocket::SocketError)>(&QTcpSocket::error),
        [&](QTcpSocket::SocketError socketError) {
            qDebug() << "Error:" << _socket.errorString();
            switch (socketError) {
            case QTcpSocket::ConnectionRefusedError:
                qDebug() << "Connection Refused!";
                emit sig_con_success(false);
                break;
            case QTcpSocket::RemoteHostClosedError:
                qDebug() << "Remote Host Closed Connection!";
                break;
            case QTcpSocket::HostNotFoundError:
                qDebug() << "Host Not Found!";
                emit sig_con_success(false);
                break;
            case QTcpSocket::SocketTimeoutError:
                qDebug() << "Connection Timeout!";
                emit sig_con_success(false);
                break;
            case QTcpSocket::NetworkError:
                qDebug() << "Network Error!";
                break;
            default:
                qDebug() << "Other Error!";
                break;
            }
        });
    // �������ӶϿ�
    QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
        qDebug() << "Disconnected from server.";
        });
    QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);
}

void TcpMgr::slot_tcp_connect(ServerInfo si)
{
    qDebug() << "receive tcp connect signal";
    // �������ӵ�������
    qDebug() << "Connecting to server...";
    _host = si.Host;
    _port = static_cast<uint16_t>(si.Port.toUInt());
    _socket.connectToHost(si.Host, _port);
}

void TcpMgr::slot_send_data(MSG_IDS reqId, QString data)
{
    uint16_t id = reqId;
    // ���ַ���ת��ΪUTF-8������ֽ�����
    QByteArray dataBytes = data.toUtf8();
    // ���㳤�ȣ�ʹ�������ֽ���ת����
    quint16 len = static_cast<quint16>(data.size());
    // ����һ��QByteArray���ڴ洢Ҫ���͵���������
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    // ����������ʹ�������ֽ���
    out.setByteOrder(QDataStream::BigEndian);
    // д��ID�ͳ���
    out << id << len;
    // ����ַ�������
    block.append(data);
    // ��������
    _socket.write(block);
}
