
#pragma execution_character_set("utf-8")
#include "RegisterSuccessHintWindow.h"
#include <Config.h>
#include <QSpacerItem>
#include <QStyleOption>
#include "Global.h"

RegisterSuccessHintWindow::RegisterSuccessHintWindow(QWidget* parent) :
    MoveableWidget(parent)
{
    initUI();
    initConnect();
}

void RegisterSuccessHintWindow::initConnect() {
    timer_ = new QTimer(this);
    timer_->setInterval(5000);
    connect(timer_, &QTimer::timeout, [this]() {
        timer_->stop();
        emit signalReturnLoginWindow();
        });
}
void RegisterSuccessHintWindow::initUI() {
    this->setObjectName("registerSuccessHintWindow");
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    //�����ޱ߿�
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->setFixedWidth(300);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->setContentsMargins(8, 16, 8, 16);
    ///����
    titleLabel = new QLabel;
    titleLabel->setObjectName("titleLabel");
    titleLabel->setText(QString("Jammyͨ�ſͻ���"));
    mainLayout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    QSpacerItem* titleSpacer = new QSpacerItem(284, 30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(titleSpacer);

    hintLabel = new QLabel;
    hintLabel->setObjectName("hintLabel");
    hintLabel->setText(registerSuccessHintWindow);
    hintLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(hintLabel, 0, Qt::AlignHCenter);
    QSpacerItem* hintSpacer = new QSpacerItem(284, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    mainLayout->addItem(hintSpacer);

    ///���ص�¼
    returnBtn = new QPushButton;
    returnBtn->setObjectName(QString("returnBtn"));
    returnBtn->setText(QString("���ص�¼"));
    returnBtn->setFixedSize(returnBtn->sizeHint().width(), 30);
    mainLayout->addWidget(returnBtn, 0, Qt::AlignHCenter);
    connect(returnBtn, &QPushButton::clicked, [this]() {
        timer_->stop();
        emit signalReturnLoginWindow();
     });


}
void RegisterSuccessHintWindow::paintEvent(QPaintEvent* event) {
    QStyleOption opt;
    opt.init(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
void RegisterSuccessHintWindow::showEvent(QShowEvent* event) {
    QWidget::showEvent(event);
    timer_->start();
}
void RegisterSuccessHintWindow::hideEvent(QHideEvent* event) {
    QWidget::hideEvent(event);
    timer_->stop();
}

RegisterSuccessHintWindow::~RegisterSuccessHintWindow()
{

}
