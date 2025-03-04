﻿
#include "TcpMgr.h"
#include <QDataStream>

// QTcpSocket _socket;
// QString _host;
// uint16_t _port;
// QByteArray _buffer;
// bool _b_recv_pending;
// quint16 _message_id;
// quint16 _message_len;

TcpMgr::TcpMgr() : _socket(nullptr), _host(""), _port(0), _buffer(),
				   _b_recv_pending(false), _message_id(0), _message_len(0) {
	QObject::connect(&_socket, &QTcpSocket::connected, [&]() {
		qDebug() << "Connected to server!";
		// 连接建立后发送消息
		emit sig_con_success(true);
	});

	QObject::connect(&_socket, &QTcpSocket::readyRead, [&]() {
		// 当有数据可读时，读取所有数据
		// 读取所有数据并追加到缓冲区
		_buffer.append(_socket.readAll());
		QDataStream stream(&_buffer, QIODevice::ReadOnly);
		stream.setVersion(QDataStream::Qt_DefaultCompiledVersion);
		forever {
			// 先解析头部
			if (!_b_recv_pending) {
				// 检查缓冲区中的数据是否足够解析出一个消息头（消息ID + 消息长度）
				if (_buffer.size() < static_cast<int>(sizeof(quint16) * 2)) {
					return; // 数据不够，等待更多数据
				}
				// 预读取消息ID和消息长度，但不从缓冲区中移除
				stream >> _message_id >> _message_len;
				// 将buffer 中的前四个字节移除
				_buffer = _buffer.mid(sizeof(quint16) * 2);
				// 输出读取的数据
				qDebug() << "Message ID:" << _message_id << ", Length:" << _message_len;
			}
			// buffer剩余长读是否满足消息体长度，不满足则退出继续等待接受
			if (_buffer.size() < _message_len) {
				_b_recv_pending = true;
				return;
			}
			_b_recv_pending = false;
			// 读取消息体
			QByteArray messageBody = _buffer.mid(0, _message_len);
			qDebug() << "receive body msg is " << messageBody;
			_buffer = _buffer.mid(_message_len);
			emit sig_recv_data((MSG_IDS)_message_id, QString::fromStdString(messageBody.toStdString()));
		}
	});

	QObject::connect(&_socket, &QTcpSocket::errorOccurred,
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
	// 处理连接断开
	QObject::connect(&_socket, &QTcpSocket::disconnected, [&]() {
		qDebug() << "Disconnected from server.";
	});
	QObject::connect(this, &TcpMgr::sig_send_data, this, &TcpMgr::slot_send_data);
}

void TcpMgr::connectToServer(ServerInfo si) {
	qDebug() << "receive tcp connect signal";
	// 尝试连接到服务器
	qDebug() << "Connecting to server...";
	_host = si.Host;
	_port = static_cast<uint16_t>(si.Port.toUInt());
	_socket.connectToHost(si.Host, _port);
}

void TcpMgr::slot_send_data(MSG_IDS reqId, QString data) {
	uint16_t id = reqId;
	// 将字符串转换为UTF-8编码的字节数组
	QByteArray dataBytes = data.toUtf8();
	// 计算长度（使用网络字节序转换）
	quint16 len = static_cast<quint16>(data.size());
	// 创建一个QByteArray用于存储要发送的所有数据
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	// 设置数据流使用网络字节序
	out.setByteOrder(QDataStream::BigEndian);
	// 写入ID和长度
	out << id << len;
	// 添加字符串数据
	block.append(data.toStdString().c_str());
	// 发送数据
	_socket.write(block);
}
