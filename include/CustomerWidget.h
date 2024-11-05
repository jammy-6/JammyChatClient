#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

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
class CustomWidgetLabel_LineEdit : public QWidget {
    Q_OBJECT
public:
    CustomWidgetLabel_LineEdit(QWidget*parent = nullptr):QWidget(parent) {
        mainLayout = new QHBoxLayout;
        mainLayout->setSpacing(4);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel;
        label->setFixedHeight(30);
        lineEdit = new QLineEdit;
        lineEdit->setFixedHeight(30);
        mainLayout->addWidget(label);
        mainLayout->addWidget(lineEdit);
        this->setLayout(mainLayout);
    }
    QHBoxLayout* mainLayout;
    QLabel *label;
    QLineEdit *lineEdit;
};


#endif 
