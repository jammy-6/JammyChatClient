#ifndef  MOVEABLEWIDGET_H
#define MOVEABLEWIDGET_H
#include <qwidget.h>
#include <QMouseEvent>
#include <qpushbutton.h>
class MoveableWidget :public QWidget {
	Q_OBJECT
public:
    MoveableWidget(QWidget* parent = nullptr) :QWidget(parent){
       
    }
    ~MoveableWidget(){}
    QPoint cur_pos;
    bool pressStatus=false;
protected:
    void mousePressEvent(QMouseEvent* event)  {
        if (qobject_cast<QPushButton*>(childAt(event->pos())) != nullptr) {
            // 如果是按钮，拒绝事件传播
            event->ignore();
            return;
        }
        pressStatus = true;
        cur_pos = event->globalPos() - pos();
    }
    void mouseMoveEvent(QMouseEvent* event) {
        if (pressStatus)
            move(event->globalPos() - cur_pos);
    }
    void mouseReleaseEvent(QMouseEvent* event) {
        if (pressStatus) {
            pressStatus = false;
            cur_pos = event->globalPos() - pos();
        }

    }



};
#endif // ! MOVEABLEWIDGET_H
