#pragma once

#include <QObject>
#include <QTimer>

class QObjectTimer : public QTimer
{
	Q_OBJECT

public:
	QObjectTimer(QObject* parent = nullptr, int milliseconds = 1000);
	~QObjectTimer();

private slots:
	void deleteMe();
};
