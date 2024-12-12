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
	bool getCountingStatus() { return this->countingStatus_; }
	void mouseReleaseEvent(QMouseEvent* e) override;
private slots:
	void slotTimeout();
private:
	QTimer* timer_;
	bool countingStatus_ = false; /// true代表正处于倒计时
	int countdown_ = 10;
};

#endif // ! CUSTOMTIMERBTN_H
