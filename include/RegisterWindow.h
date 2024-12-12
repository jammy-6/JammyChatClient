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
#include "Global.h"
#include "CustomTimerBtn.h"
#include "MoveableWidget.h"
class Controller;
class RegisterWindow : public MoveableWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    void initUI();
    void initConnect();
    void updateMsgHint(QWidget* widget, QString hint, bool status);
    ///用于判断用户所填入的信息是否有误
    bool judgeInfo();
    bool judgeRegistInfoComplete();

    ~RegisterWindow();


protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    friend class Controller;

    QMenu contextMenu;
    QAction* reloadQssAction;
    QLabel* titleLabel;
    QLabel* msgHintLabel;

    CustomWidgetLabel_LineEdit *registerUser;
    CustomWidgetLabel_LineEdit *registerEmail;
    CustomWidgetLabel_LineEdit *registerPassword;
    QPushButton* registerPasswordVisible;
    CustomWidgetLabel_LineEdit *registerConfirmPassword;
    QPushButton* registerConfirmPasswordVisible;
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
    CustomTimerBtn* getValidateCodeBtn;

    QPushButton* confirmBtn;
    QPushButton* cancelBtn;
private slots:
    void reloadQss();
    

};

#endif 
