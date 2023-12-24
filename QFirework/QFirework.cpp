#include "QFirework.h"

QFirework::QFirework(QWidget* parent) : QMainWindow(parent) {
	ui.setupUi(this);

	// random seed
	srand(time(NULL));

	// create timer here
	timer = new QTimer;
	connect(timer, &QTimer::timeout, this, &QFirework::proceed);
	timer->start(10);

	// create painter
	painter = new QPainter;
}

QFirework::~QFirework() {
	// delete timer
	if (timer) delete timer;

	// delete painter
	if (painter) delete painter;
}

void QFirework::paintEvent(QPaintEvent* event) {
	// begin painting
	painter->begin(this);

	// paint each pixmap on the main window
	double opa = 1.;
	for (QQueue<QPixmap>::iterator it = map_queue.end();
		it-- != map_queue.begin(); opa -= 0.2) {
		painter->setOpacity(opa);
		painter->drawPixmap(0, 0, *it);
	}

	// end painting
	painter->end();
}

void QFirework::keyPressEvent(QKeyEvent* event) {
	switch (event->key()) {
	case Qt::Key_Up:
		if (add_firework_cycle > 5) {
			--add_firework_cycle;
		}
		break;

	case Qt::Key_Down:
		if (add_firework_cycle < 50) {
			++add_firework_cycle;
		}
		break;

	default:
		QMainWindow::keyPressEvent(event);
	}
}

void QFirework::cleanList() {
	// iterate all of the list and clean those with a left_time less than 0
	for (int i = 0; i < list.size(); ++i) {
		HI::state st = list[i]->getState();
		if (st.left_time <= 0) {
			list.removeAt(i--);
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
	static size_t count = 50;
	if (++count >= add_firework_cycle) {
		firework = new QMainFirework(this);
		list.push_back(firework);
		count = 0;
	}

	// clean objects
	cleanList();

	// update map_queue
	requestMap();
}

void QFirework::requestMap() {
	map_queue.push_back(map_painter.paintMap(list, width(), height()));

	if (map_queue.size() > MAX_MAPS) {
		map_queue.pop_front();
	}

	update();
}
