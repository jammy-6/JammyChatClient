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

protected:
    void paintEvent(QPaintEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    friend class Controller;
    QMenu contextMenu;
    QAction* reloadQssAction;
    QLabel* titleLabel;
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
