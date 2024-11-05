#ifndef  CUSTOMTIMERBTN_H
#define CUSTOMTIMERBTN_H
#include <qpushbutton.h>
#include <qtimer.h>
#include <QMouseEvent>
class CustomTimerBtn : public QPushButton {
	Q_OBJECT

public:
	CustomTimerBtn(QWidget* parent = nullptr);
	~CustomTimerBtn();

	void mouseReleaseEvent(QMouseEvent* e) override;
private slots:
	void slotTimeout();
private:
	QTimer* timer_;
	int countdown_ = 10;
};

#endif // ! CUSTOMTIMERBTN_H
