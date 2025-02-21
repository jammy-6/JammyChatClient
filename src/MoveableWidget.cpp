#include "MoveableWidget.h"
#include <qpushbutton.h>
MoveableWidget::MoveableWidget(QWidget *parent = nullptr) : QWidget(parent) {
}
MoveableWidget::~MoveableWidget() {}

void MoveableWidget::mousePressEvent(QMouseEvent *event) {
	if (qobject_cast<QPushButton *>(childAt(event->pos())) != nullptr) {
		// 如果是按钮，拒绝事件传播
		event->ignore();
		return;
	}
	pressStatus = true;
	cur_pos = event->globalPos() - pos();
}
void MoveableWidget::mouseMoveEvent(QMouseEvent *event) {
	if (pressStatus)
		move(event->globalPos() - cur_pos);
}
void MoveableWidget::mouseReleaseEvent(QMouseEvent *event) {
	if (pressStatus) {
		pressStatus = false;
		cur_pos = event->globalPos() - pos();
	}
}