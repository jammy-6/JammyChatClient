#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

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
#include <QLineEdit>
#include "CustomerWidget.h"


const QString errorMailFormat = "” œ‰∏Ò Ω¥ÌŒÛ£°";

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    void initUI();
    void initConnect();
    void updateMsgHint(QWidget* widget, QString hint, bool status);
    ~RegisterWindow();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    

protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    QPoint cur_pos;
    QMenu contextMenu;
    QAction* reloadQssAction;
    QLabel* titleLabel;
    QLabel* msgHintLabel;

    CustomWidgetLabel_LineEdit *registerUser;
    CustomWidgetLabel_LineEdit *registerEmail;
    CustomWidgetLabel_LineEdit *registerPassword;
    CustomWidgetLabel_LineEdit *registerConfirmPassword;
    //QLabel* registerUserLabel;
    //QLineEdit* registerUserEdit;
    //QLabel* registerEmailLabel;
    //QLineEdit* registerEmailEdit;
    //QLabel* registerPasswordLabel;
    //QLineEdit* registerPasswordEdit;
    //QLabel* registerConfirmPasswordLabel;
    //QLineEdit* registerConfirmPasswordEdit;
    QLabel* registerValidateCodeLabel;
    QLineEdit* registerValidateCodeEdit;
    QPushButton* getValidateCodeBtn;

    QPushButton* confirmBtn;
    QPushButton* cancelBtn;
private slots:
    void reloadQss();
    

};

#endif 
