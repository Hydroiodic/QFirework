#include "QObjectTimer.h"

QObjectTimer::QObjectTimer(QObject* parent, int milliseconds) 
	: QTimer(parent) {
	this->connect(this, &QTimer::timeout, this, &QObjectTimer::deleteMe);
	this->start(milliseconds);
}

QObjectTimer::~QObjectTimer() {
	/* there's nothing to do here */
}

void QObjectTimer::deleteMe() {
	this->disconnect();
	this->stop();
	delete this;
}
