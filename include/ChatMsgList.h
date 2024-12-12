
///QWidget的写法，现在弃用了，改为QML
//#ifndef CHATMSGLIST_H
//#define CHATMSGLIST_H
//#include <QListWidget>
//#include <QWheelEvent>
//#include <QEvent>
//#include <QScrollBar>
//#include <QDebug>
//#include <QEnterEvent>
//
//
//
//class ChatMsgList: public QListWidget
//{
//    Q_OBJECT
//public:
//    ChatMsgList(QWidget *parent = nullptr);
//
//protected:
//    bool eventFilter(QObject *watched, QEvent *event) override;
//    void enterEvent(QEnterEvent* event) override {
//        this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//        QListWidget::enterEvent(event); // 调用基类的 leaveEvent 方法
//    }
//
//    void leaveEvent(QEvent* event) override {
//        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//        QListWidget::leaveEvent(event); // 调用基类的 leaveEvent 方法
//    }
//private:
//    bool _load_pending;
//signals:
//    void sig_loading_chat_user();
//};
//
//#endif // CHATMSGLIST_H
