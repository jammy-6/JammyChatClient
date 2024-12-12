#pragma execution_character_set("utf-8")
#include "CustomTimerBtn.h"

CustomTimerBtn::CustomTimerBtn(QWidget* parent) {
	timer_ = new QTimer(this);
	connect(timer_, &QTimer::timeout, this, &CustomTimerBtn::slotTimeout);
}
CustomTimerBtn::~CustomTimerBtn() {
	timer_->stop();
}
void CustomTimerBtn::slotTimeout() {
	if (countdown_ <= 0) {
		countdown_ = 10;
		this->setEnabled(true);
		this->setText(QString("获取"));
		countingStatus_ = false;
		timer_->stop();
		return;
	}
	countdown_--;
	this->setText(QString::number(countdown_));
	timer_->start();
	
}

void CustomTimerBtn::mouseReleaseEvent(QMouseEvent* e) {
	if (e->button() == Qt::LeftButton) {
		this->setText(QString::number(countdown_));
		timer_->start(1000);
		countingStatus_ = true;
		this->setEnabled(false);
		emit clicked();
	}
	QPushButton::mouseReleaseEvent(e);
}