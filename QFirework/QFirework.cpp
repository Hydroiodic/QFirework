#include "QFirework.h"

QFirework::QFirework(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	// create timer here
	timer = new QTimer;
	connect(timer, &QTimer::timeout, this, &QFirework::proceed);
	timer->start(20);
}

QFirework::~QFirework() {
	// delete timer
	if (timer) delete timer;
}

void QFirework::paintEvent(QPaintEvent* event) {
	foreach(const QPixmap & map, map_queue) {
		// TODO
	}
}

void QFirework::cleanList() {
	QList<HI::QGravity*>::iterator it = list.begin();

	// iterate all of the list and clean those with a left_time less than 0
	while (it != list.end()) {
		HI::state st = (*it)->getState();
		if (st.left_time <= 0) {
			delete* it;
			list.erase(it++);
		}
	}
}

void QFirework::proceed() {
	HI::QGravity* firework = nullptr;

	// proceed all objects
	foreach(firework, list) {
		firework->proceed(this->list);
	}

	// create new object
	firework = new QMainFirework(this);
	list.push_back(firework);

	// clean objects
	cleanList();

	// update map_queue
	requestMap();
}

void QFirework::requestMap() {
	map_queue.push_back(map_painter.paintMap(list));

	if (map_queue.size() > MAX_MAPS) {
		map_queue.pop_front();
	}

	update();
}
