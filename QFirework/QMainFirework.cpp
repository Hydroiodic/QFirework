#include "QMainFirework.h"

QMainFirework::QMainFirework(QObject* parent) 
	: QGravity(parent, HI::state()) {
	/* there's nothing to do here */
}

QMainFirework::~QMainFirework() {
	/* there's nothing to do here */
}

void QMainFirework::initializeState() {
	QMainWindow* parent_window = (QMainWindow*)parent();

	st.vx = 0;
	st.vy = -(rand() % 10 + 10);
	st.x = rand() % parent_window->width();
	st.y = parent_window->height();

	st.left_time = (rand() % 2 ? -1 : 1) * rand() % 2 + 10;
}

void QMainFirework::proceed(QList<HI::QGravity*>& list) {
	HI::QGravity::proceed(list);

	// here explode
	if (st.left_time <= 0) {
		explode();
	}
}

void QMainFirework::explode() {
	// TODO
}


