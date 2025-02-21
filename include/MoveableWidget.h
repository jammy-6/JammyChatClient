#ifndef MOVEABLEWIDGET_H
#define MOVEABLEWIDGET_H
#include "ChatWindowGlobal.h"
#include <QMouseEvent>
#include <qwidget.h>

class CHAT_WINDOW_EXPORT MoveableWidget : public QWidget {
	Q_OBJECT
public:
	MoveableWidget(QWidget *parent);
	~MoveableWidget();
	QPoint cur_pos;
	bool pressStatus = false;

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};
#endif // ! MOVEABLEWIDGET_H
