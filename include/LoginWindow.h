#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QList>
#include <QLabel>
#include <QContextMenuEvent>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>
#include <QDate>
#include <QHttpMultiPart>
#include <QPainter>
#include <QPen>
#include <QScrollArea>
#include <algorithm>
#include <QTimer>
#include <QMutex>
#include <functional>
#include <QColor>
#include <QFrame>
#include <QApplication>
#include <QLayout>
#include <qlineedit.h>
#include <MoveableWidget.h>
#include "Singleton.h"
class Controller;

class LoginWindow : public MoveableWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    void initUI();
    void initConnect();
    ~LoginWindow();
    bool judgeRegistInfoComplete();
    void updateMsgHint(QWidget* widget, QString hint, bool status);
protected:
    void paintEvent(QPaintEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;


protected:
void mousePressEvent(QMouseEvent* event) override {
    if (event->button() == Qt::LeftButton) {
        m_dragging = true;
        m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void mouseMoveEvent(QMouseEvent* event) override {
    if (m_dragging) {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
    else {
        handleResize(event);
    }
}

void mouseReleaseEvent(QMouseEvent* event) override {
    if (event->button() == Qt::LeftButton) {
        m_dragging = false;
        event->accept();
    }
}

void handleResize(QMouseEvent* event) {
    const int margin = 10;
    QRect rect = this->rect();
    if (event->pos().x() > rect.width() - margin && event->pos().y() > rect.height() - margin) {
        this->setCursor(Qt::SizeFDiagCursor);
        if (event->buttons() & Qt::LeftButton) {
            int newWidth = event->pos().x();
            int newHeight = event->pos().y();
            this->resize(newWidth, newHeight);
        }
    }
    else {
        this->unsetCursor();
    }
}

private:
    bool m_dragging = false;
    QPoint m_dragPosition;

private:
    friend class Controller;
    QMenu contextMenu;
    QAction* reloadQssAction;
    QLabel* titleLabel;
    QLabel* msgHintLabel;
    QLabel* titlePhotoLabel;
    QLabel* userLabel;
    QLineEdit* userEdit;
    QLabel* passwordLabel;
    QLineEdit* passwordEdit;
    QPushButton* forgetPasswordBtn;
    QPushButton* loginBtn;
    QPushButton* registerBtn;
private slots:
    void reloadQss();
    

};

#endif 
