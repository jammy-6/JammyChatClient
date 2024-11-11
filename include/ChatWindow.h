#ifndef CHATWINDOW_H
#define CHATWINDOW_H

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
#include <QChart>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
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
#include <QListWidget>
#include "Singleton.h"
class Controller;

class ChatWindow : public MoveableWidget
{
    Q_OBJECT

public:
    explicit ChatWindow(QWidget *parent = nullptr);
    void initUI();
    void initConnect();
    ~ChatWindow();
    bool judgeRegistInfoComplete();
    void updateMsgHint(QWidget* widget, QString hint, bool status);
protected:
    void paintEvent(QPaintEvent* event) override;

private:
    friend class Controller;

    QWidget* sideBar;
    QLabel* iconLabel;
    QPushButton* chatBtn;
    QPushButton* contactListBtn;

    QWidget* contactListWidget;
    QWidget* searchWidget;
    QLineEdit* searchLineEdit;
    QPushButton* addFriendBtn;
    QListWidget* friendWidget;

    QWidget* chatWidget;


private slots:
    void reloadQss();
    

};

#endif 
