#ifndef RESETPASSWORDWINDOW_H
#define RESETPASSWORDWINDOW_H

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
class ResetPasswordWindow : public MoveableWidget
{
    Q_OBJECT

public:
    explicit ResetPasswordWindow(QWidget *parent = nullptr);
    void initUI();
    void initConnect();
    void updateMsgHint(QWidget* widget, QString hint, bool status);
    ///用于判断用户所填入的信息是否有误
    bool judgeInfo();
    bool judgeResetInfoComplete();
    ///判断当前所填入信息是否可以发送验证码
    bool judgeResetInfoCanSendCode();
    ///禁用当前控件下所有按钮
    void disableAllBtn(bool status);
    ~ResetPasswordWindow();


protected:
    void paintEvent(QPaintEvent* event);
    void contextMenuEvent(QContextMenuEvent* event) override;

private:
    friend class Controller;

    QMenu contextMenu;
    QAction* reloadQssAction;
    QLabel* titleLabel;
    QLabel* msgHintLabel;

    CustomWidgetLabel_LineEdit *resetUser;
    CustomWidgetLabel_LineEdit * resetEmail;

    QLabel* resetValidateCodeLabel;
    QLineEdit* resetValidateCodeEdit;
    CustomTimerBtn* getValidateCodeBtn;

    CustomWidgetLabel_LineEdit * resetPassword;
    QPushButton* resetPasswordVisible;

    QPushButton* confirmBtn;
    QPushButton* returnBtn;
private slots:
    void reloadQss();
    

};

#endif 
