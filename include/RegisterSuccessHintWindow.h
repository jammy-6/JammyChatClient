#ifndef REGISTERSUCCESSHINTWINDOW_H
#define REGISTERSUCCESSHINTWINDOW_H

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
#include <QPushbutton>
#include <qlineedit.h>
#include <QTimer>
#include "MoveableWidget.h"
class RegisterSuccessHintWindow : public MoveableWidget
{
    Q_OBJECT

public:
    explicit RegisterSuccessHintWindow(QWidget* parent = nullptr);
    void initUI();
    void initConnect();
    ~RegisterSuccessHintWindow();


protected:
    void paintEvent(QPaintEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void hideEvent(QHideEvent* event) override;
signals:
    void signalReturnLoginWindow();
private:

    QLabel* titleLabel;
    QLabel* hintLabel;
    QPushButton* returnBtn;
    QTimer *timer_;
private slots:
    


};

#endif // !1
